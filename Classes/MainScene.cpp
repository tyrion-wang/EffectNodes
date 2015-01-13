//
//  MainScene.cpp
//  EffectNodes
//
//  Created by Tyrion on 15/1/12.
//
//

#include "MainScene.h"
#include "MainLayer.h"

bool MainScene::init(){
    if (CCScene::init()) {
        MainLayer* mainLayer = MainLayer::create();
        addChild(mainLayer);
        return true;
    }
    return false;
}