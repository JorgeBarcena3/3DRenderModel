#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"


#include <cmath>
#include <cassert>
#include "..\headers\Model3D.hpp"
#include <Vector.hpp>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include "../headers/View.hpp"
#include "../headers/Mesh.h"

using namespace toolkit;


RenderModel::Model3D::Model3D(const char* path)
{

    //loadObj(path);

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


        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++)
        {
            vector< int  > meshIndices;

            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {

                int facesPoligon = shapes[s].mesh.num_face_vertices[f];

                triangles.push_back(vector<int>(facesPoligon));
                vertices_vector.push_back(vector<float>(4));


                // access to vertex
                tinyobj::index_t id_vertice = shapes[s].mesh.indices[index_offset + vertices];
                meshIndices.push_back(id_vertice.vertex_index);

                triangles[triangles.size() - 1][vertices] = (id_vertice.vertex_index);

                tinyobj::real_t vx = attrib.vertices[3 * id_vertice.vertex_index + vertices];
                tinyobj::real_t vy = attrib.vertices[3 * id_vertice.vertex_index + 1];
                tinyobj::real_t vz = attrib.vertices[3 * id_vertice.vertex_index + 2];
                vertices_vector.push_back(
                    vector<float>({
                           vx,
                           vy,
                           vz,
                           1.f
                        })
                );

                tinyobj::real_t r = attrib.colors[3 * id_vertice.vertex_index + 0];
                tinyobj::real_t g = attrib.colors[3 * id_vertice.vertex_index + 1];
                tinyobj::real_t b = attrib.colors[3 * id_vertice.vertex_index + 2];
                originalColors.push_back(
                    vector<float>({
                           175,
                           175,
                           175
                        })
                );

            }

            // Se generan los índices de los triángulos:
            size_t number_of_triangles = triangles.size();

            original_indices.resize(original_indices.size() + (number_of_triangles * 3));

            Index_Buffer::iterator indices_iterator = original_indices.begin();

            for (size_t triangle_index = 0; triangle_index < number_of_triangles; triangle_index++)
            {
                *indices_iterator++ = triangles[triangle_index][0];
                *indices_iterator++ = triangles[triangle_index][1];
                *indices_iterator++ = triangles[triangle_index][2];
            }

            //Añadimos las distintas meshes con los vertices
            meshList.push_back(new Mesh(original_indices));

            // Se cargan en un búffer los datos del array:

            size_t lastVertex = original_vertices.size();
            size_t number_of_vertices = original_vertices.size() + vertices_vector.size();

            original_vertices.resize(number_of_vertices);

            for (size_t index = lastVertex; index < number_of_vertices; index++)
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
            size_t number_of_colors = original_colors.size() + originalColors.size();

            assert(number_of_colors == number_of_vertices);             // Debe haber el mismo número
                                                                        // de colores que de vértices
            original_colors.resize(number_of_colors);

            for (size_t index = lastVertex; index < number_of_colors; index++)
            {
                original_colors[index].set((int)originalColors[index][0], (int)originalColors[index][1], (int)originalColors[index][2]);
            }


        }
    }
}

RenderModel::Model3D::~Model3D()
{
}

void RenderModel::Model3D::loadObj(const char* path)
{
    //vector< vector<float> > originalCoordinates;
    //vector< vector<float> > originalColors;
    //vector< vector<int  > > triangles;
    //vector< vector<int  > > meshIndices;

    //tinyobj::attrib_t attrib;
    //std::vector<tinyobj::shape_t> shapes;
    //std::vector<tinyobj::material_t> materials;

    //std::string warn;
    //std::string err;

    //bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path);


    //if (ret) //Colocamos los datos necesarios
    //{

    //    for (size_t i = 0; i < attrib.GetVertices().size(); i += 3)
    //    {
    //        originalCoordinates.push_back(
    //            vector<float>({
    //                attrib.vertices[i],
    //                attrib.vertices[i + 1],
    //                attrib.vertices[i + 2],
    //                }));

    //        originalColors.push_back(
    //            vector<float>({
    //               attrib.colors[i],
    //               attrib.colors[i + 1],
    //               attrib.colors[i + 2],
    //                }));
    //    }

    //    for (auto mesh : shapes)
    //    {

    //        for (int i = 0; i < mesh.mesh.indices.size(); i += 3)
    //        {
    //            triangles.push_back(
    //                vector<int>({
    //                   mesh.mesh.indices.at(i).vertex_index,
    //                   mesh.mesh.indices.at(i + 1).vertex_index,
    //                   mesh.mesh.indices.at(i + 2).vertex_index
    //                    }));

    //            meshIndices.push_back(
    //                vector<int>({
    //                   mesh.mesh.indices.at(i).vertex_index
    //                    }));

    //            meshIndices.push_back(
    //                vector<int>({
    //                   mesh.mesh.indices.at(i + 1).vertex_index
    //                    }));

    //            meshIndices.push_back(
    //                vector<int>({
    //                   mesh.mesh.indices.at(i + 2).vertex_index
    //                    }));


    //        }


    //    }

    //}
}

void RenderModel::Model3D::update(float t, View& view)
{

    //// Se actualizan los parámetros de transformatión (sólo se modifica el ángulo):

    static float angle = 0.f;

    angle += 0.025f;

    // Se crean las matrices de transformación:

    Scaling3f     scaling(0.2f);
    Rotation3f    rotation_x;
    Rotation3f    rotation_y;
    Translation3f translation(0, 0, -10);
    Projection3f  projection(5, 15, 20, float(view.width) / float(view.height));

    rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(0.50f);
    rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle);

    // Creación de la matriz de transformación unificada:

    Transformation3f transformation = projection * translation * rotation_x * rotation_y * scaling;

    // Se transforman todos los vértices usando la matriz de transformación resultante:

    for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
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

void RenderModel::Model3D::paint(View& view)
{

    for (auto mesh : meshList)
    {
        mesh->render(view, *this);
    }

}

