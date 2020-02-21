#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include "Model3D.hpp"

namespace RenderModel {


    class Material
    {

    public:


    public:

        
        Model3D::Color Ka;
        
        Model3D::Color Kd;
        
        Model3D::Color Ks;
        
        Model3D::Color Ke;

    public:

        Material(Model3D::Color _ka, Model3D::Color _kd, Model3D::Color _ks, Model3D::Color _ke);
        ~Material();


    };

}

#endif
