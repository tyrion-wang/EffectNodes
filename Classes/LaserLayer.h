//
//  LaserLayer.h
//  EffectNodes
//
//  Created by Tyrion on 15/1/12.
//
//

#ifndef __EffectNodes__LaserLayer__
#define __EffectNodes__LaserLayer__

#include "GameHeader.h"
#include "Laser.h"
//#include "cocos2d.h"
//using namespace cocos2d;
//#include "cocos-ext.h"
//using namespace cocos2d::extension;
//#include "GLProgramWithUnifos.h"

class LaserLayer : public CCLayer
{
public:
    CREATE_FUNC(LaserLayer);
    virtual bool init();
public:
    //touch
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
public:
    //back
    void controlButtonEvent_back(CCObject *senderz, CCControlEvent controlEvent);
    CCControlButton* m_controlButton_back;
public:
    LaserLayer(){
        
    }
    virtual ~ LaserLayer(){
    }
    void update(float dt);
public:
    Laser* m_laser;
};

#endif /* defined(__EffectNodes__LaserLayer__) */
