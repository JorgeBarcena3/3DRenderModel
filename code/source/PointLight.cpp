
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "..\headers\PointLight.hpp"
#include "..\headers\Math.hpp"

RenderModel::PointLight::PointLight(Point3f _position, Color _color) :
    Light(_position, _color)
{
}

toolkit::Point4f RenderModel::PointLight::getDirection(toolkit::Point4f pointInWorld)
{

    return Point4f({
        pointInWorld[0] - position[0],
        pointInWorld[1] - position[1],
        pointInWorld[2] - position[2]
        });

}
