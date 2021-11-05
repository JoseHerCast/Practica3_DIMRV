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

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  -- INICIALIZAR SDL + OPENGL --
//  ------------------------------
//  ------------------------------
//
//  -- Iniciar SDL --
//  -----------------
//  atexit( SDL_Quit );
//  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){
//    cerr << "No se pudo iniciar la libreria SDL: " << SDL_GetError() << endl;        
//    exit(1);
//  }
//  
//  -- Información de la Tarjeta de Video --
//  ----------------------------------------
//  const SDL_VideoInfo *VideoInfo = SDL_GetVideoInfo();  
//  if( VideoInfo == NULL ) {
//    cerr << "No se pudo obtener el VideoInfo: " << SDL_GetError() << endl;          
//    exit(1);
//  } 
//  int P_bpp = (int)VideoInfo->vfmt->BitsPerPixel;
//  if ( ( P_bpp != 16 ) && ( P_bpp != 32 ) ) P_bpp = 16;
//  
//  -- Configuración SDL --
//  -----------------------
//  int VideoFlags = 0;
//  VideoFlags  = SDL_OPENGL;     //  <---- OPENGL ---                                   
//  VideoFlags |= SDL_HWPALETTE;       
//  if (VideoInfo->hw_available) VideoFlags |= SDL_HWSURFACE;
//  else                         VideoFlags |= SDL_SWSURFACE;
//  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,   16 );
//  SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE,  1 );
//  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,  1 );
//  SDL_GL_SetAttribute( SDL_GL_RED_SIZE,      5 ); // 5 -- 5 -- 8
//  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,    6 ); // 5 -- 6 -- 8
//  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,     5 ); // 5 -- 5 -- 8
//
//  --  Inicia la Pantalla --
//  -------------------------
//  int V_Ancho = 640, V_Alto = 480; 
//  SDL_Surface *pantalla = SDL_SetVideoMode( V_Ancho, V_Alto, P_bpp, VideoFlags );
//  if( pantalla == NULL ){
//    cerr << "No se pudo iniciar el modo de pantalla: " << SDL_GetError() << endl;           
//    exit(1);
//  }
//
//  -- Pone nombre a la ventana. --
//  -------------------------------
//  SDL_WM_SetCaption( "Nombre_Ventana", NULL );  
//  
//  -- Cargamos el Icono de la Ventana --
//  -------------------------------------
//  SDL_Surface *img_icono = IMG_Load( "Nombre_Icono.PNG" );
//  if( !img_icono ) {
//    cerr << "No se pudo cargar: " << "Nombre_Icono.PNG" << endl;
//    exit(1);
//   }
//  SDL_WM_SetIcon( img_icono, NULL );
//  SDL_FreeSurface( img_icono ); img_icono = NULL;
//
//  -- Activación de Repetición de Teclas. --
//  -----------------------------------------
//  if ( SDL_EnableKeyRepeat( 1, SDL_DEFAULT_REPEAT_INTERVAL ) )	 {
//    cerr << "Falla activando repeticion de teclas: " << SDL_GetError() << endl;
//    exit(1);
//  }
//
//  -- Configuración del entorno 3D --
//  ----------------------------------
//  glClearColor( GLfloat R,           // Borrado del Buffer Color.
//                GLfloat G,           // Componentes R-G-B-A
//                GLfloat B, 
//                GLfloat A );    
//  glClearDepth( 1.0f );              // Borrado del Buffer Depth
//  glDepthFunc( GL_LEQUAL );          // Función de Borrado Buffer Depth      
//  glClearStencil( 0 );               // Borrado del Buffer Stencil
//  glFrontFace( GL_CCW );             // GL_CCW   o GL_CW.
//  glCullFace( GL_BACK );             // GL_FRONT o GL_BACK.
//  glShadeModel( GL_SMOOTH );         // Activamos el Sombreado Suave, (GL_FLAT) Plano.
//  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL); //  GL_FILL, GL_LINE y GL_POINT
//  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
//  glViewport( 0, 0, V_Ancho, V_Alto ); // Define la Ventana de visualizado.
//  glMatrixMode(GL_PROJECTION);         // Selecciona la Matriz de Proyección.
//  glLoadIdentity();                    // Reemplaza la matriz. 
//  gluPerspective( 45.0f, (GLfloat)V_Ancho/(GLfloat)V_Alto, .5f , -1000.0f );
//  glMatrixMode(GL_MODELVIEW);          // Selecciona la Matriz de Modelado.               
//  glLoadIdentity();                    // Reemplaza la matriz.
//  glEnable( GL_DEPTH_TEST );        // Activamos el Test de Profundidad.
//  glEnable( GL_CULL_FACE );         // NO DIBUJA LAS CARAS TRASERAS
//  glEnable( GL_COLOR_MATERIAL );    // Activa el Color de los Vértices.
//
//  -- Empezar a Dibujar --
//  -----------------------
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//  glLoadIdentity();
//             // cp -> Posición de la Cámara. ( Camera Possition )
//             // ce -> Ojo de la Cámara.      ( Camera Eye )
//  gluLookAt( cpx, cpy, cpz, cex, cey, cez, 0.0f, 1.0f, 0.0f );
//
//
//  -- DIBUJAR --
//  -------------
//  Esta parte es tratada en cada Práctica.
//
//
//  -- Terminar de Dibujar --
//  -------------------------
//  // glFlush();  // Fuerza las operaciones pendientes.
//  SDL_GL_SwapBuffers();
//
//  -- Cerrar SDL + OPENGL --
//  --------------------------
//  SDL_FreeSurface( pantalla );    // -- Liberar memoria pantalla --
//  pantalla = NULL;
//  SDL_Quit();                     // -- Cerrar SDL --
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  TIPOS OPENGL:
//  -------------
//  -------------
//    typedef void            GLvoid;       // Sin tipo definido.
//    typedef unsigned char   GLboolean;    // Boleano, [ Verdad - Mentira ]
//    typedef signed char     GLbyte;       // 1-byte con signo.
//    typedef unsigned char   GLubyte;      // 1-byte sin signo.
//    typedef unsigned int    GLenum;       // Enumerado.
//    typedef short           GLshort;      // 2-byte con signo.
//    typedef unsigned short  GLushort;     // 2-byte sin signo.
//    typedef int             GLint;        // 4-byte con signo.
//    typedef unsigned int    GLuint;       // 4-byte sin signo.
//    typedef int             GLsizei;      // 4-byte con signo.
//    typedef float           GLfloat;      // Coma flotante precisión simple.
//    typedef double          GLdouble;     // Coma flotante precisiónd doble.
//
//    typedef float           GLclampf;
//    typedef double          GLclampd;
//    typedef unsigned int    GLbitfield;
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  LISTAS COMPILADAS:
//  ------------------
//  ------------------
//  glListBase( 0 );  		// valor inicial para glGenLists() normalmanete 0.
//  GLuint lista = glGenLists(1);
//  glNewList( lista, GL_COMPILE );
//    DIBUJAR PRIMITIVAS
//  glEndList();
//
//  glCallList( lista );		  // Dibuja la lista compilada	
//
//  glDeleteLists( lista,  1 );   // Borra una lista
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  DIBUJANDO PRIMITIVAS:
//  ---------------------
//  ---------------------
//  Configuracion previa de puntos, lineas y patrones:
//  --------------------------------------------------
//
//  glPointSize( GLfloat tamaño );  Establece el tamaño de los puntos
//  glLineWidth( GLfloat grosor );  Establece el grosor de las líneas
//  GLushort patron = 0x5555;   // Patron de la Línea, usando los BITS. 
//  GLint    factor = 5;        // Factor de repetición del Patron 
//  glEnable( GL_LINE_STIPPLE ); 
//    glLineStipple( factor, patron );
//    DIBUJAR LINEAS CON UN PATRON
//  glDisable( GL_LINE_STIPPLE ); 
//
//  La función glBegin() - glEnd():
//  -------------------------------
//
//  glBegin( GLenum Parametros );  Dibuja diferentes tipos de primitivas.
//    PARAMETOS:
//    - GL_POINTS         Dibuja puntos.
//
//    - GL_LINES          Dibuja líneas usando dos puntos.
//
//    - GL_LINE_STRIP     Dibuja líneas con  dos  puntos  iniciales,  los  siguientes
//                        puntos continúan la línea.   
//    - GL_LINE_LOOP      Dibuja líneas  como (GL_LINE_STRIP) pero cierra  el  último
//                        punto con el primero.                        
//    - GL_TRIANGLES      Dibuja triángulos con 3 puntos.
//
//    - GL_TRIANGLE_STRIP Dibuja triángulos encadenados. Con los trés primeros puntos
//                        hace el primer triángulo, luego con cada nuevo punto y  los
//                        dos anteriores crea los siguientes.
//    - GL_TRIANGLE_FAN   Dibuja triángulos usando  el primer punto de  todos  y  los
//                        dos últimos. El primer punto de cada triángulo es  común  y 
//				          es el primero de todos.
//    - GL_QUADS          Dibuja un Rectángulo usando 4 puntos.
//
//    - GL_QUAD_STRIP     Dibuja un Rectángulos usando los 2 puntos anteriores  y los
//                        2 posteriores.      
//    - GL_POLYGON        Dibuja un Polígono Convexo de "n" puntos.
//
//    DIBUJAR PUNTOS, COLORES, NORMALES, COORDENADAS DE TEXTURA...
//
//  glEnd();     Termina de dibujar puntos. 
//
//  Establecer el color:
//  --------------------
//  glColor3f(  GLfloat rojo, GLfloat verde, GLfloat azul ); [ 0.0f - 255.0f ]
//  glColor3ub( GLubyte rojo, GLubyte verde, GLubyte azul ); [ 0 - 255 ]
//  glColor4f(  GLfloat rojo, GLfloat verde, GLfloat azul, GLfloat alpha ); 
//  glColor4ub( GLubyte rojo, GLubyte verde, GLubyte azul, GLfloat alpha );
//  GLfloat Rojo[3]  = { 1.0f, 0.0f, 0.0f };
//  GLubyte Verde[3] = { 0, 255, 0 }
//  glColor3fv(  Rojo  );  glColor4fv(  *GLfloat[4] );  
//  glColor3ubv( Verde );  glColor4ubv( *GLubyte[4] );  
// 
//  Establecer las coordenadas:
//  ---------------------------
//  glNormal3f( GLfloat x, GLfloat y, GLfloat z );  // -- Normales, ver más abajo --
//  glTexCoord2f( GLfloat u, GLfloat v );  // -- Coordenadas de Textura, ver más abajo --
//
//  glVertex2f( GLfloat x,    GLfloat y  );
//  glVertex3i( GLint   x,    GLint   y  );
//  glVertex3f( GLfloat x,    GLfloat y,     GLfloat z    );
//  glVertex3fv( GLfloat *punto[3] );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  OPERACIONES USUALES CON LAS MATRICES:
//  -------------------------------------
//  -------------------------------------
//  glLoadIdentity();	 Borra la matriz actual.
//  glPushMatrix(); 	 Mete en la Pila una Copia de la Matriz actual.
//  glPopMatrix();	     Saca de la Pila la última Copia de la Matriz.
//  GLfloat Matriz[4][4];
//  glMultMatrixf( (const GLfloat *) Matriz );  Multiplica la Matriz Actual. 
//
//  glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z );
//    Realiza una rotación del espacio coordenado por una medida  de  (angle) tomados 
//    en grados a lo largo del vector determinado. Es  recomendable  que  (x,y,z) sea
//    un vector normalizado (o sea magnitud(x,y,z) = 1).
//
//  glTranslatef( GLfloat x, GLfloat y, GLfloat z );
//    Esta  función  traslada  el  espacio  coordenado  en x, y, z unidades sobre sus 
//    respectivos ejes coordenados X, Y, Z. 
//
//  glScalef( GLfloat x, GLfloat y, GLfloat z );
//     Cambia la proporción de los objetos respecto a los ejes coordenados, lo que es
//     equivalente a decir que los estira o encoge una cantidad determinada por los
//     parámetros de la función x,y,z.
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  OBJETOS CUADRÁTICOS:
//  --------------------
//  --------------------
//  gluNewQuadric(); Crea un objeto cuadrático. 
//                   GLUquadricObj *Esfera = gluNewQuadric();
//
//  gluQuadricOrientation( GLUquadricObj *Quadratic, GLenum Parametros );
//    PARAMETROS:       DETERMINA LA ORIENTACION DE LAS NORMALES DE ILUMINACIÓN        
//    - GLU_OUTSIDE      NORMALES EXTERIORES
//    - GLU_INSIDE       NORMALES INTERIORES
//
//  gluQuadricNormals( GLUquadricObj *Quadratic, GLenum Parametros );
//    PARAMETROS:       CALCULA LAS NORMALES DE ILUMINACIÓN DEL QUADRATIC
//    - GLU_SMOOTH      NORMALES SUAVES
//    - GLU_FLAT        NORMALES PLANAS
//
//  gluQuadricDrawStyle( GLUquadricObj *Quadratic, GLenum Parametros);
//    PARAMETROS:       Define la forma de dibujar.
//    - GLU_FILL
//    - GLU_LINE
//    - GLU_POINT
//
//  gluQuadricTexture( GLUquadricObj *Quadratic, GL_TRUE  ); // ACTIVA TEXTURA
//       
//  gluSphere(     Esfera, GLfloat radio, GLint Longitud, GLint Latitud ); 
//
//  gluCylinder( Cilindro, GLfloat radioInferior, GLfloat radioSuperior, 
//                                    GLfloat altura, GLint segmentos, GLint pilas );
//
//  gluDisk(        Disco, GLfloat radioInterior, GLfloat radioExterior, 
//                                                    GLint segmentos, GLint pilas );
//
//  gluPartialDisk( Disco, GLfloat radioInterior, GLfloat radioExterior, segmentos, 
//
//                               pilas, GLfloat anguloInicial, GLfloat anguloFinal );
//
//  gluDeleteQuadric( GLUquadricObj *Quadratic );    Borra un objeto cuadrático.
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  ILUMINACIÓN:
//  ------------
//  ------------
//  CLASES DE LUZ:
//  --------------
//    Luz Direccional -- El Sol, rayos paralelos.
//    Luz Puntual     -- Una Bombilla, rayos en todas direcciones.
//    Luz Focal       -- Un Foco, rayos en forma de cono atenuado.
//
//  glLightfv( GLenum luz, GLenum Parametros, GLfloat Color[4] );
//    LUZ:     		     de GL_LIGHT0 a GL_LIGHT7.
//    PARAMETROS:
//    - GL_AMBIENT            Color residual de la luz ambiente.
//    - GL_DIFFUSE            Color de la Luz.
//    - GL_SPECULAR           Color de los Brillos.
//    - GL_POSITION           Posicion del punto de Luz. Tiene dos tipos:
//                            w = 0.0f Luz Direccional o Solar
//                            w = 1.0f Luz Puntual.
//    - GL_SPOT_DIRECTION     Dirección del Cono de Luz. Luz Focal.
//
//  glLightf( GLenum luz, GLenum Parametros, GLfloat valor );
//    LUZ:     		     de GL_LIGHT0 a GL_LIGHT7.
//    PARAMETROS:
//    - GL_SPOT_CUTOFF           Angulo de obertura del cono [ 0 - 90 grados ]
//    - GL_SPOT_EXPONENT         Perdida intensidad al centro cono [ 0-128 ] 
//    - GL_CONSTANT_ATTENUATION  Por defecto 1 Rango [ 0 - 1 ]
//    - GL_LINEAR_ATTENUATION    Por defecto 0 Rango [ 0 - 1 ]
//    - GL_QUADRATIC_ATTENUATION Por defecto 0 Rango [ 0 - 1 ]
//      Tenemos que la función que atenúa la iluminación con la distancia es:
//      1/( GL_CONSTANT_ATTENUATION + GL_LINEAR_ATTENUATION * distancia 
//                                         + GL_QUADRATIC_ATTENUATION * distancia^2 )
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  NORMALES DE ILUMINACIÓN:
//  ------------------------
//  ------------------------
//  glNormal3f( GLfloat x, GLfloat y, GLfloat z ); // Las normales de iluminación son
//      vectores unitarios que representan la dirección de la reflexión de la luz.
//      Vector unitario es el que su módulo es uno. 1 = sqrt( (x*x) + (y*y) + (z*z) )
//      Se puede calcular las normales utilizando el producto en cruz:
//        nx = ( ay * bz ) - ( az * by )
//        ny = ( az * bx ) - ( ax * bz )
//        nz = ( ax * by ) - ( ay * bx )
//      Despues hay que normalizar este vector, bien manualmente o automáticamente.
//        modulo = (GLfloat) sqrt( ( nx * nx ) + ( ny * ny ) + ( nz * nz ) );
//        nx /= modulo; ny /= modulo; nz /= modulo;
//
//  glEnable(  GL_NORMALIZE );   Normaliza los vectores de las normales en tiempo de
//  glDisable( GL_NORMALIZE );   ejecución. Esto reduce potencia de calculo.
//  glEnable( GL_AUTO_NORMAL );  Calcula las normales.	 
//  glDisable( GL_AUTO_NORMAL );	
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  MATERIALES:
//  -----------
//  -----------
//  glDisable( GL_COLOR_MATERIAL );
//  glMaterialfv( GL_enum Caras, GL_enum Parametros, GLfloat Color[4] );
//    CARAS:
//    - GL_FRONT                 Cara Frontal
//    - GL_BACK            	     Cara Trasera
//    - GL_FRONT_AND_BACK        Caras Frontal y Trasera
//    PARAMETROS:
//    - GL_AMBIENT               Color Zona no Iluminada
//    - GL_DIFFUSE               Color Zona Iluminada
//    - GL_AMBIENT_AND_DIFFUSE   Color Zona Iluminada y no Iluminada
//    - GL_SPECULAR              Color Zona Reflejos
//    - GL_SHININESS             Catidad de Reflejos [ 0.0f - 128.0f ]
//    - GL_EMISSION              Color Luz Emitida
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  CONFIGURACIÓN DE DIBUJADO:
//  --------------------------
//  --------------------------
//  glShadeModel( GL_SMOOTH );                    //  GL_SMOOTH | GL_FLAT
//  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );  //  GL_FILL   | GL_LINE  | GL_POINT
//  glFrontFace( GL_CCW );                        //  GL_CCW    | GL_CW.
//  glCullFace( GL_enum Parametros );
//    PARAMETROS:
//    - GL_FRONT          NO CALCULA LAS CARAS FRONTALES
//    - GL_BACK           NO CALCULA LAS CARAS TRASERAS
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  ESTADOS MÁS USUALES:
//  --------------------
//  --------------------
//  glEnable( GL_enum Parametros ); glDisable( GL_enum Parametros );
//    PARAMETROS:
//    - GL_DEPTH_TEST         ACTIVA/DESACTIVA TEST DE PROFUNDIDAD 
//    - GL_CULL_FACE          ACTIVA/DESACTIVA NO DIBUJA LAS CARAS glCullFace()
//    - GL_LIGHTING           ACTIVA/DESACTIVA TODAS LAS LUCES
//    - GL_LIGHT0-7           ACTIVA/DESACTIVA LA LUZ NUMERO [0-7]
//    - GL_COLOR_MATERIAL     ACTIVA/DESACTIVA ENTRE glColor/glMaterial
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  MANEJO DE ATRIBUTOS:
//  --------------------
//  --------------------
//  glPushAttrib( GL_enum Parametros );          // -- GUARDA EL ESTADO DE LOS BIT --
//    PARAMETROS:
//    - GL_COLOR_BUFFER_BIT  -> GL_ALPHA_TEST | GL_BLEND
//    - GL_DEPTH_BUFFER_BIT  -> GL_DEPTH_TEST
//    - GL_FOG_BIT           -> GL_FOG
//    - GL_LIGHTING_BIT      -> GL_COLOR_MATERIAL | GL_LIGHTING | GL_LIGHT0-7 
//    - GL_POLYGON_BIT       -> GL_CULL_FACE | GL_POLYGON_MODE | GL_POLYGON_SMOOTH
//
//  glPopAttrib();       // -- Restaura el Estado de Bit guardado con glPushAttrib();
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  USANDO ARRAYS PARA DIBUJAR:
//  ---------------------------
//  ---------------------------
//  GLfloat Normal_Cubo[]   = { 0.0f, 0.0f, 1.0f, 0.0f, ... };
//  GLfloat TexCoord_Cubo[] = { 0.0f, 0.0f, 1.0f, 0.0f, ... };
//  GLfloat Vertex_Cubo[]   = { 0.0f, 0.0f, 1.0f, 0.0f, ... };
//  GLubyte Color_Cubo[]    = { 255,   255,    0,  127, ... };
//
//  glEnableClientState( GL_enum Parametros );    // Activa los Punteros a Arrays
//    Parámetros:
//    - GL_NORMAL_ARRAY 
//    - GL_TEXTURE_COORD_ARRAY
//    - GL_COLOR_ARRAY
//    - GL_VERTEX_ARRAY
//
//  glNormalPointer(      GL_FLOAT, 0, Array_Normal );
//  glTexCoordPointer( 2, GL_FLOAT, 0, Array_Coord  );
//  glColorPointer(    3, GL_UNSIGNED_BYTE, 0, Array_Color );
//  glVertexPointer(   3, GL_FLOAT, 0, Array_Vertex );
//
//  glDrawArrays( GL_TRIANGLES, inico, final );   // Dibuja usando Arrays.
//
//  glDisableClientState( GL_enum Parametros );   // Desactiva los Punteros a Arrays
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  FUNCIONES DEL BUFFER DE COLOR:
//  ------------------------------
//  ------------------------------
//  glClearColor( GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha );
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//  glColorMask( GLboolean Red, GLboolean Green, GLboolean Blue, GLboolean Alpha );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  FUNCIONES DEL BUFFER DE PROFUNDIDAD:
//  ------------------------------------
//  ------------------------------------
//  glClearDepth( GLfloat z );
//  glClear( GL_DEPTH_BUFFER_BIT );
//  glEnable( GL_DEPTH_TEST ); glDisable( GL_DEPTH_TEST );
//
//  glDepthFunc( GLenum funcion );
//    funcion:
//    - GL_NEVER    Siempre false.
//    - GL_LESS     True si Z de referencia <  Z de profundidad.
//    - GL_EQUAL    True si Z de referencia =  Z de profundidad.
//    - GL_LEQUAL   True si Z de referencia <= Z de profundidad.
//    - GL_GREATER  True si Z de referencia >  Z de profundidad.
//    - GL_NOTEQUAL True si Z de referencia != Z de profundidad.
//    - GL_GEQUAL   True si Z de referencia => Z de profundidad.
//    - GL_ALWAYS   Siempre true.
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  FUNCIONES DEL BUFFER DE ESTARCIDO:
//  ----------------------------------
//  ----------------------------------
//  void glClearStencil( GLint s );
//  void glStencilMask( GLuint mascara );
//  glClear( GL_STENCIL_BUFFER_BIT );
//  glEnable(GL_STENCIL_TEST);  glDisable(GL_STENCIL_TEST);
//
//  void glStencilFunc( GLenum func, GLint ref, GLuint mascara );
//    funciones:
//    - GL_NEVER    La verificación de estarcido siempre falla (no se dibuja).
//    - GL_LESS     Pasa si el valor de referencia <  que el valor de estarcido
//    - GL_EQUAL    Pasa si el valor de referencia == que el valor de estarcido
//    - GL_LEQUAL   Pasa si el valor de referencia <= que el valor de estarcido.
//    - GL_GREATER  Pasa si el valor de referencia >  que el valor de estarcido
//    - GL_NOTEQUAL Pasa si el valor de referencia != que el valor de estarcido.
//    - GL_GEQUAL   Pasa si el valor de referencia >= que el valor de estarcido.
//    - GL_ALWAYS   Por  defecto. La  verificación  de  estarcido  siempre  pasa 
//                  (siempre se realiza una operación de dibujo).
//
//  void glStencilOp( GLenum fallo, GLenum zfallo, GLenum zpass );
//    operacion:
//    - GL_KEEP     Mantiene los contenidos actuales del buffer de estarcido.
//    - GL_ZERO     Establece el valor cero en el buffer de estarcido.
//    - GL_REPLACE  Establece el valor de la función de referencia en el estarcido.
//    - GL_INCR     Incrementa el valor actual del buffer de estarcido.
//    - GL_DECR     Decrementa el valor actual del buffer de estarcido.
//    - GL_INVERT   Invierte el orden binario del valor actual del buffer estarcido.
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  FUNCIONES DEL BUFFER DE ACUMULACIÓN:
//  ------------------------------------
//  ------------------------------------
//  glAccum( GLenum func, GLfloat valor );
//    funciones:
//    - GL_ACCUM   Añade valores de color escalados al buffer de acumulación.
//    - GL_LOAD    Abre  valores  de  color  escalados en  el  buffer de acumulación, 
//                 sustituyendo los que hubiera antes.
//    - GL_ADD     Añade un color constante a los valores del buffer de acumulación.
//    - GL_MULT    Multiplica los valores de color en el buffer de acumulación por un
//                 color constante (efectos de filtro).
//    - GL_RETURN  Copia el buffer de acumulación en el buffer de color principal.
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  NIEBLA:
//  -------
//  -------
//  GLfloat color_de_niebla[4]={r,g,b,a};
//  glFogfv( GL_FOG_COLOR, color_de_niebla );
//
//  GLint color_de_niebla[4]={r,g,b,a};
//  glFogfi( GL_FOG_COLOR, color_de_niebla );
//
//  glFogi( GL_FOG_MODE, GLenum funciones );
//    funciones:
//    - GL_LINEAR   Para indicios de profundidad.
//    - GL_EXP      Para niebla espesa o nubes.
//    - GL_EXP2     Para neblina y humo.
//
//  glFogf( GLenum funciones, GLfloat valor );
//    funciones:
//    - GL_FOG_DENSITY  de 0.0f a 1.0f, valor normal 0.1f ( No para GL_LINEAR )
//    - GL_FOG_START    de 0.0f a 1.0f.
//    - GL_FOG_END      de 0.0f a 1.0f.
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  FUNCIONES DE MEZCLA DE COLOR:
//  -----------------------------
//  -----------------------------
//  glEnable(GL_BLEND); glDisable(GL_BLEND);
//
//  glBlendFunc( GLenum origen, GLenum destino );
//    origen:
//    - GL_ZERO       Color fuente=0,0,0,0. 
//    - GL_ONE        Usos <?> Color fuente. 
//    - GL_DST_COLOR  El color origen se multiplica por el color del píxel de destino 
//    - GL_SRC_ALPHA  El color origen se multiplica por el valor alfa de origen. 
//    - GL_DST_ALPHA  El color origen se multiplica por el valor alfa de destino. 
//                    Microsoft OpenGL no lo soporta. 
//    - GL_ONE_MINUS_DST_COLOR  Origen se multiplica por (1,1,1,1; color de destino).
//    - GL_ONE_MINUS_SRC_ALPHA  Origen se multiplica por (1, valor alfa de origen).
//    - GL_ONE_MINUS_DST_ALPHA  Origen se multiplica por (1, valor alfa de destino).
//                              Microsoft OpenGL no lo soporta. 
//    - GL_SRC_ALPHA_SATURATE   Origen se multiplica por el mínimo delos valores alfa
//                              de origen y (1, valor de destino). No Micro. OpenGL  
//
//    destino:
//    - GL_ZERO       Color destino=0,0,0,0. 
//    - GL_ONE        Usos <?>Color destino. 
//    - GL_DST_COLOR  Color de destino se multiplica por el color del píxel de origen
//    - GL_SRC_ALPHA  Color de destino se  multiplica por el valor alfa de de origen. 
//    - GL_DST_ALPHA  Color  de  destino  se multiplica por el valor alfa de destino. 
//                    Microsoft OpenGL no lo soporta. 
//    - GL_ONE_MINUS_DST_COLOR  Destino se multiplica por (1,1,1,1; color de origen). 
//    - GL_ONE_MINUS_SRC_ALPHA  Destino se multiplica por (1, valor alfa de origen ). 
//    - GL_ONE_MINUS_DST_ALPHA  Destino se multiplica por (1, valor alfa de destino).
//                              Microsoft OpenGL no lo soporta. 
//    - GL_SRC_ALPHA_SATURATE   Destino se multiplica por el mínimo  de  los  valores
//                              alfa de origen y (1, valor de destino). No M. OpenGL
//
//  ANTI-ESCALONADO, MAS RÁPIDO QUE CON EL BUFFER DE ACUMULACIÓN
//  glEnable( GL_BLEND );
//    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//    glEnable( GL_LINE_SMOOTH );
//    glEnable( GL_POINT_SMOOTH );
//    glEnable( GL_POLYGON_SMOOTH );
//    -- DIBUJAR OBJETOS --
//            ...
//            ...
//  glDisable( GL_BLEND );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  CARGA DE IMÁGENES PARA TEXTURAS:
//  --------------------------------
//  --------------------------------
//  SDL_Surface *Temp = IMG_Load( nombre_archivo );
//  SDL_Surface *bmp  = SDL_DisplayFormat( Temp );      // Puede ser no aconsejable.
//  SDL_Surface *bmp  = SDL_DisplayFormatAlpha( Temp ); // Puede ser no aconsejable.
//  SDL_FreeSurface( Temp ); SDL_FreeSurface( bmp  );
//
//  GLuint textura;                                 // DEFINE LAS TEXTURAS
//  glGenTextures( 1, &textura );                   // CREA LAS TEXTURAS
//  glBindTexture( GL_TEXTURE_1D, textura );        // ASIGNA LA TEXTURA 1D
//  glBindTexture( GL_TEXTURE_2D, textura );        // ASIGNA LA TEXTURA 2D
//  glEnable( GL_TEXTURE_1D ); glDisable( GL_TEXTURE_1D );
//  glEnable( GL_TEXTURE_2D ); glDisable( GL_TEXTURE_2D );
//  glDeleteTextures( 1, &textura );                // BORRA LAS TEXTURAS
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  CREACIÓN DE TEXTURAS 1D:
//  ------------------------
//  ------------------------
//  glTexImage1D( GL_TEXTURE_1D, level, format, w, border, format, type, pixels )
//    level:  0,1,2.. nivel de detalle de la textura. Si sólo hay una textura nivel=0
//    format: 3 - 4   - El número de componentes de Color GL_RBG = 3 | GL_RGBA = 4
//    w:      SDL_imagen->w  - El ancho de la imagen en pixels.
//    border: 0 - Sin borde, 1 - Con borde.
//    format: GL_RBG | GL_RGBA 
//    type:   GL_UNSIGNED_BYTE | GL_BYTE | GL_BITMAP | GL_SHORT | GL_INT | GL_FLOAT
//    pixel:  SDL_imagen->pixels
//
//  gluBuild1DMipmaps(GL_TEXTURE_1D, format, w, format, type, pixels )
//    format: 3 - 4   - El número de componentes de Color GL_RBG = 3 | GL_RGBA = 4
//    w:      SDL_imagen->w  - El ancho de la imagen en pixels.
//    format: GL_RBG | GL_RGBA 
//    type:   GL_UNSIGNED_BYTE | GL_BYTE | GL_BITMAP | GL_SHORT | GL_INT | GL_FLOAT
//    pixel:  SDL_imagen->pixels
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  CREACIÓN DE TEXTURAS 2D:
//  ------------------------
//  ------------------------
//  glTexImage2D( GL_TEXTURE_2D, level, format, w, h, border, format, type, pixels )
//    level:  0,1,2.. nivel de detalle de la textura. Si sólo hay una textura nivel=0
//    format: 3 - 4   - El número de componentes de Color GL_RBG = 3 | GL_RGBA = 4
//    w:      SDL_imagen->w  - El ancho de la imagen en pixels.
//    h:      SDL_imagen->h  - El alto de la imagen en pixels.
//    border: 0 - Sin borde, 1 - Con borde.
//    format: GL_RBG | GL_RGBA 
//    type:   GL_UNSIGNED_BYTE | GL_BYTE | GL_BITMAP | GL_SHORT | GL_INT | GL_FLOAT
//    pixel:  SDL_imagen->pixels
//
//  gluBuild2DMipmaps(GL_TEXTURE_2D, format, w, h, format, type, pixels )
//    format: 3 - 4   - El número de componentes de Color GL_RBG = 3 | GL_RGBA = 4
//    w:      SDL_imagen->w  - El ancho de la imagen en pixels.
//    h:      SDL_imagen->h  - El alto de la imagen en pixels.
//    format: GL_RBG | GL_RGBA 
//    type:   GL_UNSIGNED_BYTE | GL_BYTE | GL_BITMAP | GL_SHORT | GL_INT | GL_FLOAT
//    pixel:  SDL_imagen->pixels
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  ASIGNANDO LAS PROPIEDADES A LA TEXTURA:
//  ---------------------------------------
//  ---------------------------------------
//  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_enum Parametros );
//  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_enum Parametros );
//    Parámetros:
//    - GL_CLAMP: Recorta la textura una vez esta supera las coordenadas 1.0 en (S,T)
//    - GL_REPEAT: Repita la textura sespués de 1.0 bien sea en S y/o T.
//
//  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_enum Parametros );
//  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_enum Parametros );
//    Parámetros:
//    - GL_NEAREST
//    - GL_LINEAR				// GL_TEXTURE_MAG_FILTER
//    - GL_NEAREST_MIPMAP_NEAREST   // GL_TEXTURE_MIN_FILTER
//
//  glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color[3] );
//
//  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
//    - GL_DECAL     la textura reemplaza los colores previos no respeta los Alpha.
//    - GL_REPLACE   la textura reemplaza los colores previos respeta los Alpha.
//    - GL_MODULATE  Combina el color del objeto conla textura.
//  glTexEnvi(  GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND  );
//  glTexEnvfv( GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color[4] );
//
//  glTexGeni( coord, pname, param );
//    coord: GL_S, GL_T, GL_R, o GL_Q
//    pname: GL_TEXTURE_GEN_MODE, GL_OBJECT_PLANE, o GL_EYE_PLANE
//    param: GL_OBJECT_LINEAR, GL_EYE_LINEAR, o GL_SPHERE_MAP
//
//  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//  glEnable(GL_TEXTURE_GEN_S);  glDisable(GL_TEXTURE_GEN_S);
//  glEnable(GL_TEXTURE_GEN_T);  glDisable(GL_TEXTURE_GEN_T);
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  COORDENADAS DE TEXTURA:
//  -----------------------
//  -----------------------
//  glTexCoord2f( GLfloat u, GLfloat v );
//                                               ( 0.5, 1 ) o
//    ( 0, 1 ) o---------o  ( 1, 1 )                       / \
//             |         |                                /   \ 
//             | TEXTURA |                               /     \ 
//             |         |                              / TEXT. \
//    ( 0, 0 ) o---------o ( 1, 0 )           ( 0, 0 ) o---------o ( 1, 0 )
//
//     U -> HORIZONTAL, V - > VERTICAL.
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------     
//  TEXTURA SIN ALPHA -> SE HACE TRANSPARENTE:
//  ------------------------------------------
//  ------------------------------------------
//  glEnable( GL_TEXTURE_2D );
//  glBindTexture( GL_TEXTURE_2D, Textura_Alpha );
//  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  glEnable( GL_BLEND );  
//  glColor4ub( 255, 255, 255, 200 );
//
//    DIBUJAR PRIMITIVA
//
//  glDisable( GL_BLEND );
//  glDisable( GL_TEXTURE_2D );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  TEXTURA CON ALPHA -> NO SE MUESTRAN LOS PIXELS CON ALPHA:
//  ---------------------------------------------------------
//  ---------------------------------------------------------
//  glEnable( GL_TEXTURE_2D );
//  glBindTexture( GL_TEXTURE_2D, Textura_Alpha );
//  glAlphaFunc( GL_GREATER, 0.5f );  // GL_ALWAYS, GL_EQUAL, GL_LEQUAL, GL_LESS...
//  glEnable( GL_ALPHA_TEST );
//
//    DIBUJAR PRIMITIVA
//
//  glDisable( GL_ALPHA_TEST );
//  glDisable( GL_TEXTURE_2D );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  TEXTURA CON ALPHA -> SE MUESTRAN LOS PIXELS CON ALPHA:
//  ------------------------------------------------------
//  ------------------------------------------------------
//  glEnable( GL_TEXTURE_2D );
//  glBindTexture( GL_TEXTURE_2D, Textura_Alpha_Blend );
//  glAlphaFunc( GL_ALWAYS, 1.0); 
//  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  glEnable( GL_ALPHA_TEST );
//  glEnable( GL_BLEND );
//
//    DIBUJAR PRIMITIVA
//
//  glDisable( GL_BLEND );
//  glDisable( GL_ALPHA_TEST );
//  glDisable( GL_TEXTURE_2D );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  CURVA BEZIER 1D:
//  ----------------
//  ----------------
//  -- Creamos un Array con los puntos de control. --
//  -------------------------------------------------
//  #define U 4            // -- Tamaño U del Array de Puntos de Control.  --
//  #define Resolucion 20  // -- Número de divisiones de la Curva.         --
//  GLfloat ctrlPoints[U][3] = {
//    { -4.0, -4.0, 0.0 },   // -- PUNTO INICIAL    --
//    { -2.0,  4.0, 0.0 },   // -- PUNTO DE CONTROL --
//    {  2.0, -4.0, 0.0 },   // -- PUNTO DE CONTROL --
//    {  4.0,  4.0, 0.0 }    // -- PUNTO FINAL      --
//  };
//   
//  -- Define la Bezier. Sólo necesitamos ejecutar ésto una vez. --
//  ---------------------------------------------------------------
//  glMap1f( 
//    GL_MAP1_VERTEX_3,  // GLenum Target - Tipo de dato generado. Vertex_3 X,Y,Z
//    0.0f,			     // GLfloat u1    - Rango menor    de u.
//    Resolucion,        // GLfloat u2    - Rango superior de u.
//    3,			     // GLint Stride  -  O -> Distancia entre puntos X,Y,Z = 3. 
//    U,		         // GLint Order   -  U -> Numero de puntos de  control = 4.
//    &ctrlPoints[0][0]  // const GLfloat * Points - Matriz de puntos de control
//  );
// 
//  -- Dibujamos la Bezier 1D. --
//  -----------------------------
//  glEnable( GL_MAP1_VERTEX_3 );
//    glBegin( GL_LINE_STRIP );
//      for (GLint i = 0; i <= Resolucion; i++) glEvalCoord1f( (GLfloat)i );
//    glEnd();
//  glDisable( GL_MAP1_VERTEX_3 );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  CURVA BEZIER 2D:
//  ----------------
//  ----------------
//  -- Creamos los Arrays con los puntos de control. --
//  ---------------------------------------------------
//  #define U 2
//  #define V 2
//  #define Resolucion 6
//  GLfloat ctrlPoints[U][V][3]= {
//    { { -4.0f,  2.0f,  4.0f },     // -- Esquina Inferior Izquierda ( 0, 0 ) --  
//      { -4.0f,  2.0f, -4.0f } },   // -- Esquina Superior Izquierda ( 0, 1 ) --
//    { { -2.0f,  4.0f,  4.0f }, 
//      { -2.0f,  4.0f, -4.0f } },
//    { {  4.0f, -2.0f,  4.0f },	 // -- Esquina Inferior Izquierda ( 1, 0 ) --
//      {  4.0f, -2.0f, -4.0f } }	 // -- Esquina Superior Derecha   ( 1, 1 ) --
//  };
//  GLfloat ctrlNormals[U][V][3]= {  
//    { { -1.0f,  1.0f,  0.0f },	
//      {  0.0f,  1.0f, -1.0f } }, 
//    { { -1.0f,  1.0f,  0.0f },	
//      {  0.0f,  1.0f,  1.0f } },
//    { { -1.0f,  1.0f,  0.0f },
//      {  0.0f,  1.0f,  1.0f } } 
//  };
//  GLfloat ctrlCoords[U][V][2]= {
//    { {  0.0f,  0.0f  },	
//      {  0.0f,  1.0f  } }, 
//    { {  0.5f,  0.0f  },	
//      {  0.5f,  1.0f  } },
//    { {  1.0f,  0.0f  },
//      {  1.0f,  1.0f  } } 
//  };
//
//  -- Define la Bezier. Sólo necesitamos ejecutar ésto una vez. --
//  ---------------------------------------------------------------
//  glMap2f(
//    GL_MAP2_VERTEX_3,	   // Tipo de datos generado
//	  0.0f,				   // GLfloat u1    - Rango inferior de u
//	  Resolucion,          // GLfloat u2    - Rango superior de u
//	  U * 3,			   // GLint uStride - U * O -> Distancia entre los puntos almacenados en u
//	  U,				   // GLint uOrder  - U -> Dimension en la direccion de u (orden)
//	  0.0f,				   // GLfloat v1    - Rango inferior de v
//	  Resolucion,          // GLfloat v2    - Rango superior de v
//	  3,				   // GLint vStride - O -> Distancia entre los puntos almacenados en v
//	  V,				   // GLint vOrder  - V -> Dimension en la direccion de v (orden)
//	  &ctrlPoints[0][0][0] // const GLfloat * Points - Matriz de puntos de control
//  );
//
//  glMap2f(
//    GL_MAP2_NORMAL,	    // Tipo de datos generado
//	  0.0f,				    // GLfloat u1    - Rango inferior de u
//	  Resolucion,           // GLfloat u2    - Rango superior de u
//	  U * 3,			    // GLint uStride - U * O -> Distancia entre los puntos almacenados en u
//	  U,				    // GLint uOrder  - U -> Dimension en la direccion de u (orden)
//	  0.0f,				    // GLfloat v1    - Rango inferior de v
//	  Resolucion,           // GLfloat v2    - Rango superior de v
//	  3,  				    // GLint vStride - O -> Distancia entre los puntos almacenados en v
//	  V,				    // GLint vOrder  - V -> Dimension en la direccion de v (orden)
//	  &ctrlNormals[0][0][0] // const GLfloat * Points - Matriz de puntos de control
//  );
//
//  glMap2f(
//    GL_MAP2_TEXTURE_COORD_2, // Tipo de datos generado
//    0.0f,                    // GLfloat u1    - Rango inferior de u
//    Resolucion,              // GLfloat u2    - Rango superior de u
//    U * 2,                   // GLint uStride - U * O -> Distancia entre los puntos almacenados en u
//    U,                       // GLint uOrder  - U -> Dimension en la direccion de u (orden)
//    0.0f,                    // GLfloat v1    - Rango inferior de v
//    Resolucion,              // GLfloat v2    - Rango superior de v
//    2,                       // GLint vStride - O -> Distancia entre los puntos almacenados en v
//    V,                       // GLint vOrder  - V -> Dimension en la direccion de v (orden)
//	  &ctrlCoords[0][0][0]     // const GLfloat *Points - Matriz de Coordenadas de Textura.
//  );
//
//  -- Dibujamos la Bezier 2D. --
//  --------------------------
//
//    glEnable( GL_MAP2_VERTEX_3 );
//    glEnable( GL_MAP2_NORMAL   );
//    glEnable( GL_MAP2_TEXTURE_COORD_2 );
//    
//      for ( GLint j = 0; j < Resolucion; j += 1 ) { 
//        glBegin( GL_QUAD_STRIP );
//          for ( GLint i = 0; i <= Resolucion; i += 1 ) { 
//              glEvalCoord2f( (GLfloat)i, (GLfloat)j     ); 
//              glEvalCoord2f( (GLfloat)i, (GLfloat)(j+1) ); 
//          } 
//        glEnd(); 
//      }
//    glDisable( GL_MAP2_NORMAL   );
//    glDisable( GL_MAP2_TEXTURE_COORD_2 );      
//    glDisable( GL_MAP2_VERTEX_3 );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  CURVA BEZIER MESH:
//  ------------------
//  ------------------
//  -- Creamos los Arrays con los puntos de control. --
//  ---------------------------------------------------
//  Igual que en el caso anterior.
//
//  -- Define la Bezier Mesh. Sólo necesitamos ejecutar ésto una vez. --
//  ---------------------------------------------------------------
//  Igual que en el caso anterior.
//
//  -- Mapea una rejilla de 6 puntos de 0 a 6 --
//  --------------------------------------------
//  glMapGrid2f( 
//    Resolucion, // GLint   un - Numero de particiones en "u".
//    0.0f,       // GLfloat u1 - Rango minimo de "u".
//    Resolucion, // GLfloat u2 - Rango máximo de "u".
//    Resolucion, // GLint   vn - Numero de particiones en "v".
//    0.0f,       // GLfloat v1 - Rango minimo de "v".
//    Resolucion  // GLfloat v2 - Rango máximo de "v".
//  );
//
//  -- Dibujamos la Bezier Mesh. --
//  -------------------------------
//  glEnable( GL_MAP2_VERTEX_3 );
//  glEnable( GL_MAP2_NORMAL   );
//  glEnable( GL_MAP2_TEXTURE_COORD_2 );
//    glEvalMesh2( 
//      GL_FILL,    // GL_POINT, GL_LINE, and GL_FILL are accepted.
//      0,          // GLint i1 - Rango minimo de "i".
//      Resolucion, // GLint i2 - Rango máximo de "i".
//      0,          // GLint j1 - Rango minimo de "j".
//      Resolucion  // GLint j2 - Rango máximo de "j".
//    );
//  glDisable( GL_MAP2_NORMAL   );
//  glDisable( GL_MAP2_TEXTURE_COORD_2 );      
//  glDisable( GL_MAP2_VERTEX_3 );
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
//  SUPERFICIE NURBS:
//  -----------------
//  -----------------
//  -- Creamos los Arrays con los puntos de control. --
//  ---------------------------------------------------
//  #define U 4            // -- Tamaño U del Array de Puntos de Control.       --
//  #define V 4            // -- Tamaño V del Array de Puntos de Control.       --
//  #define Resolucion 9   // -- Número de divisiones de la Nurb. Con 9 son 10. --
//  GLfloat ctrlPoints[U][V][3]= {
//    { { -6.0f, -6.0f, 0.0f },	   // -- Esquina Inferior Izquierda  ( 0, 0 ) --
//	    { -8.0f, -2.0f, 0.0f }, { -8.0f,  2.0f, 0.0f },	
//      { -6.0f,  6.0f, 0.0f } },  // -- Esquina Superior Izquierda  ( 0, 1 ) --
//    { { -2.0f, -8.0f, 0.0f },	{ -2.0f, -2.0f, 8.0f },	{ -2.0f,  2.0f, 8.0f }, { -2.0f,  8.0f, 0.0f } },
//    { {  2.0f, -8.0f, 0.0f }, {  2.0f, -2.0f, 8.0f }, {  2.0f,  2.0f, 8.0f }, {  2.0f,  8.0f, 0.0f } },
//    { {  6.0f, -6.0f, 0.0f },    // -- Esquina Inferior Derecha    ( 1, 0 ) --
//		{  8.0f, -2.0f, 0.0f }, {  8.0f,  2.0f, 0.0f }, 
//		{  6.0f,  6.0f, 0.0f } }   // -- Esquina Superior Derecha    ( 1, 1 ) --
//  };  
//
//  -- Secuencia de nudos de las NURBS --
//  -------------------------------------
//  GLfloat Uknots[U+4] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
//  GLfloat Vknots[V+4] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
//
//  -- Iniciación y configuración de la NURB --
//  -------------------------------------------
//  GLUnurbsObj *theNurb = gluNewNurbsRenderer();
//
//  -- El parámetro es un boleano que, cuando esta en GL_TRUE, indica que la curva
//  -- NURBS puede ser descartada por Teselación si los puntos de control mienten
//  -- fuera de la vista actual. Por defecto es GL_FALSE.
//  gluNurbsProperty( theNurb, GLU_CULLING, GL_TRUE );
//  
//  -- El parámetro especifica el número de puntos por unidad de longitud en los
//  -- ejes de coordenadas U y V. Es usado cuando GLU_SAMPLING_METHOD esta seleccionado
//  -- en GLU_DOMAIN_DISTANCE. El valor inicial es de 100.
//  gluNurbsProperty( theNurb, GLU_U_STEP, Resolucion );
//  gluNurbsProperty( theNurb, GLU_V_STEP, Resolucion );
//  
//  -- GLU_SAMPLING_METHOD -> GLU_PATH_LENGTH | GLU_OBJECT_PATH_LENGTH | GLU_DOMAIN_DISTANCE --
//  --   - GLU_PATH_LENGTH, la superficie es renderizada asi que la máxima longitud, en pixels,
//  --       de las caras de los polígonos de teselación no son mas grandes que lo especificado 
//  --       por GLU_SAMPLING_TOLERANCE.
//  --   - GLU_OBJECT_PATH_LENGTH, es similar a GLU_PATH_LENGTH excepto que ello es visto 
//  --       independiente, que si, la superficie es renderizada así que la máxima longitud, 
//  --       en el espacio del objeto, de las caras de los polígonos de teselación no sean 
//  --       mayores que lo especificado por GLU_SAMPLING_TOLERANCE.
//  --   - GLU_DOMAIN_DISTANCE, especifica en coordenadas paramétricas, cuantos puntos por 
//  --        unidad de longitud son tomados en la dirección U, V.
//  gluNurbsProperty( theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE );
//  
//  -- Especifica la longitud máxima, en pixels o en la undidad de longitud del
//  -- espacio del objeto, a usar cuando el metodo de Sampling sea GLU_PATH_LENGTH
//  -- o GLU_OBJECT_PATH_LENGTH. El valor por defecto es de 0.0 pixels.
//  gluNurbsProperty( theNurb, GLU_SAMPLING_TOLERANCE, 25.0 ); 
//
//  -- GLU_DISPLAY_MODE -> GLU_FILL | GLU_OUTLINE_POLYGON | GLU_OUTLINE_PATCH --
//  --   - GLU_FILL              DIBUJA LA NURB RELLENA.
//  --   - GLU_OUTLINE_POLYGON   DIBUJA LA NURB EN LINEAS.
//  --   - GLU_OUTLINE_PATCH     DIBUJA LA NURB EN LINEAS DE CONTROL O PATCH.
//  gluNurbsProperty( theNurb, GLU_DISPLAY_MODE, GLU_FILL ); 
//  gluNurbsProperty( theNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON );
//
//  -- Dibujamos la Superficie Nurbs. --
//  ------------------------------------
//  gluNurbsProperty( theNurb, GLU_DISPLAY_MODE, GLU_FILL ); 
//  gluBeginSurface( theNurb ); // -- EMPEZAMOS A DIBUJAR LA NURB --   
//    gluNurbsSurface(
//      theNurb,	          // Puntero al generador NURBS
//      8, Uknots,		      // Número de nudos y matriz de nudos en la dirección u	
//      8, Vknots,		      // Número de nudos y matriz de nudos en la dirección v	
//      U * 3,			      // U * O -> Distancia entre puntos de control en la dirección u
//      3,			          // O     -> Distancia entre puntos de control en la dirección v
//      &ctrlPoints[0][0][0], // Puntos de control 
//      U, V,			        // U , V -> Ordenes u y v de superficie
//      GL_MAP2_VERTEX_3      // Tipo de superficie
//    );	
//  gluEndSurface( theNurb );  // -- TERMINAMOS DE DIBUJAR LA NURB --
//
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------


