#version 330 core  

/*in*/
in vec2 _texCoord;

/*out*/
out vec4 _fragColor; 

/*uniform*/
uniform sampler2D _texture1;
uniform sampler2D _texture2;

uniform float _rate;

/*main*/
void main()  
{
    _fragColor = mix(texture(_texture1, _texCoord), texture(_texture2, _texCoord), _rate);
}