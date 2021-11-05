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

#include "SDL_con_OpenGL.h"

SDL_Surface *c_sdl_con_opengl::pantalla;  // -- Variable global en una clase --

// -----------------------------------------------------------------------------
// -- Inicializar SDL con OPENGL -----------------------------------------------
// -----------------------------------------------------------------------------
void Inicia_SDL_con_GL( void ) {
  atexit( SDL_Quit );
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){
    cerr << "No se pudo iniciar la libreria SDL: " << SDL_GetError() << endl;        
    exit(1);
  }
  const SDL_VideoInfo *VideoInfo = SDL_GetVideoInfo();  
  if( VideoInfo == NULL ) {
    cerr << "No se pudo obtener el VideoInfo: " << SDL_GetError() << endl;          
    exit(1);
  } 
  int P_bpp = (int)VideoInfo->vfmt->BitsPerPixel;
  if ( ( P_bpp != 16 ) && ( P_bpp != 32 ) ) P_bpp = 16;
  // ---------------------------------------------------------------------------
  // -- ESTO IMPRIME LA INFORMACIÓN DE LA TARJETA GRÁFICA ----------------------
  // ---------------------------------------------------------------------------
  /*
  ofstream tarjeta_grafica("tarjeta_grafica.txt");
  tarjeta_grafica << "Resolución de Ventana : " << V_Ancho << " X " << V_Alto << " Pixels." << endl;
  tarjeta_grafica << "Bits por Pixel: " << (int)VideoInfo->vfmt->BitsPerPixel << " -> " << P_bpp << endl;
  tarjeta_grafica << "Soporta Superficies por Hardware: " << boolalpha << (bool)VideoInfo->hw_available << noboolalpha << endl;
  tarjeta_grafica << "Memoria de Video: " << VideoInfo->video_mem << " K." << endl;
  tarjeta_grafica << "Mask RGBA -> " << hex;
  tarjeta_grafica << VideoInfo->vfmt->Rmask << " -> ";
  tarjeta_grafica << VideoInfo->vfmt->Gmask << " -> ";
  tarjeta_grafica << VideoInfo->vfmt->Bmask << " -> ";
  tarjeta_grafica << VideoInfo->vfmt->Amask << dec << endl;
  tarjeta_grafica.close();
  */
  // ---------------------------------------------------------------------------
  int VideoFlags = 0;
  VideoFlags  = SDL_OPENGL;                                         
  VideoFlags |= SDL_HWPALETTE;       
  if (VideoInfo->hw_available) VideoFlags |= SDL_HWSURFACE;
  else                         VideoFlags |= SDL_SWSURFACE;
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,   16 );
  SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE,  1 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,  1 );
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE,      5 ); // 5 -- 5 -- 8
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,    6 ); // 5 -- 6 -- 8
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,     5 ); // 5 -- 5 -- 8
  c_sdl_con_opengl::pantalla = SDL_SetVideoMode( V_Ancho, V_Alto, P_bpp, VideoFlags );
  if( c_sdl_con_opengl::pantalla == NULL ){
    cerr << "No se pudo iniciar el modo de pantalla: " << SDL_GetError() << endl;           
    exit(1);
  }
  SDL_WM_SetCaption( N_Ventana, NULL );    // -- Pone nombre a la ventana. --
  if ( SDL_EnableKeyRepeat( 1, SDL_DEFAULT_REPEAT_INTERVAL) )	 {
    cerr << "Falla activando repeticion de teclas: " << SDL_GetError() << endl;
    exit(1);
  }  
  // -- Cargamos el Icono de la Ventana ----------------------------------------
  SDL_Surface *img_icono = IMG_Load( Nombre_Icono );
  if( !img_icono ) {
    cerr << "No se pudo cargar: " << Nombre_Icono << endl;
    exit(1);
   }
  SDL_WM_SetIcon( img_icono, NULL );
  SDL_FreeSurface( img_icono ); img_icono = NULL;
}

