#include "..\headers\Mesh.hpp"
#include "..\headers\View.hpp"
#include "..\headers\Model3D.hpp"
#include "..\headers\Material.hpp"
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include <algorithm>


using namespace toolkit;

RenderModel::Mesh::Mesh(vector<int> _indices) :
    indices(_indices)
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

    for (int i = 0; i < indices.size(); i++)
    {
        model.display_vertices[indices.at(i)] = Point4i(Matrix44f(transformation) * Matrix41f(model.transformed_vertices[indices.at(i)]));
    }


    for (int* index = indices.data(), *end = index + indices.size(); index < end; index += 3)
    {
        if (is_frontface(model.transformed_vertices.data(), index))
        {
            vector< Point4i > display_vertices_clipped = view.clip(model.display_vertices.data(), index, index + 3);

            // Se establece el color del polígono a partir del color de su primer vértice:
            view.rasterizer.set_color(model.transformed_colors[*index]);

            // Se rellena el polígono:
            const int clipIndice[] = { 0,1,2,3,4,5,6,7,8,9 };

            if (display_vertices_clipped.size() > 0)
                view.rasterizer.fill_convex_polygon_z_buffer(display_vertices_clipped.data(), clipIndice, clipIndice + display_vertices_clipped.size());

        }

    }

}

bool RenderModel::Mesh::is_frontface(const Vertex* const projected_vertices, const int* const indices)
{
    const Vertex& v0 = projected_vertices[indices[0]];
    const Vertex& v1 = projected_vertices[indices[1]];
    const Vertex& v2 = projected_vertices[indices[2]];

    // Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
    // Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

    return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) > 0.f);
}