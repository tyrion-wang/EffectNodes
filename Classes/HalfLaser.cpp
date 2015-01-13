//
//  HalfLaser.cpp
//  EffectNodes
//
//  Created by Tyrion on 15/1/13.
//
//

#include "HalfLaser.h"

HalfLaser::HalfLaser(){
    m_program=NULL;
    m_maskTex=NULL;
    m_maskTex2=NULL;
    m_noiseTex=NULL;
    m_noiseTex2=NULL;
    m_highlight=1.0;
    m_time=0;
    m_PorN=1;
    m_kLightColor=1.0;
    m_kGlowColor=1.0;
    m_noiseScale=1.0;
}

HalfLaser::~HalfLaser(){
    if(m_program)m_program->release();
    if(m_maskTex)m_maskTex->release();
    if(m_maskTex2)m_maskTex2->release();
    if(m_noiseTex)m_noiseTex->release();
    if(m_noiseTex2)m_noiseTex2->release();
    
}

bool HalfLaser::init(){
    //lightTex
    if (CCSprite::initWithFile("LaserRes/light2.png")) {
        {
            ccTexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
            this->getTexture()->setTexParameters(&texParams);
        }
        //maskTex
        m_maskTex=CCTextureCache::sharedTextureCache()->addImage("LaserRes/mask.png");
        m_maskTex->retain();
        {
            ccTexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
            m_maskTex->setTexParameters(&texParams);
        }
        //maskTex2
        m_maskTex2=CCTextureCache::sharedTextureCache()->addImage("LaserRes/mask2.png");
        m_maskTex2->retain();
        {
            ccTexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
            m_maskTex2->setTexParameters(&texParams);
        }
        
        //noiseTex
        m_noiseTex=CCTextureCache::sharedTextureCache()->addImage("LaserRes/noise.png");
        m_noiseTex->retain();
        {
            ccTexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
            m_noiseTex->setTexParameters(&texParams);
        }
        //noiseTex2
        m_noiseTex2=CCTextureCache::sharedTextureCache()->addImage("LaserRes/noise2.png");
        m_noiseTex2->retain();
        {
            ccTexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
            m_noiseTex2->setTexParameters(&texParams);
        }
        
        //create and set shader program
        {
            GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("LaserRes/laser.fsh").c_str())->getCString();
            CGLProgramWithUnifos* program = new CGLProgramWithUnifos();
            program->autorelease();
            program->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
            //bind attribute
            program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            //link  (must after bindAttribute)
            program->link();
            //get cocos2d-x build-in uniforms
            program->updateUniforms();
            //get my own uniforms
            program->attachUniform("u_maskTex");
            program->attachUniform("u_maskTex2");
            program->attachUniform("u_noiseTex");
            program->attachUniform("u_noiseTex2");
            program->attachUniform("u_spriteSize");
            program->attachUniform("u_LUPos");
            program->attachUniform("u_noiseSize");
            program->attachUniform("u_highlight");
            program->attachUniform("u_time");
            program->attachUniform("u_PorN");
            program->attachUniform("u_scale");
            program->attachUniform("u_kLightColor");
            program->attachUniform("u_kGlowColor");
            program->attachUniform("u_noiseScale");
            //set program
            m_program=program;
            m_program->retain();
            
            //check gl error
            CHECK_GL_ERROR_DEBUG();
        }
        //update
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void HalfLaser::updateStartAndEnd(){
    CCPoint mid=ccpMult(m_start+m_end, 0.5) ;
    CCPoint dir=ccpNormalize(m_end-m_start);
    float A;
    if(dir.y<=0){
        A=acosf(dir.x)*180/M_PI;
    }else{
        A=(2*M_PI-acosf(dir.x))*180/M_PI;
    }
    this->setPosition(mid);
    this->setRotation(A);
    
    float targetLen=ccpDistance(m_start, m_end);
    float contentLen=this->getContentSize().width;
    float scaleX=targetLen/contentLen;
    this->setScaleX(scaleX);
}

void HalfLaser::setStart(const CCPoint&start){
    m_start=start;
    updateStartAndEnd();
}

void HalfLaser::setEnd(const CCPoint&end){
    m_end=end;
    updateStartAndEnd();
}

void HalfLaser::setBlendFunc(GLenum src,GLenum dst){
    //
    ccBlendFunc blendFunc={src,dst};
    this->CCSprite::setBlendFunc(blendFunc);
    
}
void HalfLaser::update(float dt){
    m_time+=dt;
    if(m_time>=10000)m_time=0;
    
}
void HalfLaser::draw(){
    {
        
        float spriteSize_tmp[2]={this->getContentSize().width*this->getScaleX(),
            this->getContentSize().height*this->getScaleY()};//because this sprite may rotate, so we use contentSize*scale instead of boundingBox().size
        float LUPos_tmp[2]={0,0};//if we use {boundingBox().getMinX(),boundingBox().getMaxY()} instead of {0,0}, when this sprite scale, the noiseTex will move, cause uncontinuous effect. to avoid this, so we should use {0,0}
        float noiseSize_tmp[2]={m_noiseTex->getContentSize().width,m_noiseTex->getContentSize().height};
        float scale_tmp[2]={this->getScaleX(),this->getScaleY()};
        //----change shader
        ccGLEnable(m_eGLServerState);
        //pass values for cocos2d-x build-in uniforms
        this->setShaderProgram(m_program);
        CGLProgramWithUnifos*program=(CGLProgramWithUnifos*)this->getShaderProgram();
        program->use();
        program->setUniformsForBuiltins();
        //pass values for my own uniforms
        program->passUnifoValue1i("u_maskTex", 1);
        program->passUnifoValue1i("u_noiseTex", 2);
        program->passUnifoValue1i("u_noiseTex2", 4);
        program->passUnifoValue1i("u_maskTex2", 3);
        program->passUnifoValueNfv("u_spriteSize", spriteSize_tmp, 2);
        program->passUnifoValueNfv("u_LUPos", LUPos_tmp, 2);
        program->passUnifoValueNfv("u_noiseSize", noiseSize_tmp, 2);
        program->passUnifoValue1f("u_highlight", m_highlight);
        program->passUnifoValue1f("u_time", m_time);
        program->passUnifoValue1f("u_PorN", m_PorN);
        program->passUnifoValueNfv("u_scale", scale_tmp, 2);
        program->passUnifoValue1f("u_kLightColor", m_kLightColor);
        program->passUnifoValue1f("u_kGlowColor", m_kGlowColor);
        program->passUnifoValue1f("u_noiseScale", m_noiseScale);
        //attach texture to texture attach point
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_maskTex->getName());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_noiseTex->getName());
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_maskTex2->getName());
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, m_noiseTex2->getName());
        glActiveTexture(GL_TEXTURE0);//back to GL_TEXTURE0
        //----call CCSprite::draw
        CCSprite::draw();
    }
}