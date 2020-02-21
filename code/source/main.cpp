
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on october of 2013                                        *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// CAMARA UPDATE
// SOLO FUNCIONA EN RELEASE
// JERARQUIA DE ESCENA

#include "../headers/View.hpp"
#include "../headers/PointLight.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


using namespace sf;
using namespace RenderModel;

static const int window_width = 800;
static const int window_height = 600;

void rotateUpdate(Transform* transform)
{
    static float angle = 0.f;

    angle += 0.01f;

    transform->rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle);
    transform->rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(angle);
    transform->rotation_z.set< Rotation3f::AROUND_THE_Z_AXIS >(angle);

}

void rotateYUpdate(Transform* transform)
{
    static float angle = 0.f;

    angle += 0.025f;

    transform->rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle);

}

void rotateXUpdate(Transform* transform)
{
    static float angle = 0.f;

    angle += 0.025f;

    transform->rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(angle);
}

void rotateZUpdate(Transform* transform)
{
    static float angle = 0.f;

    angle += 0.025f;

    transform->rotation_z.set< Rotation3f::AROUND_THE_Z_AXIS >(angle);
}

int main()
{
    // Create the window and the view that will be shown within the window:

    Window window(VideoMode(window_width, window_height), "3D Render Model", Style::Titlebar | Style::Close, ContextSettings(32));

    Camera camera(
        5,                                              // Near
        15,                                             // Far
        20,                                             // Fov
        float(window_width) / float(window_height),     // Ratio
        toolkit::Point3f({ 0,0,0 }),                    // Position
        toolkit::Point3f({ 0,0,0 })                     // Rotation
    );

    PointLight light(
        Point3f({ 0,0,-2 }),      // Postion
        View::Color({ 100,0,0 })  // Rotation
    );

    View view(
        window_width,   // Width
        window_height,  // Height
        camera,         // Camara
        light           // Light
    );

    view.addModel("Sphere",                         // Nombre
        Model3D(                                    // Modelo
            "..//..//assets//models//sphere.obj",   // Path
            2.00f,                                  // Scale
            Point3f({ 0,0,0 }),                     // Rotation
            Point3f({ 0, 0, -10 }),                // Position
            shared_ptr<View>(new View(view)),       // Vista
            shared_ptr<Model3D>(nullptr)            // Padre
        )
    );


    view.models3D["Sphere"]->setUpdateFunction(rotateUpdate);

    // Initialization:

    window.setVerticalSyncEnabled(true);

    glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GLdouble(window_width), 0, GLdouble(window_height), -1, 1);

    // Run the main loop:

    bool running = true;

    do
    {
        // Attend the window events:

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

        // Update the view:

        view.update(0);

        // Repaint the view:

        view.paint();

        // Swap the OpenGL buffers:

        window.display();
    } while (running);

    // Close the application:

    return (EXIT_SUCCESS);
}
