#include "..\headers\Mesh.h"
#include "..\headers\View.hpp"
#include "..\headers\Math.hpp"
#include "..\headers\Model3D.hpp"
#include "..\headers\Material.h"
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include <algorithm>


using namespace toolkit;

RenderModel::Mesh::Mesh(vector<int>_meshIndices, vector<int> _normalIndices, vector<int>  material) :
    meshIndices(_meshIndices),
    normalIndices(_normalIndices),
    materialIndices(material)
{
}

RenderModel::Mesh::~Mesh()
{
}

void RenderModel::Mesh::render(View& view, Model3D& model)
{
    // Se convierten las coordenadas transformadas y proyectadas a coordenadas
       // de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
       // La coordenada Z se escala a un valor suficientemente grande dentro del
       // rango de int (que es lo que espera fill_convex_polygon_z_buffer).

    Scaling3f        scaling = Scaling3f(float(view.width / 2), float(view.height / 2), 100000000.f);
    Translation3f    translation = Translation3f(float(view.width / 2), float(view.height / 2), 0.f);
    Transformation3f transformation = translation * scaling;

    for (int i = 0; i < meshIndices.size(); i++)
    {
        model.display_vertices[meshIndices.at(i)] = Point4i(Matrix44f(transformation) * Matrix41f(model.transformed_vertices[meshIndices.at(i)]));
    }


    for (int* indices = meshIndices.data(), *end = indices + meshIndices.size(); indices < end; indices += 3)
    {
        if (is_frontface(model.transformed_vertices.data(), indices))
        {
            // A�adimos el recorte
            if (view.cutout(model.display_vertices.data(), indices, indices + 3))
            {

                // Se establece el color del pol�gono a partir del color de su primer v�rtice:
                view.rasterizer.set_color(getColor(view, &model, indices));

                // Se rellena el pol�gono:
                view.rasterizer.fill_convex_polygon_z_buffer(model.display_vertices.data(), indices, indices + 3);

            }

        }

    }

}

bool RenderModel::Mesh::is_frontface(const Vertex* const projected_vertices, const int* const indices)
{
    const Vertex& v0 = projected_vertices[indices[0]];
    const Vertex& v1 = projected_vertices[indices[1]];
    const Vertex& v2 = projected_vertices[indices[2]];

    // Se asumen coordenadas proyectadas y pol�gonos definidos en sentido horario.
    // Se comprueba a qu� lado de la l�nea que pasa por v0 y v1 queda el punto v2:

    return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) > 0.f);
}

RenderModel::Mesh::Color RenderModel::Mesh::getColor(View& view, Model3D* model, int* indices)
{

    vec3f vecColor;

    if (model->original_normals.size() > 0)
    {

        vec3f N = vec3<float>::toVec3f((*model).original_normals[normalIndices[*indices]]).normalize();
        vec3f L = (vec3<float>::toVec3f((*model).transformed_vertices[*indices]) - vec3<float>::toVec3f(view.lightPosition)).normalize();
        vecColor = vec3<float>::toVec3f(model->original_colors[*indices]);

        if (model->material_list.size() > 0)
            vecColor *= model->material_list[materialIndices[*indices]]->Kd.data.component.r;

        vecColor *= std::max(0.f, dot(N, L));



    }
    else
    {
        vecColor = vec3<float>::toVec3f(model->original_colors[*indices]);

    }


    Model3D::Color myColor;
    myColor.set((float)vecColor.r, (float)vecColor.g, (float)vecColor.b);

    return myColor;
   
}
