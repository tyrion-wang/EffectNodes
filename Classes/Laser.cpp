//
//  Laser.cpp
//  EffectNodes
//
//  Created by Tyrion on 15/1/13.
//
//

#include "Laser.h"

Laser::Laser(){
    m_halfLaser1=NULL;
    m_halfLaser2=NULL;
    m_slimHalfLaser1=NULL;
    m_slimHalfLaser2=NULL;
}

bool Laser::init(){
    
    //halfLaser1
    m_halfLaser1 = HalfLaser::create();
    m_halfLaser1->setPorN(1);
    m_halfLaser1->setBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    m_halfLaser1->setScaleY(1.3);//(1.0);
    m_halfLaser1->m_kGlowColor=1.6;//1.0;
    m_halfLaser1->m_kLightColor=0.0;
    m_halfLaser1->m_noiseScale=2.2;//0.5;
    addChild(m_halfLaser1);
    
    //halfLaser2
    m_halfLaser2 = HalfLaser::create();
    m_halfLaser2->setPorN(-1);
    m_halfLaser2->setBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    m_halfLaser2->setScaleY(1.3);//(1.0);
    m_halfLaser2->m_kGlowColor=1.6;//1.0;
    m_halfLaser2->m_kLightColor=0.0;
    m_halfLaser2->m_noiseScale=2.2;//0.5;
    addChild(m_halfLaser2);
    
    //slimHalfLaser1
    m_slimHalfLaser1 = HalfLaser::create();
    m_slimHalfLaser1->setPorN(1);
    m_slimHalfLaser1->setBlendFunc(GL_ONE, GL_ONE);
    m_slimHalfLaser1->setScaleY(0.4);//(0.6);//(0.1);
    m_slimHalfLaser1->m_kGlowColor=2.5;//1.5;
    m_slimHalfLaser1->m_kLightColor=0.5;//0.4;//0.3;
    m_slimHalfLaser1->m_noiseScale=1.5;
    addChild(m_slimHalfLaser1);
    
    //slimHalfLaser2
    m_slimHalfLaser2 = HalfLaser::create();
    m_slimHalfLaser2->setPorN(-1);
    m_slimHalfLaser2->setBlendFunc(GL_ONE, GL_ONE);
    m_slimHalfLaser2->setScaleY(0.4);//(0.6);//(0.1);
    m_slimHalfLaser2->m_kGlowColor=2.5;//1.5;
    m_slimHalfLaser2->m_kLightColor=0.5;//0.4;//0.3;
    m_slimHalfLaser2->m_noiseScale=1.5;
    addChild(m_slimHalfLaser2);
    
    return true;
}

void Laser::setLaserStart(const CCPoint&start){
    m_start=start;
    m_halfLaser1->setStart(m_start);
    m_halfLaser2->setStart(m_start);
    m_slimHalfLaser1->setStart(m_start);
    m_slimHalfLaser2->setStart(m_start);
}
void Laser::setLaserEnd(const CCPoint&end){
    m_end=end;
    m_halfLaser1->setEnd(m_end);
    m_halfLaser2->setEnd(m_end);
    m_slimHalfLaser1->setEnd(m_end);
    m_slimHalfLaser2->setEnd(m_end);
}