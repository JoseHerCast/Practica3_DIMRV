#include <vector>
#include <string>
#include <stdio.h>

class obj3dmodel
{
    //Estos serán nuestros vertices
    struct vertex {
        double x;
        double y;
        double z;
    };
    //Estas serán nuestras coordenadas uv
    struct text {
        double u;
        double v;
    };
    //Cada cara estará formada por 3 vertices (triangulos)
    struct face {
        unsigned int v1, v2, v3;
    };
    //Declaramos los arreglos de vertices y de caras
    std::vector<vertex> vertices;
    std::vector<vertex> normales;
    std::vector<text> textura;
    std::vector<face> caras;

public:
    //Función de lectura del archivo
    bool readfile(const char* filename);
    //Función de dibujo del modelo
    void solidDraw();
    void wireDraw();
};