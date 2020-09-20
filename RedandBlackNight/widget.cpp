#include "widget.h"
#include "ui_widget.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QRadioButton>
#include <QVector>
#include <QKeyEvent>
#include "dialog.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1000,800);
    setWindowTitle("红黑夜法官");
    connect(ui->toolButton_present,&QToolButton::clicked,this,[=](){//发言触发
        ui->textEdit_show->setVisible(true);
        for(int i=1;i<get_num()+1;i++)
        {
            QString str;
            if(player[i].is_identity())
            {
                str="红牌";
            }
            else
            {
                str="黑牌";
            }
            QInputDialog dia1(this);
            dia1.setWindowTitle("发言");
            dia1.setLabelText("请玩家"+QString::number(i)+"发言,你的身份是"+str);
            dia1.setInputMode(QInputDialog::TextInput);
            dia1.exec();
            ui->textEdit_show->insertPlainText(dia1.textValue());
            ui->textEdit_show->insertPlainText("\n");
        }
        ui->toolButton_present->setVisible(false);
    });

    connect(ui->toolButton_present2,&QToolButton::clicked,this,[=](){//发言2触发
        ui->textEdit_show->setVisible(true);
        for(int i=flag1;i<get_num()+1;i++)//从村长到最后一个依次发言
        {
            QString str;
            if(player[i].is_identity())
            {
                str="红牌";
                red_sum++;
            }
            else
            {
                str="黑牌";
                black_sum++;
            }
            if(is_live(i))
            {
                QInputDialog dia1(this);
                dia1.setWindowTitle("发言");
                dia1.setLabelText("请玩家"+QString::number(i)+"发言,你的身份是"+str);
                dia1.setInputMode(QInputDialog::TextInput);
                dia1.exec();
                ui->textEdit_show->insertPlainText(dia1.textValue());
                ui->textEdit_show->insertPlainText("\n");
            }
        }
        for(int i=1;i<flag1;i++)//从第一个到村长依次发言
        {
            QString str;
            if(player[i].is_identity())
            {
                str="红牌";
                red_sum++;
            }
            else
            {
                str="黑牌";
                black_sum++;
            }
            if(is_live(i))
            {
                QInputDialog dia1(this);
                dia1.setWindowTitle("发言");
                dia1.setLabelText("请玩家"+QString::number(i)+"发言,你的身份是"+str);
                dia1.setInputMode(QInputDialog::TextInput);
                dia1.exec();
                ui->textEdit_show->insertPlainText(dia1.textValue());
                ui->textEdit_show->insertPlainText("\n");
            }
        }
    });

      Dialog *A = new Dialog(this);
    connect(ui->toolButton_presentover,&QToolButton::clicked,this,[=](){//发言结束触发
        for(int i=1;i<get_num()+1;i++)
        {
            A->init(get_num(),player[i].get_ticket());
            A->exec();
        }
        for(int i=1;i<get_num()+1;i++)
        {
            player[i].ticket_sum=A->a[i];
        }
        for(int i=1;i<get_num()+1;i++)
        {
            A->a[i]=0;
        }
        select_village_head(get_num());
        ui->toolButton_presentover->setVisible(false);
        ui->toolButton_present2->setVisible(true);
    });

    connect(ui->toolButton_presentover2,&QToolButton::clicked,this,[=](){//发言2结束触发
        for(int i=0;i<get_num();i++)
        {
            A->init(get_num(),player[i].get_ticket());
            A->exec();
        }
        for(int i=0;i<get_num();i++)
        {
            player[i].ticket_sum=A->a[i];
        }
        for(int i=0;i<get_num();i++)
        {
            A->a[i]=0;
        }
    });

    connect(ui->toolButton_voteover,&QToolButton::clicked,this,[=](){//投票结束触发
        expel(get_num());
        gameover(red_sum,black_sum);
    });

    connect(ui->toolButton_night,&QToolButton::clicked,this,[=](){//选择夜晚触发
        select_scene_status();
    });

    init();//调用初始化函数

    connect(ui->toolButton_start,&QToolButton::clicked,[=](){//开始游戏触发
        QInputDialog dia(this);
        dia.setWindowTitle("玩家人数");
        dia.setLabelText("请输入本次玩家人数");
        dia.setFixedSize(400,200);
        dia.setInputMode(QInputDialog::IntInput);
        bool ok=true;
        set_num(QInputDialog::getInt(this,"玩家人数","请输入本次玩家人数",0,0,20,0,&ok));
        dia.exec();
        for(int i=0;i<get_num();i++)//玩家初始化
        {
            player[i].init();
        }
        generateDiffRand(get_num());//得到玩家的身份
        ui->tableWidget_information->setVisible(true);
        ui->toolButton_start->setVisible(false);
        ui->toolButton_present->setVisible(true);
        ui->toolButton_presentover->setVisible(true);
        ui->toolButton_voteover->setVisible(true);
        ui->toolButton_night->setVisible(true);
        ui->toolButton_presentover2->setVisible(true);

        ui->tableWidget_information->setColumnCount(5);
        ui->tableWidget_information->setHorizontalHeaderLabels(QStringList()<<"玩家名称"<<"是否睁眼"<<"是否存活"<<"是否是村长"<<"拥有的票数");
        ui->tableWidget_information->setRowCount(get_num());
        QStringList namelist;
        for(int i=0;i<get_num();i++)
        {
            namelist<<"玩家"+QString::number(i+1);
        }
        for(int i=0;i<get_num();i++)
        {
            int col=0;
            ui->tableWidget_information->setItem(i,col++,new QTableWidgetItem(namelist[i]));
            ui->tableWidget_information->setItem(i,col++,new QTableWidgetItem("睁眼"));
            ui->tableWidget_information->setItem(i,col++,new QTableWidgetItem("存活"));
            ui->tableWidget_information->setItem(i,col++,new QTableWidgetItem("不是"));
            ui->tableWidget_information->setItem(i,col++,new QTableWidgetItem("1票"));
        }
    });

    connect(ui->toolButton_quit,&QToolButton::clicked,this,&Widget::close);//退出游戏触发
}

