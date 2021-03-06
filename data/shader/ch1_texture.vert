#version 330 core  

/*layout*/
layout(location = 0) in vec3 aPos;  
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec2 aTexCoord;

/*out*/
out vec3 _ourColor;
out vec2 _texCoord;

/*main*/
void main()
{  
    gl_Position = vec4(aPos, 1.0); 
    _ourColor = aCol;
    _texCoord = aTexCoord;
}