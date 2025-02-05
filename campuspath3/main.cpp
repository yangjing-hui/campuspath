#include "mainwindow.h"
#include <QApplication>
#include<qicon.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowOpacity(1);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowTitle("河海大学校园最短距离导航系统");
    w.setWindowIcon(QIcon("C:/Users/Administrator/Desktop/icon.png"));
//   this->resize( QSize( 612.5, 432.5 ));
//    w.setMinimumSize ( 612.5*0.5, 432.5*0.5 );
    w.resize( QSize(1197 / 2 , 979 / 2 ));



//    setMaximumSize();

    w.show();

    return a.exec();
}
