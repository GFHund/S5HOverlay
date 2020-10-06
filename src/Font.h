#ifndef __FONT__
#define __FONT__
#include "pixelFormat/RGBA.h"
class Font{
    protected:
    int mFontSize;
    std::string mFontFamily;
    RGBA mFontColor;
    RGBA mBgColor;
    float mLineHeight;

    public:
    void setFontSize(int size){
        this->mFontSize = size;
    }
    void setFontFamily(std::string family){
        this->mFontFamily = family;
    }
    void setFontColor(RGBA color){
        this->mFontColor = color;
    }
    void setBackgroundColor(RGBA color){
        this->mBgColor = color;
    }
    void setLineHeight(float lineHeight){
        this->mLineHeight = lineHeight;
    }

    int getFontSize(){
        return this->mFontSize;
    }
    std::string getFontFamily(){
        return this->mFontFamily;
    }
    RGBA getFontColor(){
        return this->mFontColor;
    }
    RGBA getBackgroundColor(){
        return this->mBgColor;
    }
    float getLineHeight(){
        return this->mLineHeight;
    }
};

#endif