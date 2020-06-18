
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"


#include <cmath>
#include <cassert>
#include <math.h>
#include <Vector.hpp>
#include "..\headers\Model3D.hpp"
#include "..\headers\Camera.hpp"
#include "..\headers\View.hpp"
#include "..\headers\Mesh.hpp"
#include "..\headers\Material.hpp"
#include "..\headers\PointLight.hpp"
#include "..\headers\Math.hpp"


using namespace toolkit;

RenderModel::Model3D::Model3D(const char* _path, float _scale, Point3f _rotation, Point3f _position, View& _view, Model3D * _padre)
    : transform(Transform(_position, _rotation, _scale))
{
    loadObj(_path);

    parent = _padre;

    if (parent != nullptr)
    {
        parent->addChild(this);
    }

    applyTransformation(_view);

}

RenderModel::Model3D::~Model3D()
{
    for (size_t i = 0; i < childs.size(); i++)
    {
        delete childs[i];
        
    } 
 
}

void RenderModel::Model3D::setUpdateFunction(std::function<void(Model3D*)> _UpdateFunction)
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
        if (attrib.normals.size() == 0) throw "Este modelo no tiene normales";
        if (attrib.vertices.size() == 0) throw "Este modelo no tiene vertices";
        if (attrib.colors.size() == 0) throw "Este modelo no tiene colores";

        //Añadimos los materiales si los hay
        for (int m = 0; m < materials.size(); m++)
        {
            Color Ka, Kd, Ks;
            Ka.set((int)(materials[m].ambient[0] * 255), (int)(materials[m].ambient[1] * 255), (int)(materials[m].ambient[2] * 255));
            Kd.set((int)(materials[m].diffuse[0] * 255), (int)(materials[m].diffuse[1] * 255), (int)(materials[m].diffuse[2] * 255));
            Ks.set((int)(materials[m].specular[0] * 255), (int)(materials[m].specular[1] * 255), (int)(materials[m].specular[2] * 255));

            material_list.push_back(shared_ptr<Material>(new Material(Ka, Kd, Ks)));
        }

        if (materials.size() == 0)
        {
            Color Ka, Kd, Ks;
            Ka.set(175, 175, 175);
            Kd.set(175, 175, 175);
            Ks.set(175, 175, 175);

            material_list.push_back(shared_ptr<Material>(new Material(Ka, Kd, Ks)));
        }


        // Offset de los indices de los triangulos
        int indexOffset = 0;

        // En cada mesh añadimos los indices de sus vertices
        // Tambien guardamos los triangulos que forman sus caras
        for (int s = 0; s < shapes.size(); s++)
        {
            vector<int> indices;
            vector<int> materialIndices;

            indices.resize(shapes[s].mesh.indices.size());


            for (int index = 0, matIndex = 0; index < indices.size(); index++)
            {
                int vertexIndex = shapes[s].mesh.indices[index].vertex_index;
                int normalIndex = shapes[s].mesh.indices[index].normal_index;

                if (index % 3 == 0 && index != 0)
                    matIndex++;

                int materialIndex = shapes[s].mesh.material_ids[matIndex] == -1 ? 0 : shapes[s].mesh.material_ids[matIndex];

                /*********
                 VERTICES
                *********/
                original_vertices.push_back(
                    Vertex({
                           attrib.vertices[3 * vertexIndex + 0],
                           attrib.vertices[3 * vertexIndex + 1],
                           attrib.vertices[3 * vertexIndex + 2],
                           1.f
                        }));

                /*********
                 NORMALES
                *********/
                original_normals.push_back(
                    Point4f({
                           attrib.normals[3 * normalIndex + 0],
                           attrib.normals[3 * normalIndex + 1],
                           attrib.normals[3 * normalIndex + 2],
                           0
                        }));

                /*********
                 COLORES
                *********/
                original_colors.push_back(Color());
                original_colors[original_colors.size() - 1].set(
                    material_list[materialIndex]->Kd.data.component.r, //(int)floor(rand() % (255 - 1) + 1) , // attrib.colors[colorOffset++] * 255,
                    material_list[materialIndex]->Kd.data.component.g, //(int)floor(rand() % (255 - 1) + 1) , // attrib.colors[colorOffset++] * 255,
                    material_list[materialIndex]->Kd.data.component.b  //(int)floor(rand() % (255 - 1) + 1) //    attrib.colors[colorOffset++] * 255,

                );


                indices[index] = indexOffset + index;
            }

            indexOffset += (int)indices.size();

            //Añadimos las distintas meshes con los vertices
            meshList.push_back(shared_ptr<Mesh>(new Mesh(indices)));


            //Reajustamos los size de los arrays
            transformed_normals.resize(original_normals.size());
            transformed_vertices.resize(original_vertices.size());
            display_vertices.resize(original_vertices.size());
            transformed_colors.resize(original_colors.size());

        }

    }
}

void RenderModel::Model3D::applyTransformation(View& view)
{
    Transformation3f transformation = view.mainCamera.getCameraProjection()
        * view.mainCamera.getInverseTransform()
        * getTransformation();

    // Se transforman todos los vértices usando la matriz de transformación resultante:

    for (int index = 0, number_of_vertices = (int)original_vertices.size(); index < number_of_vertices; index++)
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

    }

}

void RenderModel::Model3D::addChild(Model3D * child)
{
    childs.push_back(child);
}

void RenderModel::Model3D::update(float t, View& view)
{

    if (UpdateFunction)
        UpdateFunction(this);


    applyTransformation(view);

}

void RenderModel::Model3D::paint(View& view)
{
    for (int index = 0; index < transformed_colors.size(); index++)
    {
        transformed_colors[index] = getIluminatedColor(index, view);
    }

    for (auto mesh : meshList)
    {
        mesh->render(view, *this);
    }

}


RenderModel::Model3D::Color RenderModel::Model3D::getIluminatedColor(int indice, View& view)
{

    vec3f N = vec3<float>::toVec3f(transformed_normals[indice]).normalize();
    vec3f L = vec3<float>::toVec3f(view.Light->getDirection(transformed_vertices[indice])).normalize();
    vec3f vecColor = vec3<float>::toVec3f(original_colors[indice]);

    vecColor *= std::max(0.f, dot(N, L));

    Model3D::Color myColor;
    myColor.set((int)vecColor.r, (int)vecColor.g, (int)vecColor.b);

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

