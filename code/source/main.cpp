
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on october of 2013                                        *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../headers/View.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


using namespace sf;
using namespace RenderModel;

static const int window_width  = 800;
static const int window_height = 600;

int main ()
{
    // Create the window and the view that will be shown within the window:

    Window window(VideoMode(window_width, window_height), "3D Render Model", Style::Titlebar | Style::Close, ContextSettings(32));

    Camera camera  (5 ,15, 20, float(window_width) / float(window_height));
    View   view(window_width, window_height, camera, Point3f({0,0,0}));

    //view.addModel("Pato", Model3D("..//..//assets//models//bird//12248_Bird_v1_L2.obj", 0.01f, Point3f({ -90,0,0 }), Point3f({ 0,  0, -10 }), shared_ptr<View>(new View(view)), shared_ptr<Model3D>( nullptr)));
    view.addModel("SpiderMan", Model3D("..//..//assets//models//spider-man.obj", 0.06f, Point3f({ 0,0,0 }), Point3f({ 0,  0, -10 }), shared_ptr<View>(new View(view)), shared_ptr<Model3D>( nullptr)));
    //view.addModel("CuboHijo",  Model3D("..//..//assets//models//cube2.obj", 0.5f, Point3f({ 0,45,0 }), Point3f({ 2, 1.3, -10 }), shared_ptr<View>(new View(view)), shared_ptr<Model3D>(nullptr)));

    // Initialization:

    window.setVerticalSyncEnabled (true);

    glDisable (GL_BLEND);
    glDisable (GL_DITHER);
    glDisable (GL_CULL_FACE);
    glDisable (GL_DEPTH_TEST);
    glDisable (GL_TEXTURE_2D);

    glViewport     (0, 0, window_width, window_height);
    glMatrixMode   (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho        (0, GLdouble(window_width), 0, GLdouble(window_height), -1, 1);

    // Run the main loop:

    bool running = true;

    do
    {
        // Attend the window events:

        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

        // Update the view:

        view.update (0);

        // Repaint the view:

        view.paint ();

        // Swap the OpenGL buffers:

        window.display ();
    }
    while (running);

    // Close the application:

    return (EXIT_SUCCESS);
}
