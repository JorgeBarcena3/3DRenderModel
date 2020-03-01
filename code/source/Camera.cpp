
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "..\headers\Camera.hpp"


RenderModel::Camera::Camera(float _near, float _far, float fov, float aspectRatio, Point3f _position, Point3f _rotation)
    : transform(Transform(_position, _rotation, 1))
{
    projection = std::shared_ptr<Projection3f>(new Projection3f(_near, _far, fov, aspectRatio));
}

RenderModel::Camera::~Camera()
{
}

void RenderModel::Camera::update(float t)
{

    std::vector<float> displacement = transform.translation.getDisplacement();

    static int direction = 1;

    if (displacement[0] > 1 || displacement[0] < -1)
        direction *= -1;

    float currentPoint = 0.01f * direction;

    transform.addDisplacement(Point3f({ currentPoint , currentPoint , 0}));


}

const toolkit::Projection3f RenderModel::Camera::getCameraProjection()
{
    return *projection;
}

const toolkit::Transformation3f RenderModel::Camera::getInverseTransform()
{

    return transform.getInverseTransformation();

}
