#include "..\headers\Camera.hpp"

RenderModel::Camera::Camera(float near, float far, float fov, float aspectRatio )
{
    projection = new Projection3f(near, far, fov, aspectRatio);
}

void RenderModel::Camera::update(float t)
{
}

const toolkit::Projection3f RenderModel::Camera::getCameraProjection()
{
    return *projection;
}
