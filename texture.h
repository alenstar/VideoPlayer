#ifndef TEXTURE_H
#define TEXTURE_H
extern "C" {
#include "logdefs.h"
#include <GL/glu.h>
#include <GL/gl.h>
//#include <GL/glx.h>
}

#include <memory>
#include "Matrices.h"

static const char* YUV420P_VS = ""
  "#version 330\n"
  ""
  "uniform mat4 u_pm;"
  "uniform vec4 draw_pos;"
  ""
  "const vec2 verts[4] = vec2[] ("
  "  vec2(-0.5,  0.5), "
  "  vec2(-0.5, -0.5), "
  "  vec2( 0.5,  0.5), "
  "  vec2( 0.5, -0.5)  "
  ");"
  ""
  "const vec2 texcoords[4] = vec2[] ("
  "  vec2(0.0, 1.0), "
  "  vec2(0.0, 0.0), "
  "  vec2(1.0, 1.0), "
  "  vec2(1.0, 0.0)  "
  "); "
  ""
  "out vec2 v_coord; "
  ""
  "void main() {"
  "   vec2 vert = verts[gl_VertexID];"
  "   vec4 p = vec4((0.5 * draw_pos.z) + draw_pos.x + (vert.x * draw_pos.z), "
  "                 (0.5 * draw_pos.w) + draw_pos.y + (vert.y * draw_pos.w), "
  "                 0, 1);"
  "   gl_Position = u_pm * p;"
  "   v_coord = texcoords[gl_VertexID];"
  "}"
  "";

static const char* YUV420P_FS = ""
 "#version 330\n"
  "uniform sampler2D y_tex;"
  "uniform sampler2D u_tex;"
  "uniform sampler2D v_tex;"
  "in vec2 v_coord;"
  "layout( location = 0 ) out vec4 fragcolor;"
  ""
  "const vec3 R_cf = vec3(1.164383,  0.000000,  1.596027);"
  "const vec3 G_cf = vec3(1.164383, -0.391762, -0.812968);"
  "const vec3 B_cf = vec3(1.164383,  2.017232,  0.000000);"
  "const vec3 offset = vec3(-0.0625, -0.5, -0.5);"
  ""
  "void main() {"
  "  float y = texture(y_tex, v_coord).r;"
  "  float u = texture(u_tex, v_coord).r;"
  "  float v = texture(v_tex, v_coord).r;"
  "  vec3 yuv = vec3(y,u,v);"
  "  yuv += offset;"
  "  fragcolor = vec4(0.0, 0.0, 0.0, 1.0);"
  "  fragcolor.r = dot(yuv, R_cf);"
  "  fragcolor.g = dot(yuv, G_cf);"
  "  fragcolor.b = dot(yuv, B_cf);"
  "}"
  "";

class Texture {
private:
    std::string _name;
    int _x, _y, _w, _h;
    float _scale;

    GLuint vert;
    GLuint frag;
    GLuint prog;
    GLint u_pos;
    uint8_t* y_pixels;
    uint8_t* u_pixels;
    uint8_t* v_pixels;
    Matrix4 pm;

    bool textures_created;
    bool shader_created;
public:
    Texture();
    ~Texture();
    //GLuint tex;
    GLuint y_tex;
    GLuint u_tex;
    GLuint v_tex;
    int getWidth();
    int getHeight();
    bool isNull();
    std::string &getName();
    void bind();
    bool load(void *frame, int w, int h);
    void draw(int x, int y, int w, int h);
    void draw();
    void resize(int w, int h);
    void setScale(float s);
    float getScale();
    void setPixels(uint8_t *pixels, int w, int h);
    void setYPixels(uint8_t *pixels, int stride);
    void setUPixels(uint8_t *pixels, int stride);
    void setVPixels(uint8_t *pixels, int stride);
    bool setupShader();
    bool setupTextures();
};
typedef std::shared_ptr <Texture> TexturePtr;
//typedef std::auto_ptr<Texture> TexturePtr;

#endif // TEXTURE_H
