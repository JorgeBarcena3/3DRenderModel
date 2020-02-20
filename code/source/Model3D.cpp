#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"


#include <cmath>
#include <cassert>
#include <math.h>
#include <Vector.hpp>
#include "..\headers\Model3D.hpp"
#include "..\headers\Camera.hpp"
#include "../headers/View.hpp"
#include "../headers/Mesh.h"
#include "../headers/Material.h"
#include "../headers/Math.hpp"

using namespace toolkit;

RenderModel::Model3D::Model3D(const char* _path, float _scale, Point3f _rotation, Point3f _position, shared_ptr<View> _view, shared_ptr<Model3D> _padre)
    : transform ( Transform(_position, _rotation, _scale) )
{
    loadObj(_path);

    parent = _padre;

    if (parent != nullptr)
    {
        parent->addChild(shared_ptr<Model3D>(this));
    }

    view = _view;   

    applyTransformation();

}

RenderModel::Model3D::~Model3D()
{

}

void RenderModel::Model3D::setUpdateFunction(std::function<void(Transform*)> _UpdateFunction)
{

    UpdateFunction = _UpdateFunction;
}

void RenderModel::Model3D::loadObj(const char* path)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    string mtlPath = path;

    if (mtlPath.find_last_of("/\\") != std::string::npos)
        mtlPath = mtlPath.substr(0, mtlPath.find_last_of("/\\"));
    else
        mtlPath = ".";


    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path, mtlPath.c_str());


    if (ret) //Colocamos los datos necesarios
    {
        vector< vector<float> > vertices_vector;
        vector< vector<float> > normals_vector;
        vector< vector<float> > originalColors;
        vector< vector<int  > > trianglesIndex;
        vector< vector<int  > > normalsIndex;

        //Añadimos los materiales
        for (int m = 0; m < materials.size(); m++)
        {
            Color Ka, Kd, Ke, Ks;
            Ka.set(materials[m].ambient[0], materials[m].ambient[1], materials[m].ambient[2]);
            Kd.set(materials[m].diffuse[0], materials[m].diffuse[1], materials[m].diffuse[2]);
            Ke.set(materials[m].emission[0], materials[m].emission[1], materials[m].emission[2]);
            Ks.set(materials[m].specular[0], materials[m].specular[1], materials[m].specular[2]);

            material_list.push_back(shared_ptr<Material>(new Material(Ka, Kd, Ks, Ke)));
        }

        // En cada mesh añadimos los indices de sus vertices
        // Tambien guardamos los triangulos que forman sus caras
        for (int s = 0; s < shapes.size(); s++)
        {
            vector<int> meshIndices;
            vector<int> materialIndices;

            // Offset de los indices de los trianguloas
            int triangleIndiceOffset = 0;
            int normalsIndiceOffset = 0;

            for (int f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {

                int facesPoligon = shapes[s].mesh.num_face_vertices[f];

                trianglesIndex.push_back(vector<int>(facesPoligon));
                trianglesIndex[trianglesIndex.size() - 1][0] = (shapes[s].mesh.indices[triangleIndiceOffset++].vertex_index);
                trianglesIndex[trianglesIndex.size() - 1][1] = (shapes[s].mesh.indices[triangleIndiceOffset++].vertex_index);
                trianglesIndex[trianglesIndex.size() - 1][2] = (shapes[s].mesh.indices[triangleIndiceOffset++].vertex_index);

                normalsIndex.push_back(vector<int>(facesPoligon));
                normalsIndex[normalsIndex.size() - 1][0] = (shapes[s].mesh.indices[normalsIndiceOffset++].normal_index);
                normalsIndex[normalsIndex.size() - 1][1] = (shapes[s].mesh.indices[normalsIndiceOffset++].normal_index);
                normalsIndex[normalsIndex.size() - 1][2] = (shapes[s].mesh.indices[normalsIndiceOffset++].normal_index);

                materialIndices.push_back(shapes[s].mesh.material_ids[f]);

            }

            // Se generan los índices de los triángulos
            int number_of_triangles = trianglesIndex.size();

            Index_Buffer meshVerices(number_of_triangles * (int)3);
            Index_Buffer meshNormals(number_of_triangles * (int)3);

            Index_Buffer::iterator mesh_indices_iterator = meshVerices.begin();
            Index_Buffer::iterator mesh_normals_indices_iterator = meshNormals.begin();

            for (int triangle_index = 0; triangle_index < number_of_triangles; triangle_index++)
            {
                *mesh_indices_iterator++ = trianglesIndex[triangle_index][0];
                *mesh_indices_iterator++ = trianglesIndex[triangle_index][1];
                *mesh_indices_iterator++ = trianglesIndex[triangle_index][2];

                *mesh_normals_indices_iterator++ = normalsIndex[triangle_index][0];
                *mesh_normals_indices_iterator++ = normalsIndex[triangle_index][1];
                *mesh_normals_indices_iterator++ = normalsIndex[triangle_index][2];
            }


            //Añadimos las distintas meshes con los vertices
            meshList.push_back(shared_ptr<Mesh>(new Mesh(meshVerices, meshNormals, materialIndices)));

            // Vertices, colores, normales... del modelo 3D

            int numeroVertices = attrib.GetVertices().size() / 3;
            int verticesoffset = 0;
            int normalsOffset = 0;
            int colorOffset = 0;

            for (int i = 0; i < numeroVertices; i++)
            {

                tinyobj::index_t idx = shapes[s].mesh.indices[normalsOffset + i];

                vertices_vector.push_back(
                    vector<float>({
                           attrib.vertices[verticesoffset++],
                           attrib.vertices[verticesoffset++],
                           attrib.vertices[verticesoffset++],
                           1.f
                        }));


                original_normals.push_back(
                    Point4f({
                           attrib.normals[3 * idx.normal_index + 0],
                           attrib.normals[3 * idx.normal_index + 1],
                           attrib.normals[3 * idx.normal_index + 2],
                           1.f
                        }));



                originalColors.push_back(
                    vector<float>({
                          floorf(rand() % (255 - 1) + 1) , // attrib.colors[colorOffset++],
                          floorf(rand() % (255 - 1) + 1) , // attrib.colors[colorOffset++],
                          floorf(rand() % (255 - 1) + 1) // attrib.colors[colorOffset++],
                        })
                );


                normalsOffset += 3;

            }

            transformed_normals.resize(original_normals.size());
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
            transformed_colors.resize(number_of_colors);

            for (int index = lastVertex; index < number_of_colors; index++)
            {
                original_colors[index].set((int)originalColors[index][0], (int)originalColors[index][1], (int)originalColors[index][2]);
            }

        }


    }
}

