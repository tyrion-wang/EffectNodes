//
//  LaserLayer.cpp
//  EffectNodes
//
//  Created by Tyrion on 15/1/12.
//
//

#include "LaserLayer.h"
#include "MainScene.h"

bool LaserLayer::init()
{
    if (CCLayer::init())
    {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
        
        setTouchEnabled( true );
        
        //start update
        this->scheduleUpdate();
        
        CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);

        m_laser=new Laser();
        m_laser->autorelease();
        m_laser->init();
        this->addChild(m_laser);
        m_laser->setLaserStart(ccp(100,100));
        m_laser->setLaserEnd(ccp(winSize.width*0.5, winSize.height*0.5));
        
        //back button
        {
            CCScale9Sprite* btnUp=CCScale9Sprite::create("button.png");
            CCScale9Sprite* btnDn=CCScale9Sprite::create("button_dn.png");
            CCLabelTTF*title=CCLabelTTF::create("back", "Arial", 30);
            CCControlButton* controlButton=CCControlButton::create(title, btnUp);
            controlButton->setBackgroundSpriteForState(btnDn,CCControlStateHighlighted);
            controlButton->setPreferredSize(CCSize(100,50));
            controlButton->setPosition(ccp(visibleOrigin.x+visibleSize.width-controlButton->getContentSize().width/2,visibleOrigin.y+controlButton->getContentSize().height/2));
            controlButton->addTargetWithActionForControlEvents(this, (SEL_CCControlHandler)(&LaserLayer::controlButtonEvent_back), CCControlEventTouchUpInside);
            this->addChild(controlButton);
            m_controlButton_back=controlButton;
        }
        
        //title
        {
            {
                CCLabelTTF* pLabel = CCLabelTTF::create("laser", "Arial", 45);
                
                // position the label on the center of the screen
                pLabel->setPosition(ccp(visibleOrigin.x + visibleSize.width/2,
                                        visibleOrigin.y + visibleSize.height - pLabel->getContentSize().height));
                
                // add the label as a child to this layer
                this->addChild(pLabel, 1);
            }
            {
                CCLabelTTF* pLabel = CCLabelTTF::create("2014-9-23", "Arial", 30);
                pLabel->setPosition(ccp(visibleOrigin.x + visibleSize.width/2,
                                        visibleOrigin.y + visibleSize.height - pLabel->getContentSize().height-60));
                this->addChild(pLabel, 1);
            }
            
        }
        return true;
    }
    return false;
}

void LaserLayer::controlButtonEvent_back(CCObject *senderz, CCControlEvent controlEvent){
    MainScene* scene = MainScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}
void LaserLayer::update(float dt){

}

bool LaserLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void LaserLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    m_laser->setLaserEnd(pTouch->getLocation());
}

void LaserLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void LaserLayer::onEnter()
{
//    CCLOG("%s","LaserLayer::onEnter");
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void LaserLayer::onExit()
{
//    CCLOG("%s","LaserLayer::onExit");
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
    
}