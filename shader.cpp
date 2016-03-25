#include "shader.h"
#include "logdefs.h"
#if 0
/* create a shader, store the result in *out. when link == 1 we link too. returns -1 on error, otherwise 0 */
int create_shader(GLuint* out, GLenum type, const char* src) {

  *out = glCreateShader(type);
  glShaderSource(*out, 1, &src, NULL);
  glCompileShader(*out);

  if (0 != print_shader_compile_info(*out)) {
    *out = 0;
    return -1;
  }

  return 0;
}

/* create a program, store the result in *out. when link == 1 we link too. returns -1 on error, otherwise 0 */
int create_program(GLuint* out, GLuint vert, GLuint frag, int link) {
  *out = glCreateProgram();
  glAttachShader(*out, vert);
  glAttachShader(*out, frag);

  if(1 == link) {
    glLinkProgram(*out);
    if (0 != print_program_link_info(*out)) {
      *out = 0;
      return -1;
    }
  }

  return 0;
}

/* checks + prints program link info. returns 0 when linking didn't result in an error, on link erorr < 0 */
int print_program_link_info(GLuint prog) {
  GLint status = 0;
  GLint count = 0;
  GLchar* error = NULL;
  GLsizei nchars = 0;

  glGetProgramiv(prog, GL_LINK_STATUS, &status);
  if(status) {
    return 0;
  }

  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &count);
  if(count <= 0) {
    return 0;
  }

  error = (GLchar*)malloc(count);
  glGetProgramInfoLog(prog, count, &nchars, error);
  if (nchars <= 0) {
    free(error);
    error = NULL;
    return -1;
  }

  LOGD("\nPROGRAM LINK ERROR");
  LOGD("\n--------------------------------------------------------\n");
  LOGD("%s", error);
  LOGD("--------------------------------------------------------\n\n");

  free(error);
  error = NULL;
  return -1;
}

/* checks the compile info, if it didn't compile we return < 0, otherwise 0 */
int print_shader_compile_info(GLuint shader) {

  GLint status = 0;
  GLint count = 0;
  GLchar* error = NULL;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(status) {
    return 0;
  }

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &count);
  if (0 == count) {
    return 0;
  }

  error = (GLchar*) malloc(count);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &count);
  if(count <= 0) {
    free(error);
    error = NULL;
    return 0;
  }

  glGetShaderInfoLog(shader, count, NULL, error);
  LOGD("\nSHADER COMPILE ERROR");
  LOGD("--------------------------------------------------------");
  LOGD("%s", error);
  LOGD("--------------------------------------------------------");

  free(error);
  error = NULL;
  return -1;
}
#endif
