#version 430 core

out vec4 _frag_out

/*****************/
/*Ray*/
struct Ray
{
    vec3 origin;
    vec3 direction; 
}
vec3 PointTo(Ray ray, float t)
{
    return ray.origin + t * ray.direction;
}
/*****************/

/*****************/
/*Hit record*/
struct HitRecord
{
    float t;
    vec3 p;
}
/*****************/

void main()
{
    _frag_out = vec4(1,1,1,1);
}
