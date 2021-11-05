//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programaci�n) www.scenebeta.com          --
//-- FECHA �LTIMA MODIFICACI�N: 31/03/2010                                    --
//------------------------------------------------------------------------------
//-- Todo  el  c�digo  y  contenido  de  este  tutorial es exclusivo  para el --
//-- aprendizaje tanto del autor como de los que colaboren en �l. Sin el  m�s --
//-- m�nimo �nimo de lucro, siempre por la satisfacci�n del aprendizaje y del --
//-- trabajo bien hecho.                                                      --
//-- No  me  hago  responsable  del  da�o  producido  por  el  uso  indebido, --
//-- modificaciones  mal  intencionadas,  �nimo  de  lucro,  etc...           --
//-- Solo pido al que le sea de utilidad este c�digo que colabore en su mejora--
//-- y perfeccionamiento poni�ndomelo en conocimiento por correo electr�nico. --
//------------------------------------------------------------------------------

#ifndef _Configuracion_
#define _Configuracion_

// CONFIGURACION DEL TECLADO ---------------------------------------------------
// -----------------------------------------------------------------------------

// * * * MOVER LA CAMARA * * *
#define T_ARRIBA     SDLK_s  // Mover Arriba.
#define T_ABAJO      SDLK_x  // Mover Abajo.
#define T_DERECHA    SDLK_c  // Mover Derecha.
#define T_IZQUIERDA  SDLK_z  // Mover Izquierda.
#define T_ACERCA     SDLK_d  // Acercar.
#define T_ALEJA      SDLK_a  // Alejar.

// * * * MOVER A DONDE MIRA LA CAMARA * * *
#define T_arriba     SDLK_g  // Mover Arriba.
#define T_abajo      SDLK_b  // Mover Abajo.
#define T_derecha    SDLK_n  // Mover Derecha.
#define T_izquierda  SDLK_v  // Mover Izquierda.
#define T_acerca     SDLK_h  // Acercar.
#define T_aleja      SDLK_f  // Alejar.
#define T_enfoque    SDLK_e  // Activa o Desactiva el Enfoque.

#define MOVER        0.2f    // Cantidad a mover.

// * * * ROTAR LOS OBJETOS SOBRE EL EJE CENTRAL * * *
#define T_RXH        SDLK_UP     // Rotar Eje X sentido Horario
#define T_RXA        SDLK_DOWN   // Rotar Eje X sentido Antihorario
#define T_RYH        SDLK_LEFT   // Rotar Eje Y sentido Horario
#define T_RYA        SDLK_RIGHT  // Rotar Eje Y sentido Antihorario

#define ROTAR        2.0f    // Cantidad a rotar.

// * * * CONFIGURACI�N DE ESTADOS OPENGL * * *
#define T_Niebla     SDLK_j  // Activa o desactiva la Niebla.
#define T_Luz        SDLK_l  // Activa o desactiva la iluminaci�n.
#define T_Luz_0      SDLK_1  // Activa o desactiva la iluminaci�n.
#define T_Luz_1      SDLK_2  // Activa o desactiva la iluminaci�n.
#define T_Luz_2      SDLK_3  // Activa o desactiva la iluminaci�n.
#define T_Material   SDLK_m  // Activa o desactiva Color Material.

// * * * CONFIGURACI�N SDL + OPENGL * * *
#define RF         0.0f    // Componente RED   del Fondo
#define GF         0.0f    // Componente GREEN del Fondo
#define BF         0.5f    // Componente BLUE  del Fondo
#define AF         0.0f    // Componente ALPHA del Fondo

#define V_Ancho     640
#define V_Alto      480
#define FOTOGRAMAS   25    // Fotogramas por segundo.
#define N_Ventana    "Curso OpenGL con SDL."
#define Nombre_Icono "Imagen/Icono/Icono.png"

// * * * CONFIGURACI�N MATEM�TICA * * *
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
  #define M_PI_2 1.57079632679489661923
#endif
#define PI2 6.28318530717958647692
#ifndef FALSE
  #define FALSE 0
  #define TRUE  1
#endif
     
#endif
