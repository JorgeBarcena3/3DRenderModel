
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
#include "Light.hpp"

namespace RenderModel
{
    class PointLight : public Light
    {
       
    public:
       
        PointLight(Point3f position, Color color);
        

        // Inherited via Light
        virtual toolkit::Point4f getDirection(toolkit::Point4f pointInWorld) override;

    };

}

#endif
