#include <vector>
#include <string>
#include <stdio.h>

class obj3dmodel
{
    //Estos ser�n nuestros vertices
    struct vertex {
        double x;
        double y;
        double z;
    };
    //Cada cara estar� formada por 3 vertices (triangulos)
    struct face {
        unsigned int v1, v2, v3;
    };
    //Declaramos los arreglos de vertices y de caras
    std::vector<vertex> vertexes;
    std::vector<face> faces;

public:
    //Funci�n de lectura del archivo
    bool readfile(const char* filename);
    //Funci�n de dibujo del modelo
    void draw();
};