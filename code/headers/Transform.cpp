#include "Transform.hpp"

RenderModel::Transform::Transform(Point3f _position, Point3f _rotation, float _scale)
{
    scale = Scaling3f(_scale);

    rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(_rotation[0]);

    rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(_rotation[1]);

    rotation_z.set< Rotation3f::AROUND_THE_Z_AXIS >(_rotation[2]);

    translation = Translation3f(_position[0], _position[1], _position[2]);
}

const toolkit::Transformation3f RenderModel::Transform::getTransformation()
{
    return (translation * rotation_x * rotation_y * rotation_z * scale);
}
