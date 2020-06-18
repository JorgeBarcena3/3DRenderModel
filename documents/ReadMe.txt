Render Model 3D - Jorge Bárcena Lumbreras

IMPLEMENTACIONES

- Carga de archivos .obj con la libreria tinyobj.
- Lectura de archivos .mtl asociados con los modelos obj (Se recogen los datos del color difuso, especular...).
- Cada modelo (.obj) es organizado en distintas Mesh.
- Recorte de la escena mediante el algoritmo de Shutter-Hodgman.
- Renderizacion de modelos 3D con SFML.
- Aplicacion de iluminacion. Hay dos tipos de luces (Luces direccionales y luces puntuales).
- Jerarquia de escena (Grafo de escena).

ERRORES

- Al finalizar el programa, hay un memory Leak y salta un error. No he sido capaz de resolverlo. 