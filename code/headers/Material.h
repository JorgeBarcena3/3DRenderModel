#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"

namespace RenderModel {


    class Material
    {

    public:

        typedef Color_Buffer_Rgba8888 Color_Buffer;
        typedef Color_Buffer::Color   Color;
       

    private:

        Color color;

    public:

        Material();
        ~Material();


    };

}

#endif
