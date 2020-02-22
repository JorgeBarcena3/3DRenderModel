
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
#include "../headers/DirectionalLight.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#define PI 3.14159265359f

using namespace sf;
using namespace RenderModel;

void rotateUpdate(Model3D* model)
{
    static float angle = 0.f;

    angle += 0.01f;

    model->transform.rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle * PI / 180);
    model->transform.rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(angle * PI / 180);
    model->transform.rotation_z.set< Rotation3f::AROUND_THE_Z_AXIS >(angle * PI / 180);

}

void rotateYUpdate(Model3D* model)
{
    static float angle = 0.f;

    angle += 0.5f;

    model->transform.rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle * PI / 180);

}

void rotateXUpdate(Model3D* model)
{
    static float angle = 0.f;

    angle += 0.025f;

    model->transform.rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(angle * PI / 180);
}

void rotateZUpdate(Model3D* model)
{
    static float angle = 0.f;

    angle += 0.025f;

    model->transform.rotation_z.set< Rotation3f::AROUND_THE_Z_AXIS >(angle * PI / 180);
}

void displaceInX(Model3D* model)
{
    model->transform.addDisplacement(Point3f({ 0.1f, 0.f, 0.f }));
}

void displaceInY(Model3D* model)
{
    model->transform.addDisplacement(Point3f({ 0.f, 0.1f, 0.f }));
}

void displaceInZ(Model3D* model)
{
    model->transform.addDisplacement(Point3f({ 0.f, 0.f, 0.1f }));
}

void configScene(View& view)
{
    //view.addModel("Island",                         // Nombre
    //    Model3D(                                    // Modelo
    //        "..//..//assets//models//island.obj",   // Path
    //        0.4f,                                  // Scale
    //        Point3f({ 0,0,0 }),                      // Rotation
    //        Point3f({ -0, -4, -10 }),                // Position
    //        shared_ptr<View>(new View(view)),       // Vista
    //        shared_ptr<Model3D>(nullptr)            // Padre
    //    )
    //);  
    //
    //view.addModel("Tree_1",                         // Nombre
    //    Model3D(                                    // Modelo
    //        "..//..//assets//models//lowpolytree.obj",   // Path
    //        0.2f,                                  // Scale
    //        Point3f({ 0,0,0 }),                      // Rotation
    //        Point3f({ 0.8, 0, -10 }),                // Position
    //        shared_ptr<View>(new View(view)),       // Vista
    //        shared_ptr<Model3D>(nullptr)            // Padre
    //    )
    //);

    //view.addModel("Tree_2",                         // Nombre
    //    Model3D(                                    // Modelo
    //        "..//..//assets//models//lowpolytree.obj",   // Path
    //        0.08f,                                  // Scale
    //        Point3f({ 0,0,0 }),                      // Rotation
    //        Point3f({ -0.4, -0.2, -10 }),                // Position
    //        shared_ptr<View>(new View(view)),       // Vista
    //        shared_ptr<Model3D>(nullptr)            // Padre
    //    )
    //);

    //view.addModel("Pato",                         // Nombre
    //    Model3D(                                    // Modelo
    //        "..//..//assets//models//10602_Rubber_Duck_v1_L3.obj",   // Path
    //        0.03f,                                  // Scale
    //        Point3f({ -90,0,0 }),                      // Rotation
    //        Point3f({ -0.4, -0.3, -10 }),                // Position
    //        shared_ptr<View>(new View(view)),       // Vista
    //        shared_ptr<Model3D>(nullptr)            // Padre
    //    )
    //);    
    //
    //view.addModel("Tower",                         // Nombre
    //    Model3D(                                    // Modelo
    //        "..//..//assets//models//War_Tower.obj",   // Path
    //        0.2f,                                  // Scale
    //        Point3f({ 0,0,0 }),                      // Rotation
    //        Point3f({ 0, -0.3, -9 }),                // Position
    //        shared_ptr<View>(new View(view)),       // Vista
    //        shared_ptr<Model3D>(nullptr)            // Padre
    //    )
    //);

    view.addModel("Tree",                         // Nombre
        Model3D(                                    // Modelo
            "..//..//assets//models//lowpolytree.obj",   // Path
            0.5f,                                  // Scale
            Point3f({ 0,0,0 }),                      // Rotation
            Point3f({ -0, -0, -10 }),                // Position
            shared_ptr<View>(new View(view)),       // Vista
            shared_ptr<Model3D>(nullptr)            // Padre
        )
    );

    view.models3D["Tree"]->setUpdateFunction(rotateYUpdate);
}

int main()
{
    Window window(VideoMode(800, 600), "3D Render Model | Jorge Barcena Lumbreras", Style::Titlebar | Style::Close, ContextSettings(32));

    Camera camera(
        5,                                                        // Near
        15,                                                       // Far
        20,                                                       // Fov
        float(window.getSize().x) / float(window.getSize().y),    // Ratio
        toolkit::Point3f({ 0, 0,0 }),                              // Position
        toolkit::Point3f({ 0,-0,0 })                               // Rotation
    );

    PointLight light(
        Point3f({ 0,4,-2 }),      // Postion
        View::Color({ 100,0,0 })  // Color
    );

    //DirectionalLight light(
    //    Point3f(  { -0.5,0, 1 }), // Direction
    //    View::Color({ 100,0,0 })  // Color
    //);

    View view(
        window.getSize().x,   // Width
        window.getSize().y,   // Height
        camera,               // Camara
        light                 // Light
    );

    //Configuramos la escena a previsualizar
    configScene(view);

    // Initialization:

    window.setVerticalSyncEnabled(true);

    glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GLdouble(window.getSize().x), 0, GLdouble(window.getSize().y), -1, 1);

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
