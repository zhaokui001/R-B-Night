#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <player.h>
#include <scene.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QtGui>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private:
    Player player[20];//玩家
    int num;

public:

    explicit Widget(QWidget *parent = 0);
    int red_sum=0,black_sum=0,flag1;
    int eye_red_num=0,eye_black_num=0;
    void set_num(const int &n);//设置玩家人数
    int get_num(){return num;}
    bool is_live(const int &i);//查看是否存活
    bool is_eye(const int &i);//查看是否睁眼
    void death(int n);//设置死亡
    void eye(int n);//设置闭眼
    void select_village_head(int n);//选择村长
    void expel(int n);//驱逐票最高者
    void choose_is_eyeopened(int n);//选择是否睁眼
    //void keyPressEvent(QKeyEvent *);
    void swap(int *a,int *b);//交换函数
    void generateDiffRand(int n);//随机数赋予玩家身份
    void select_scene_status();//选择场景状态
    void gameover(int m,int n);//游戏结束
    void init();//初始化

    ~Widget();

private:
    Ui::Widget *ui;
    Scene scene;
};

#endif // WIDGET_H
