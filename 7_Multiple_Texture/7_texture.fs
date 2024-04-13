#version 330 core
in vec2 TexCoord;
out vec4 aColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main() {
    //aColor = vec4(0.7, 0.7, 0.7, 1.0);
    aColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}