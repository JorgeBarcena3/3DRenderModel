
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include "Model3D.hpp"

namespace RenderModel {

    /*
    * Guarda la informacion relativa al material
    */
    class Material
    {

    public:


    public:

        /*
        * Color ambiente
        */
        Model3D::Color Ka;
        
        /*
        * Color difuso
        */
        Model3D::Color Kd;

        /*
        * Color especular
        */
        Model3D::Color Ks;
        

    public:

        Material(Model3D::Color _ka, Model3D::Color _kd, Model3D::Color _ks);
        ~Material();


    };

}

#endif
