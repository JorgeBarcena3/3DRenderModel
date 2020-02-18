
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COLOR_BUFFER_HEADER
#define COLOR_BUFFER_HEADER

    namespace RenderModel
    {
        class Color_Buffer
        {
        protected:

            int width;
            int height;

        public:

            Color_Buffer(int width, int height)
            :
                width (width ),
                height(height)
            {
            }

        public:

            int get_width () const
            {
                return (width);
            }

            int get_height () const
            {
                return (height);
            }

            int offset_at (int x, int y) const
            {
                return (y * width + x);
            }

        public:

            virtual int  bits_per_color () const = 0;
            virtual void set_color      (int r, int  g, int b) = 0;
            virtual void set_pixel      (int x, int  y) = 0;
            virtual void set_pixel      (int offset) = 0;
            virtual void gl_draw_pixels (int raster_x, int raster_y) const = 0;

        };

    }

#endif
