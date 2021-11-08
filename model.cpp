#include "model.h"
#include <SDL_opengl.h>


bool obj3dmodel::readfile(const char* filename)
{   
    char linea[55];

    //Aqui leemos el archivo OBJ
    FILE* obj = fopen(filename, "r");
    if (obj == NULL) {
        printf("\nImpossible to open the file %s\n",filename);
        return false;
    }
    
    char *aux;
    //Leemos linea a linea
    while (fgets(linea, sizeof(linea), obj)) {
        switch (linea[0])
        {
        case 'V':
        case 'v':
            //Si nuestra linea es Vt (coordenada de textura)
            if (linea[1]=='t') {
                text t;
                //strtok(); le el buffer de entrada del fichero hasta que el caracter concuerda con el proporcionado
                aux = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
                //Obtenemos los valores posteriores separados por un espacio
                aux = strtok(NULL, " "); t.u = atof(aux);
                aux = strtok(NULL, " "); t.v = atof(aux);
                //Añadimos el valor leido a nuestro arreglo de vertices
                this->textura.push_back(t);
                break;
            }
            //Si nuestra linea es Vn (Normal)
            else if (linea[1]=='n') {
                vertex v;
                //strtok(); le el buffer de entrada del fichero hasta que el caracter concuerda con el proporcionado
                aux = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
                //Obtenemos los valores posteriores separados por un espacio
                aux = strtok(NULL, " "); v.x = atof(aux);
                aux = strtok(NULL, " "); v.y = atof(aux);
                aux = strtok(NULL, " "); v.z = atof(aux);
                //Añadimos el valor leido a nuestro arreglo de vertices
                this->normales.push_back(v);
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
                this->vertices.push_back(v);
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
            this->caras.push_back(f);

            break;
        default:
            break;
        }
    }

    //Aqui leemos el archivo MTL
    char* mtlname = (char*)malloc(strlen(filename) * sizeof(char));
    strcpy(mtlname, filename);
    mtlname[strlen(mtlname) - 3] = NULL;
    strcat(mtlname, "mtl");


    FILE* mtl = fopen(mtlname, "r");
    if (mtl == NULL) {
        printf("\nImpossible to open the file %s\n", mtlname);
        return false;
    }

    while (fgets(linea, sizeof(linea), mtl)) {
        printf("\n%s\n", linea);
    }

    fclose(mtl);
    fclose(obj);
}

void obj3dmodel::solidDraw()
{
    glBegin(GL_TRIANGLES);
    //Dibujamos las caras
    for (int i = 0; i < caras.size(); i++)
    {
        //Almacenamos el valor de los vertices recorriendo cara por cara
        vertex v1 = vertices[caras[i].v1 - 1];
        vertex v2 = vertices[caras[i].v2 - 1];
        vertex v3 = vertices[caras[i].v3 - 1];

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}

void obj3dmodel::wireDraw()
{
    glBegin(GL_LINES);
    //Dibujamos las caras
    for (int i = 0; i < caras.size(); i++)
    {
        //Almacenamos el valor de los vertices recorriendo cara por cara
        vertex v1 = vertices[caras[i].v1 - 1];
        vertex v2 = vertices[caras[i].v2 - 1];
        vertex v3 = vertices[caras[i].v3 - 1];

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);

        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}