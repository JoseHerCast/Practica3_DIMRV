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

#include "Fuentes_Bitmap.h"

c_fuente_bitmap::c_fuente_bitmap( const char *bitmap_nombre ) {                           
  atexit( SDL_Quit );
  tmp = IMG_Load( bitmap_nombre );
  if ( tmp == NULL ) {
    cerr << "Falla IMG_Load: " << bitmap_nombre << endl;
    exit(1);
  }                     
  glGenTextures( 1, &text_bitmap );
  glBindTexture( GL_TEXTURE_2D, text_bitmap );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, tmp->w, tmp->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tmp->pixels );
  wh = tmp->h; alto =  wh >> 4;
  SDL_FreeSurface( tmp ); tmp = NULL;
  SDL_EnableUNICODE(1);               
  base  = glGenLists( 256 );
  glBindTexture( GL_TEXTURE_2D, text_bitmap );
  c_alto  = GLfloat(alto)/wh;
  c_ancho = GLfloat(alto)/wh;
  avance = GLint( alto * 0.8f);
  for ( GLint loop = 0; loop < 256; loop++ ) {
    cx = alto * ( GLfloat )( loop % 16 ) ; 
    cy = alto * ( GLfloat )( loop / 16 ) ;
    cx =  cx / wh;  
    cy =  cy / wh;
    glNewList(( base + loop ), GL_COMPILE );
      glBegin( GL_QUADS );
		glTexCoord2f( cx, cy + c_alto ); glVertex2i( 0, 0 );
		glTexCoord2f( cx + c_ancho, cy + c_alto ); glVertex2i( alto, 0 );
		glTexCoord2f( cx + c_ancho, cy ); glVertex2i( alto, alto );
        glTexCoord2f( cx, cy ); glVertex2i( 0, alto );
      glEnd( );
      glTranslatef( avance, 0, 0 );
    glEndList( );
  }
  rojo = 255; verde = 255; azul = 255;           
}

c_fuente_bitmap::~c_fuente_bitmap( void ) {                       
  glDeleteTextures( 1, &text_bitmap ); 
  glDeleteLists( base, 256 );
  // cerr << "Fuentes_Bitmap Destruida." << endl;
}

void c_fuente_bitmap::escribe( GLint x, GLint y, const char *texto  ) {
  glListBase( base );
  glColor3ub( rojo, verde, azul );
    glBindTexture( GL_TEXTURE_2D, text_bitmap );
    glEnable( GL_BLEND );
    glLoadIdentity();
    if ( !( rojo | verde | azul ) ) {
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
      glBlendFunc( GL_ZERO, GL_ONE_MINUS_SRC_COLOR );
      glTranslated( x, V_Alto - alto - y, 0 );
      glCallLists( strlen( texto ), GL_UNSIGNED_BYTE, texto );
    } else if ( ( rojo & verde & azul ) ) {
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
      glBlendFunc( GL_ONE, GL_ONE );
      glTranslated( x, V_Alto - alto - y, 0 );
      glCallLists( strlen( texto ), GL_UNSIGNED_BYTE, texto ); 
    } else {
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
      glBlendFunc( GL_ZERO, GL_ONE_MINUS_SRC_COLOR );
      glTranslated( x, V_Alto - alto - y, 0 );
      glCallLists( strlen( texto ), GL_UNSIGNED_BYTE, texto );
      glLoadIdentity();
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
      glBlendFunc( GL_ONE, GL_ONE );
      glTranslated( x, V_Alto - alto - y, 0 );
      glCallLists( strlen( texto ), GL_UNSIGNED_BYTE, texto );    
    }
    glDisable( GL_BLEND );
}

void c_fuente_bitmap::escribe_b_n( GLint x, GLint y, const char *texto  ) {
  glListBase( base );
  glLoadIdentity();
  glBindTexture( GL_TEXTURE_2D, text_bitmap );
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
  glTranslated( x, V_Alto - alto - y, 0 );
  glCallLists( strlen( texto ), GL_UNSIGNED_BYTE, texto );
}

int c_fuente_bitmap::ancho_de( const char *texto ) {
  ancho_texto = 0;
  for ( GLint i = 0; i < strlen( texto ); i++ ) {
     ancho_texto += avance;
  }
  return  ancho_texto;
}

void c_fuente_bitmap::ver( void ) {
  glDisable( GL_CULL_FACE );
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, text_bitmap );
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
  glBegin( GL_QUADS );
    glTexCoord2f( 0.0f, 0.0f ); glVertex2i( -1,  1 );
    glTexCoord2f( 0.0f, 1.0f ); glVertex2i( -1, -1 ); 
    glTexCoord2f( 1.0f, 1.0f ); glVertex2i(  1, -1 ); 
    glTexCoord2f( 1.0f, 0.0f ); glVertex2i(  1,  1 ); 
  glEnd( );
  glDisable( GL_TEXTURE_2D );
  glEnable( GL_CULL_FACE );
}
