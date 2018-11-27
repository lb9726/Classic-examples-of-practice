#include "widget.h"
#include "ui_widget.h"
#include <stdlib.h>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_vDuration = QString();
    m_vFenBianLv = QString();
//    system("start /b C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\ffmpeg -i C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\Test1.mp4 2>C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\libo.txt");
//    system("C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\ffmpeg -i C:\\Users\\yonghao\\Desktop\\视频\\新三国2010第36集.mp4 2>C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\libo1.txt");
//    system("start /b C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\ffmpeg -i C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\qiyi.mp4 2>C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\libo2.txt");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::convertVideoFormat()
{
    QString runpath = QCoreApplication::applicationDirPath();
    qDebug()<<"path = "<< runpath;
//    path.replace("\","\\");
    runpath.replace("/", "\\");
    qDebug()<<"path = "<< runpath;
    QString ffmpeg32 = runpath + "\\" + "ffmpeg32\\bin\\ffmpeg.exe";
    QString srcVideopath = "C:\\Users\\yonghao\\Desktop\\视频\\Test1.mp4";
    QString fenbianlv = m_FblString;
    QString zhenlv = "";
    QString desVideopath = "C:\\Users\\yonghao\\Desktop\\视频\\Test1.avi";
    QString cmd = ffmpeg32 + " -i " + srcVideopath  + " -s " + " -b:v " + desVideopath;
//    int ab = system("C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\ffmpeg.exe -i C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\Test1.mp4 -s 1280x544 -b:v 2386k t1.avi");
    int ab = system(cmd.toLatin1().data());
    qDebug()<<"ab = "<<ab;
//    system("pause");
    // incomplete universal character name \U  需要两个\\才行
}

void Widget::getVideoInfo(QString filename)
{
    QFile videoInfo(filename);

    bool findDuration = false;
    bool findFenBianLv = false;
    int i = 0;
    qDebug()<<"filesiez = "<< videoInfo.size();
    while(videoInfo.size() <= 0)
    {
        qDebug()<<"file size is 0";
    }
    if (!videoInfo.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"open file error!";
        return ;
    }
    QTextStream in (&videoInfo);
    QString line = in.readLine();
    qDebug()<<"first line = "<< line;
    qDebug()<<"filename = "<<filename;
    qDebug()<<"!in.atEnd()="<<!in.atEnd()<<"findDur = "<<findDuration <<"findfen ="<< findFenBianLv;

    while (!in.atEnd()) {
        if (line.contains("Duration"))
        {
            m_vDuration = line;
            findDuration = true;
            qDebug()<<"m_vDuration = "<< m_vDuration;
        }
        else if (line.contains("Video"))
        {
            m_vFenBianLv = line;
            findFenBianLv = true;
            qDebug()<<"m_vFenBianLv = "<< m_vFenBianLv;
        }
        qDebug()<<"i = "<< i++;
        qDebug()<<"line abc  = "<<line;
        if (findDuration && findFenBianLv)
            break;
        line = in.readLine();
    }
    qDebug()<<"!in.atEnd()="<<!in.atEnd()<<" findDur = "<<findDuration <<" findfen ="<< findFenBianLv;
    qDebug()<<"endededede !";
    videoInfo.close();
    return;
}

qreal Widget::videoFileSize(QString videoPathName)
{
    QFile videoF(videoPathName);
    qreal a;
    qint64 fsize = videoF.size();
    a = fsize *1.0 / 1024 / 1024;

    qDebug()<< "filesize is = "<< fsize << "M";
    qDebug()<< "filesize is = "<< a << "M";
    return a;
}

QString Widget::getTotalTime(QString ttime)
{
    // Duration: 00:02:27.28, start: 0.000000, bitrate: 2443 kb/s 取出时间的字符串
    QStringList str = m_vDuration.split(","); //用','分离出单个字符串
    qDebug()<<str;
    for(int i = 0; i < str.length(); i++)
    {
        qDebug()<<"str i ="<<i<< " "<< str.at(i);
    }
    QStringList str2 = str.at(0).split(" ");
    qDebug()<<str2;
    for(int j = 0; j < str2.length(); j++)
    {
        qDebug()<<"str2 j ="<<j<< " "<< str2.at(j);
    }
    qDebug()<<str2.at(str2.length()-1);
    m_TimeString = str2.at(str2.length()-1);
    return str2.at(str2.length()-1);
}

