#ifndef PALYER_H
#define PALYER_H


class Player//玩家类的建立
{
private:
    double ticket;//该玩家拥有的票数
    bool identity;//该玩家的身份
    bool live;//该玩家是否存活
    bool eye;//该玩家是否睁眼
public:
    Player(){//构造函数
        live=true;
        eye=true;
    };
    double ticket_sum;//该玩家得到的票数
    void set_ticket(double tic);//设置该玩家拥有的票数
    double get_ticket(){return ticket;}
    void set_red();//设置为红牌
    void set_black();//设置为黑牌
    void set_live();//设置为存活
    void set_death();//设置为死亡
    void set_eyeopened();//设置为睁眼
    void set_eyeclosed();//设置为闭眼
    bool is_identity(){return identity;}//获取玩家身份
    bool is_live(){return live;}//获取玩家是否存活
    bool is_eye(){return eye;}//获取玩家是否睁眼
    void init();//初始化函数

};

#endif // PALYER_H
