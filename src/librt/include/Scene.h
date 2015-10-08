//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.h
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#ifndef __SCENE_H__
#define __SCENE_H__

#include "Camera.h"
#include "defs.h"
#include "Ray.h"
#include "Lists.h"
#include "RGBR_f.h"


class Scene
{

public:
                                Scene                                       (void);
                                ~Scene                                      (void);

    void                        SetBackgroundColor                          (RGBR_f color);
    RGBR_f                   GetBackgroundColor                             (void);

    void                        AddLight                                    (Light lightin);
    void                        AddSurface                                  (Surface *pSurfacein);


    Camera                      *GetCamera                                  (void);
    STVector3                    GetLightDirection                          (int i,Intersection *pIntersection);

    int                         FindIntersection                            (Ray ray, Intersection *pIntersection, bool bAny);
    int                         FindClosestIntersection                     (Ray ray, Intersection *pIntersection);
    int                         SelectClosest                               (IntersectionList *pIntersectionList, Intersection *pIntersection);
    RGBR_f                   GetLightColor                             		(int i);
 	STVector3 				GetLightPosition(int i,Intersection *pIntersection);


private:


    // surfaces
    SurfaceList                  m_surfaceList;


    // camera
    Camera                      *m_pCamera;

    // lights
    LightList                   m_lights;


    // background color
    RGBR_f                     m_background;

    // clear scene
    void                        Clear               (void);

};


#endif //__SCENE_H__


