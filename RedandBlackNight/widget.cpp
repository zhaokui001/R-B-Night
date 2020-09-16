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

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1000,800);
    setWindowTitle("红黑夜法官");
    QVector<QRadioButton*> rad={ui->radioButton,ui->radioButton_2,ui->radioButton_3,ui->radioButton_4,ui->radioButton_5,ui->radioButton_6,
                                ui->radioButton_7,ui->radioButton_8,ui->radioButton_9,ui->radioButton_10,ui->radioButton_11,ui->radioButton_12,
                                ui->radioButton_13,ui->radioButton_14,ui->radioButton_15,ui->radioButton_16,ui->radioButton_17,ui->radioButton_18,
                               ui->radioButton_19,ui->radioButton_20};



    connect(ui->toolButton_present,&QToolButton::clicked,this,[=](){//发言触发
        ui->textEdit_show->setVisible(true);
        for(int i=0;i<get_num();i++)
        {
            QInputDialog dia1(this);
            dia1.setWindowTitle("发言");
            dia1.setLabelText("请玩家"+QString::number(i+1)+"发言");
            dia1.setInputMode(QInputDialog::TextInput);
            dia1.exec();
            ui->textEdit_show->insertPlainText(dia1.textValue());
            ui->textEdit_show->insertPlainText("\n");
        }

    });
    connect(ui->toolButton_presentover,&QToolButton::clicked,this,[=](){//发言结束触发
        for(int i=0;i<get_num();i++)
        {
            ui->groupBox->setTitle("请玩家"+QString::number(i+1)+"投票");
            ui->groupBox->setVisible(true);

        }
    });



    init();//调用初始化函数

    connect(ui->toolButton_start,&QToolButton::clicked,[=](){//开始游戏触发
        QInputDialog dia(this);
        dia.setWindowTitle("玩家人数");
        dia.setLabelText("请输入本次玩家人数");
        dia.setFixedSize(400,200);
        dia.setInputMode(QInputDialog::IntInput);
        bool ok=true;
        set_num(QInputDialog::getInt(this,"玩家人数","请输入本次玩家人数",0,0,100,0,&ok));
        dia.exec();
        ui->tableWidget_information->setVisible(true);
        ui->toolButton_start->setVisible(false);
        ui->toolButton_present->setVisible(true);
        ui->toolButton_presentover->setVisible(true);
        ui->toolButton_voteover->setVisible(true);
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
        for(int i=get_num();i<20;i++)
        {
            rad[i]->setVisible(false);
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
    ui->groupBox->setVisible(false);
    for(int i=1;i<get_num()+1;i++)//玩家初始化
    {
        player[i].init();
    }
    scene.init();//场景初始化
    generateDiffRand(get_num());//得到玩家的身份
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

//void Widget::keyPressEvent(QKeyEvent *event)
//{
//    int key=event->key();
//    if(key==Qt::Key_Return)
//    {
//            continue;
//    }
//}

void Widget::select_village_head(int n)//选择村长
{
    int max,flag=0;
    max=player[0].get_ticket_sum();
    for(int i=1;i<n;i++)
    {
        if(player[i].get_ticket_sum()>=max)
        {
            max=player[i].get_ticket_sum();
        }
    }
    for(int i=0;i<player[i].get_ticket_sum();i++)
    {
        flag++;
    }
    if(flag>1)
    {
        QMessageBox::information(this,"投票","出现平票，请玩家依次投票");
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            if(player[i].get_ticket_sum()==max)
            {
                QMessageBox::information(this,"村长","玩家"+QString::number(i+1)+"成为村长");
                ui->tableWidget_information->setItem(i,3,new QTableWidgetItem("是"));
                if(n/2==0)
                {
                    ui->tableWidget_information->setItem(i,4,new QTableWidgetItem("1.5票"));
                }
                else
                {
                    ui->tableWidget_information->setItem(i,4,new QTableWidgetItem("0.5票"));
                }
                break;
            }     
        }
    }
}

void Widget::expel(int n)//驱逐
{
    int max,flag=0;
    max=player[0].get_ticket_sum();
    for(int i=1;i<n;i++)
    {
        if(player[i].get_ticket_sum()>=max)
        {
            max=player[i].get_ticket_sum();
        }

    }
    for(int i=0;i<n;i++)
    {
        if(player[i].get_ticket_sum()==max)
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
        for(int i=0;i<n;i++)
        {
            if(player[i].get_ticket_sum()==max)
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
                QMessageBox::information(this,"驱逐","玩家"+QString::number(i+1)+"被驱逐,他的身份是"+str);
                death(i);
                ui->tableWidget_information->setItem(i,2,new QTableWidgetItem("死亡"));
                ui->tableWidget_information->setItem(i,1,new QTableWidgetItem("闭眼"));
                break;
            }
        }
    }
}

void Widget::choose_is_eyeopened(int n)//玩家选择是否闭眼
{
    for(int i=0;i<n;i++)
    {
        QMessageBox::question(this,"选择睁眼","请玩家"+QString::number(n+1)+"选择是否睁眼");
        if(QMessageBox::No==QMessageBox::question(this,"选择睁眼","请玩家"+QString::number(n+1)+"选择是否睁眼"))
        {
            ui->tableWidget_information->setItem(n,1,new QTableWidgetItem("闭眼"));
            player[n].set_eyeclosed();
        }
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
    for(i=1;i<n;i++)
    {
        swap(&a[i],&a[i+rand()%(n-i)]);
    }
    for(i=1;i<(n/2)+1;i++)
    {
        player[a[i]].set_red();
    }
    for(i=(n/2)+1;i<n;i++)
    {
        player[a[i]].set_black();
    }
}



Widget::~Widget()
{
    delete ui;
}
