
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MESH_HEADER
#define MESH_HEADER

#include <memory>
#include <vector>
#include "Point.hpp"
#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include "Model3D.hpp"

namespace RenderModel {

    using std::shared_ptr;
    using std::vector;
    using toolkit::Point4i;
    using toolkit::Point4f;
    class View;
    class Material;

    /*
    * Guarda la informacion de un mesh en un modelo 3D
    */
    class Mesh
    {

    public:

        typedef Model3D::Index_Buffer Index_Buffer;
        typedef Model3D::Color        Color;
        typedef Point4f               Vertex;


    private:

        /*
        * Indices de la mesh con respecto a el modelo 3D
        */
        Index_Buffer               indices;

    public:

        /*
        * Constructor que se inicializa con los indices relativos al modelo3D
        */
        Mesh(vector<int> indices);
        ~Mesh();

        /*
        * Renderiza el mesh
        */
        void render(View& view, Model3D & model);

    private:

        /*
        * Se determina si la cara se debe renderizar o no
        */
        bool is_frontface(const Vertex* const projected_vertices, const int* const indices);

    };

}

#endif
