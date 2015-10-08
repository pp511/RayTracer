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
RGBR_f Shader::Run(int i, Intersection *pIntersection, STVector3 *lightDirection,Scene *pScene, STVector3 lp)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(i,pIntersection, lightDirection,pScene,lp);
            break;
        case PHONG:
            color = Phong(i,pIntersection, lightDirection,pScene,lp);
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
    RGBR_f Int = RGBR_f(1, 1, 1, 1);
    RGBR_f color, lightcolor;
    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
   //    normal and light direction

    float dotp= STVector3::Dot(pIntersection->normal,*lightDirection);

     if(dotp < 0)
    	 	dotp = 0;

     lightcolor = pScene->GetLightColor(i);
     color.r = Int.r * lightcolor.r * dotp;
     color.g = Int.g * lightcolor.g * dotp;
     color.b = Int.b * lightcolor.b * dotp;

    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------

    //---------------------------------------------------------

    return(color);
}




// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(int i, Intersection *pIntersection, STVector3 *lightDirection, Scene *pScene, STVector3 lp)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color;



    //RGBR_f RayTracer::PhongShader(STVector3 &n, STVector3 &lPosition, RGBR_f sphereColor, int p) {
        RGBR_f ambIntensity = (RGBR_f(0.8, 0.8, 0.8, 1));
        RGBR_f intesity = RGBR_f(1, 1, 1, 1);
        RGBR_f ambient = RGBR_f(ambIntensity.r * 0.5, ambIntensity.g * 0.5, ambIntensity.b * 0.5, 1);
        RGBR_f lightcolor, specTerm, diffTerm;

        lightcolor = pScene->GetLightColor(i);

        float dotproduct = STVector3::Dot(pIntersection->normal,*lightDirection);
        float max = (dotproduct > 0 ? dotproduct : 0);
        diffTerm.r = intesity.r * lightcolor.r*max;
        diffTerm.g = intesity.g * lightcolor.g*max;
        diffTerm.b = intesity.b * lightcolor.b*max;

        STVector3 lookAt = STVector3(0.0, 0.0, -1);
        lookAt.Normalize();

        STVector3 h = lp - lookAt;
     //   int power = p;
        int power = 2;
        h.Normalize();
        float dp2 = STVector3::Dot(pIntersection->normal, h);

        RGBR_f ks = RGBR_f(1, 1, 1, 1);
        float dp3 = pow((dp2 > 0 ? dp2 : 0), power);
        specTerm.r = intesity.r * ks.r*dp3;
        specTerm.g = intesity.g * ks.g*dp3;
        specTerm.b = intesity.b * ks.b*dp3;

        RGBR_f result;
        result.r = ambient.r + diffTerm.r + specTerm.r;
        result.g = ambient.g + diffTerm.g + specTerm.g;
        result.b = ambient.b + diffTerm.b + specTerm.b;

        return result;

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

