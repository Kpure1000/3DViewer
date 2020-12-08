#version 430 core

in vec2 _texCoord;
out vec4 _frag_out;

/*uniform*/
/*get screen size*/
uniform vec2 _screen_size;
uniform float _rdSeed[4];

/*Camera Data*/
uniform vec3 ca_lookFrom;
uniform vec3 ca_left_buttom;
uniform vec3 ca_horizontal;
uniform vec3 ca_vertical;

/**********************************/
/*random*/
int rdCount=0;
float RandXY(float x, float y){
     return fract(cos(x * (12.9898) + y * (4.1414)) * 43758.5453);
}
float Rand(){
    float a = RandXY(_texCoord.x, _rdSeed[0]);
    float b = RandXY(_rdSeed[1], _texCoord.y);
    float c = RandXY(rdCount++, _rdSeed[2]);
    float d = RandXY(_rdSeed[3], a);
    float e = RandXY(b, c);
    float f = RandXY(d, e);

    return f;
}
/**********************************/
/*Ray*/
struct Ray
{
    vec3 origin;
    vec3 direction; 
};
Ray Ray_Con(vec3 Origin, vec3 Direction)
{
    Ray r;
    r.origin=Origin;
    r.direction=Direction;
    return r;
}
vec3 Ray_PointTo(Ray ray, float t)
{
    return ray.origin + t * ray.direction;
}
/**********************************/

/**********************************/
/*Hitable*/
/*Hit record*/
struct HitRecord
{
    float t;
    vec3 p;
    vec3 normal;
};
/***************/
/*Sphere: first, a sphere!*/
struct Sphere
{
    vec3 center;
    float radius;
};
Sphere Sphere_Con(vec3 Center, float Radius)
{
    Sphere newSp;
    newSp.center=Center;newSp.radius=Radius;
    return newSp;
}
bool Sphere_Hit(Sphere sp, Ray ray, 
    float tMin, float tMax, out HitRecord rec)
{
    vec3 oc = ray.origin - sp.center;
    float a = dot(ray.direction,ray.direction);
    float b = dot(oc,ray.direction);
    float c = dot(oc,oc)-sp.radius*sp.radius;
    float discriminant = b*b-a*c;
    if(discriminant > 0)
    {
        float temp = (-b-sqrt(discriminant))/a;
        if(temp < tMax && temp > tMin){
            rec.t = temp;
            rec.p = Ray_PointTo(ray,rec.t);
            rec.normal = (rec.p - sp.center) / sp.radius;
            return true;
        }
        temp = (-b+sqrt(discriminant))/a;
        if(temp < tMax && temp > tMin){
            rec.t = temp;
            rec.p = Ray_PointTo(ray,rec.t);
            rec.normal = (rec.p - sp.center) / sp.radius;
            return true;
        }
        return false;
    }
}

/***************/
/*Metarial*/

/***************/
/**********************************/

vec3 Irradiance(Ray ray, Sphere sp)
{
    HitRecord rec;
    if(Sphere_Hit(sp, ray, 0.001, 10000, rec))
    {
        return 0.5*vec3(rec.normal + vec3(1,1,1));
    }
    else
    {
        vec3 nor = ray.direction;
        float t = 0.5 + 0.5*nor.y;
        return (1-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
    }
}
/**********************************/
/*Camera*/
Ray CreateRayFromCamera(vec2 uv)
{
    Ray newRay = Ray_Con(ca_lookFrom,
     ca_left_buttom + uv.x * ca_horizontal + uv.y * ca_vertical - ca_lookFrom);
    return newRay;
}

/*unit color*/
void NormalColor(inout vec3 Color)
{
    Color.x = min(1.0, max(0.0, Color.x));
    Color.y = min(1.0, max(0.0, Color.y));
    Color.z = min(1.0, max(0.0, Color.z));
}
void main()
{
    int sampleTimes=10;
    vec3 lt = vec3(-2.0,-1.0,-1.0);
    float hor = 4.0;
    float ver = hor * _screen_size.y / _screen_size.x;
    vec3 horizontal = vec3(hor,0.0,0.0);
    vec3 vertical = vec3(0.0,ver,0.0);

    Sphere sphere1 = Sphere_Con(vec3(0,0,-1.5),0.5);
    Sphere sphere2 = Sphere_Con(vec3(0,-1000.0,-1.0),1000.0);


    vec2 uv;
    uv.x = (gl_FragCoord.x) / _screen_size.x;
    uv.y = (gl_FragCoord.y) / _screen_size.y;

    Ray ray = Ray_Con(ca_lookFrom,
     ca_left_buttom + uv.x * horizontal + uv.y * vertical - ca_lookFrom);

    vec3 color;
    color = Irradiance(ray,sphere1);
    
    NormalColor(color);

    _frag_out = vec4(color,1);

}
