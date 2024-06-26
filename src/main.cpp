#include "initializer.h"
#include "mainwindow.h"
#include <QApplication>
#include "itestwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Initializer initializer;
    initializer.initialize(&app);

    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();
}
