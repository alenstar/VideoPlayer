#include "texture.h"

Texture::Texture()
{
    tex = 0;
    _x = 0;
    _y = 0;
    _w = 0;
    _h = 0;

    glGenTextures(1, &tex);
}

Texture::~Texture()
{
    if (tex)
    glDeleteTextures(1, &tex);
}

int Texture::getWidth()
{
    return _w;
}

int Texture::getHeight()
{
    return _h;
}

bool Texture::isNull()
{
    return false;
}

std::string& Texture::getName()
{
    return _name;
}

bool Texture::load(void* frame, int w, int h){

    if(tex){
        glDeleteTextures(1, &tex);
    }
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, frame);
    _w = w;
    _h = h;
    return true;
}

void Texture::bind()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( _x * 1.0f, _w * 1.0f, _h * 1.0f, _y * 1.0f, 0.0, 1.f);
        glBindTexture(GL_TEXTURE_2D, tex);			// 设置为图像纹理

        glBegin( GL_QUADS );
        glTexCoord2d(0.0,0.0); glVertex2d(0.0, 0.0);
        glTexCoord2d(1.0,0.0); glVertex2d(_w * 1.0f, 0.0);
        glTexCoord2d(1.0,1.0); glVertex2d(_w * 1.0f, _h * 1.0f);
        glTexCoord2d(0.0,1.0); glVertex2d(0.0, _h * 1.0f);
        glEnd();
        glMatrixMode(GL_MODELVIEW);	//选择模型观察矩阵
}
