#include "scene.h"

Scene::Scene()
{

}
void Scene::set_status(const int &sta)//设置场景的状态
{
    status=sta;
}

void Scene::init()//初始化
{
    set_status(0);
}
