#include "..\headers\Camera.hpp"

RenderModel::Camera::Camera(float near, float far, float fov, float aspectRatio )
{
    projection = std::shared_ptr<Projection3f>( new Projection3f(near, far, fov, aspectRatio) );
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
