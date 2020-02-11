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


RenderModel::Model3D::Model3D(int _vertices[][4], int _colors[][3], int _triangles[][3])
{
    static const int vertices[][4] =
    {
        { -4, -4, +4, 1 },      // 0   // v�rtices del cubo
        { +4, -4, +4, 1 },      // 1
        { +4, +4, +4, 1 },      // 2
        { -4, +4, +4, 1 },      // 3
        { -4, -4, -4, 1 },      // 4
        { +4, -4, -4, 1 },      // 5
        { +4, +4, -4, 1 },      // 6
        { -4, +4, -4, 1 },      // 7
        { -5, -5,  0, 1 },      // 8    // v�rtices de los pol�gonos cortantes
        { +5, -5,  0, 1 },      // 9
        { +5, +5,  0, 1 },      // 10
        { -5, +5,  0, 1 },      // 11
        {  0, -5, +5, 1 },      // 12
        {  0, +5, +5, 1 },      // 13
        {  0, +5, -5, 1 },      // 15
        {  0, -5, -5, 1 },      // 14
    };

    // Se cargan en un b�ffer los datos del array:

    size_t number_of_vertices = sizeof(vertices) / sizeof(int) / 4;

    original_vertices.resize(number_of_vertices);

    for (size_t index = 0; index < number_of_vertices; index++)
    {
        original_vertices[index] = Vertex(vertices[index]);
    }

  
    transformed_vertices.resize(number_of_vertices);
    display_vertices.resize(number_of_vertices);

    // Se definen los datos de color de los v�rtices:

    static const int colors[][3] =
    {
        { 255,   0,   0 },      // 0
        {   0, 255,   0 },      // 1
        {   0,   0, 255 },      // 2
        {   0,   0, 255 },      // 3
        { 255, 255,   0 },      // 4
        { 255,   0, 255 },      // 5
        { 255,   0,   0 },      // 6
        { 255,   0,   0 },      // 7
        { 175, 175, 175 },      // 8
        { 175, 175, 175 },      // 9
        { 175, 175, 175 },      // 10
        { 175, 175, 175 },      // 11
        { 225, 225, 225 },      // 12
        { 225, 225, 225 },      // 13
        { 225, 225, 225 },      // 14
        { 225, 225, 225 },      // 15
    };

    size_t number_of_colors = sizeof(colors) / sizeof(int) / 3;

    assert(number_of_colors == number_of_vertices);             // Debe haber el mismo n�mero
                                                                // de colores que de v�rtices
    original_colors.resize(number_of_colors);

    for (size_t index = 0; index < number_of_colors; index++)
    {
        original_colors[index].set(colors[index][0], colors[index][1], colors[index][2]);
    }

    // Se generan los �ndices de los tri�ngulos:

    static const int triangles[][3] =
    {
        {  0,  1,  2 },         // cube front
        {  0,  2,  3 },
        {  4,  0,  3 },         // cube left
        {  4,  3,  7 },
        {  5,  4,  7 },         // cube back
        {  5,  7,  6 },
        {  1,  5,  6 },         // cube right
        {  1,  6,  2 },
        {  3,  2,  6 },         // cube top
        {  3,  6,  7 },
        {  0,  4,  5 },         // cube bottom
        {  0,  5,  1 },
        {  8,  9, 10 },         // middle frontface
        {  8, 10, 11 },
        { 10,  9,  8 },         // middle backface
        { 11, 10,  8 },
        { 12, 13, 14 },         // middle leftface
        { 12, 14, 15 },
        { 14, 13, 12 },         // middle rightface
        { 15, 14, 12 },
    };

    size_t number_of_triangles = sizeof(triangles) / sizeof(int) / 3;

    original_indices.resize(number_of_triangles * 3);

    Index_Buffer::iterator indices_iterator = original_indices.begin();   

    for (size_t triangle_index = 0; triangle_index < number_of_triangles; triangle_index++)
    {
        *indices_iterator++ = triangles[triangle_index][0];
        *indices_iterator++ = triangles[triangle_index][1];
        *indices_iterator++ = triangles[triangle_index][2];
    }

    //A�adimos las distintas meshes con los vertices
    meshList.push_back(new Mesh(original_indices));

}

RenderModel::Model3D::~Model3D()
{
}

void RenderModel::Model3D::update(float t, View& view)
{

    //// Se actualizan los par�metros de transformati�n (s�lo se modifica el �ngulo):

    static float angle = 0.f;

    angle += 0.025f;

    // Se crean las matrices de transformaci�n:

    Scaling3f     scaling(0.2f);
    Rotation3f    rotation_x;
    Rotation3f    rotation_y;
    Translation3f translation(0, 0, -10);
    Projection3f  projection(5, 15, 20, float(view.width) / float(view.height));

    rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(0.50f);
    rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle);

    // Creaci�n de la matriz de transformaci�n unificada:

    Transformation3f transformation = projection * translation * rotation_x * rotation_y * scaling;

    // Se transforman todos los v�rtices usando la matriz de transformaci�n resultante:

    for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
    {
        // Se multiplican todos los v�rtices originales con la matriz de transformaci�n y
        // se guarda el resultado en otro vertex buffer:

        Vertex& vertex = transformed_vertices[index] = Matrix44f(transformation) * Matrix41f(original_vertices[index]);

        // La matriz de proyecci�n en perspectiva hace que el �ltimo componente del vector
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

