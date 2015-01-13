//
//  HalfLaser.h
//  EffectNodes
//
//  Created by Tyrion on 15/1/13.
//
//

#ifndef __EffectNodes__HalfLaser__
#define __EffectNodes__HalfLaser__

#include "GameHeader.h"
#include "cocos2d.h"
using namespace cocos2d;
#include "cocos-ext.h"
using namespace cocos2d::extension;
#include "GLProgramWithUnifos.h"

class HalfLaser:public CCSprite{
public:
    HalfLaser();
    ~HalfLaser();
    CREATE_FUNC(HalfLaser);
    virtual bool init();
    void setBlendFunc(GLenum src,GLenum dst);
    void updateStartAndEnd();
    void setStart(const CCPoint&start);
    void setEnd(const CCPoint&end);
    void draw();
    void update(float dt);
    void setPorN(float value){m_PorN=value;}
    CGLProgramWithUnifos*m_program;
    CCTexture2D*m_maskTex;
    CCTexture2D*m_maskTex2;
    CCTexture2D*m_noiseTex;
    CCTexture2D*m_noiseTex2;
    float m_highlight;
    float m_time;
    float m_PorN;
    CCPoint m_start;
    CCPoint m_end;
    float m_kLightColor;
    float m_kGlowColor;
    float m_noiseScale;
};

#endif /* defined(__EffectNodes__HalfLaser__) */
