/*
	Tiny3D 'Minimalistic' (OpenGL) Visualizer Framework for Winamp v0.02

	Description:

	Cleaned up Justin's stuff, added new types, OpenGL support, 
	made it more object oriented, etc -- most of the code was
	written from scratch, or copied and modified from my Nympho3D
	and Lily3D engines (neither of them is finished or presentable) :P

	Last FrameWork Revision: 11/18/2007

	How to use?

	Make a copy of this project and modify as needed.

	Hints?
	... to add more interactivity modify the WndProc :)
	... if you just want to render something add the code to the visRender
	... you can call getVisInstance() anytime you wish :)
	... everything else should be self explanatory :P

	... DEMO Embed :))

	Compiles with both VC++ Express 2005 (most probably also 2008) and GCC, possibly others :P

	pS: code blocks marked :P

	gcc compile command:
		gcc visframework.c font3d.c -lopengl32 -lglu32 -lgdi32 -shared -o vis_love1.dll

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
#ifndef __VisFramework_h__
#define __VisFramework_h__

#include "common.h"

// TODO: change these as needed
#define VIS_USER_TITLE "Razer Visualization Demo"
#define VIS_USER_MODULE_TITLE "Razer Visualization Demo Module"
#define VIS_USER_CLASS "RazerVizDemo"

#define VIS_HDRVER 0x101

// TODO: change these as needed
#define VIS_SCENE_WIDTH  1 // 800x600
#define VIS_SCENE_HEIGHT 1
#define VIS_SCENE_FOV	 1000.0f

typedef struct winampVisModule
{
  char *description;
  HWND hwndParent;
  HINSTANCE hDllInstance;
  int sRate;
  int nCh;
  int latencyMs;
  int delayMs;

  int spectrumNch;
  int waveformNch;
  unsigned char spectrumData[2][576];
  unsigned char waveformData[2][576];

  void (*Config)(struct winampVisModule *this_mod);
  int (*Init)(struct winampVisModule *this_mod);
  int (*Render)(struct winampVisModule *this_mod);
  void (*Quit)(struct winampVisModule *this_mod);

  void *userData;

} winampVisModule;

typedef struct 
{
  int version;
  char *description;
  winampVisModule* (*getModule)(int);

} winampVisHeader;

// exported symbols
typedef winampVisHeader* (*winampVisGetHeaderType)();

// prototypes
void visConfig	(struct winampVisModule *this_mod);
int  visInit	(struct winampVisModule *this_mod);
int	 visRender	(struct winampVisModule *this_mod);
void visQuit	(struct winampVisModule *this_mod);

winampVisModule *getVisModule(int which);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void resizeGLWindow(int width, int height);

typedef struct
{
	winampVisHeader hdr;		//
	winampVisModule this_mod;	//

	HDC		hDC;				// holds the "canvas" of the window
	HGLRC	hRC;				// holds the 3D OpenGL canvas of the window
	HWND	hWnd;				// holds the handle of the window

	bool keys[256];				// array of pressed keys at a certain point :0

	embedWindowState myWindowState;

} winampGLVisualizer;

static winampGLVisualizer  g_sVis = 
{
		{ 
			VIS_HDRVER, 
			VIS_USER_TITLE, 
			getVisModule 
		},

		{ 
			VIS_USER_MODULE_TITLE,
			NULL,	// hwndParent
			NULL,	// hDllInstance
			0,		// sRate
			0,		// nCh
			20,		// latencyMS	( TODO: mess with this to fit your needs )
			70,		// delayMS		( TODO: mess with this to fit your needs )
			2,		// spectrumNch	( TODO: you can also mess with this )
			2,		// waveformNch	( TODO: you can also mess with this )
			{ 0, },	// spectrumData
			{ 0, },	// waveformData
			visConfig,
			visInit,
			visRender, 
			visQuit
		},

		NULL,
		NULL,
		NULL,
		{ 0, }, // keys

		// embedWindowState struct
		{NULL, 0, {0,0,0,0}, NULL, {0, }}
};

static winampGLVisualizer *g_pVis = &g_sVis;

winampGLVisualizer *getVisInstance()
{
	return g_pVis;
}

winampVisModule *getVisModule(int which)
{
	switch (which)
	{
		case 0: return &getVisInstance()->this_mod;
		default:return NULL;
	}
}

#ifdef __cplusplus
extern "C" {
#endif
__declspec( dllexport ) winampVisHeader *winampVisGetHeader()
{
	return &getVisInstance()->hdr;
}
#ifdef __cplusplus
}
#endif

void resizeGLWindow(int width, int height)
{
	if (height==0)
	{
		height=1;
	}

	glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(float)width/(float)height,0.1f,VIS_SCENE_FOV);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

#endif /* !__VisFramework_h__ */
