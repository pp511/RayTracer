//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Intersection.cpp
// Intersection points - store surface normal, time of intersection
// distance squared, surface
//
// This is used to carry data about the surface for rendering
//------------------------------------------------------------------------------


#include "Intersection.h"
#include "Surface.h"



Intersection::Intersection(void)
    :   distanceSqu         (0),
        surface             (NULL),
        point               (STVector3(0,0,0)),
        normal              (STVector3(0,0,1)),
		intersection_color  (RGBR_f(1,1,1,1))
{

}


Intersection::~Intersection(void)
{

}

float Intersection::dotproduct(STVector3 raydirection){     //Dot Product 3-Vectors
  float dotp = this->normal.x*(raydirection.x) + this->normal.y*(raydirection.y) + this->normal.z*(raydirection.z);
  return dotp;
}

RGBR_f getMatColor(void);
void setMatColor(RGBR_f matcolor);


void Intersection::setMatColor(RGBR_f matcolor)
{
	intersection_color = matcolor;
}

RGBR_f Intersection::getMatColor(void)
{
	return intersection_color;
}