// -----------------------------------------------------------------------------
// -- Inicializar SDL con OPENGL -----------------------------------------------
// -----------------------------------------------------------------------------
c_sdl_con_opengl::c_sdl_con_opengl( void ) {                                
  Inicia_SDL_con_GL();
  // -- Se inicia la cuenta de tiempo. -----------------------------------------
  frames = Uint32( 1000 / FOTOGRAMAS );
  tiempo = SDL_GetTicks() + frames;
  // -- Inicializa la semilla de numeros aleatorios. ---------------------------
  srand(time(0));
  terminar = false;
  color_material = false;
  lighting = false;
  x  = 0.0f; y  = 0.0f; z  = 0.0f;
  ax = 0.0f; ay = 0.0f; az = 0.0f;
  activa_enfoque_camara = false;
  cpx = 0.0f; cpy = 0.0f; cpz = 4.0f;
  cex = 0.0f; cey = 0.0f; cez = 0.0f;
    
  Cube_Map_Texture_Size_Ext = 0;
  Texture_Units_ARB = 0;
  Texture_Cube_Map  = false;
  Multitexture      = false;
  this->compatible();
  
  this->configuracion_3D();
}

// -----------------------------------------------------------------------------
// -- Cerar SDL ----------------------------------------------------------------
// -----------------------------------------------------------------------------
c_sdl_con_opengl::~c_sdl_con_opengl( void ) {
  SDL_FreeSurface( pantalla );          // -- Liberar memoria pantalla --
  pantalla = NULL;
  SDL_Quit();                           // -- Cerrar SDL --
}	

// -----------------------------------------------------------------------------
// -- Ver a Donde Enfoca la Cámara ---------------------------------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::ver_enfoque_camara( void ) { 
      glPushAttrib(GL_LIGHTING_BIT);
      glDisable( GL_LIGHTING ); 
      glDisable( GL_DEPTH_TEST );
      glEnable( GL_COLOR_MATERIAL ); 
      glColor3ub( 255, 0, 0 ); 
      glPointSize( 8.0f );
      glBegin( GL_POINTS );  glVertex3f( cex, cey, cez ); glEnd(); 
      glLineWidth( 2.0f );
      glBegin( GL_LINE_LOOP );
         glVertex3f( cex - 0.2f, cey + 0.2f, cez );
         glVertex3f( cex + 0.2f, cey + 0.2f, cez );
         glVertex3f( cex + 0.2f, cey - 0.2f, cez );
         glVertex3f( cex - 0.2f, cey - 0.2f, cez );
      glEnd();
      glEnable( GL_DEPTH_TEST );
      glPopAttrib();
}

// -----------------------------------------------------------------------------
// -- Configuración del entorno 3D ---------------------------------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::configuracion_3D( void ) {
  glClearColor( RF, GF, BF, AF );    // Borrado del Buffer Color.
  glClearDepth( 1.0f );              // Borrado del Buffer Depth
  glDepthFunc( GL_LEQUAL );          // Función de Borrado Buffer Depth      
  glEnable ( GL_DEPTH_TEST );        // Activamos el Test de Profundidad.
  glClearStencil( 0 );               // Borrado del Buffer Stencil
  glFrontFace( GL_CCW );             // GL_CCW   o GL_CW.
  glCullFace( GL_BACK );             // GL_FRONT o GL_BACK.
  glEnable( GL_CULL_FACE );          // NO DIBUJA LAS CARAS TRASERAS
  glShadeModel( GL_SMOOTH );         // Activamos el Sombreado Suave, (GL_FLAT) Plano.
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL); //  GL_FILL, GL_LINE y GL_POINT
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
  glViewport( 0, 0, V_Ancho, V_Alto ); // Define la Ventana de visualizado.
  glMatrixMode(GL_PROJECTION);         // Selecciona la Matriz de Proyección.
  glLoadIdentity();                    // Reemplaza la matriz. 
  gluPerspective( 45.0f, (GLfloat)V_Ancho/(GLfloat)V_Alto, .5f , -1000.0f );
  glMatrixMode(GL_MODELVIEW);          // Selecciona la Matriz de Modelado.               
  glLoadIdentity();                    // Reemplaza la matriz.
  // Configuración de Transparencias -------------------------------------------
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glAlphaFunc( GL_GREATER, 0.5f );
  // -- Agregamos niebla -------------------------------------------------------
  colorNiebla[0] = RF; colorNiebla[1] = GF; colorNiebla[2] = BF; colorNiebla[3] = AF;
  glFogi ( GL_FOG_MODE, GL_LINEAR );   // GL_LINEAR, GL_EXP, GL_EXP2
  glFogf ( GL_FOG_DENSITY, 1.0f    );  // 1.0f - 0.036f
  glFogf ( GL_FOG_START,   20.0f   );  // 0.0f
  glFogf ( GL_FOG_END,     60.0f   );  // 1.0f
  glFogfv( GL_FOG_COLOR, colorNiebla );
  glDisable( GL_FOG );
  glEnable( GL_COLOR_MATERIAL );
  glDisable( GL_LIGHTING );
  glDisable( GL_LIGHT0 );
  glDisable( GL_LIGHT1 );
  glDisable( GL_LIGHT2 );
}

