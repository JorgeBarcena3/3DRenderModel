
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DIRECTIONALLIGHT_HEADER
#define DIRECTIONALLIGHT_HEADER

#include "Rasterizer.hpp"
#include "View.hpp"
#include "Light.hpp"

namespace RenderModel
{
    class DirectionalLight : public Light
    {

    public:

        DirectionalLight(Point3f position, Color color);
        
        virtual toolkit::Point4f getDirection(toolkit::Point4f pointInWorld) override;

    };

}

#endif
