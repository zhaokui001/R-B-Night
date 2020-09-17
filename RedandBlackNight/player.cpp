#include "player.h"


void Player::set_ticket(double tic)//设置玩家拥有的票数
{
    ticket=tic;
}

void Player::set_red()//设置为红牌身份
{
    identity=true;
}

void Player::set_black()//设置为黑牌身份
{
    identity=false;
}

void Player::set_live()//设置为存活
{
    live=true;
}

void Player::set_death()//设置为死亡
{
    live=false;
}

void Player::set_eyeopened()//设置为睁眼
{
    eye=true;
}

void Player::set_eyeclosed()//设置为闭眼
{
    eye=false;
}

void Player::init()//初始化函数
{
    live=true;
    eye=true;
    ticket_sum=0;
    set_ticket(1.0);
}
