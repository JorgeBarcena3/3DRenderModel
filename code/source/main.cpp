
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "../headers/View.hpp"
#include "../headers/PointLight.hpp"
#include "../headers/DirectionalLight.hpp"
#include "../headers/Math.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;
using namespace RenderModel;

void planet_update(Model3D * model)
{
    static float angle = 0.f;

    angle += 0.8f;

    model->transform.rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle * PI / 180);
    model->transform.rotation_x.set< Rotation3f::AROUND_THE_X_AXIS >(angle * PI / 180);
    model->transform.rotation_z.set< Rotation3f::AROUND_THE_Z_AXIS >(angle * PI / 180);

}

void asteroide(Model3D * model)
{
    static float angle = 0.f;

    angle += 0.5f;

    model->transform.rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS >(angle * PI / 180);

}

void configScene(View& view)
{
    
    view.addModel("Planet",                           // Nombre
        new Model3D(                                  // Modelo
            "..//..//assets//models//PlanetBlue2.obj",// Path
            0.2f,                                     // Scale
            Point3f({ 0,90,0 }),                      // Rotation
            Point3f({ 0, 0, -10 }),                   // Position
            view,                                     // Vista
            nullptr                                   // Padre
        )
    ); 
    
    view.addModel("Tree_1",                           // Nombre
        new Model3D(                                  // Modelo
            "..//..//assets//models//lowpolytree.obj",// Path
            1.0f,                                     // Scale
            Point3f({ -0,0,90 }),                     // Rotation
            Point3f({ -6, 0, 0 }),                    // Position
            view,                                     // Vista
            view.models3D["Planet"]                   // Padre
        )
    );
    
    view.addModel("Tree_2",                            // Nombre
        new Model3D(                                   // Modelo
            "..//..//assets//models//lowpolytree.obj", // Path
            1.0f,                                      // Scale
            Point3f({ -0,0,-90 }),                     // Rotation
            Point3f({ 6, 0, 0 }),                      // Position
            view,                                      // Vista
            view.models3D["Planet"]                    // Padre
        )
    );

    view.addModel("Tree_3",                            // Nombre
        new Model3D(                                   // Modelo
            "..//..//assets//models//lowpolytree.obj", // Path
            0.9f,                                      // Scale
            Point3f({ -0,0,-0 }),                      // Rotation
            Point3f({ 0, 5.5f, 0 }),                   // Position
            view,                                      // Vista
            view.models3D["Planet"]                    // Padre
        )
    );
    
    view.addModel("Tree_4",                            // Nombre
        new Model3D(                                   // Modelo
            "..//..//assets//models//lowpolytree.obj", // Path
            0.5f,                                      // Scalele
            Point3f({ -0,0,-180 }),                    // Rotationion
            Point3f({ 0, -5.0f, 0 }),                  // Positionn
            view,                                      // Vistaista
            view.models3D["Planet"]                    // Padre
        )
    );  
    
    view.addModel("Asteroide_1",                      // Nombre
        new Model3D(                                  // Modelo
            "..//..//assets//models//PlanetPink1.obj",// Path
            0.5f,                                     // Scale
            Point3f({ -90,0,-0 }),                    // Rotation
            Point3f({ 7, 5, 0 }),                     // Position
            view,                                     // Vista
            view.models3D["Planet"]                   // Padre
        )
    );
    
    view.addModel("Asteroide_2",                         // Nombre
        new Model3D(                                     // Modelo
            "..//..//assets//models//PlanetGreen1.obj",  // Path
            0.2f,                                        // Scale
            Point3f({0,0,-0 }),                          // Rotation
            Point3f({ -7, 0, 0 }),                       // Position
            view,                                        // Vista
            view.models3D["Asteroide_1"]                 // Padre
        )
    );


    view.models3D["Planet"]->setUpdateFunction(planet_update);
    view.models3D["Asteroide_1"]->setUpdateFunction(asteroide);
   

    
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

    //PointLight light(
    //    Point3f({ 5,4,0 }),      // Postion
    //    View::Color({ 100,0,0 })  // Color
    //);

    DirectionalLight light(
        Point3f(  { -0.5,0, 1 }), // Direction
        View::Color({ 100,0,0 })  // Color
    );

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

 /*   return (EXIT_SUCCESS);*/
}
