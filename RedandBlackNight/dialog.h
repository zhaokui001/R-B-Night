#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <widget.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    double a[20]={0};
    void set_playernum(int n);//设置玩家数量
    int get_playernum(){return playernum;}//获取玩家数量
//    void set_ischecked(int n);//设置
//    int get_ischecked(){return ischecked;}//获取玩家是否被投票
    void select(int n,int m,double t);//进行投票行为
    void select_new_village_head(int n,int m);//选举村长的投票行为
    ~Dialog();

private:
    Ui::Dialog *ui;
    int playernum;
    int ischecked;
};




#endif // DIALOG_H
