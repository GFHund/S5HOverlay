#include "LastLapTimeState.h"
#include "../Font.h"
#include "../Exceptions/ShaderReadFailureException.h"

void LastLapTimeState::init(Renderer renderer){
    this->ticker = new Ring();
    Font font;
    RGBA backgroundColor;
    backgroundColor.r = 0;
    backgroundColor.g = 0;
    backgroundColor.b = 0;
    backgroundColor.a = 100;
    RGBA fontColor;
    fontColor.r = 255;
    fontColor.g = 255;
    fontColor.b = 255;
    fontColor.a = 255;

    font.setBackgroundColor(backgroundColor);
    font.setFontColor(fontColor);
    font.setFontFamily("Dosis-Medium.ttf");
    font.setFontSize(16);
    Image* img = Image::getImageFromText("Dies ist ein Test",font);
    this->ticker->setImage(0,img);

    Shader* sha =  nullptr;
    try{
        //                               vertexProgram.glsl   fragmentProgram.glsl
        sha = Shader::getShaderPrograms("vertexProgram.glsl","fragmentProgram.glsl");
    }catch(ShaderReadFailureException e){
        std::cout << "Shader Read Failure Exception" << std::endl;
        return;
    }
    
    this->ticker->setShader(sha);

    renderer.init3DObject(this->ticker);
}
void LastLapTimeState::tick(std::chrono::duration<int,std::milli> duration){
    float d = (float)duration.count();
    dogEngine::CQuaternion curRotation = this->ticker->getRotation();
    float speed = 360.0f / 500000.0f;//360 Deg / 5000 ms
    //std::cout << "Speed: " << speed << std::endl;
    //std::cout << "duration: " << d << std::endl;
    dogEngine::CQuaternion additionalRotation = dogEngine::CQuaternion(dogEngine::CVector3(0,1,0),speed*d);
    dogEngine::CQuaternion resultRotation = curRotation * additionalRotation;
    this->ticker->setRotation(resultRotation);
}
void LastLapTimeState::render(Renderer renderer){
    renderer.render3DObject(this->ticker);
}
void LastLapTimeState::finish(Renderer renderer){
    delete this->ticker;
}