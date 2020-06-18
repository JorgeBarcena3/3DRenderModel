
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DIRECTIONALLIGHT_HEADER
#define DIRECTIONALLIGHT_HEADER

#include "Rasterizer.hpp"
#include "View.hpp"
#include "Light.hpp"

namespace RenderModel
{

    /**
    * Administra la direccional luz
    */
    class DirectionalLight : public Light
    {

    public:

        /**
        * Constructor
        */
        DirectionalLight(Point3f position, Color color);

        /**
        * Devuelve la direccion de la luz
        */
        virtual toolkit::Point4f getDirection(toolkit::Point4f pointInWorld) override;

    };

}

#endif
