
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <Projection.hpp>
#include <memory>
#include "Transform.hpp"


namespace RenderModel
{  

    using toolkit::Projection3f;
    using toolkit::Point3f;


    /*
    * Clase camara
    */
    class Camera
    {

    private:
        
        /*
        * Matriz de proyeccion
        */
        std::shared_ptr<Projection3f> projection;

    public:

        /*
        * Transform de la camara
        */
        Transform transform;

        /*
        * Constructor de la camara
        */
        Camera(float _near, float _far, float fov, float aspectRatio, Point3f _position, Point3f _rotation);

        /*
        * Destructor de la clase camara
        */
        ~Camera();

        /*
        * Update de la camara
        */
        void update(float t);

        /*
        * Devuelve la matriz de proyeccion
        */
        const Projection3f getCameraProjection();

        /*
        * Devuelve la matriz inversa de transformacion
        */
        const Transformation3f getInverseTransform();

    };

}

#endif
