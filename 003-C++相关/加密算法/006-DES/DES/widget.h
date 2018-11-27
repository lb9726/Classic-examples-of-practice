#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <vector>
#include <string>
#include "Array.h"
using std::vector;
using std::string;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void showCode();
    void decodeECB();
    void decodeCBC();
    void decodeCFB();
    void decodeOFB();
    void decodeCTR();
    void setKey();

    void clearECB();
    void clearCBC();
    void clearCFB();
    void clearOFB();
    void clearCTR();

private:
    Ui::Widget *ui;
    QString bit_to_QString(const vector<Array> &v);
    vector<Array> QString_to_bit(const QString &qs);
    string debugString;
};

#endif // WIDGET_H
