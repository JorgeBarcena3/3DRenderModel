#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"


#include <cmath>
#include <cassert>
#include "..\headers\Model3D.hpp"
#include "..\headers\Camera.hpp"
#include <Vector.hpp>

#include "../headers/View.hpp"
#include "../headers/Mesh.h"

using namespace toolkit;


RenderModel::Model3D::Model3D(const char* _path, float _scale, Point3f _rotation, Point3f _position, shared_ptr<View> _view, shared_ptr<Model3D> _padre)
{
    loadObj(_path);

    padre = _padre;

    if (padre != nullptr)
    {
        padre->addChild(shared_ptr<Model3D>(this));
    }

    view = _view;

    scale = Scaling3f(_scale);

    rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(_rotation[0]);

    rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(_rotation[1]);

    translation = Translation3f(_position[0], _position[1], _position[2]);

    applyTransformation();
   
}


RenderModel::Model3D::~Model3D()
{
   
}

void RenderModel::Model3D::loadObj(const char* path)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path);


    if (ret) //Colocamos los datos necesarios
    {
        vector< vector<float> > vertices_vector;
        vector< vector<float> > originalColors;
        vector< vector<int  > > triangles;


        // En cada mesh añadimos los indices de sus vertices
        // Tambien guardamos los triangulos que forman sus caras
        for (int s = 0; s < shapes.size(); s++)
        {
            vector< int > meshIndices;

            // Offset de los indices de los trianguloas
            int triangleIndiceOffset = 0;

            for (int f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {

                int facesPoligon = shapes[s].mesh.num_face_vertices[f];

                triangles.push_back(vector<int>(facesPoligon));
                triangles[triangles.size() - 1][0] = (shapes[s].mesh.indices[triangleIndiceOffset++].vertex_index);
                triangles[triangles.size() - 1][1] = (shapes[s].mesh.indices[triangleIndiceOffset++].vertex_index);
                triangles[triangles.size() - 1][2] = (shapes[s].mesh.indices[triangleIndiceOffset++].vertex_index);

            }

            // Se generan los índices de los triángulos
            int number_of_triangles = triangles.size();

            Index_Buffer meshVerices(number_of_triangles * 3);


            Index_Buffer::iterator mesh_indices_iterator = meshVerices.begin();

            for (int triangle_index = 0; triangle_index < number_of_triangles; triangle_index++)
            {
                *mesh_indices_iterator++ = triangles[triangle_index][0];
                *mesh_indices_iterator++ = triangles[triangle_index][1];
                *mesh_indices_iterator++ = triangles[triangle_index][2];
            }

            //Añadimos las distintas meshes con los vertices
            meshList.push_back(shared_ptr<Mesh> (new Mesh(meshVerices)));

        }

        // Vertices, colores, normales... del modelo 3D

        int numeroVertices = attrib.GetVertices().size() / 3;
        int verticesoffset = 0;
        int colorOffset = 0;

        for (int i = 0; i < numeroVertices; i++)
        {
            vertices_vector.push_back(
                vector<float>({
                       attrib.vertices[verticesoffset++],
                       attrib.vertices[verticesoffset++],
                       attrib.vertices[verticesoffset++],
                       1.f
                    }));


            originalColors.push_back(
                vector<float>({
                      175, // attrib.colors[colorOffset++],
                      175, // attrib.colors[colorOffset++],
                      175 // attrib.colors[colorOffset++],
                    })
            );

        }

        // Se cargan en un búffer los datos del array:

        int lastVertex = original_vertices.size();
        int number_of_vertices = original_vertices.size() + vertices_vector.size();

        original_vertices.resize(number_of_vertices);

        for (int index = lastVertex; index < number_of_vertices; index++)
        {
            original_vertices[index] = Vertex({
                 vertices_vector[index].at(0),
                 vertices_vector[index].at(1),
                 vertices_vector[index].at(2),
                 vertices_vector[index].at(3)
                });
        }

        transformed_vertices.resize(number_of_vertices);
        display_vertices.resize(number_of_vertices);

        // Se definen los datos de color de los vértices:

        lastVertex = original_colors.size();
        int number_of_colors = original_colors.size() + originalColors.size();

        assert(number_of_colors == number_of_vertices);             // Debe haber el mismo número
                                                                    // de colores que de vértices
        original_colors.resize(number_of_colors);

        for (int index = lastVertex; index < number_of_colors; index++)
        {
            original_colors[index].set((int)originalColors[index][0], (int)originalColors[index][1], (int)originalColors[index][2]);
        }


    }
}

void RenderModel::Model3D::applyTransformation()
{

    Projection3f  projection(5, 15, 20, float(view->width) / float(view->height));

    // Creación de la matriz de transformación unificada:

    Transformation3f transformation = view->mainCamera.getCameraProjection() * translation * rotation_x * rotation_y * scale;

    // Se transforman todos los vértices usando la matriz de transformación resultante:

    for (int index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
    {
        // Se multiplican todos los vértices originales con la matriz de transformación y
        // se guarda el resultado en otro vertex buffer:

        Vertex& vertex = transformed_vertices[index] = Matrix44f(transformation) * Matrix41f(original_vertices[index]);

        // La matriz de proyección en perspectiva hace que el último componente del vector
        // transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

        float divisor = 1.f / vertex[3];

        vertex[0] *= divisor;
        vertex[1] *= divisor;
        vertex[2] *= divisor;
        vertex[3] = 1.f;
    }
}

void RenderModel::Model3D::addChild(shared_ptr<Model3D> child)
{
    hijos.push_back(child);
}

void RenderModel::Model3D::update(float t, View& view)
{

    applyTransformation();
   
}

void RenderModel::Model3D::paint(View& view)
{

    for (auto mesh : meshList)
    {
        mesh->render(view, *this);
    }

}

