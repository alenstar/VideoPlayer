#ifndef TEXTURE_H
#define TEXTURE_H
#include <memory>
#include <GL/glu.h>

#include "logdefs.h"

class Texture {
private:
    std::string _name;
    int _x, _y, _w, _h;
public:
    Texture();
    ~Texture();
    GLuint tex;
    int getWidth();
    int getHeight();
    bool isNull();
    std::string &getName();
    void bind();
    bool load(void *frame, int w, int h);
};
typedef std::shared_ptr <Texture> TexturePtr;
//typedef std::auto_ptr<Texture> TexturePtr;

#endif // TEXTURE_H
