#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_d_clicked();

    void on_pushButton_e_clicked();

    void on_pushButton_fe_clicked();

    void on_pushButton_fd_clicked();

    void on_toolButton_1_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_key_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
