#include "model.h"
#include <SDL_opengl.h>


bool obj3dmodel::readfile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }

    char linea[55];
    char *aux;
    while (fgets(linea, sizeof(linea), file)) {
        switch (linea[0])
        {
        case 'V':
        case 'v':
            if (linea[1]=='t') {
                break;
            }
            else if (linea[1]=='n') {
                break;
            }
            else {
                vertex v;
                aux = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
                //Obtenemos los valores posteriores separados por un espacio
                aux = strtok(NULL, " "); v.x = atof(aux);
                aux = strtok(NULL, " "); v.y = atof(aux);
                aux = strtok(NULL, " "); v.z = atof(aux);
                this->vertexes.push_back(v);
            }
            break;
        case 'F':
        case 'f':
            face f;
            aux = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
            //Obtenemos los valores posteriores separados por un espacio
            aux = strtok(NULL, "/"); f.v1 = atoi(aux);
            aux = strtok(NULL, " ");
            aux = strtok(NULL, "/"); f.v2 = atoi(aux);
            aux = strtok(NULL, " ");
            aux = strtok(NULL, "/"); f.v3 = atoi(aux);

            this->faces.push_back(f);

            break;
        default:
            break;
        }
    }

    fclose(file);
}

void obj3dmodel::draw()
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++)
    {
        vertex v1 = vertexes[faces[i].v1 - 1];
        vertex v2 = vertexes[faces[i].v2 - 1];
        vertex v3 = vertexes[faces[i].v3 - 1];

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}