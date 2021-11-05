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
// -- Fuentes_Bitmap ------------------------------------------------------------
// -----------------------------------------------------------------------------
// #include "../Includes/Fuentes_Bitmap.h"
//
// c_fuente_bitmap *fuente = new c_fuente_bitmap( "fuente.png" );
//
// fuente->color( 255, 255, 255 ); /* BLANCO, DOBLE DE RAPIDO */
//
// fuente->escribe( pos_x, pos_y, "Texto." );
//
// delete fuente;
//
// -----------------------------------------------------------------------------
#ifndef _Fuentes_Bitmap_
#define _Fuentes_Bitmap_

#include <iostream>
using namespace std;
#include <GL/gl.h>										
#include <GL/glu.h>										
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Configuracion.h"

class c_fuente_bitmap {
  public:
    c_fuente_bitmap( const char *bitmap_nombre );
    ~c_fuente_bitmap( void );
    void color( GLubyte r, GLubyte v, GLubyte a ) { rojo = r; verde = v; azul = a; }
    void escribe( GLint x, GLint y, const char *texto );
    void escribe_b_n( GLint x, GLint y, const char *texto );
    GLint  ancho_de( const char *texto );
    GLint  altura( void ) { return alto; }
    void ver( void );

  private:
    GLubyte rojo, verde, azul;
    char texto[2];
    GLuint text_bitmap, base;
    GLint alto, avance, wh, ancho_texto;
    GLfloat cx, cy, c_ancho, c_alto;
    SDL_Surface *tmp;
};

#endif
