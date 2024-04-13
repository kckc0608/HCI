#version 330 core
// in vec3 fragColor;
out vec3 aColor;
uniform vec3 uniformColor;
void main() {
    // aColor = fragColor;
    aColor = uniformColor;
}