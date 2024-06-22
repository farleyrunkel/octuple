#include "mainwindow.h"
#include "itestwidget.h"
#include "SARibbonMainWindow.h"
#include "SARibbonBar.h"
#include "SARibbonCategory.h"
#include "SARibbonPannel.h"
#include "SARibbonButtonGroupWidget.h"
#include <QCalendarWidget>

MainWindow::MainWindow(QWidget *parent)
    : SARibbonMainWindow(parent, false)
{
    resize(1280, 800);
    setupMainUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupMainUi()
{
    setupRibbonBar();

    auto t = new ITestWidget;
    setCentralWidget(t);

    auto a = new QCalendarWidget(t);
    a->setGeometry(20, 20, width(), 50);
    setLayout(new QVBoxLayout);
    layout()->addWidget(a);
    setStyleSheet("background:transparent;");
   // t->raise();
}

void MainWindow::setupRibbonBar()
{
    if (!isUseRibbon()) {
        return;
    }
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
}
