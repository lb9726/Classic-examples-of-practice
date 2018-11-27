#include "respondcallback.h"
#include "mainwindow.h"

RespondCallback::RespondCallback()
{
    MainWindow::GetInstance()->RegisterCallback(this);
}

RespondCallback::~RespondCallback()
{

}

void RespondCallback::onButtonPressed()
{
    qDebug("Hello,world");
}
