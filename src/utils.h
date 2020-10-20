#ifndef __UTILS_H__
#define __UTILS_H__
void print_shaders(void){
    #define GRAPHICS_API_OPENGL_33 

 const char *defaultVShaderStr =
#if defined(GRAPHICS_API_OPENGL_21)
    "#version 120                       \n"
#elif defined(GRAPHICS_API_OPENGL_ES2)
    "#version 100                       \n"
#endif
#if defined(GRAPHICS_API_OPENGL_ES2) || defined(GRAPHICS_API_OPENGL_21)
    "attribute vec3 vertexPosition;     \n"
    "attribute vec2 vertexTexCoord;     \n"
    "attribute vec4 vertexColor;        \n"
    "varying vec2 fragTexCoord;         \n"
    "varying vec4 fragColor;            \n"
#elif defined(GRAPHICS_API_OPENGL_33)
    "#version 330                       \n"
    "in vec3 vertexPosition;            \n"
    "in vec2 vertexTexCoord;            \n"
    "in vec4 vertexColor;               \n"
    "out vec2 fragTexCoord;             \n"
    "out vec4 fragColor;                \n"
#endif
    "uniform mat4 mvp;                  \n"
    "void main()                        \n"
    "{                                  \n"
    "    fragTexCoord = vertexTexCoord; \n"
    "    fragColor = vertexColor;       \n"
    "    gl_Position = mvp*vec4(vertexPosition, 1.0); \n"
    "}                                  \n";

    // Fragment shader directly defined, no external file required
    const char *defaultFShaderStr =
#if defined(GRAPHICS_API_OPENGL_21)
    "#version 120                       \n"
#elif defined(GRAPHICS_API_OPENGL_ES2)
    "#version 100                       \n"
    "precision mediump float;           \n"     // precision required for OpenGL ES2 (WebGL)
#endif
#if defined(GRAPHICS_API_OPENGL_ES2) || defined(GRAPHICS_API_OPENGL_21)
    "varying vec2 fragTexCoord;         \n"
    "varying vec4 fragColor;            \n"
#elif defined(GRAPHICS_API_OPENGL_33)
    "#version 330       \n"
    "in vec2 fragTexCoord;              \n"
    "in vec4 fragColor;                 \n"
    "out vec4 finalColor;               \n"
#endif
    "uniform sampler2D texture0;        \n"
    "uniform vec4 colDiffuse;           \n"
    "void main()                        \n"
    "{                                  \n"
#if defined(GRAPHICS_API_OPENGL_ES2) || defined(GRAPHICS_API_OPENGL_21)
    "    vec4 texelColor = texture2D(texture0, fragTexCoord); \n" // NOTE: texture2D() is deprecated on OpenGL 3.3 and ES 3.0
    "    gl_FragColor = texelColor*colDiffuse*fragColor;      \n"
#elif defined(GRAPHICS_API_OPENGL_33)
    "    vec4 texelColor = texture(texture0, fragTexCoord);   \n"
    "    finalColor = texelColor*colDiffuse*fragColor;        \n"
#endif
    "}                                  \n";

    printf("%s\n", defaultFShaderStr);
    printf("%s\n", defaultVShaderStr);


}
#endif