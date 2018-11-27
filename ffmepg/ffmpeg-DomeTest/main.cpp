#include "widget.h"
#include <QApplication>
#include <QDebug>

extern "C"
{
    #include "libavcodec/avcodec.h"
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

//    w.getVideoInfo("C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\libo.txt");
//    w.getVideoInfo("C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\libo1.txt");
    w.getVideoInfo("C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\libo.txt");
    qDebug()<<"will copy ended!";
    w.getTotalTime("");
    w.getFenBianLv("");
    w.getSeconds("");
    w.videoFileSize("C:\\Users\\yonghao\\Desktop\\ffmpeg-20170921-183fd30-win32-shared\\bin\\Test1.mp4");
    w.getRevertString();
    return a.exec();
}
