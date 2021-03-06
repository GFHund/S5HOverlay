#include "RenderFont.h"
#include "../Exceptions/InitFontException.h"
#include "../Exceptions/LoadingFontException.h"
#include "../Exceptions/SetFontSizeException.h"
#include <math.h>
#include <iostream>


RenderFont::RenderFont(){}

RenderFont::~RenderFont(){}

void RenderFont::init(){
    std::cout << "Init Font"<< std::endl;
    FT_Error error = FT_Init_FreeType(&library);
    if(error){
        throw InitFontException("Fehler beim initialisieren von FreeType");
    }
    setBgColor(0,0,0,255);
    setFontColor(255,255,255,255);
    std::cout << "Load Font"<< std::endl;
    setFontFamily("Dosis-Medium.ttf");
    std::cout << "set Font size"<< std::endl;
    setFontSize(20);
}

void RenderFont::setFontFamily(std::string fontfile){
    FT_Error error = FT_New_Face(library,fontfile.c_str(),0,&face);
    if ( error == FT_Err_Unknown_File_Format )
    {
        throw LoadingFontException("Font Format is unsupported");
        //std::cout << "Font Format is unsupported";
        //return 1;
    }
    else if ( error )
    {
        throw LoadingFontException("Font could not be Opened");
        //std::cout << "Font could not be Opened";
        //return 1;
    }
}

void RenderFont::setFontColor(unsigned char r,unsigned char g, unsigned char b,unsigned char a){
    this->fontColor.r = r;
    this->fontColor.g = g;
    this->fontColor.b = b;
    this->fontColor.a = a;
}
void RenderFont::setBgColor(unsigned char r,unsigned char g, unsigned char b,unsigned char a){
    this->bgColor.r = r;
    this->bgColor.g = g;
    this->bgColor.b = b;
    this->bgColor.a = a;
}
void RenderFont::setFontSize(unsigned int size){
    mFontSize = size;
    const int dpi = 100;
    int pointSize = size * 64.0;
    FT_Error error = FT_Set_Char_Size(face,pointSize,0,dpi,0);//50 * 64
    //FT_Error error = FT_Set_Char_Size(face,50 * 64,0,dpi,0);//50 * 64
    if(error){
        //std::cout << "Could not set Char Size";
        throw SetFontSizeException("Could not set Char Size");
    }
}

void RenderFont::setLineHeight(float lineHeight){
    this->mLineHeight = lineHeight;
}


Image* RenderFont::renderFont(std::string text){
    int height = 2048;
    int width = 2048;

    std::cout << "init Default Image" << std::endl;

    Image* img = Image::getDefaultImage(width,height,this->bgColor.r,this->bgColor.g,this->bgColor.b, this->bgColor.a);
    
    
    FT_GlyphSlot slot;
    FT_Matrix matrix;
    FT_Vector pen;
    double angle;

//std::cout << "set Font Matrix" << std::endl;
    slot = face->glyph;
    angle = 0;//(25.0 /360)*3.14159 *2; // Use 25 degrees
    matrix.xx = (FT_Fixed) (cos(angle)*0x10000L);
    matrix.xy = (FT_Fixed)(-sin(angle)*0x10000L);
    matrix.yx = (FT_Fixed)(sin(angle)*0x10000L);
    matrix.yy = (FT_Fixed)(cos(angle)*0x10000L);
    
    int koorX = 0;
    //int koorY = (height - 200)* 64;
    int koorY = (height * 0.05) * 64;
    
    pen.x = koorX;//300*64;
    pen.y = koorY;

//std::cout << "go Thorught text" << std::endl;
    for(int i=0;i < text.length();i++){
        FT_Set_Transform(face,&matrix,&pen);

        FT_Error error = FT_Load_Char(face, text[i],FT_LOAD_RENDER);
        if(error){
            continue;
        }

        FT_Int x = slot->bitmap_left;
        FT_Int y = height - slot->bitmap_top;
        //std::cout << "char " << text[i] << std::endl;
        //std::cout << "x " << x << std::endl;
        //std::cout << "y " << y << std::endl;
        FT_Bitmap* bitmap = &slot->bitmap;
        FT_Int xMax = x + bitmap->width;
        FT_Int yMax = y + bitmap->rows;
        //std::cout << "xMax " << xMax << std::endl;
        //std::cout << "yMax " << yMax << std::endl;
        int row = x / width;
        int xKoorigiert = x % width;
        int xMaxKorrigiert = xMax % width;
        if(x > width || xMax > width){
            y-= height * 0.25f * row;
            yMax -= height * 0.25f * row;
        }
        //std::cout << "xKoorigiert " << xKoorigiert << std::endl;
        //std::cout << "xMaxKorrigiert " << xMaxKorrigiert << std::endl;
        //std::cout << "y " << y << std::endl;
        //std::cout << "yMax " << yMax << std::endl << std::endl;

        FT_Int k,j,p,q;
        //for(k=x,p=0;k<xMax;k++,p++){
        for(k=xKoorigiert,p=0;k<xMaxKorrigiert;k++,p++){
            for(j=y,q=0;j<yMax;j++,q++){
                if(k<0 || j<0 || k >= width ||j>= height) continue;
                int index = j*width+k;
                int index2 = q* bitmap->width +p;
                unsigned char bufferVal = bitmap->buffer[index2];
                if(bufferVal > 0){
                    unsigned char r = this->fontColor.r;
                    unsigned char g = this->fontColor.g;
                    unsigned char b = this->fontColor.b;
                    unsigned char a = this->fontColor.a;
                    img->setPixel(k,j,r,g,b, a);
                }
                
                //image[index] = bitmap->buffer[index2];
            }
        }
        
        pen.x += slot->advance.x;        
        pen.y += slot->advance.y;
        
    }

    return img;
}