#include "mainwindow.h"
#include "itestwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 500);
    setupMainUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupMainUi()
{
    setCentralWidget(new ITestWidget);
}
