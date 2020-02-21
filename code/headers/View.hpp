
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
    class PointLight;


    class View
    {

    public:

        typedef Color_Buffer_Rgba8888 Color_Buffer;
        typedef Color_Buffer::Color   Color;
        typedef map<string, shared_ptr<Model3D>>  Models3D;
        



        int width;
        int height;

        Color_Buffer               Color_buffer;
        Rasterizer< Color_Buffer > rasterizer;
        Models3D                   models3D;
        Camera                     mainCamera;


    public:

        PointLight * Light;

        View(int width, int height, Camera camera, PointLight& lightPosition);

        void addModel(string name, Model3D model);
        void update(float t);
        void paint();

        vector< Point4i >  clip(const Point4i* const vertices, int* indices_begin, int* indices_end);

    };

}

#endif
