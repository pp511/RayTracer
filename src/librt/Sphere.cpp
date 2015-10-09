//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"

// constructor
Sphere::Sphere(void)
    : m_radius(0.5)
{
      m_center = STVector3(0,0,0);
}


// clean up here
Sphere::~Sphere()
{

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection) 
{

    bool bFound = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    /*Centre of Sphere*/
    float xc,yc,zc,xd,yd,zd,xo,yo,zo,r,t;
    xc=this->m_center.x;
    yc=this->m_center.y;
    zc=this->m_center.z;

    /*Origin Vector*/
	xo=ray.Origin().x;
	yo=ray.Origin().y;
	zo=ray.Origin().z;

	/*Directojn of the Ray*/
	xd=ray.Direction().x;
	yd=ray.Direction().y;
	zd=ray.Direction().z;

	/*Radius of Sphere*/
	r=this->m_radius;

    float a = xd*xd + yd*yd + zd*zd;

	float b = 2*(xd*(xo-xc)+yd*(yo-yc)+zd*(zo-zc));

    //(x+y)^2=x^2 + 2*x*y + y^2
    float c = xo*xo-2*xo*xc+xc*xc + yo*yo-2	*yo*yc+yc*yc + zo*zo-2*zo*zc+zc*zc - r*r;

    float discriminant = b*b - (4.0f)*a*c;

    if(discriminant < 0)
    	bFound = false;
    else
    {
		float D = sqrtf(discriminant);
		float t1 = (-0.5f)*(b+D)/a;
		float t2 = (-0.5f)*(b-D)/a;

		if (D < 0.0f)
		return false;

		/* Chosing the closest intersection point*/
		if (t1 > 0.000001f)
		{
			t = (float)t1;
			bFound = true;
		}
		if ((t2 > 0.000001f) && (t2 < t1))
		{
			t = (float)t2;
			bFound = true;
		}

		// 2. Store the results of the intersection
		STVector3 raydistance = ray.Origin() - pIntersection->point ;
		pIntersection->distanceSqu = STVector3::Dot(raydistance, raydistance);
		pIntersection->point = ray.Origin() + t*ray.Direction();
	//	std::cout << "\n Sphere Intersection " <<pIntersection->point.x <<pIntersection->point.y<<pIntersection->point.z << std::endl;
		pIntersection->normal = (pIntersection->point - m_center) / r;
		pIntersection->surface = this;
		pIntersection->intersection_color = this->getmatColor();
		bFound = true;
}
	// 3. if found and return true, otherwise, return false
    return(bFound);

}

//-------------------------------------------------
// Change the dimention os sphere
//-------------------------------------------------
void Sphere::resizeSphere(float resize)
{
	m_radius = m_radius*resize;
}
//-------------------------------------------------
// Translate the sphere to a new postion
//-------------------------------------------------
void Sphere::moveSphere(STVector3 pos)
{
	m_center +=STVector3(pos);
}
//-------------------------------------------------
// Apply material color to the sphere
//-------------------------------------------------

void Sphere::applymatColor(RGBR_f matcolor)
{
	m_color = matcolor;
}

//-------------------------------------------------
// Retreives the material color of sphere
//-------------------------------------------------
RGBR_f Sphere::getmatColor(void)
{
	return m_color;
}

