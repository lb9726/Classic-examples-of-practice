#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "respondcallback.h"

class IButtonPressedCallback;
class RespondCallback;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* GetInstance(bool hold = true);
    void RegisterCallback(IButtonPressedCallback* callback);

private:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
   MainWindow(const MainWindow&) = delete;
//   MainWindow() = delete;
private slots:
    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
    std::vector <IButtonPressedCallback*> _callbacks;
};

#endif // MAINWINDOW_H
