#include "dialog.h"
#include "ui_dialog.h"
#include <QVector>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

void Dialog::set_playernum(int n)//设置玩家数量
{
    playernum=n;
}

void Dialog::init(int n,double t)
{
    static int trigger = 1;
    QVector<QRadioButton*> rad={ui->radioButton,ui->radioButton_2,ui->radioButton_3,ui->radioButton_4,ui->radioButton_5,ui->radioButton_6,
                                ui->radioButton_7,ui->radioButton_8,ui->radioButton_9,ui->radioButton_10,ui->radioButton_11,ui->radioButton_12,
                                ui->radioButton_13,ui->radioButton_14,ui->radioButton_15,ui->radioButton_16,ui->radioButton_17,ui->radioButton_18,
                               ui->radioButton_19,ui->radioButton_20};
    for(int i=n;i<20;i++)
    {
        rad[i]->setVisible(false);
    }


    if(trigger)
    {
        connect(ui->toolButton,&QToolButton::clicked,this,[=](){
            for(int i=0;i<n;i++)
            {
                if(rad[i]->isChecked())
                {
                    a[i]+=t;
                }
            }
            for(int i=0;i<n;i++)
            {
                if(rad[i]->isChecked())
                {
                    rad[i]->setChecked(false);
                }
            }
            close();
        });
        trigger = 0;
    }

}

void Dialog::select_new_village_head(int n)
{
    static int trigger = 1;
    QVector<QRadioButton*> rad={ui->radioButton,ui->radioButton_2,ui->radioButton_3,ui->radioButton_4,ui->radioButton_5,ui->radioButton_6,
                                ui->radioButton_7,ui->radioButton_8,ui->radioButton_9,ui->radioButton_10,ui->radioButton_11,ui->radioButton_12,
                                ui->radioButton_13,ui->radioButton_14,ui->radioButton_15,ui->radioButton_16,ui->radioButton_17,ui->radioButton_18,
                               ui->radioButton_19,ui->radioButton_20};
    for(int i=n;i<20;i++)
    {
        rad[i]->setVisible(false);
    }


    if(trigger)
    {
        connect(ui->toolButton,&QToolButton::clicked,this,[=](){
            for(int i=0;i<n;i++)
            {
                if(rad[i]->isChecked())
                {
                    a[i]=1;
                }
            }
            for(int i=0;i<n;i++)
            {
                if(rad[i]->isChecked())
                {
                    rad[i]->setChecked(false);
                }
            }
            close();
        });
        trigger = 0;
    }
}

Dialog::~Dialog()
{
    delete ui;
}
