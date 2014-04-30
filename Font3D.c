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
#include "Font3D.h"

void font_Create( Font3D *font, HDC hDC, const char *fontName, int fontSize )
{
	HFONT fnt;

	if(font == NULL) return;
	if(hDC  == NULL) return;

	if(fontName == NULL)
	{
		//default
		fontName = "Verdana";
	}

	if(fontSize == 0)
	{
		fontSize = -12;
	}

	font->base = glGenLists(256);

	fnt = CreateFont(-fontSize, 0, 0, 0,	FW_BOLD, FALSE,	FALSE, FALSE, /*ANSI_*/SYMBOL_CHARSET,	OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
					  ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,	fontName);

   	SelectObject(hDC, fnt);
	wglUseFontOutlines(	hDC, 0,	255, font->base, 0.0f,	0.2f, WGL_FONT_POLYGONS, font->gmf);
}

void font_Print(Font3D *font, const char *s, ...)
{
	float			length=0;
	unsigned int	loop;
	char			text[256];
	va_list			ap;

	if(font != NULL && s != NULL)
	{

		va_start(ap, s);
	    vsprintf(text, s, ap);
		va_end(ap);

		for (loop=0;loop<(strlen(text));loop++)
		{
			length+=font->gmf[text[loop]].gmfCellIncX;
		}

		glEnable(GL_COLOR_MATERIAL);

		glTranslatef(-length/2,0.0f,0.0f);
		glPushAttrib(GL_LIST_BIT);
		glListBase(font->base);
	   	glCallLists((GLsizei) strlen(text), GL_UNSIGNED_BYTE, text);
		glPopAttrib();

		glDisable(GL_COLOR_MATERIAL);
	}
}

void font_Destroy( Font3D *font )
{
	if(font != NULL)
	{
		glDeleteLists(font->base, 256);
	}
}
