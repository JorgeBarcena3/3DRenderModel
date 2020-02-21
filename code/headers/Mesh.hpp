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

    class Mesh
    {

    public:

        typedef Model3D::Index_Buffer Index_Buffer;
        typedef Model3D::Color        Color;
        typedef Point4f               Vertex;


    private:

        Index_Buffer               indices;

    public:

        Mesh(vector<int> indices);
        ~Mesh();

        void render(View& view, Model3D & model);

    private:

        bool is_frontface(const Vertex* const projected_vertices, const int* const indices);

    };

}

#endif
