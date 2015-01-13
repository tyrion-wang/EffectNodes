//
//  MainLayer.h
//  EffectNodes
//
//  Created by Tyrion on 15/1/12.
//
//

#ifndef __EffectNodes__MainLayer__
#define __EffectNodes__MainLayer__

enum{
    tag_menu,
};

#include "GameHeader.h"
class MainLayer : public CCLayer
{
public:
    CREATE_FUNC(MainLayer);
    virtual bool init();
    void menuCallback(CCNode* pSender);
private:
    vector<string> m_demoNameList;
};

#endif /* defined(__EffectNodes__MainLayer__) */
