#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QStringList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void convertVideoFormat();
    void getVideoInfo(QString filename);
    qreal videoFileSize(QString videoPathName);
    QString getTotalTime(QString ttime);
    QString getFenBianLv(QString fenbianlv);
    qint64 getSeconds(QString ptime);
    QString getRevertString();
private:
    Ui::Widget *ui;
    QString m_vDuration;
    QString m_vFenBianLv;
    QString m_TimeString;
    QString m_FblString;
};

#endif // WIDGET_H
