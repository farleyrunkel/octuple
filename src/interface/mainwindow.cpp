#include "mainwindow.h"
#include "itestwidget.h"
#include "SARibbonMainWindow.h"
#include "SARibbonBar.h"
#include "SARibbonCategory.h"
#include "SARibbonPannel.h"
#include "SARibbonButtonGroupWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : SARibbonMainWindow(parent)
{
    resize(1280, 800);
    setupMainUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupMainUi()
{
    SARibbonBar *ribbon = this->ribbonBar();
    ribbon->setRibbonStyle(SARibbonBar::RibbonStyleCompactTwoRow);
    ribbon->applicationButton()->setText(("File"));
    SARibbonCategory *category = ribbon->addCategoryPage(tr("Category1"));
    SARibbonPannel *pannel = category->addPannel(tr("Pannel1"));
    QAction* actSave = new QAction(this);
    actSave->setText("save");
    actSave->setIcon(QIcon(":/icon/icon/save.svg"));
    actSave->setObjectName("actSave");
    actSave->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
    pannel->addLargeAction(actSave);

    setCentralWidget(new ITestWidget);
}
