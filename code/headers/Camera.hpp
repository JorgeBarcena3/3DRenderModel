
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <Projection.hpp>
#include <memory>


namespace RenderModel
{  

    using toolkit::Projection3f;
    using toolkit::Projection3f;


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
        * Constructor de la camara
        */
        Camera(float near, float far, float fov, float aspectRatio);

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

    };

}

#endif
