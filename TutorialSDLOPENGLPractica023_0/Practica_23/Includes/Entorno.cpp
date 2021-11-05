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

#include "Entorno.h"

c_entorno::c_entorno( const char *direccion ) { 
  strcpy( &entorno_nombres[0][0], direccion );
  strcpy( &entorno_nombres[1][0], direccion );
  strcpy( &entorno_nombres[2][0], direccion );
  strcpy( &entorno_nombres[3][0], direccion );
  strcpy( &entorno_nombres[4][0], direccion );
  strcpy( &entorno_nombres[5][0], direccion );
  strcat( &entorno_nombres[0][0], "positive_x.jpg" );
  strcat( &entorno_nombres[1][0], "negative_x.jpg" );
  strcat( &entorno_nombres[2][0], "positive_y.jpg" );
  strcat( &entorno_nombres[3][0], "negative_y.jpg" );
  strcat( &entorno_nombres[4][0], "positive_z.jpg" );
  strcat( &entorno_nombres[5][0], "negative_z.jpg" );
  glGenTextures(6, &tex_fondo[0] );
  for( int n = 0; n <6 ; n++ ) {
    glBindTexture( GL_TEXTURE_2D, tex_fondo[n] );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    imagen[n] = IMG_Load( &entorno_nombres[n][0] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imagen[n]->w, imagen[n]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen[n]->pixels);
    SDL_FreeSurface( imagen[n] );
    imagen[n] = NULL;
  }
  // glListBase( 0 );
  env = 1000;
  glNewList( lista_fondo = glGenLists(1), GL_COMPILE );
    glBegin( GL_QUADS ); glNormal3f( 0.0f, 0.0f, 1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3i( -env,  env, -env );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3i( -env, -env, -env );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3i(  env, -env, -env ); 
      glTexCoord2f( 1.0f, 0.0f ); glVertex3i(  env,  env, -env ); 
    glEnd();
    glBindTexture( GL_TEXTURE_2D, tex_fondo[0] );
    glBegin( GL_QUADS ); glNormal3f( 1.0f, 0.0f, 0.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3i( -env,  env,   env );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3i( -env, -env,   env );  
      glTexCoord2f( 1.0f, 1.0f ); glVertex3i( -env, -env,  -env );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3i( -env,  env,  -env );
    glEnd();
    glBindTexture( GL_TEXTURE_2D, tex_fondo[1] );
    glBegin( GL_QUADS ); glNormal3f( -1.0f, 0.0f, 0.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3i(  env,  env,  -env );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3i(  env, -env,  -env );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3i(  env, -env,   env );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3i(  env,  env,   env ); 
    glEnd();
    glBindTexture( GL_TEXTURE_2D, tex_fondo[4] );
    glBegin( GL_QUADS ); glNormal3f( 0.0f, 0.0f, -1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3i(  env,  env,  env ); 
      glTexCoord2f( 0.0f, 1.0f ); glVertex3i(  env, -env,  env );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3i( -env, -env,  env );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3i( -env,  env,  env );
    glEnd();
    glBindTexture( GL_TEXTURE_2D, tex_fondo[2] );
    glBegin( GL_QUADS ); glNormal3f( 0.0f, -1.0f, 0.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3i( -env,  env,  env );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3i( -env,  env, -env );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3i(  env,  env, -env );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3i(  env,  env,  env ); 
    glEnd();
    glBindTexture( GL_TEXTURE_2D, tex_fondo[3] );
    glBegin( GL_QUADS ); glNormal3f( 0.0f, -1.0f, 0.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3i(  env, -env,  env );         
      glTexCoord2f( 0.0f, 1.0f ); glVertex3i(  env, -env, -env ); 
      glTexCoord2f( 1.0f, 1.0f ); glVertex3i( -env, -env, -env );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3i( -env, -env,  env );
    glEnd();
  glEndList();
}

void c_entorno::mostrar( void ) {
  glPushAttrib( GL_FOG_BIT );
  glDisable( GL_FOG );
  glEnable( GL_TEXTURE_2D ); 
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
    glBindTexture( GL_TEXTURE_2D, tex_fondo[5] );
    glCallList( lista_fondo );
  glDisable( GL_TEXTURE_2D ); 
  glPopAttrib(); 
}

void c_entorno::crea_cube_map( void ) {
  cubefaces[0] = GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT;
  cubefaces[1] = GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT;
  cubefaces[2] = GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT;
  cubefaces[3] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT;
  cubefaces[4] = GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT;
  cubefaces[5] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT;
  glGenTextures(1, &tex_cube_map );
  glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, tex_cube_map );
  glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST );
  for( int n = 0; n <6 ; n++ ) {
    imagen[n] = IMG_Load( &entorno_nombres[n][0] );
    gluBuild2DMipmaps( cubefaces[n], GL_RGB, imagen[n]->w, imagen[n]->h, GL_RGB, GL_UNSIGNED_BYTE, imagen[n]->pixels);
    SDL_FreeSurface( imagen[n] );
    imagen[n] = NULL;
  }
}

void c_entorno::activa_cube_map( void ) {
    glEnable( GL_TEXTURE_CUBE_MAP_EXT );
    glBindTexture( GL_TEXTURE_CUBE_MAP_EXT, tex_cube_map );
    glTexParameteri( GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT );
    glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT );
    glEnable( GL_TEXTURE_GEN_S ); 
    glEnable( GL_TEXTURE_GEN_T ); 
    glEnable( GL_TEXTURE_GEN_R );
}

void c_entorno::desactiva_cube_map( void ) {
    glDisable( GL_TEXTURE_GEN_S ); 
    glDisable( GL_TEXTURE_GEN_T ); 
    glDisable( GL_TEXTURE_GEN_R );
    glDisable(GL_TEXTURE_CUBE_MAP_EXT);
}

c_entorno::~c_entorno( void ) { 
  glDeleteLists( lista_fondo,  1 );
  glDeleteTextures( 6, &tex_fondo[0] );
  glDeleteTextures( 1, &tex_cube_map  );
}