void Widget::init()//初始化
{
    ui->toolButton_present->setVisible(false);
    ui->toolButton_presentover->setVisible(false);
    ui->toolButton_voteover->setVisible(false);
    ui->tableWidget_information->setVisible(false);
    ui->textEdit_show->setVisible(false);
    ui->toolButton_present2->setVisible(false);
    ui->toolButton_night->setVisible(false);
    ui->toolButton_presentover2->setVisible(false);

    scene.init();//场景初始化
}

void Widget::set_num(const int &n)//设置玩家人数
{
    num=n;
}

bool Widget::is_live(const int &i)//得到是否存活
{
    return player[i].is_live();
}

bool Widget::is_eye(const int &i)//得到是否睁眼
{
    return player[i].is_eye();
}

void Widget::death(int n)//设置死亡
{
    player[n].set_death();
}

void Widget::eye(int n)//设置闭眼
{
    player[n].set_eyeclosed();
}

void Widget::select_village_head(int n)//选择村长
{
    int max;
    max=player[1].ticket_sum;
    for(int i=1;i<n+1;i++)
    {
        if(player[i].ticket_sum>=max)
        {
            max=player[i].ticket_sum;
        }
    }
    for(int i=1;i<n+1;i++)
    {
        if(player[i].ticket_sum==max)
        {
            flag1=i;

            QMessageBox::information(this,"村长","玩家"+QString::number(i)+"成为村长");
            ui->tableWidget_information->setItem(i-1,3,new QTableWidgetItem("是"));
            if(n%2==0)
            {
                player[i].set_ticket(1.5);
                ui->tableWidget_information->setItem(i-1,4,new QTableWidgetItem("1.5票"));
            }
            else
            {
                player[i].set_ticket(0.5);
                ui->tableWidget_information->setItem(i-1,4,new QTableWidgetItem("0.5票"));
            }
            break;
        }
    }
}