// -----------------------------------------------------------------------------
// -- c_sdl_con_opengl.empieza(); ----------------------------------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::empieza(void) {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  gluLookAt( cpx, cpy, cpz, cex, cey, cez, 0.0f, 1.0f, 0.0f );
  glRotatef( ax, 1.0f, 0.0f, 0.0f );
  glRotatef( ay, 0.0f, 1.0f, 0.0f );
}

// -----------------------------------------------------------------------------
// -- c_sdl_con_opengl.empieza( c_entorno *mostrar_entorno ); ------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::empieza( c_entorno *mostrar_entorno ) {
  glClear( GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  gluLookAt( cpx, cpy, cpz, cex, cey, cez, 0.0f, 1.0f, 0.0f );
  mostrar_entorno->mostrar();
  glRotatef( ax, 1.0f, 0.0f, 0.0f );
  glRotatef( ay, 0.0f, 1.0f, 0.0f );
}

// -----------------------------------------------------------------------------
// -- c_sdl_con_opengl.termina(); ----------------------------------------------
// -----------------------------------------------------------------------------
bool c_sdl_con_opengl::termina(void) {
  if ( activa_enfoque_camara ) {
    glLoadIdentity();
    gluLookAt( cpx, cpy, cpz, cex, cey, cez, 0.0f, 1.0f, 0.0f );
    this->ver_enfoque_camara();
  }
  glFlush(); 
  SDL_GL_SwapBuffers();
  this->leer_teclado();	
  this->espera_frame();
  return terminar;
}

// -----------------------------------------------------------------------------
// -- Leer el Teclado ----------------------------------------------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::leer_teclado(void) {
  while(SDL_PollEvent(&evento))     // -- Consultamos los eventos --
  {
    switch( evento.type )
    {
      case SDL_QUIT: { terminar = true; break; }
      case SDL_KEYDOWN:  
        if(evento.key.keysym.sym == SDLK_ESCAPE ) { terminar = true; break; }
    }
  }
  SDL_PumpEvents();
  teclado = SDL_GetKeyState(NULL);
  
  // * * * MOVER LA CAMARA * * *
  if (teclado[T_ARRIBA])     cpz -= MOVER;
  if (teclado[T_ABAJO])      cpz += MOVER;
  if (teclado[T_DERECHA])    cpx += MOVER;
  if (teclado[T_IZQUIERDA])  cpx -= MOVER;
  if (teclado[T_ACERCA])     cpy += MOVER;
  if (teclado[T_ALEJA])      cpy -= MOVER;
  
  // * * * MOVER A DONDE MIRA LA CAMARA * * *
  if (teclado[T_arriba])     cey += MOVER;
  if (teclado[T_abajo])      cey -= MOVER;
  if (teclado[T_derecha])    cex += MOVER;
  if (teclado[T_izquierda])  cex -= MOVER;
  if (teclado[T_acerca])     cez += MOVER;
  if (teclado[T_aleja])      cez -= MOVER;
  if (teclado[T_enfoque]) { 
    if ( activa_enfoque_camara ) activa_enfoque_camara = false; 
    else                         activa_enfoque_camara = true; 
    SDL_Delay( 300 );
  }
  
  // * * * ROTAR LOS OBJETOS SOBRE EL EJE CENTRAL * * *
  if (teclado[T_RXH])     { ax -= ROTAR; if ( ax < 0.0f )   ax += 360.0f; }
  if (teclado[T_RXA])     { ax += ROTAR; if ( ax > 360.0f ) ax -= 360.0f; }
  if (teclado[T_RYH])     { ay -= ROTAR; if ( ay < 0.0f )   ay += 360.0f; }
  if (teclado[T_RYA])     { ay += ROTAR; if ( ay > 360.0f ) ay -= 360.0f; }

  if (teclado[T_Niebla]) {
    if (glIsEnabled( GL_FOG )) glDisable( GL_FOG );
    else                       glEnable(  GL_FOG );
    SDL_Delay( 300 );
  }
  if (teclado[T_Material]) {
    if (glIsEnabled(GL_COLOR_MATERIAL)) glDisable(GL_COLOR_MATERIAL);
    else                                glEnable(GL_COLOR_MATERIAL);
    SDL_Delay( 300 );
  }   
  if (teclado[T_Luz]) {            
    if (glIsEnabled(GL_LIGHTING)) glDisable(GL_LIGHTING);
    else                          glEnable(GL_LIGHTING);
    SDL_Delay( 300 );
  }
  if (teclado[T_Luz_0]) {
    if (glIsEnabled(GL_LIGHT0)) glDisable(GL_LIGHT0);
    else                        glEnable(GL_LIGHT0);
    SDL_Delay( 300 );
  }
  if (teclado[T_Luz_1]) {
    if (glIsEnabled(GL_LIGHT1)) glDisable(GL_LIGHT1);
    else                        glEnable(GL_LIGHT1);
    SDL_Delay( 300 );
  }
  if (teclado[T_Luz_2]) {
    if (glIsEnabled(GL_LIGHT2)) glDisable(GL_LIGHT2);
    else                        glEnable(GL_LIGHT2);
    SDL_Delay( 300 );
  }
  
}

