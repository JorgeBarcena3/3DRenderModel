
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "..\headers\Material.hpp"


RenderModel::Material::Material(Model3D::Color _ka, Model3D::Color  _kd, Model3D::Color  _ks) :
    Ka(_ka),
    Kd(_kd),
    Ks(_ks)
{
}

RenderModel::Material::~Material()
{
}
