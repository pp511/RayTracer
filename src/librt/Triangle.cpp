//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
// 
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"



// contructor
Triangle::Triangle(void)
        : Surface()
{

}


// clean up
Triangle::~Triangle()
{

}

void Triangle::generateVertices(STVector3 a,STVector3 b,STVector3 c)
{
	m_a = a;
	m_b = b;
	m_c = c;
}
//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    LinearSolver L;
    bool bFoundSolution = false;
    
    // TO DO: Proj2 raytracer
    // CAP5705 - Solve for intersections.
    // 1. Use barycentric coordinates and linear equations to solve for intersections
    // 2. If a solution is found return true, otherwise, return false
    // 3. If a solution is found, u, v and w are updated; otherwise they are useless
    //------------------------------------------------

    //------------------------------------------------------

    return(bFoundSolution);
}

STVector3 Triangle::crossproduct(STVector3 u, const STVector3 v)
{
   return STVector3(u.y*v.z - u.z*v.y , u.z*v.x - u.x*v.z , u.x*v.y- u.y*v.x);
}

float Triangle::dotproduct(STVector3 u, const STVector3 v)
{
   return (u.x*v.x+u.y*v.y+u.z*v.z);
}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    //    Use barycentric coordinates and linear equations
    // 2. Store the results of the intersection
    // 3. If found return true, otherwise, return false
    // NOTE: The Intersection pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

    //------------------------------------------------------
    	STVector3 edge1,edge2;
    	edge1.x = m_b.x - m_a.x;
    	edge1.y = m_b.y - m_a.y;
    	edge1.z = m_b.z - m_a.z;
    	edge2.x = m_c.x - m_a.x;
    	edge2.y = m_c.y - m_a.y;
    	edge2.z = m_c.z - m_a.z;

        STVector3 raydir = ray.Direction();

        STVector3 h = crossproduct(raydir,edge2);

        float a = dotproduct(edge1,h);

        if (a > -0.00001 && a < 0.00001)
        {
        	 return(false);
        }


        float f =1 / a;

        STVector3 Rorg = ray.Origin();
        STVector3 s = ray.Origin() - m_a;

        float u = f * (dotproduct(s,h));

        if( u< 0 || u >1.0)
            return false;
        STVector3 q = crossproduct(s,edge1);

        float v = f *(dotproduct(raydir,q));

        if(v <0.0 || u+v > 1.0)
            return false;

        float t = f * (dotproduct(edge2,q));

        if(t> 0.00001){
            float intx = ray.Origin().x+t*(raydir.x);
            float inty = ray.Origin().y+t*(raydir.y);
            float intz = ray.Origin().z+t*(raydir.z);
            std::cout<< " Triangle Intersection "<<intx<<" "<< inty<<" "<<intz<<std::endl;

            pIntersection->point = STVector3(intx,inty,intz);
            pIntersection->surface = this;
            pIntersection->normal =ComputeNormalVector();
            pIntersection->distanceSqu = t*t;
            bFound = true;
        }
        return(bFound);
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal(0,0,1);

    // TO DO: Proj2 raytracer
    // CAP5705 - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------

    //---------------------------------------------------
    STVector3 edge1 = this->m_c - this->m_a;
    STVector3 edge2 = this->m_b - this->m_a;

    return(crossproduct(edge1,edge2));
}


// TO DO: Proj2 raytracer
// CAP5705 - Add object specific properties.
// 1. Add any object specific properties you need
//    to create your special effects (e.g. specularity, transparency...)
// 2. Remember to declare these in your .h file
// 
//---------------------------------------------------------
//---------------------------------------------------------
