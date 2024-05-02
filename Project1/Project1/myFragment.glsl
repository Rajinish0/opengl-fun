#version 330 core
out vec4 FragColor;
in vec2 tCoords;

uniform sampler2D tex;

void main()
{
    //vec4 tcol = texture(tex, tCoords);
   // if (tcol.a < 0.5) {
     //   discard; 
    //}
    FragColor = texture(tex, tCoords);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}