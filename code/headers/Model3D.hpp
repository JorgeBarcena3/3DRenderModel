#ifndef MODEL3D_HEADER
#define MODEL3D_HEADER


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

    using std::shared_ptr;
    using std::unique_ptr;
    using std::vector;
    using toolkit::Point4f;
    using toolkit::Point4i;
    using toolkit::Point3f;
    using toolkit::Scaling3f;
    using toolkit::Rotation3f;
    using toolkit::Translation3f;
    class View;
    class Mesh;
    class View;
    class Material;

    /*
    * Clase que va a manejar un modelo 3D
    */
    class Model3D
    {

    public:

        typedef Color_Buffer_Rgba8888            Color_Buffer;
        typedef Color_Buffer::Color              Color;
        typedef Point4f                          Vertex;
        typedef vector< Vertex >                 Vertex_Buffer;
        typedef vector<int    >                 Index_Buffer;
        typedef vector< Color  >                 Vertex_Colors;
        typedef vector< Point3f  >               Normals_Buffer;
        typedef vector< shared_ptr<Material> >   Materials_Buffer;

        /*
        * La clase Mesh puede acceder a las variables privadas del modelo3D
        */
        friend class Mesh;

    private:

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

        /*
        * Vertices originales del modelo
        */
        Vertex_Buffer      original_vertices;

        /*
        * Normales del modelo
        */
        Normals_Buffer      original_normals;

        /*
        * Normales del modelo
        */
        Materials_Buffer    material_list;

        /*
        * Colores originales
        */
        Vertex_Colors      original_colors;

        /*
        * Vertices despues de aplicarles X transformacion
        */
        Vertex_Buffer      transformed_vertices;

        /*
        * Vertices de la pantalla
        */
        vector< Point4i  > display_vertices;

        /*
        * Lista de mesh que componen el modelo
        */
        vector< shared_ptr< Mesh > > meshList;

        /*
        * Referencia a la vista a la que pertenece el modelo
        */
        shared_ptr< View >     view;

        /*
        * Padre de la del modelo 3D
        */
        shared_ptr<Model3D>   padre;

    public:

        /*
        * Hijos que contiene el modelo 3D
        */
        vector<shared_ptr<Model3D>>   hijos;


    public:

        Model3D(const char* path, float scale, Point3f rotation, Point3f position, shared_ptr<View> view, shared_ptr<Model3D> padre);
        ~Model3D();

        void loadObj(const char* path);
        void applyTransformation();
        void addChild(shared_ptr<Model3D> child);
        void update(float t, View& view);
        void paint(View& view);


    };

}

#endif
