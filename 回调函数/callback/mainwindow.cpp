#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

MainWindow *MainWindow::GetInstance(bool hold)
{
   static MainWindow* sInstance = nullptr;
   if (hold)
   {
       sInstance = sInstance ? sInstance : new MainWindow();
   }
   else if (sInstance)
   {
       delete sInstance;
       sInstance = nullptr;
   }
   return sInstance;
}

void MainWindow::RegisterCallback(IButtonPressedCallback *callback)
{
    // auto auto自动类型推断，用于从初始化表达式中推断出变量的数据类型。通过auto的自动类型推断，可以大大简化我们的编程工作。
    auto result = std::find(_callbacks.begin(), _callbacks.end(), callback);
    if (result == _callbacks.end())
        _callbacks.push_back(callback);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    GetInstance(false);
}

void MainWindow::on_pushButton_pressed()
{
    ui->pushButton->setText("hzp");
    for (auto it : _callbacks)
        it->onButtonPressed();
}
