
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include <map> 
#include <string>
#include <memory>
#include "Rasterizer.hpp"
#include "Model3D.hpp"
#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include "Camera.hpp"


namespace RenderModel
{

    using std::map;
    using std::string;
    using std::shared_ptr;
    using toolkit::Point4f;
    class Light;

    /*
    * Clase que administra la vista de la pantalla
    */
    class View
    {

    public:

        typedef Color_Buffer_Rgba8888 Color_Buffer;
        typedef Color_Buffer::Color   Color;
        typedef map<string, Model3D * >  Models3D;
        

        /*
        * Ancho de la pantalla
        */
        int width;

        /*
        * Alto de la pantalla
        */
        int height;

        /*
        * Buffer de colores de la pantalla
        */
        Color_Buffer               Color_buffer;
        Rasterizer< Color_Buffer > rasterizer;

        /*
        * Mapa de modelos 3D
        */
        Models3D                   models3D;

        /*
        * Camara principal
        */
        Camera                     mainCamera;


        /*
        * Luz de la escena
        */
        shared_ptr< Light > Light;

        /*
        * Constructor de la vista
        */
        View(int width, int height, Camera camera, RenderModel::Light & lightPosition);

        /*
        * Destructor
        */
        ~View();

        /*
        * Añade un modelo a la vista
        */
        void addModel(string name, Model3D * model);

        /*
        * Update de la vista
        */
        void update(float t);

        /*
        * Renderiza los modelos 3D en la pantalla
        */
        void paint();

        /*
        * Se encarga de recortar los limites de la pantalla
        */
        vector< Point4i >  clip(const Point4i* const vertices, int* indices_begin, int* indices_end);

    };

}

#endif
