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
    //Leemos linea a linea
    while (fgets(linea, sizeof(linea), file)) {
        switch (linea[0])
        {
        case 'V':
        case 'v':
            //Si nuestra linea es Vt (coordenada de textura)
            if (linea[1]=='t') {
                break;
            }
            //Si nuestra linea es Vn (Normal)
            else if (linea[1]=='n') {
                break;
            }
            //Si nuestra linea es un simple vertice
            else {
                vertex v;
                //strtok(); le el buffer de entrada del fichero hasta que el caracter concuerda con el proporcionado
                aux = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
                //Obtenemos los valores posteriores separados por un espacio
                aux = strtok(NULL, " "); v.x = atof(aux);
                aux = strtok(NULL, " "); v.y = atof(aux);
                aux = strtok(NULL, " "); v.z = atof(aux);
                //Añadimos el valor leido a nuestro arreglo de vertices
                this->vertexes.push_back(v);
            }
            break;
        case 'F':
        case 'f':
            //Si nuestra linea es una cara (Face)
            face f;
            aux = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
            //Obtenemos los valores posteriores separados por un espacio
            aux = strtok(NULL, "/"); f.v1 = atoi(aux);
            aux = strtok(NULL, " ");
            aux = strtok(NULL, "/"); f.v2 = atoi(aux);
            aux = strtok(NULL, " ");
            aux = strtok(NULL, "/"); f.v3 = atoi(aux);
            //Añadimos el valor leido a nuestro arreglo de caras (de momento solo los valores de los vertices)
            //Se estan omitiendo las normales y el texturizado
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
    //Dibujamos las caras
    for (int i = 0; i < faces.size(); i++)
    {
        //Almacenamos el valor de los vertices recorriendo cara por cara
        vertex v1 = vertexes[faces[i].v1 - 1];
        vertex v2 = vertexes[faces[i].v2 - 1];
        vertex v3 = vertexes[faces[i].v3 - 1];

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}