QString Widget::getFenBianLv(QString fenbianlv)
{
    // Stream #0:0(und): Video: h264 (Constrained Baseline) (avc1 / 0x31637661), yuv420p(tv, bt709), 640x352, 392 kb/s, 15 fps, 15 tbr, 15k tbn, 30 tbc (default)
    QStringList str = m_vFenBianLv.split(",");
    QString fbl;
    qDebug()<<str;
    for(int i = 0; i < str.length(); i++)
    {
        QString temp = str.at(i);
        qDebug()<<"str i ="<<i<< " "<< temp;
        if (temp.contains("x"))
        {
            qDebug()<<"maybe yes temp = "<< temp;
            if (temp.contains(" ")) // 包含空格
            {
                QStringList blank = temp.split(" ");// 使用空格分割出字符串
                for(int k = 0; k < blank.length(); k++)
                {
                    QString blankstr = blank.at(k);
                    if (blankstr.contains("x")) // 包含x
                    {
                        QStringList s = blankstr.split("x");
                        qDebug()<<"sss="<< s;
                        for(int j = 0; j < s.length(); j++)
                        {
                            QString vWidth = s.at(0);
                            QString vHeight = s.at(1);
                            bool vWidFlag = false;
                            bool vHeiFlag = false;
                            vWidth.toInt(&vWidFlag, 10); // 转换为int数值，看能否成功
                            vHeight.toInt(&vHeiFlag, 10);// 转换为int数值，看能否成功
                            if (vWidFlag && vHeiFlag)// 转换成功，则表明是分辨率的字符串
                            {
                                 fbl = blankstr;
                            }
                        }
                    }
                }
            }
        }
    }
    qDebug()<<"fbl = "<< fbl;
    m_FblString = fbl;
    return fbl;
}

qint64 Widget::getSeconds(QString ptime)
{
    int second[3] = {0};
    if (!m_TimeString.contains(":")) // 时间格式有误
    {
        qDebug("time format is wrong!");
        return -1;
    }
    QString temp;
    QStringList tstr = m_TimeString.split(":");
    for (int i = 0; i < tstr.length(); i++)
    {
        temp = tstr.at(i);
        if (i == tstr.length() - 1)
        {
            if (temp.contains("."))
            {
                temp = temp.split(".").at(0);
            }
        }
        second[i] = temp.toInt();
        qDebug()<<"temp.toInt() = "<< temp.toInt() << "second = "<< second[i];
    }
    qint64 totalsecond = 0;
    int tmp = 1;
    int tmp1 = 0;
    for(int j = 2; j >= 0; j--)
    {
        tmp1 = second[j] * tmp;
        tmp  = tmp * 60;
        totalsecond += tmp1;
    }
    qDebug()<< "totalseond = "<< totalsecond;
    return totalsecond;
}

QString Widget::getRevertString()
{
    // 组成一个命令行字符串，在命令行中执行命令
//    int ab = system("C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\ffmpeg.exe -i C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\Test1.mp4 -s 1280x544 -b:v 2386k t1.avi");
    QString runpath = QCoreApplication::applicationDirPath();
    qDebug()<<"path = "<< runpath;
    runpath.replace("/", "\\");
    qDebug()<<"path = "<< runpath;
    QString ffmpeg32 = runpath + "\\" + "ffmpeg32\\bin\\ffmpeg.exe";
    QString srcVideopath = "C:\\Users\\yonghao\\Desktop\\Test1.mp4";
    QString desVideopath = "C:\\Users\\yonghao\\Desktop\\libo.avi";
//    QString fenbianlv = m_FblString;
    qreal temp = videoFileSize(srcVideopath) * 8 * 1024 / getSeconds(m_TimeString);
    qDebug()<<"temp system string = "<< temp<< (int)temp;
    qint64 zl = (int)temp;
    QString zhenlv = QString::number(zl, 10) + "k";
    qDebug()<<"zhenlv = "<< zhenlv;
    QString cmd = ffmpeg32 + " -i " + srcVideopath  + " -s " + m_FblString + " -b:v " +  zhenlv +" " + desVideopath;
    qDebug()<< "cmd = "<< cmd;
    qDebug()<< "cmd.toLatin1().data() = "<< cmd.toLatin1().data();
    int ret = system(cmd.toLatin1().data());
    qDebug()<< "ret = "<< ret;
    return "";
}
