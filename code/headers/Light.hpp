
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "View.hpp"
#include "Rasterizer.hpp"

namespace RenderModel
{

    /*
    * Administra la luz
    */
    class Light
    {
    public:

        typedef RenderModel::View::Color Color;

    protected:

        /*
        * Posicion de la luz
        */
        toolkit::Point3f position;

        /*
        * Color de la luz
        */
        Color            color;

    public:

        /*
        * Constructor de la luz
        */
        Light(Point3f position, Color color);

        /*
        * Direccion de la luz a una posicion
        */
        virtual toolkit::Point4f getDirection(toolkit::Point4f pointInWorld) = 0;

    };

}

#endif
