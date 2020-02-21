#include "..\headers\Material.hpp"


RenderModel::Material::Material(Model3D::Color _ka, Model3D::Color  _kd, Model3D::Color  _ks, Model3D::Color  _ke) :
    Ka(_ka),
    Kd(_kd),
    Ks(_ks),
    Ke(_ke)
{
}

RenderModel::Material::~Material()
{
}
