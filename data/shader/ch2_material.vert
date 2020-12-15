#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;

uniform vec3 _lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

void main()
{
    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);
    FragPos = vec3(_view * _model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(_view * _model))) * aNormal;
    LightPos = vec3(_view * vec4(_lightPos, 1.0)); // Transform world-space light position to view-space light position
}