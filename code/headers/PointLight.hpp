
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef POINTLIGHT_HEADER
#define POINTLIGHT_HEADER

#include "Rasterizer.hpp"
#include "View.hpp"
#include "Light.hpp"

namespace RenderModel
{

    /**
    * Administra las point lights
    */
    class PointLight : public Light
    {
       
    public:

        /**
        * Constructor de la luz
        */       
        PointLight(Point3f position, Color color);        

        /**
        * Devuelve la direccion de la luz
        */
        virtual toolkit::Point4f getDirection(toolkit::Point4f pointInWorld) override;

    };

}

#endif
