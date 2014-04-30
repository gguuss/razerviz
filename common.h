/*
	Common Includes, compiler settings, types, etc.
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
#ifndef __common_h__
#define __common_h__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

//for old C style I/O
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#pragma warning(disable: 4996)

// Make bool available in C too :)
#ifndef __cplusplus
	typedef enum { false, true } bool;
#endif

// Winamp SDK
#include "winamp\wa_ipc.h"

#endif /* !__common_h__ */