// -----------------------------------------------------------------------------
// -- Esperar al frame ---------------------------------------------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::espera_frame( void ) {
  t_espera = tiempo - SDL_GetTicks();
  if ( ( t_espera > 0 ) && ( t_espera < frames ) ) SDL_Delay( t_espera );
  else tiempo = SDL_GetTicks();
  tiempo += frames;
}

// -----------------------------------------------------------------------------
// -- Empieza_ortho_2D() -------------------------------------------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::empieza_ortho_2D( void ) { 
  color_material = glIsEnabled( GL_COLOR_MATERIAL );
  lighting       = glIsEnabled( GL_LIGHTING );
  glEnable( GL_COLOR_MATERIAL );
  glDisable( GL_LIGHTING );
  glMatrixMode( GL_PROJECTION );
  glPushMatrix( );               // -- Guarda la Matriz de Proyección --
  glLoadIdentity( );
  glOrtho( 0, V_Ancho, 0, V_Alto, -1, 1 ); // -- Cambia a modo ortogáfico --
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix( );              // -- Guarda la Matriz de Modelado --
  glLoadIdentity( );
  glEnable( GL_TEXTURE_2D );
  glDisable( GL_DEPTH_TEST );
}

// -----------------------------------------------------------------------------
// -- Termina_ortho_2D() -------------------------------------------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::termina_ortho_2D( void ) {
  glEnable( GL_DEPTH_TEST );
  glDisable( GL_TEXTURE_2D ); 
  glMatrixMode( GL_PROJECTION );
  glPopMatrix( );                // -- Restaura la Matriz de Proyección --
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix( );                // -- Restaura la Matriz de Modelado --
  if ( !color_material ) glDisable( GL_COLOR_MATERIAL );
  if (  lighting       ) glEnable(  GL_LIGHTING );   
}

// -----------------------------------------------------------------------------
// -- Informacion --------------------------------------------------------------
// -----------------------------------------------------------------------------
char *c_sdl_con_opengl::info_t_espera_frames( void ) {
  sprintf( texto, "msg:%d/%d", frames - t_espera, frames );
  return texto;
}

char *c_sdl_con_opengl::info_posicion( void ) {
  sprintf( texto, "%3.1f %3.1f %3.1f", cpx, cpy, cpz );  
  return texto;
}

char *c_sdl_con_opengl::info_rotacion( void ) {
  sprintf( texto, "%3.0f %3.0f", ax, ay );  
  return texto;
}

char *c_sdl_con_opengl::info_estados( void ) {
  if ( activa_enfoque_camara )    texto[0]='E'; else texto[0]=' ';
  if ( color_material )           texto[1]='M'; else texto[1]=' ';
  if ( lighting       )           texto[2]='L'; else texto[2]=' ';
  if ( glIsEnabled( GL_LIGHT0 ) ) texto[3]='1'; else texto[3]=' ';
  if ( glIsEnabled( GL_LIGHT1 ) ) texto[4]='2'; else texto[4]=' ';
  if ( glIsEnabled( GL_LIGHT2 ) ) texto[5]='3'; else texto[5]=' ';
  if ( glIsEnabled( GL_FOG ) )    texto[6]='J'; else texto[6]=' ';
  texto[7] = '\0';
  return texto;
}

