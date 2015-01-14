//
//  GLProgramWithUnifos.cpp
//  EffectNodes
//
//  Created by Tyrion on 15/1/12.
//
//

#include "GLProgramWithUnifos.h"

GLProgramWithUnifos::GLProgramWithUnifos(){
}

GLProgramWithUnifos::~GLProgramWithUnifos(){
}

GLProgramWithUnifos* GLProgramWithUnifos::createWithFileName(const char* vShaderFilename, const char* fShaderFilename)
{
    GLProgramWithUnifos* pRet = new GLProgramWithUnifos();
    if (pRet && pRet->initWithVertexShaderFilename(vShaderFilename, fShaderFilename))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

GLProgramWithUnifos* GLProgramWithUnifos::createWithByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    GLProgramWithUnifos* pRet = new GLProgramWithUnifos();
    if (pRet && pRet->initWithVertexShaderByteArray(vShaderByteArray, fShaderByteArray))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void GLProgramWithUnifos::attachUniform(string unifoName){
    m_unifoMap[unifoName] = glGetUniformLocation(this->getProgram(),unifoName.c_str());
}

void GLProgramWithUnifos::passUnifoValue1f(string unifoName,GLfloat v){
    glUniform1f(m_unifoMap[unifoName],v);
}

void GLProgramWithUnifos::passUnifoValue1i(string unifoName,GLint v){
    glUniform1i(m_unifoMap[unifoName],v);
}

void GLProgramWithUnifos::passUnifoValueMatrixNfv(string unifoName,const GLfloat *array,int arrayLen){
    assert(arrayLen==4||arrayLen==9||arrayLen==16);
    switch (arrayLen) {
        case 4:
            glUniformMatrix2fv(m_unifoMap[unifoName],1,GL_FALSE,array);
            break;
        case 9:
            glUniformMatrix3fv(m_unifoMap[unifoName],1,GL_FALSE,array);
            break;
        case 16:
            glUniformMatrix4fv(m_unifoMap[unifoName],1,GL_FALSE,array);
            break;
        default:
            assert(false);
            break;
    }
}

void GLProgramWithUnifos::passUnifoValueNfv(string unifoName,const GLfloat*array,int arrayLen){
    assert(arrayLen>=1&&arrayLen<=4);
    switch (arrayLen) {
        case 1:
            glUniform1fv(m_unifoMap[unifoName],1,array);
            break;
        case 2:
            glUniform2fv(m_unifoMap[unifoName],1,array);
            break;
        case 3:
            glUniform3fv(m_unifoMap[unifoName],1,array);
            break;
        case 4:
            glUniform4fv(m_unifoMap[unifoName],1,array);
            break;
        default:
            assert(false);
            break;
    }
    
}

void GLProgramWithUnifos::passUnifoValueNfvN(string unifoName,const GLfloat*array,int arrayLen,int arrayCount){
    assert(arrayLen>=1&&arrayLen<=4);
    switch (arrayLen) {
        case 1:
            glUniform1fv(m_unifoMap[unifoName],arrayCount,array);
            break;
        case 2:
            glUniform2fv(m_unifoMap[unifoName],arrayCount,array);
            break;
        case 3:
            glUniform3fv(m_unifoMap[unifoName],arrayCount,array);
            break;
        case 4:
            glUniform4fv(m_unifoMap[unifoName],arrayCount,array);
            break;
        default:
            assert(false);
            break;
    }
    
}

void GLProgramWithUnifos::passUnifoValueNiv(string unifoName,const GLint*array,int arrayLen){
    assert(arrayLen>=1&&arrayLen<=4);
    switch (arrayLen) {
        case 1:
            glUniform1iv(m_unifoMap[unifoName],1,array);
            break;
        case 2:
            glUniform2iv(m_unifoMap[unifoName],1,array);
            break;
        case 3:
            glUniform3iv(m_unifoMap[unifoName],1,array);
            break;
        case 4:
            glUniform4iv(m_unifoMap[unifoName],1,array);
            break;
        default:
            assert(false);
            break;
    }
    
}

void GLProgramWithUnifos::passUnifoValueMatrixNfv(string unifoName,const vector<GLfloat>&valueList){
    passUnifoValueMatrixNfv(unifoName, &valueList.front(), (int)valueList.size());
}

void GLProgramWithUnifos::passUnifoValueNfv(string unifoName,const vector<GLfloat>&valueList){
    passUnifoValueNfv(unifoName, &valueList.front(), (int)valueList.size());
}

void GLProgramWithUnifos::passUnifoValueNiv(string unifoName,const vector<GLint>&valueList){
    passUnifoValueNiv(unifoName, &valueList.front(), (int)valueList.size());
}