#ifndef TRANSFORM_HEADER
#define TRANSFORM_HEADER


#include <vector>
#include <memory>
#include "Point.hpp"
#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>

namespace RenderModel {

    using toolkit::Point3f;
    using toolkit::Scaling3f;
    using toolkit::Rotation3f;
    using toolkit::Translation3f;
    using toolkit::Transformation3f;

    /*
    * Clase que va a manejar un modelo 3D
    */
    class Transform
    {   


    public:

        /*
        * Escala del modelo
        */
        Scaling3f     scale;

        /*
        * Rotacion en X del modelo
        */
        Rotation3f    rotation_x;

        /*
        * Rotacion en Y del modelo
        */
        Rotation3f    rotation_y;

        /*
        * Rotacion en Z del modelo
        */
        Rotation3f    rotation_z;

        /*
        * Translacion del modelo
        */
        Translation3f translation;

    public:

        Transform(Point3f position, Point3f rotation, float scale);
        const Transformation3f getTransformation();

    };

}

#endif
