//
//  LaserScene.cpp
//  EffectNodes
//
//  Created by Tyrion on 15/1/13.
//
//

#include "LaserScene.h"
#include "LaserLayer.h"

bool LaserScene::init(){
    if (CCScene::init()) {
        LaserLayer* layer = LaserLayer::create();
        addChild(layer);
        return true;
    }
    return false;
}