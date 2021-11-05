//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programación) www.scenebeta.com          --
//-- FECHA ÚLTIMA MODIFICACIÓN: 31/03/2010                                    --
//------------------------------------------------------------------------------
//-- Todo  el  código  y  contenido  de  este  tutorial es exclusivo  para el --
//-- aprendizaje tanto del autor como de los que colaboren en él. Sin el  más --
//-- mínimo ánimo de lucro, siempre por la satisfacción del aprendizaje y del --
//-- trabajo bien hecho.                                                      --
//-- No  me  hago  responsable  del  daño  producido  por  el  uso  indebido, --
//-- modificaciones  mal  intencionadas,  ánimo  de  lucro,  etc...           --
//-- Solo pido al que le sea de utilidad este código que colabore en su mejora--
//-- y perfeccionamiento poniéndomelo en conocimiento por correo electrónico. --
//------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// SDL_con_OpenGL.h ---------------------------------------------------------------
// -----------------------------------------------------------------------------
// LINKER:
// -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lopengl32 -lglu32 -mwindows
// -----------------------------------------------------------------------------
// #include "../Includes/SDL_con_OpenGL.h"
// #include "../Includes/Entorno.h"
// #include "../Includes/Fuentes_Bitmap.h"
// #include "../Includes/Luces.h"
// #include "../Includes/Materiales.h"
// #include "../Includes/Texturas_2D.h"
// #include "../Includes/Figuras.h"
// 
// int main(int argc, char *argv[]) {
//   // -- CREACION DEL ENTORNO 3D ------------------------------------------------
//   c_sdl_con_opengl *sdl_con_opengl = new c_sdl_con_opengl;
//   c_entorno *entorno = new c_entorno( "Imagen/Cube_Maps/deadmeat/" );
//   if ( sdl_con_opengl->Texture_Cube_Map ) entorno->crea_cube_map();
//   else {
//     cerr << "Tu Tarjeta Grafica no es compatible con Texture_Cube_Map." << endl;
//     exit(1);
//   }
//
//   // -- CREACION DE UNA FUENTE DE TEXTO ----------------------------------------
//   c_fuente_bitmap *fuente = new c_fuente_bitmap( "Fuentes/Arial_256.png" );
//
//   // -- CREAMOS LAS LUCES ------------------------------------------------------
//   c_luz *luz = new c_luz[1];
//   luz[0].position(  5.0f,  5.0f, 5.0f );
//   luz[0].direccional( GL_LIGHT0 );
//
//   // -- CREAMOS LOS MATERIALES -------------------------------------------------
//   c_material *material = new c_material[1];
//
//   // -- CREAMOS LAS TEXTURAS ---------------------------------------------------
//   c_textura_2D *textura_2D = new c_textura_2D[1];
//   textura_2D[0].carga_2D( "Imagen/Texturas/Marmol_Verde.jpg", 0 );
//   textura_2D[0].modo( GL_MODULATE );
//
//   // -- CREAMOS LAS LISTAS COMPILADAS ------------------------------------------
//   glListBase( 0 );
//   GLuint lista = glGenLists(1);
//   
//   glNewList( lista + 0, GL_COMPILE );
//     Dibuja_Esfera( 2.0f, 64 );
//   glEndList();
//   
//   // -- CONFIGURACIÓN DE VISUALIZACION -----------------------------------------
//   // glEnable(  GL_COLOR_MATERIAL );   // ACTIVA glColor3ub();
//      glDisable( GL_COLOR_MATERIAL );   // ACTIVA glMaterialfv();
//      glEnable(  GL_CULL_FACE );        // ACTIVA OCULTAR CARAS TRASERAS
//   // glDisable( GL_CULL_FACE );        // MUESTRA LAS CARAS TRASERAS
//   // glEnable(  GL_FOG );              // ACTIVA LA NIEBLA
//      glDisable( GL_FOG );              // DESACTIVA LA NIEBLA
//      glEnable(  GL_LIGHTING );         // ACTIVA LA LUZ
//   // glDisable( GL_LIGHTING );         // ACTIVA LA LUZ
//      glEnable( GL_LIGHT0 );            // ACTIVA LA LUZ Nº 0
//   // glEnable( GL_LIGHT1 );            // ACTIVA LA LUZ Nº 1
//   // glEnable( GL_LIGHT2 );            // ACTIVA LA LUZ Nº 2
//
//   // -- POSICION DE LA CÁMARA Y BUCLE PRINCIPAL --------------------------------
//   sdl_con_opengl->posicion_camara( 0.0f, 5.0f, 20.0f ); 
//   do { sdl_con_opengl->empieza( entorno );
//   
//     luz[0].posiciona();
// 
//     material[0].activa();
//     glPushMatrix();
//
//       glCallList( lista + 0 );
//
//       glTranslatef( 10.0f, 0.0f, 0.0f );
//       textura_2D[0].activa();
//         glCallList( lista + 0 );
//       textura_2D[0].desactiva();	
//
//       glTranslatef( -20.0f, 0.0f, 0.0f );
//       entorno->activa_cube_map();
//         glCallList( lista + 0 );
//       entorno->desactiva_cube_map();
//
//     glPopMatrix();
// 
//     // -- FIN BUCLE PRINCIPAL Y MOSTRAR INFORMACIÓN DE ESTADOS -----------------
//     sdl_con_opengl->empieza_ortho_2D();
//       sdl_con_opengl->ver_info( fuente, "Práctica: XX" );
//     sdl_con_opengl->termina_ortho_2D();
//   } while ( !sdl_con_opengl->termina() );
//
//   // -- BORRANDO OBJETOS -------------------------------------------------------
//   glDeleteLists( lista,  1 );
//   delete[] textura_2D;
//   delete[] material; 
//   delete[] luz;
//   delete fuente;
//   delete entorno;
//   delete sdl_con_opengl;
// 
//   // -- FIN DE MAIN ------------------------------------------------------------
//   return EXIT_SUCCESS;
// }
//
// -----------------------------------------------------------------------------
#ifndef _SDL_con_OpenGL_
#define _SDL_con_OpenGL_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <math.h>
using namespace std;

