
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef POINTLIGHT_HEADER
#define POINTLIGHT_HEADER

#include "Rasterizer.hpp"
#include "View.hpp"

namespace RenderModel
{
    class PointLight
    {
        typedef RenderModel::View::Color Color;

    public:

        toolkit::Point3f position;
        Color   color;

    public:
       
        PointLight(Point3f position, Color color);
        
    };

}

#endif
