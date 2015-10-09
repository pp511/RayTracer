//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Sphere.h
// Sphere surface object
//------------------------------------------------------------------------------


#ifndef __SPHERE_H__
#define __SPHERE_H__



#include "Surface.h"
#include "Ray.h"
#include "Intersection.h"


class Sphere  : public Surface 
{

public:
                                Sphere                              (void);
                                ~Sphere                             (void);

    bool                FindIntersection                    (Ray ray, Intersection *pIntersection);

    void resizeSphere(float resize);
    void moveSphere(STVector3 pos);
    void applymatColor(RGBR_f matcolor);
    RGBR_f getmatColor(void);


private:

    float                       m_radius;
    RGBR_f 						m_color;


    // TO DO: Proj2 raytracer
    // CAP5705 - Add object specific properties.
    // 1. Add any object specific properties you need
    //    to create your special effects
    // 2. Remember to initialize these properties in the .cpp file
    //---------------------------------------------------------
    //---------------------------------------------------------
};


#endif //__SPHERE_H__

