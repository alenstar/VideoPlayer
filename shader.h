#ifndef SHADER_H
#define SHADER_H
#include <GL/gl.h>
int create_shader(GLuint* out, GLenum type, const char* src);           /* create a shader, returns 0 on success, < 0 on error. e.g. create_shader(&vert, GL_VERTEX_SHADER, DRAWER_VS); */
int create_program(GLuint* out, GLuint vert, GLuint frag, int link);    /* create a program from the given vertex and fragment shader. returns 0 on success, < 0 on error. e.g. create_program(&prog, vert, frag, 1); */
int print_shader_compile_info(GLuint shader);                           /* prints the compile info of a shader. returns 0 when shader compiled, < 0 on error. */
int print_program_link_info(GLuint prog);                               /* prints the program link info. returns 0 on success, < 0 on error. */

#endif // SHADER_H
