//
//  Laser.h
//  EffectNodes
//
//  Created by Tyrion on 15/1/13.
//
//

#ifndef __EffectNodes__Laser__
#define __EffectNodes__Laser__

#include "GameHeader.h"
#include "HalfLaser.h"
class Laser:public CCNode
{
public:
    HalfLaser* m_halfLaser1;
    HalfLaser* m_halfLaser2;
    HalfLaser* m_slimHalfLaser1;
    HalfLaser* m_slimHalfLaser2;
    CCPoint m_start;
    CCPoint m_end;
    Laser();
    bool init();
    void setLaserStart(const CCPoint&start);
    void setLaserEnd(const CCPoint&end);
};

#endif /* defined(__EffectNodes__Laser__) */
