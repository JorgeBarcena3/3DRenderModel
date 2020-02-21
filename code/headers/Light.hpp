/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "View.hpp"
#include "Rasterizer.hpp"

namespace RenderModel
{
    class Light
    {
    public:

        typedef RenderModel::View::Color Color;

    protected:

        toolkit::Point3f position;
        Color            color;

    public:

        Light(Point3f position, Color color);

        virtual toolkit::Point4f getDirection(toolkit::Point4f pointInWorld) = 0;

    };

}

#endif
