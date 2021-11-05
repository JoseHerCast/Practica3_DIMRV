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
// Práctica 23:
// ----------------------------------------------------------------------------- 
// Usando un editor 3D, en este caso el Wings 3D he  exportado  dos  modelos  en
// formato OBJ + MTL. La librería "Cargador_Obj.h" s e  en  carga  de  leer  los
// archivos en formato de texto y cargarlos en memoria. También en  el  caso  de
// que  los modelos tengan  texturas  las  podemos  cargar  usando  la  librería
// "Texturas_2D.h".
// El siguiente paso consiste en  compilar  dos  listas  dibujando  los  modelos
// cargados en memoria, terminado esto se deben borrar los objetos de la memoria
// para liberar espacio. No es así con el caso de las texturas, puesto que estas
// no se almacenan en las listas compiladas. El resto del código es sobradamente
// conocido si se ha seguido todas las prácticas.
//
// -----------------------------------------------------------------------------
// LINKER:
// -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lopengl32 -lglu32 -mwindows
// -----------------------------------------------------------------------------
// INCLUDES:
// -SDL_con_OpenGL.h -Configuracion.h -TUTORIAL_OPENGL.h -Entorno.h -Fuentes_Bitmap.h -Mirror.h
// -Luces.h -Texturas_2D.h -Cargador_Obj.h
// -----------------------------------------------------------------------------

#include "../Includes/SDL_con_OpenGL.h"
#include "../Includes/Luces.h"
#include "../Includes/Texturas_2D.h"

#include "../Includes/Cargador_Obj.h"  // -- Estudiar el código --

int main(int argc, char *argv[]) {
// -- INICIO DE MAIN -----------------------------------------------------------

  // -- CREACION DEL ENTORNO 3D ------------------------------------------------
  c_sdl_con_opengl *sdl_con_opengl = new c_sdl_con_opengl;
  c_entorno *entorno = new c_entorno( "Imagen/Cube_Maps/lava/" );

  // -- CREACION DE UNA FUENTE DE TEXTO ----------------------------------------
  c_fuente_bitmap *fuente = new c_fuente_bitmap( "Fuentes/Arial_256.png" );

  // -- CREAMOS LAS LUCES ------------------------------------------------------
  c_luz *luz = new c_luz[2];
  luz[0].position(  5.0f,  5.0f, 5.0f );
  luz[0].diffuse(   0.8f,  0.8f, 0.8f );
  luz[0].ambient(   0.2f,  0.2f, 0.2f );
  luz[0].direccional( GL_LIGHT0 );
  luz[1].position( -5.0f, -5.0f, -5.0f );
  luz[1].diffuse(   0.4f,  0.4f, 0.4f );
  luz[1].ambient(   0.2f,  0.2f, 0.2f );
  luz[1].direccional( GL_LIGHT1 );


  // -- CARGAMOS LOS MODELOS OBJ -----------------------------------------------
  C_Obj *Modelo_OBJ = new C_Obj[2];
  Modelo_OBJ[0].Carga( "Modelos_3d/Corvette/Corvette.obj" );
  Modelo_OBJ[1].Carga( "Modelos_3d/Tie-Fighter/Tie-Fighter.obj" );
    
  // -- CARGAMOS LAS TEXTURAS DE LOS MODELOS OBJ -------------------------------
  c_textura_2D *textura_2D[2];
  textura_2D[0] = new c_textura_2D[ Modelo_OBJ[0].N_Texturas() ];
  textura_2D[1] = new c_textura_2D[ Modelo_OBJ[1].N_Texturas() ];
  Modelo_OBJ[0].Carga_Texturas( textura_2D[0], 0 );
  Modelo_OBJ[1].Carga_Texturas( textura_2D[1], 0 );

  
  // -- CREAMOS LAS LISTAS COMPILADAS USANDO LOS MODELOS OBJ -------------------
  glListBase( 0 );
  GLuint lista = glGenLists(2);

  glNewList( lista + 0, GL_COMPILE );
    Modelo_OBJ[0].Dibuja_Todo();
  glEndList();

  glNewList( lista + 1, GL_COMPILE );
    Modelo_OBJ[1].Dibuja_Todo();
  glEndList();

  
  // -- BORRAMOS LOS OBJETOS, YA NO LOS NECESITAMOS ----------------------------
  delete[] Modelo_OBJ;
  

  // -- CONFIGURACIÓN DE VISUALIZACION -----------------------------------------
  // glEnable(  GL_COLOR_MATERIAL );   // ACTIVA glColor3ub();
     glDisable( GL_COLOR_MATERIAL );   // ACTIVA glMaterialfv();
     glEnable(  GL_CULL_FACE );        // ACTIVA OCULTAR CARAS TRASERAS
  // glDisable( GL_CULL_FACE );        // MUESTRA LAS CARAS TRASERAS
  // glEnable(  GL_FOG );              // ACTIVA LA NIEBLA
     glDisable( GL_FOG );              // DESACTIVA LA NIEBLA
     glEnable(  GL_LIGHTING );         // ACTIVA LA LUZ
  // glDisable( GL_LIGHTING );         // ACTIVA LA LUZ
     glEnable( GL_LIGHT0 );            // ACTIVA LA LUZ Nº 0
     glEnable( GL_LIGHT1 );            // ACTIVA LA LUZ Nº 1
  // glEnable( GL_LIGHT2 );            // ACTIVA LA LUZ Nº 2
    

  // -- POSICION DE LA CÁMARA Y BUCLE PRINCIPAL --------------------------------
  sdl_con_opengl->posicion_camara( 0.0f, 0.0f, 30.0f );
  sdl_con_opengl->enfoque_camara(  0.0f, 0.0f, 0.0f );
  sdl_con_opengl->activa_enfoque_camara = false;
  do { sdl_con_opengl->empieza( entorno );

    // -- CALCULOS DEL MOVIMIENTO DE LAS LUCES ---------------------------------
    luz[0].posiciona(); luz[1].posiciona();

    // -- MOSTRAR LAS LISTAS COMPILADAS ---------------------------------------- 
    glTranslatef( -8.0f, 0.0f, 0.0f );
    glCallList( lista + 0 );
  
    glTranslatef( 16.0f, 0.0f, 0.0f );
    glCallList( lista + 1 );


    // -- FIN BUCLE PRINCIPAL Y MOSTRAR INFORMACIÓN DE ESTADOS -----------------
    sdl_con_opengl->empieza_ortho_2D(); 
      sdl_con_opengl->ver_info( fuente, "Práctica: 23" );
    sdl_con_opengl->termina_ortho_2D();
  } while ( !sdl_con_opengl->termina() );
  
  Captura_Pantalla( "Practica_23.BMP" );

  // -- BORRANDO OBJETOS -------------------------------------------------------
  glDeleteLists( lista, 2 );   // -- BORRAMOS LAS LISTAS     --
  delete[] textura_2D[0];      // -- BORRAMOS LAS TEXTURAS   --
  delete[] textura_2D[1];      // -- BORRAMOS LAS TEXTURAS   --
  delete[] luz;                // -- BORRAMOS LAS LUCES      --
  delete fuente;               // -- BORRAMOS LA FUENTE      --
  delete entorno;              // -- BORAMOS  EL FONDO       --
  delete sdl_con_opengl;       // -- BORRAMOS EL ENTORNO     --

  // -- FIN DE MAIN ------------------------------------------------------------
  return EXIT_SUCCESS;
}

