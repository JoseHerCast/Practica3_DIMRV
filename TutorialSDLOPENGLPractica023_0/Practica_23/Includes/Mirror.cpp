//------------------------------------------------------------------------------
//-- TUTORIAL SDL + OPENGL ( Programado en C++ con Dev-C++ 4.9.9.2 )          --
//------------------------------------------------------------------------------
//-- AUTOR: PIPAGERARDO                                                       --
//-- EMAIL: pipagerardo@hotmail.es                                            --
//-- SUGERENCIAS: (Foros privados de programaci?n) www.scenebeta.com          --
//-- FECHA ?LTIMA MODIFICACI?N: 31/03/2010                                    --
//------------------------------------------------------------------------------
//-- Todo  el  c?digo  y  contenido  de  este  tutorial es exclusivo  para el --
//-- aprendizaje tanto del autor como de los que colaboren en ?l. Sin el  m?s --
//-- m?nimo ?nimo de lucro, siempre por la satisfacci?n del aprendizaje y del --
//-- trabajo bien hecho.                                                      --
//-- No  me  hago  responsable  del  da?o  producido  por  el  uso  indebido, --
//-- modificaciones  mal  intencionadas,  ?nimo  de  lucro,  etc...           --
//-- Solo pido al que le sea de utilidad este c?digo que colabore en su mejora--
//-- y perfeccionamiento poni?ndomelo en conocimiento por correo electr?nico. --
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//-- Este c?digo no es m?o, lo baj? de alg?n sitio de  internet. Si  localizo -- 
//-- al autor lo pondr? aqu? ...                                              --
//------------------------------------------------------------------------------

#include "Mirror.h"

void setpixel( SDL_Surface *screen, int x, int y, Uint32 newcolor ) {
  Uint8 *ubuff8;
  Uint16 *ubuff16;
  Uint32 *ubuff32;
  Uint32 color = newcolor;
  char c1, c2, c3; 
  /* Lock the screen, if needed */
  if( SDL_MUSTLOCK(screen) ) {
    if( SDL_LockSurface(screen) < 0 ) return;
  }
  /* How we draw the pixel depends on the bitdepth */
  switch( screen->format->BytesPerPixel ) {
    case 1: 
      ubuff8 = (Uint8*) screen->pixels;
      ubuff8 += (y * screen->pitch) + x; 
      *ubuff8 = (Uint8) color;
      break;
    case 2:
      ubuff8 = (Uint8*) screen->pixels;
      ubuff8 += (y * screen->pitch) + (x*2);
      ubuff16 = (Uint16*) ubuff8;
      *ubuff16 = (Uint16) color; 
      break;  
    case 3:
      ubuff8 = (Uint8*) screen->pixels;
      ubuff8 += (y * screen->pitch) + (x*3);
      if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
	c1 = (color & 0xFF0000) >> 16;
	c2 = (color & 0x00FF00) >> 8;
	c3 = (color & 0x0000FF);
      } else {
	c3 = (color & 0xFF0000) >> 16;
	c2 = (color & 0x00FF00) >> 8;
	c1 = (color & 0x0000FF);	
      }
      ubuff8[0] = c3;
      ubuff8[1] = c2;
      ubuff8[2] = c1;
      break;
    case 4:
      ubuff8 = (Uint8*) screen->pixels;
      ubuff8 += (y*screen->pitch) + (x*4);
      ubuff32 = (Uint32*)ubuff8;
      *ubuff32 = color;
      break;
    default:
      fprintf(stderr, "Error: Unknown bitdepth!\n");
  }
  /* Unlock the screen if needed */
  if( SDL_MUSTLOCK(screen) ) {
    SDL_UnlockSurface(screen);
  }
}

Uint32 getpixel( SDL_Surface *surface, int x, int y ) {
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch(bpp) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
    default:
      return 0;       /* shouldn't happen, but avoids warnings */
    }
}

SDL_Surface *MirrorSurfaceX( SDL_Surface *screen ) {
  SDL_Surface* newimg = SDL_CreateRGBSurface( SDL_HWSURFACE, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask );
  for( int y = 0; y < screen->h; y++ ) {
    for( int x = 0; x < screen->w; x++ ) {
      setpixel( newimg, x, y, getpixel( screen, x, screen->h - y - 1 ) );
    }
  }
  return newimg;
}

SDL_Surface *MirrorSurfaceY( SDL_Surface *screen ) {
  SDL_Surface* newimg = SDL_CreateRGBSurface( SDL_HWSURFACE, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask );
  for( int y = 0; y < screen->h; y++ ) {
    for( int x = 0; x < screen->w; x++ ) {
      setpixel( newimg, x, y, getpixel( screen, screen->w - x - 1, y ) );
    }
  }
  return newimg;
}