void c_sdl_con_opengl::ver_info( c_fuente_bitmap *fuente, const char *mensaje ) {
  int static alto = fuente->altura(); int pos = 0;
  fuente->escribe_b_n( 0, pos, mensaje ); pos += alto;
  fuente->escribe_b_n( 0, pos, this->info_t_espera_frames() ); pos += alto;
  // fuente->escribe_b_n( 0, pos, this->info_posicion() ); pos += alto;
  fuente->escribe_b_n( 0, pos, this->info_rotacion() ); pos += alto;
  fuente->escribe_b_n( 0, pos, this->info_estados()  );
}

// -----------------------------------------------------------------------------
// -- Compatibilidad de las Extensiones de la Tarjeta Gráfica ------------------
// -----------------------------------------------------------------------------
void c_sdl_con_opengl::compatible( void ) {
  // ofstream tarjeta_grafica_EXT("tarjeta_grafica_EXT.txt");
  const GLubyte* glExtensions = glGetString( GL_EXTENSIONS ); 
  int i;
  for ( i = 0; glExtensions[i] != '\0'; i++ );
  char *Extensiones = new char[i + 1];
  for ( i = 0; glExtensions[i] != '\0'; i++ ) Extensiones[i] =  char( glExtensions[i] );
  Extensiones[i] = '\0';
  #define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT  0x851C
  #define GL_MAX_TEXTURE_UNITS_ARB          0x84E2
  glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT, &Cube_Map_Texture_Size_Ext ); 
  glGetIntegerv( GL_MAX_TEXTURE_UNITS_ARB,         &Texture_Units_ARB );
  char *p = strtok( Extensiones, " " );
  if( p ) { 
    // tarjeta_grafica_EXT << p << endl; 
    if ( strcmp( p, "GL_ARB_texture_cube_map" ) == 0 ) Texture_Cube_Map = true;
    if ( strcmp( p, "GL_ARB_multitexture" ) == 0 )     Multitexture     = true; 
  }
  while( p ) {
    p = strtok( NULL, " " );
    if( p ) { 
      // tarjeta_grafica_EXT << p << endl; 
      if ( strcmp( p, "GL_ARB_texture_cube_map" ) == 0 ) Texture_Cube_Map = true;
      if ( strcmp( p, "GL_ARB_multitexture" ) == 0 )     Multitexture     = true; 
    }
  }
  delete[] Extensiones;
  // tarjeta_grafica_EXT.close();
}

// -----------------------------------------------------------------------------
// -- FUNCION QUE CAPTURA LA PANTALLA ------------------------------------------
// -----------------------------------------------------------------------------
void Captura_Pantalla( const char *nombre_archivo ) {
  SDL_Surface *tmp;
  GLint viewport[4];		/* Vista actual */
  glGetIntegerv( GL_VIEWPORT, viewport );
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    tmp = SDL_CreateRGBSurface( SDL_SWSURFACE, viewport[2], viewport[3], 24, 0xff0000, 0x00ff00, 0x0000ff, 0x000000 );
  #else
    tmp = SDL_CreateRGBSurface( SDL_SWSURFACE, viewport[2], viewport[3], 24, 0x0000ff, 0x00ff00, 0xff0000, 0x000000 );
  #endif
  glPixelStorei( GL_PACK_ALIGNMENT,   4 );
  glPixelStorei( GL_PACK_ROW_LENGTH,  0 );
  glPixelStorei( GL_PACK_SKIP_ROWS,   0 );
  glPixelStorei( GL_PACK_SKIP_PIXELS, 0 );
  glCopyPixels( 0, 0, viewport[2], viewport[3], GL_COLOR );
  glReadPixels( 0, 0, viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE, tmp->pixels );
  tmp = MirrorSurfaceX( tmp ); // -- La imagen es invertida en el eje X --
  SDL_SaveBMP( tmp, nombre_archivo );
  SDL_FreeSurface( tmp ); tmp = NULL;
}
