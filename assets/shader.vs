#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;
out vec2 fragTexCoord;
out vec4 fragColor;
uniform mat4 mvp;
uniform float time;
void main()                        
{
    fragTexCoord = vertexTexCoord; 
    // fragColor = vec4(
    //             cos(vertexPosition.x + time) * sin(vertexPosition.z + time) + 1., 
    //             cos(vertexPosition.z + time) * sin(vertexPosition.x + time) + 0.5,
    //              1., 1.0);
    vec4 fadeColor = vec4(1., 1., 1., (vertexPosition.z * 0.5));
    fragColor = vertexColor * fadeColor;
    gl_Position = mvp*vec4(vertexPosition.x, cos(vertexPosition.z + time) * sin(vertexPosition.x + time), vertexPosition.z, 1.); 
}                                  
