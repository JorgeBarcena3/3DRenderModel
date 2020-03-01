
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "..\headers\Transform.hpp"
#include "..\headers\Translation.hpp"
#include "..\headers\Math.hpp"
#include <math.h>


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
    Transformation3f T = Transformation3f();
    T = T * translation;
    T = T * rotation_x * rotation_y * rotation_z;
    T = T * scale;

    return T;
}

const toolkit::Transformation3f RenderModel::Transform::getInverseTransformation()
{
    Transformation3f T = getTransformation();

    toolkit::Transformation3f::Matrix m = T.matrix;

    float A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
    float A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
    float A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
    float A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
    float A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
    float A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
    float A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
    float A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
    float A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
    float A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
    float A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
    float A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    float A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
    float A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
    float A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
    float A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
    float A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
    float A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

    float det = m[0][0] * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223)
        - m[0][1] * (m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223)
        + m[0][2] * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123)
        - m[0][3] * (m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);

    det = 1 / det;

    toolkit::Transformation3f::Matrix minv;

    minv[0][0] = det * (minv[1][1] * A2323 - minv[1][2] * A1323 + minv[1][3] * A1223);
    minv[0][1] = det * -(minv[0][1] * A2323 - minv[0][2] * A1323 + minv[0][3] * A1223);
    minv[0][2] = det * (minv[0][1] * A2313 - minv[0][2] * A1313 + minv[0][3] * A1213);
    minv[0][3] = det * -(minv[0][1] * A2312 - minv[0][2] * A1312 + minv[0][3] * A1212);
    minv[1][0] = det * -(minv[1][0] * A2323 - minv[1][2] * A0323 + minv[1][3] * A0223);
    minv[1][1] = det * (minv[0][0] * A2323 - minv[0][2] * A0323 + minv[0][3] * A0223);
    minv[1][2] = det * -(minv[0][0] * A2313 - minv[0][2] * A0313 + minv[0][3] * A0213);
    minv[1][3] = det * (minv[0][0] * A2312 - minv[0][2] * A0312 + minv[0][3] * A0212);
    minv[2][0] = det * (minv[1][0] * A1323 - minv[1][1] * A0323 + minv[1][3] * A0123);
    minv[2][1] = det * -(minv[0][0] * A1323 - minv[0][1] * A0323 + minv[0][3] * A0123);
    minv[2][2] = det * (minv[0][0] * A1313 - minv[0][1] * A0313 + minv[0][3] * A0113);
    minv[2][3] = det * -(minv[0][0] * A1312 - minv[0][1] * A0312 + minv[0][3] * A0112);
    minv[3][0] = det * -(minv[1][0] * A1223 - minv[1][1] * A0223 + minv[1][2] * A0123);
    minv[3][1] = det * (minv[0][0] * A1223 - minv[0][1] * A0223 + minv[0][2] * A0123);
    minv[3][2] = det * -(minv[0][0] * A1213 - minv[0][1] * A0213 + minv[0][2] * A0113);
    minv[3][3] = det * (minv[0][0] * A1212 - minv[0][1] * A0212 + minv[0][2] * A0112);

    return Transformation3f(minv);
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
