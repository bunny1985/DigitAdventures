/*
 * Demo1Scene.cpp
 *
 *  Created on: 1 paź 2014
 *      Author: Michal
 */

#include <Demos/Demo1Scene.h>

Demo1Scene::Demo1Scene()
{
    // TODO Auto-generated constructor stub

}

Demo1Scene::~Demo1Scene()
{
    // TODO Auto-generated destructor stub
}


CCScene* Demo1Scene::scene(){
	CCScene* scene = CCScene::create();
	scene->addChild(Demo1Scene::create());
	return scene;
}
bool Demo1Scene::init(){
	return true;
}
