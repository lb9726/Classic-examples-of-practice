#include "mainwindow.h"
#include <QApplication>
#include "respondcallback.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = MainWindow::GetInstance();
    RespondCallback * _rc = new RespondCallback;
    w->show();

    return a.exec();
}
