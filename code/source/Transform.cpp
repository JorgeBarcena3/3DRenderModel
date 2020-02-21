#include "../headers/Transform.hpp"
#include <math.h>
#define PI 3.14159265359f

RenderModel::Transform::Transform(Point3f _position, Point3f _rotation, float _scale)
{
    scale = Scaling3f(_scale);

    rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(_rotation[0] * PI / 180);

    rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(_rotation[1] * PI / 180);

    rotation_z.set< Rotation3f::AROUND_THE_Z_AXIS >(_rotation[2] * PI / 180);

    translation = Translation3f(_position[0], _position[1], _position[2]);
}

const toolkit::Transformation3f RenderModel::Transform::getTransformation()
{
    Transformation3f rotation = rotation_z * rotation_y * rotation_x;

    return (translation * scale * rotation);
}

void RenderModel::Transform::addDisplacement(Point3f displacememnt)
{
    std::vector<float> displacement = translation.getDisplacement();
    translation.set(toolkit::Vector3f({ 
        displacement[0] + displacememnt[0],
        displacement[1] + displacememnt[1],
        displacement[2] + displacememnt[2] 
        })
    );
}