#include <GL/gl.h>										
#include <GL/glu.h>										
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Configuracion.h"
#include "Entorno.h"
#include "Fuentes_Bitmap.h"
#include "Mirror.h"

void Inicia_SDL_con_GL();

class c_sdl_con_opengl {
  public:
    c_sdl_con_opengl();
    ~c_sdl_con_opengl();
    void posicion_camara( GLfloat xx, GLfloat yy, GLfloat zz ) { cpx = xx; cpy = yy; cpz = zz; }
    void enfoque_camara(  GLfloat xx, GLfloat yy, GLfloat zz ) { cex = xx; cey = yy; cez = zz; }
    void ver_enfoque_camara( void );
    void empieza( void );
    void empieza( c_entorno *mostrar_entorno );
    void empieza_ortho_2D( void );
    void termina_ortho_2D( void );
    void ver_info( c_fuente_bitmap *fuente, const char *mensaje );
    bool termina(void);
    static SDL_Surface *pantalla;
    GLint Cube_Map_Texture_Size_Ext, Texture_Units_ARB;
    bool Texture_Cube_Map, Multitexture;
    bool activa_enfoque_camara;
    
  private:
    void configuracion_3D( void );
    void leer_teclado(void);
    void espera_frame( void );
    char *info_t_espera_frames( void );
    char *info_posicion( void );
    char *info_rotacion( void );
    char *info_estados( void );
    void compatible( void );
    SDL_Event evento;           // Eventos del Teclado y Ratón.
    Uint8 *teclado;             // Teclado
    bool terminar, color_material, lighting;
    Uint32 frames, tiempo, t_espera;
    GLfloat  x,  y,  z;
    GLfloat ax, ay, az;
    GLfloat cpx, cpy, cpz; // Posición de la Cámara.
    GLfloat cex, cey, cez; // A donde mira la Cámara.
    char texto[80];
    GLfloat colorNiebla[4];
    
};

void Captura_Pantalla( const char *nombre_archivo );

#endif
