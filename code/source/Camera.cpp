#include "..\headers\Camera.hpp"


RenderModel::Camera::Camera(float _near, float _far, float fov, float aspectRatio, Point3f _position, Point3f _rotation)
    : transform(Transform(_position, _rotation, 1))
{
    projection = std::shared_ptr<Projection3f>( new Projection3f(_near, _far, fov, aspectRatio) );
}

RenderModel::Camera::~Camera()
{
}

void RenderModel::Camera::update(float t)
{
}

const toolkit::Projection3f RenderModel::Camera::getCameraProjection()
{
    return *projection;
}

const toolkit::Transformation3f RenderModel::Camera::getInverseTransform()
{
    return transform.getTransformation();
}
