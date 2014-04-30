/*
	Love Demo -- Dedicated to Valeria :))))
	
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
#ifndef __demo_h__
#define __demo_h__

#include "font3d.h"		/* 3D outline fonts */

// Global Defines
#define MAX_HEARTS 34
#define MAX_DEPTH -10.0f
#define HEART_STEP 0.2f
#define HEART_STEP_SMALL 0.1f;

// Global Vars
Font3D g_font;

// Array of hearts
unsigned int g_hearts[ MAX_HEARTS ] = { 0, };

float heart_mat[] = {0.5f,0.0f,0.3f,1.0f};

float LightParam[] = {50,80,100,15,70,100,100,100,40,70,0};
float fPos[] =
{
	(50-30) *MAX_DEPTH/100, //0
	(80-30) *MAX_DEPTH/100, //1
	(100-30)*MAX_DEPTH/100, //2
	1.f
};

float f;
float fAmbient[4],fDiffuse[4],fSpecular[4],fAmbMat[4],fDifMat[4],fSpecMat[4],fShine,fEmission[4];

#endif /* !__demo_h__ */