void Widget::expel(int n)//驱逐
{
    int max,flag=0;
    max=player[0].ticket_sum;
    for(int i=1;i<n;i++)
    {
        if(player[i].ticket_sum>=max)
        {
            max=player[i].ticket_sum;
        }

    }
    for(int i=0;i<n;i++)
    {
        if(player[i].ticket_sum==max)
        {
            flag++;
        }
    }
    if(flag>1)
    {
        QMessageBox::information(this,"投票","出现平票，请玩家依次投票");
    }
    else
    {
        for(int i=1;i<n+1;i++)
        {
            if(player[i].ticket_sum==max)
            {
                QString str;
                if(player[i].is_identity())
                {
                    str="红牌";
                    red_sum++;
                }
                else
                {
                    str="黑牌";
                    black_sum++;
                }
                QMessageBox::information(this,"驱逐","玩家"+QString::number(i)+"被驱逐,他的身份是"+str);
                death(i);
                ui->tableWidget_information->setItem(i-1,2,new QTableWidgetItem("死亡"));
                ui->tableWidget_information->setItem(i-1,1,new QTableWidgetItem("闭眼"));
                if(i==flag1)
                {
                    Dialog *A1=new Dialog(this);
                    QMessageBox::information(this,"提示","村长被驱逐,请指定新的村长");
                    A1->select_new_village_head(get_num());
                    A1->exec();
                    for(int i=1;i<get_num()+1;i++)
                    {
                        if(A1->a[i]==1)
                        {
                            QMessageBox::information(this,"提示","玩家"+QString::number(i)+"被选为村长");
                            ui->tableWidget_information->setItem(i+1,3,new QTableWidgetItem("是"));
                            player[i].set_ticket(player[flag1].get_ticket());
                            flag1=i;
                        }
                    }
                }
                break;
            }
        }
    }
}

void Widget::choose_is_eyeopened(int n)//玩家选择是否闭眼
{
    for(int i=0;i<n;i++)
    {
        if(player[i].is_live())
        {
            if(QMessageBox::question(this,"选择睁眼","请玩家"+QString::number(i+1)+"选择是否睁眼")==QMessageBox::No)
            {
                ui->tableWidget_information->setItem(i,1,new QTableWidgetItem("闭眼"));
                player[i].set_eyeclosed();
                if(player[i].is_identity())
                {
                    eye_red_num++;
                }
                else
                {
                    eye_black_num++;
                }
            }
        }
    }
    if(scene.get_status()==1&&(get_num()-eye_red_num)%2==0)
    {
        player[flag1].set_ticket(1);
        ui->tableWidget_information->setItem(flag1-1,4,new QTableWidgetItem("1票"));
    }
    else if(scene.get_status()==2&&(get_num()-eye_black_num)%2==0)
    {
        player[flag1].set_ticket(1);
        ui->tableWidget_information->setItem(flag1-1,4,new QTableWidgetItem("1票"));
    }
}

void Widget::swap(int *a,int *b)//交换函数
{
    if(*a!=*b)
    {
        *a^=*b;
        *b^=*a;
        *a^=*b;
    }
 }

void Widget::generateDiffRand(int n)//得到玩家的身份
{
    int a[100];
    int i;
    time_t t;
    for(i=0;i<n+1;i++)
    {
        a[i]=i;
    }
    srand((int)time(&t));
    for(i=1;i<n+1;i++)
    {
        swap(&a[i],&a[i+rand()%(n+1-i)]);
    }
    for(int i=1;i<n+1;i++)
    {
        qDebug()<<a[i];
    }
    for(i=1;i<(n/2)+1;i++)
    {
        player[a[i]].set_red();
    }
    for(i=(n/2)+1;i<n+1;i++)
    {
        player[a[i]].set_black();
    }
}

void Widget::select_scene_status()//选择场景状态
{
    int a[100];
    int i;
    time_t t;
    for(i=0;i<3;i++)
    {
        a[i]=i;
    }
    srand((int)time(&t));
    for(i=1;i<3;i++)
    {
        swap(&a[i],&a[i+rand()%(3-i)]);
    }
    scene.set_status(a[1]);
    if(scene.get_status()==1)
    {
        QMessageBox::information(this,"提示","进入红夜");
        choose_is_eyeopened(get_num());
    }
    else if(scene.get_status()==2)
    {
        QMessageBox::information(this,"提示","进入黑夜");
        choose_is_eyeopened(get_num());
    }
}

void Widget::gameover(int m,int n)//游戏结束
{
    if(m==get_num()/2+1)
    {
        QMessageBox::information(this,"游戏结束","黑牌玩家获得胜利");
    }
    else if(n==get_num()/2)
    {
        QMessageBox::information(this,"游戏结束","红牌玩家获得胜利");
    }
}

Widget::~Widget()
{
    delete ui;
}
