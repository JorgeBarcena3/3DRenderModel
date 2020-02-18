
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
#include <Vector.hpp>

using namespace toolkit;

namespace RenderModel
{

    View::View(int width, int height, Camera _camera)
        :
        width(width),
        height(height),
        Color_buffer(width, height),
        rasterizer(Color_buffer),
        mainCamera(_camera)
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

    bool View::cutout(const Point4i* const vertices, int* indices_begin, int* indices_end)
    {
        for (int* i = indices_begin; i != indices_end; i++)
        {
            int px0 = (vertices[*i])[0];
            int py0 = (vertices[*i])[1];

            if (
                (px0 <= 0 || px0 >= width)
                || (py0 <= 0 || py0 >= width)

                )
            {
                //No lo renderizamos
                return false;
            }
        }

        return true;
    }



}
