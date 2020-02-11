#ifndef MODEL3D_HEADER
#define MODEL3D_HEADER


#include <vector>
#include <memory>
#include "Point.hpp"
#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"

namespace RenderModel {

    using std::shared_ptr;
    using std::unique_ptr;
    using std::vector;
    using toolkit::Point4i;
    using toolkit::Point4f;
    class View;
    class Mesh;
    class View;

    class Model3D
    {

    public:

        typedef Color_Buffer_Rgba8888 Color_Buffer;
        typedef Color_Buffer::Color   Color;
        typedef Point4f               Vertex;
        typedef vector< Vertex >      Vertex_Buffer;
        typedef vector< int    >      Index_Buffer;
        typedef vector< Color  >      Vertex_Colors;

    public:

        Vertex_Buffer      original_vertices;
        Index_Buffer       original_indices;
        Vertex_Colors      original_colors;
        Vertex_Buffer      transformed_vertices;
        vector< Point4i  > display_vertices;

        vector< Mesh * > meshList;


    public:

        Model3D(int vertices[][4], int colors[][3], int triangles[][3]);
        ~Model3D();

        void update(float t, View& view);
        void paint(View& view);  
        

    };

}

#endif
