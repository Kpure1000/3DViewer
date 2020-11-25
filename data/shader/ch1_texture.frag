#version 330 core  

/*in*/
in vec3 ourColor;
in vec2 texCoord;

/*out*/
out vec4 FragColor; 

/*uniform*/
uniform sampler2D texture1;
uniform sampler2D texture2;


/*main*/
void main()  
{
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}