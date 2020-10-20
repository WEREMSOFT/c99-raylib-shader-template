#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float time;
void main()
{                                  
    vec4 texelColor = texture(texture0, fragTexCoord);
    
    // finalColor = texelColor*colDiffuse*fragColor;
    finalColor = texelColor * colDiffuse * fragColor * vec4(
                cos(time + fragTexCoord.x) * sin(time + fragTexCoord.y) + 1., 
                sin(time + fragTexCoord.x) * cos(time + fragTexCoord.y) + 1., 
                cos(fragTexCoord.x + fragTexCoord.y) + 0.5, 1.);
}