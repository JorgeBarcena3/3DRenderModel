
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "..\headers\DirectionalLight.hpp"

RenderModel::DirectionalLight::DirectionalLight(Point3f _position, Color _color) :
    Light(_position, _color)
{
}

toolkit::Point4f RenderModel::DirectionalLight::getDirection(toolkit::Point4f pointInWorld)
{
    return Point4f({ position[0], position[1], position[2], 0 });
}
