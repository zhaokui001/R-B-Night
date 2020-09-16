#ifndef SCENE_H
#define SCENE_H


class Scene//场景类的建立
{
private:
    int status;//场景的状态，0表示白天，1表示红夜，2表示黑夜
public:
    Scene();
    void set_status(const int &sta);//设置场景的状态

    int get_status(){return status;}//获取场景的状态

    void init();//初始化
};

#endif // SCENE_H
