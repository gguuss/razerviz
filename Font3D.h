/*
	Simple "Object Oriented" 3D font "class"
	This file is part of the Tiny3D framework.
	
	Copyright (C) 2007, Mihail Szabolcs
                                              
	This program is free software; you can redistribute it and/or             
	modify it under the terms of the GNU General Public License               
	as published by the Free Software Foundation; either version 2            
	of the License, or (at your option) any later version.                    
                                                                           
	This program is distributed in the hope that it will be useful,           
	but WITHOUT ANY WARRANTY; without even the implied warranty of            
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       
                                                                            
	See the GNU General Public License for more details.            
*/
#ifndef __Font3D_h__
#define __Font3D_h__

#include "common.h"

typedef struct
{
	unsigned int base;
	GLYPHMETRICSFLOAT gmf[256];

} Font3D;

void font_Create(Font3D *font, HDC hDC, const char *fontName, int fontSize );
void font_Print(Font3D *font, const char *s, ...);
void font_Destroy( Font3D *font );


#endif /* !__Font3D_h__ */
