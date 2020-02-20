
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../headers/View.hpp"
#include "../headers/SutherlandHodgmanClipping.hpp"
#include <Vector.hpp>

using namespace toolkit;
using toolkit::Point4f;

namespace RenderModel
{

    View::View(int width, int height, Camera _camera, Point3f _lightPosition)
        :
        width(width),
        height(height),
        Color_buffer(width, height),
        rasterizer(Color_buffer),
        mainCamera(_camera),
        lightPosition(_lightPosition)
    {

    }

    void View::addModel(string name, Model3D model)
    {
        models3D.insert(std::pair<string, shared_ptr<Model3D>>(name, shared_ptr<Model3D>(new Model3D(model))));
    }

    void View::update(float t)
    {
        mainCamera.update(t);

        //Pasada por los padres de todos las entidades
        for (auto model : models3D)
        {
            model.second->update(t, *this);
        }

    }

    void View::paint()
    {

        // Se borra el framebúffer y se dibujan los triángulos:
        rasterizer.clear();

        for (auto model : models3D)
        {
            model.second->paint(*this);
        }

        // Se copia el framebúffer oculto en el framebúffer de la ventana:
        rasterizer.get_color_buffer().gl_draw_pixels(0, 0);

    }

    vector< Point4i >  View::clip(const Point4i* const vertices, int* indices_begin, int* indices_end)
    {
        vector<Point4i> clipped_vertex;
        SutherlandHodgmanClipping::clip(vertices, indices_begin, indices_end, width, height, clipped_vertex);

        return clipped_vertex;
    } 

}