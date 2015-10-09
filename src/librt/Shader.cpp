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
    m_mode = PHONG;

    RGBR_f matcolor = pIntersection->getMatColor();

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
 //   color = RGBR_f(color.r *255, color.g, color.b,color.a);
    color = RGBR_f(color.r * matcolor.r, color.g * matcolor.g, color.b * matcolor.b, color.a * matcolor.a);
    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(int i, Intersection *pIntersection, STVector3 *lightDirection, Scene *pScene, STVector3 lp)
{
    assert(pIntersection);
    assert(lightDirection);
    RGBR_f Imax = RGBR_f(1, 1, 1, 1);
    RGBR_f color, diffused;
    float Kd =0.8;
    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
   //    normal and light direction
#if 1
    STVector3 normal= pIntersection->normal/pIntersection->distanceSqu;
    float dotp= STVector3::Dot(normal,*lightDirection);
#else
   float dotp= STVector3::Dot(pIntersection->normal,*lightDirection);
  //float dotp= STVector3::Dot(pIntersection->normal/STVector3::Dot(pIntersection->normal,pIntersection->normal),*lightDirection);

#endif
  //  std::cout<<"Dotproduce"<<dotp<<std::endl;
    if(dotp < 0) // max(0,n.l)
    {
    	 	dotp = 0;
    }
    color = pScene->GetLightColor(i);
    RGBR_f matcolor = pIntersection->getMatColor();

     diffused.r = Imax.r * color.r * dotp * Kd ;
     diffused.g = Imax.g * color.g * dotp * Kd ;
     diffused.b = Imax.b * color.b * dotp * Kd ;

    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------

    //---------------------------------------------------------

    return(diffused);
}




// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(int i, Intersection *pIntersection, STVector3 *lightDirection, Scene *pScene, STVector3 lp, Ray ray)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color;
   // std::cout<<"****Phong*****"<<std::endl;
    RGBR_f Imax = RGBR_f(1, 1, 1, 1);

    RGBR_f Ia = RGBR_f(1, 1,1,1);
    RGBR_f Ka = RGBR_f(0.5,0.5,0.5,0.5);
    RGBR_f ambient = RGBR_f(Ia.r*Ka.r, Ia.g*Ka.g, Ia.b*Ka.b, 1);

    RGBR_f diffused = Lambertian(i,pIntersection, lightDirection,pScene,lp);

    RGBR_f Ks = RGBR_f(0.5,0.5,0.5,0.5);
    STVector3 eye = STVector3(200.0,200.0,200.0) ;
    STVector3 eyeray = eye - pIntersection->point;
   // STVector3 eyeray = ray.origin - pIntersection->point;
    STVector3 l = *lightDirection/(sqrtf(STVector3::Dot(*lightDirection,*lightDirection)));
    STVector3 v = eyeray/(STVector3::Dot(eyeray,eyeray));
    STVector3 h = (v + l)/sqrtf(STVector3::Dot(v + l, v + l));
    STVector3 normal= pIntersection->normal/pIntersection->distanceSqu;
  //  STVector3 normal= pIntersection->normal/(STVector3::Dot(pIntersection->normal,pIntersection->normal));

    int exp = 5;
    float multiplier;
    float cosalpha = STVector3::Dot(normal,h);
    if(cosalpha < 0) // max(0,n.l)
    		multiplier = 0;
    else
    		multiplier = pow(cosalpha,exp);

    RGBR_f specular;
    color = pScene->GetLightColor(i);

    specular.r = Imax.r * Ks.r * multiplier *color.r;
    specular.g = Imax.g * Ks.g * multiplier *color.g;
    specular.b = Imax.b * Ks.b * multiplier *color.b;

    RGBR_f phongcolor;
    phongcolor.r = ambient.r + diffused.r + specular.r;
    phongcolor.g = ambient.g + diffused.g + specular.g;
    phongcolor.b = ambient.b + diffused.b + specular.b;

        return phongcolor;

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

