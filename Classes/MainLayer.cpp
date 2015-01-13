//
//  MainLayer.cpp
//  EffectNodes
//
//  Created by Tyrion on 15/1/12.
//
//

#include "MainLayer.h"
#include "LaserScene.h"
bool MainLayer::init(){
    if (CCLayer::init()) {
        
        m_demoNameList.push_back("LaserScene");
        m_demoNameList.push_back("LaserScene1");
        m_demoNameList.push_back("LaserScene2");
        m_demoNameList.push_back("LaserScene3");
        m_demoNameList.push_back("LaserScene4");
        m_demoNameList.push_back("LaserScene5");
        m_demoNameList.push_back("LaserScene6");
        m_demoNameList.push_back("LaserScene7");
        
        CCArray* buttonArray = CCArray::create();
        
        CCPoint startPoint = ccp(130, winSize.height*0.7);
        float buttonNum = 0;
        float heightOffset = 0;
        int demoNum = (int)m_demoNameList.size();
        for (int i=0; i<demoNum; i++) {
            const char* demoName = m_demoNameList[i].c_str();
//            CCLog("demoName %s", demoName);
            CCMenuItem* button = CCMenuItemSprite::create(CCScale9Sprite::create("button.png"), CCScale9Sprite::create("button_dn.png"), this, menu_selector(MainLayer::menuCallback));
            button->setScale(3.0);
            button->setPosition(ccpAdd(startPoint, ccp(button->boundingBox().size.width*1.2*buttonNum, heightOffset)));
            button->setTag(i);
            buttonArray->addObject(button);
            
            CCLabelTTF* buttonName = CCLabelTTF::create(demoName, FONT_NAME, 30);
            buttonName->setPosition(ccpAdd(button->getPosition(), ccp(0, 10)));
            addChild(buttonName, 10);
            
            buttonNum++;
            if (i == 3) {
                heightOffset -= 200;
                buttonNum = 0;
            }
            if (i == 7) {
                heightOffset -= 200;
                buttonNum = 0;
            }
        }
        
        CCMenu* menu = CCMenu::createWithArray(buttonArray);
        menu->setPosition(CCPointZero);
        addChild(menu, 0 ,tag_menu);
        return true;
    }
    return false;
}

void MainLayer::menuCallback(CCNode* pSender)
{
    int tag = pSender->getTag();
    string demoName = m_demoNameList[tag];
//    CCLog("demoName %s", demoName.c_str());
    if(demoName == "LaserScene"){
        LaserScene* laserScene = LaserScene::create();
        CCDirector::sharedDirector()->replaceScene(laserScene);
    }else if(demoName == "LaserScene1"){
        
    }
}