#include "texture.h"
#include <assert.h>

//#define USE_GLSL

Texture::Texture() : textures_created(false), shader_created(false), _scale(1.0f)
{
    y_tex = 0;
    u_tex = 0;
    v_tex = 0;
    _x = 0;
    _y = 0;
    _w = 0;
    _h = 0;

    glGenTextures(1, &y_tex);
    glGenTextures(1, &u_tex);
    glGenTextures(1, &v_tex);
}

Texture::~Texture()
{
    if (y_tex > 0)
    glDeleteTextures(1, &y_tex);
    if (u_tex > 0)
    glDeleteTextures(1, &u_tex);
    if (v_tex > 0)
    glDeleteTextures(1, &v_tex);
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
    return y_tex > 0 ? false:true;
}

std::string& Texture::getName()
{
    return _name;
}

bool Texture::load(void* frame, int w, int h){

    glBindTexture(GL_TEXTURE_2D, y_tex);
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
    glViewport(0, 0, _w, _h);

        glBindTexture(GL_TEXTURE_2D, y_tex);			// 设置为图像纹理

        glBegin( GL_QUADS );
        glTexCoord2d(0.0,0.0); glVertex2d(0.0, 0.0);
        glTexCoord2d(1.0,0.0); glVertex2d(_w * 1.0f, 0.0);
        glTexCoord2d(1.0,1.0); glVertex2d(_w * 1.0f, _h * 1.0f);
        glTexCoord2d(0.0,1.0); glVertex2d(0.0, _h * 1.0f);
        glEnd();
        glMatrixMode(GL_MODELVIEW);	//选择模型观察矩阵
}


bool Texture::setupShader() {
#ifdef USE_GLSL
  if(shader_created) {
    LOGD("Already creatd the shader.\n");
    return false;
  }

  if(create_shader(&vert, GL_VERTEX_SHADER, YUV420P_VS)){
    LOGE("create_shader: falied");
  }
  if(create_shader(&frag, GL_FRAGMENT_SHADER, YUV420P_FS)){
    LOGE("create_shader: falied");
  }
  if(create_program(prog, vert, frag)){
    LOGE("create_program: falied");
  }

  glLinkProgram(prog);
  print_shader_link_info(prog);

  glUseProgram(prog);
  glUniform1i(glGetUniformLocation(prog, "y_tex"), 0);
  glUniform1i(glGetUniformLocation(prog, "u_tex"), 1);
  glUniform1i(glGetUniformLocation(prog, "v_tex"), 2);

  u_pos = glGetUniformLocation(prog, "draw_pos");
#endif

  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  resize(viewport[2], viewport[3]);

  return true;
}

bool Texture::setupTextures() {
/*
  if(textures_created) {
    LOGD("Textures already created.\n");
    return false;
  }
  */

  glGenTextures(1, &y_tex);
  glBindTexture(GL_TEXTURE_2D, y_tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, _w, _h, 0, GL_RED, GL_UNSIGNED_BYTE, NULL); // y_pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenTextures(1, &u_tex);
  glBindTexture(GL_TEXTURE_2D, u_tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, _w/2, _h/2, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenTextures(1, &v_tex);
  glBindTexture(GL_TEXTURE_2D, v_tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, _w/2, _h/2, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  textures_created = true;
  return true;
}

void Texture::draw(int x, int y, int w, int h) {
  //assert(textures_created == true);

  if(w == 0) {
    w = 1;
  }

  if(h == 0) {
    h = 1;
  }
#ifdef USE_GLSL
  glBindVertexArray(vao);
  glUseProgram(prog);

  glUniform4f(u_pos, x, y, w, h);
#endif

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, y_tex);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, u_tex);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, v_tex);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture::draw()
{
    if(! y_tex){
        LOGW("Texture is invaild");
        return;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( _x * 1.0f, _w * _scale, _h * _scale, _y * 1.0f, 0.0, 1.f);
    glViewport(0, 0, _w * _scale, _h * _scale);

    glBindTexture(GL_TEXTURE_2D, y_tex);			// 设置为图像纹理
    glBegin( GL_QUADS );
    glTexCoord2d(0.0,0.0); glVertex2d(0.0, 0.0);
    glTexCoord2d(1.0,0.0); glVertex2d(_w * 1.0f, 0.0);
    glTexCoord2d(1.0,1.0); glVertex2d(_w * 1.0f, _h * 1.0f);
    glTexCoord2d(0.0,1.0); glVertex2d(0.0, _h * 1.0f);
    glEnd();

    glMatrixMode(GL_MODELVIEW);	//选择模型观察矩阵

}

void Texture::resize(int w, int h)
{
  //pm.identity();
  //pm.ortho(0, win_w, win_h, 0, 0.0, 100.0f);
#ifdef USE_GLSL
  glUseProgram(prog);
  glUniformMatrix4fv(glGetUniformLocation(prog, "u_pm"), 1, GL_FALSE, pm.get());
#endif
}

void Texture::setScale(float s)
{
    if (s > 0){
        _scale = s;
    }
}

float Texture::getScale()
{
    return _scale;
}

void Texture::setPixels(uint8_t* pixels, int w, int h) {
    _w = w;
    _h = h;
    glBindTexture(GL_TEXTURE_2D, y_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _w, _h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

}

void Texture::setYPixels(uint8_t* pixels, int stride) {
  assert(textures_created == true);

  glBindTexture(GL_TEXTURE_2D, y_tex);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _w, _h, GL_RED, GL_UNSIGNED_BYTE, pixels);
}

void Texture::setUPixels(uint8_t* pixels, int stride) {
  assert(textures_created == true);

  glBindTexture(GL_TEXTURE_2D, u_tex);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _w/2, _h/2, GL_RED, GL_UNSIGNED_BYTE, pixels);
}

void Texture::setVPixels(uint8_t* pixels, int stride) {
  assert(textures_created == true);

  glBindTexture(GL_TEXTURE_2D, v_tex);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _w/2, _h/2, GL_RED, GL_UNSIGNED_BYTE, pixels);
}
