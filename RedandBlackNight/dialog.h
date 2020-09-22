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
    void set_playernum(int n);
    int get_playernum(){return playernum;}
    void set_ischecked(int n);
    int get_ischecked(){return ischecked;}
    void init(int n,int m,double t);
    void select_new_village_head(int n,int m);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int playernum;
    int ischecked;
};




#endif // DIALOG_H
