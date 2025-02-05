#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPushbutton>
#include <QStack>
#include <QPainter>
#include <QTime>
#include <QMessageBox>
#include <QString>

//这里定义关键点的最大数为319
#define VN 319
//这里定义边的最大数为421
#define EN 421
#define JN 63 //建筑物数量

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //原始图片大小，每个地图不一样，这里是河海大学的是1657 * 914
    double xx_yuan= 1197 /2 ;
    double yy_yuan= 979 /2 ;
    double xx= 1197/2 ;
    double yy= 979/2 ;


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent2(QMouseEvent *m);
    void DijkstraPath(int v0);
    void showPath(int ve,int v0);
    void paintEvent(QPaintEvent *event);
    void sleep(unsigned int msec);

private slots:
    void buttonClick();
//    void on_pushButton_clicked();
//    void deleteButton();
    void closehanshu();
    void changepathcolor();
    void shuoming();
    void aboutme();
    void changepathwidth();
    void addjianzhu();
    void jianzhuxinxi();
private:
    Ui::MainWindow *ui;
    QPushButton *btClose;
    QPoint last;

    QPushButton *buttons[VN];
    QPushButton *huitu_button[10000];

    int huitu_button_cnt=0;

    int size;
    int vn,en;
    int ve,v0;

    struct Vec{
        double x,y;
    };
    struct Edge{
        int s,e;
    };

    struct Graph{
        int n;
        int e;
        int matrix[VN][VN];
    }g;

    Vec v[VN],v_yuan[VN];
    Edge e[EN];
    int dist[VN];
    int path[VN];

    int hualujing[VN];

    int lujing;

    double ludian_x[VN];
    double ludian_y[VN];

    double buttons_x[VN];
    double buttons_y[VN];

    double buttons_x_yuan[VN];
    double buttons_y_yuan[VN];

    struct Jianzhu{
        double x,y,x2,y2;
        double sizex,sizey;
        QPushButton *button;
    }jianzhu[JN];

    int move_flag; //地图右键移动

    int edge_cnt;//边计数，临时
    int edge_s,edge_e;//临时
    int edge_flag;

    int jianzhu_cnt; //建筑计数，临时
//    int jianzhu_flag;

    int flag;//判断左右键

    int huizhi_cnt=1; //延时绘制计数

    QPushButton *close_button;

    QPushButton *pathcolor_button;
    QPushButton *addjianzhu_button;//添加建筑？
    QPushButton *shuoming_button;
    QPushButton *about_button;
    QPushButton *pathwidth_button;
    //颜色标记 1为红色
    int color_flag=1;

    int path_width=4;

    int newjianzhu_cnt=0;
    QPushButton *newjianzhu_button[20];
    QString newjianzhu_text[20];
    double newjianzhu_x[20];
    double newjianzhu_y[20];
    double newjianzhu_x2[20];
    double newjianzhu_y2[20];

    int jianzhu_flag=0;
    double gongneng_x[7];
    double gongneng_y[7];
    double gongneng_sizex=60;
    double gongneng_sizey=30;


};


#endif // MAINWINDOW_H
