#include <vector>
#include <string>
#include <stdio.h>

class obj3dmodel
{
    struct vertex {
        double x;
        double y;
        double z;
    };
    struct face {
        unsigned int v1, v2, v3;
    };
    std::vector<vertex> vertexes;
    std::vector<face> faces;

public:
    bool readfile(const char* filename);
    void draw();
};