void RenderModel::Model3D::applyTransformation()
{
    Transformation3f transformation = view->mainCamera.getCameraProjection()
                    * getTransformation();

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

        //Normales
        Vertex& Normalvertex = transformed_normals[index] = Matrix44f(transformation) * Matrix41f(original_normals[index]);

        divisor = 1.f / Normalvertex[3];
        Normalvertex[0] *= divisor;
        Normalvertex[1] *= divisor;
        Normalvertex[2] *= divisor;
        Normalvertex[3] = 1.f;

        transformed_colors[index] = getColor(index);
       
    }

}

void RenderModel::Model3D::addChild(shared_ptr<Model3D> child)
{
    childs.push_back(child);
}

void RenderModel::Model3D::update(float t, View& view)
{

    if (UpdateFunction)
        UpdateFunction(&transform);
    

    applyTransformation();

}

void RenderModel::Model3D::paint(View& view)
{
    for (int index = 0; index < transformed_colors.size(); index++)
    {
        transformed_colors[index] = getColor(index);
    }

    for (auto mesh : meshList)
    {
        mesh->render(view, *this);
    }

}


RenderModel::Model3D::Color RenderModel::Model3D::getColor(int indice)
{

    vec3f vecColor;

    if (original_normals.size() > 0)
    {

        vec3f N = vec3<float>::toVec3f(transformed_normals[indice]).normalize();
        vec3f L = (vec3<float>::toVec3f(transformed_vertices[indice]) - vec3<float>::toVec3f(view->lightPosition)).normalize();
        vecColor = vec3<float>::toVec3f(original_colors[indice]);

        if (material_list.size() > 0)
            vecColor *= material_list[0]->Kd.data.component.r;

        vecColor *= std::max(0.f, dot(N, L));

    }
    else
    {
        vecColor = vec3<float>::toVec3f(original_colors[indice]);
    }

    Model3D::Color myColor;
    myColor.set((float)vecColor.r, (float)vecColor.g, (float)vecColor.b);

    return myColor;

}

Transformation3f RenderModel::Model3D::getTransformation()
{
    Transformation3f myTransform = transform.getTransformation();

    if (parent)
    {
        return parent->getTransformation() * myTransform;
    }

    return myTransform;
}

