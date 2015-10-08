//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

#include "Shader.h"
#include <assert.h>
#include "Intersection.h"



Shader::Shader(void)
    : m_mode          (LAMBERTIAN)
{
}


void Shader::SetMode(RenderMode mode)
{
    m_mode = mode;
}


// Runs the shader according to the specified render mode
RGBR_f Shader::Run(int i, Intersection *pIntersection, STVector3 *lightDirection,Scene *pScene, STVector3 lp,Ray ray)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(i,pIntersection, lightDirection,pScene,lp);
            break;
        case PHONG:

            color = Phong(i,pIntersection, lightDirection,pScene,lp,ray);
            break;
        default:
            color = Lambertian(i, pIntersection, lightDirection,pScene,lp);
            break;
        }

    // TO DO: Proj2 raytracer
    // CAP5705 - Add special effects.
    // 1. Add calls to your new special effects function to the switch statement
    // 2. Update the RenderMode structure in def.h to flag these
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(int i, Intersection *pIntersection, STVector3 *lightDirection, Scene *pScene, STVector3 lp)
{
    assert(pIntersection);
    assert(lightDirection);
    RGBR_f Imax = RGBR_f(1, 1, 1, 1);
    RGBR_f color, diffused;
    float Kd =0.5;
    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
   //    normal and light direction
#if 1
    STVector3 normal= pIntersection->normal/pIntersection->distanceSqu;
    float dotp= STVector3::Dot(normal,*lightDirection);
#else
    float dotp= STVector3::Dot(pIntersection->normal,*lightDirection);
#endif
  //  std::cout<<"Dotproduce"<<dotp<<std::endl;
    if(dotp < 0) // max(0,n.l)
    {
    	 	dotp = 0;
    }
    diffused = pScene->GetLightColor(i);
     color.r = Imax.r * diffused.r * dotp * Kd;
     color.g = Imax.g * diffused.g * dotp * Kd;
     color.b = Imax.b * diffused.b * dotp * Kd;

    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------

    //---------------------------------------------------------

    return(color);
}




// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(int i, Intersection *pIntersection, STVector3 *lightDirection, Scene *pScene, STVector3 lp, Ray ray)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color;

    RGBR_f Imax = RGBR_f(1, 1, 1, 1);

    RGBR_f Ia = RGBR_f(0.7, 0.7, 0.7, 0.7);
    RGBR_f Ka = RGBR_f(0.5,0.5,0.5,0.5);
    RGBR_f ambient = RGBR_f(Ia.r*Ka.r, Ia.g*Ka.g, Ia.b*Ka.b, 1);

    RGBR_f diffused = Lambertian(i,pIntersection, lightDirection,pScene,lp);

    RGBR_f Ks = RGBR_f(0.9,0.9,0.9,0.9);
    STVector3 eye = STVector3(200.0,200.0,200.0) ;
    STVector3 eyeray = eye - pIntersection->point;
   // STVector3 eyeray = ray.origin - pIntersection->point;
    STVector3 l = *lightDirection/(sqrtf(STVector3::Dot(*lightDirection,*lightDirection)));
    STVector3 v = eyeray/(STVector3::Dot(eyeray,eyeray));
    STVector3 h = (v + l)/sqrtf(STVector3::Dot(v + l, v + l));

    int exp = 10;
    float multiplier;
    float cosalpha = STVector3::Dot(pIntersection->normal,h);
    if(cosalpha < 0) // max(0,n.l)
    		multiplier = 0;
    else
    		multiplier = pow(cosalpha,exp);

    RGBR_f specular;
    specular.r = Imax.r * Ks.r * multiplier;
    specular.g = Imax.g * Ks.g * multiplier;
    specular.b = Imax.b * Ks.b * multiplier;

    RGBR_f phongcolor;
    color.r = ambient.r + diffused.r + specular.r;
    color.g = ambient.g + diffused.g + specular.g;
    color.b = ambient.b + diffused.b + specular.b;

        return color;

    // TO DO: Proj2 raytracer
    // CAP5705 - Add Phong shading.
    // 1. Implement the phong shading equation here
    // 2. Remember to add any attributes you might need for shading to 
    //    your surface objects as they are passed in with the pIntersection
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}


Shader::~Shader()
{
}


// TO DO: Proj2 raytracer
// CAP5705 - Add shading functions for special effects.
// 1. Declare functions for your special effects in the .h file
// 2. See the Run function to see when each shading function is called
//---------------------------------------------------------
//---------------------------------------------------------

