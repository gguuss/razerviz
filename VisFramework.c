/*
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
#include "VisFramework.h"
#include "include\SwitchBlade.h"

void visConfig(struct winampVisModule *this_mod)
{
	//TOOD: add specific configuration stuff here (e.g show an nice dialog, etc)
    MessageBox(this_mod->hwndParent,"Nothing to configure.","Configuration",MB_OK | MB_ICONINFORMATION);
}


void LoadKeyImageToRazer(const char * filename, RZSBSDK_DKTYPE targetKey, RZSBSDK_KEYSTATETYPE keyState){
    wchar_t * longFileString;
    int size;    
    
    // Determine file size
    size = strlen(filename)+1;

    // Allocate an appriate size memory block.
    longFileString = (wchar_t*)malloc(sizeof(wchar_t) * size);  
    mbstowcs(longFileString, filename, size);
    
    RzSBSetImageDynamicKey(targetKey, keyState, longFileString);
    
    free(longFileString);
}

////////////////////////////////////////////////////////////////////
// DK button
/////////////////////////////////////////////////////////////////////


// TODO: MARK AS GLOBAL
HWND parent = NULL; // our parent window's handle
static int colormode = 0;

// TODO: Can this be done with a winamp library?
#define EXT_LPARAM 0x800000
HRESULT STDMETHODCALLTYPE OnDkClickedButton(RZSBSDK_DKTYPE type, RZSBSDK_KEYSTATETYPE keystate)
{	
    INPUT keyCode;
    HWND winamp;
    int cmdCode = 0;
    bool sendCmd = false;
    //windowCommand wc;

    static int lastinput = 0;

    // more at http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (type) {
	    case RZSBSDK_DK_NONE:
		    break;
        case RZSBSDK_DK_1:		    
            colormode = 0;
            break;
        case RZSBSDK_DK_2:
            // Stop?
            // VK_MEDIA_STOP
		    colormode = 1;
            break;
        case RZSBSDK_DK_3:
		    colormode = 2;
            break;
        case RZSBSDK_DK_4:
            colormode = 3;
		    break;
        case RZSBSDK_DK_5:
            colormode = 4;
		    break;
        case RZSBSDK_DK_6:
            // poor man's debounce
            if (keystate != RZSBSDK_KEYSTATE_UP){
                // Back               
                LoadKeyImageToRazer(".\\imagedata\\rewind-color.png",RZSBSDK_DK_6, RZSBSDK_KEYSTATE_UP);
            } else {
                sendCmd = true;
                cmdCode = WINAMP_BUTTON1;
                LoadKeyImageToRazer(".\\imagedata\\rewind.png",RZSBSDK_DK_6, RZSBSDK_KEYSTATE_UP);                
            }
		    break;
        case RZSBSDK_DK_7:
            if (keystate != RZSBSDK_KEYSTATE_UP){
                // Play / Pause                
                sendCmd = true;
                cmdCode = WINAMP_BUTTON3;
                LoadKeyImageToRazer(".\\imagedata\\play-color.png",RZSBSDK_DK_7, RZSBSDK_KEYSTATE_UP);
            } else {
                LoadKeyImageToRazer(".\\imagedata\\play.png",RZSBSDK_DK_7, RZSBSDK_KEYSTATE_UP);
            }
		    break;
        case RZSBSDK_DK_8:
            // Fast FW
            if (keystate != RZSBSDK_KEYSTATE_UP){                
                sendCmd = true;
                cmdCode = WINAMP_BUTTON5;
                LoadKeyImageToRazer(".\\imagedata\\fforward-color.png",RZSBSDK_DK_8, RZSBSDK_KEYSTATE_UP);
            } else {
                LoadKeyImageToRazer(".\\imagedata\\fforward.png",RZSBSDK_DK_8, RZSBSDK_KEYSTATE_UP);
            }
	        break;
        case RZSBSDK_DK_9:
            // VOL_UP
            if (keystate != RZSBSDK_KEYSTATE_UP){
                keybd_event(VK_VOLUME_UP, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                LoadKeyImageToRazer(".\\imagedata\\volup-color.png",RZSBSDK_DK_9, RZSBSDK_KEYSTATE_UP);
            } else {
                keybd_event(VK_VOLUME_UP, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
                LoadKeyImageToRazer(".\\imagedata\\volup.png",RZSBSDK_DK_9, RZSBSDK_KEYSTATE_UP);
            }
		    break;
        case RZSBSDK_DK_10:
            // VOLDOWN
		    // SIMULATE MOUSE WHEEL DOWN                        
            if (keystate != RZSBSDK_KEYSTATE_UP){                
                keybd_event(VK_VOLUME_DOWN, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                LoadKeyImageToRazer(".\\imagedata\\voldown-color.png",RZSBSDK_DK_10, RZSBSDK_KEYSTATE_UP);
            } else {
                keybd_event(VK_VOLUME_DOWN, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
                LoadKeyImageToRazer(".\\imagedata\\voldown.png",RZSBSDK_DK_10, RZSBSDK_KEYSTATE_UP);                
            }
            break;	
	    default:
		    break;
	}
    
    if (sendCmd) {
        winamp = FindWindow("Winamp v1.x", NULL);
        if (!winamp){
            MessageBox(parent, "Whoopsie", "Could not find winamp window", MB_OK);    
            return;
        }
        //TODO(gguuss): What is the secret of 273?
        SendMessage(winamp, 273, cmdCode, 0);
    }

    lastinput = 0;
    return S_OK;
}

int visInit(struct winampVisModule *this_mod)
{
	// init Win32 stuff
	int styles; // our Window styles

	WNDCLASS wc; // our Window class
	HWND (*e)(embedWindowState *v);
     
	// OpenGL pixel format related
	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat;

	getVisInstance()->myWindowState.flags |= EMBED_FLAGS_NOTRANSPARENCY;   
	getVisInstance()->myWindowState.r.left		= 0;
	getVisInstance()->myWindowState.r.top		= 0;
	getVisInstance()->myWindowState.r.right		= VIS_SCENE_WIDTH;
	getVisInstance()->myWindowState.r.bottom	= VIS_SCENE_HEIGHT;
   
	*(void**)&e = (void *)SendMessage(this_mod->hwndParent,WM_WA_IPC,(LPARAM)0,IPC_GET_EMBEDIF);    

	if (!e)
	{
		MessageBox(this_mod->hwndParent,"This plugin requires Winamp 5.0+.","Error",MB_OK | MB_ICONERROR);
		return 1;
	}

	parent = e(&getVisInstance()->myWindowState);

	SetWindowText(getVisInstance()->myWindowState.me, this_mod->description);
	
	memset(&wc,0,sizeof(wc));
	wc.lpfnWndProc = WndProc;
	wc.hInstance = this_mod->hDllInstance;
	wc.lpszClassName = VIS_USER_CLASS;
	
	if (!RegisterClass(&wc)) 
	{
		MessageBox(this_mod->hwndParent,"Error registering window class.","Error",MB_OK | MB_ICONERROR);
		return 1;
	}

	styles = WS_VISIBLE|WS_CHILDWINDOW|WS_OVERLAPPED|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	styles|= CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //add more

	getVisInstance()->hWnd = CreateWindowEx(
		0,
		VIS_USER_CLASS,
		NULL,
		styles,
		0,0,
		VIS_SCENE_WIDTH,VIS_SCENE_HEIGHT,
		parent,
		NULL,
		this_mod->hDllInstance,
		0);

	if (!getVisInstance()->hWnd) 
	{
		MessageBox(this_mod->hwndParent,"Error while creating window.","Error",MB_OK | MB_ICONERROR);
		return 1;
	}

	SetWindowLong(getVisInstance()->hWnd,GWL_USERDATA,(LONG)this_mod); 
	SendMessage(this_mod->hwndParent, WM_WA_IPC, (WPARAM)getVisInstance()->hWnd, IPC_SETVISWND);

	// Enable OpenGL on the created Window
	if (!(getVisInstance()->hDC=GetDC(getVisInstance()->hWnd)))
	{
		return 1;
	}

	memset(&pfd,0,sizeof(pfd));
	pfd.nSize      = sizeof(pfd);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16; // we use 16bit color depth for better compatibility
	pfd.cDepthBits = 16; // Z-Buffer
	pfd.iLayerType = PFD_MAIN_PLANE;

	nPixelFormat = ChoosePixelFormat(getVisInstance()->hDC, &pfd);
	SetPixelFormat(getVisInstance()->hDC, nPixelFormat, &pfd);

	if (!(getVisInstance()->hRC=wglCreateContext( getVisInstance()->hDC )))
	{
		return 1;
	}
   
    
	if(!wglMakeCurrent(getVisInstance()->hDC,getVisInstance()->hRC))
	{
		return 1;
	}
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// setup the perspective :P
	resizeGLWindow(VIS_SCENE_HEIGHT,VIS_SCENE_WIDTH);
	// show the window
	ShowWindow(parent,SW_SHOWNORMAL);

    	
    RzSBStart();

    // Next time use noun project
    // TODO: Are these images correctly getting added as a DLL resource?    
    LoadKeyImageToRazer(".\\imagedata\\rewind.png",RZSBSDK_DK_6, RZSBSDK_KEYSTATE_UP);
    LoadKeyImageToRazer(".\\imagedata\\play.png",RZSBSDK_DK_7, RZSBSDK_KEYSTATE_UP);
    LoadKeyImageToRazer(".\\imagedata\\fforward.png",RZSBSDK_DK_8, RZSBSDK_KEYSTATE_UP);
    LoadKeyImageToRazer(".\\imagedata\\volup.png",RZSBSDK_DK_9, RZSBSDK_KEYSTATE_UP);
    LoadKeyImageToRazer(".\\imagedata\\voldown.png",RZSBSDK_DK_10, RZSBSDK_KEYSTATE_UP);
    RzSBDynamicKeySetCallback(OnDkClickedButton);

    // END UNSTABLE

	return 0;
}



//////////////////////////////////////////////////////////////////////////
// Convert a pixel from one format (ARGB) to another(RGB565-16bit) 
//////////////////////////////////////////////////////////////////////////
unsigned short __inline ARGB2RGB565(int x)
{
	unsigned short r = (unsigned short ) ( (x & 0x00F80000) >> 8 );
	unsigned short g = (unsigned short ) ( (x & 0x0000FC00) >> 5 );
	unsigned short b = (unsigned short ) ( (x & 0x000000F8) >> 3 );
	unsigned short rgb565 = 0;	
	
	rgb565 = r | g | b;

	return rgb565;
}

/**
 * COLORFROMROW
 * Calculates an ARGB value based on the input row. This function is used in the demo
 * to make it easy to calculate color gradients for the visualization.
 * 
 * @param row The current row to calculate from (0...numrows)
 * @return A short representing the ARGB value.
 */
static int wheelrotate = 0;
unsigned short __inline COLORFROMROW(int row)
{   
    if (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) > 0){
        // FIXME: consts, please.
        if (colormode == 0){
            // Black and white example
            return ARGB2RGB565( (int)
                ((int)(256 - (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) ) ) ) | 
                ((int)(256 - (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) ) ) << 8) | 
                ((int)(256 - (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) ) ) << 16)
            );            
        } else if (colormode == 1){
            // Green and blue
            if (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) > 0){
                return ARGB2RGB565( (int)
                    ((int)(256 - (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) ) ) << 8) | 
                    ((int)(row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE)))
                );
            }
            return ARGB2RGB565(0);
        } else  if (colormode == 2){        
            // Purple and Blue sample
            return ARGB2RGB565( (int)
                ((int)(256 - (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) ) ) << 0) | 
                ((int)(row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE)) << 16)
            );
            return ARGB2RGB565(0);
        } else if (colormode == 3) {
            // Red to green        
            return ARGB2RGB565( (int)
                ((int)(256 - (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) ) ) << 16) | 
                ((int)(row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE)) << 8)
            );
            return ARGB2RGB565(0);

            // Green to red
            // Uncomment to reverse colors on this section
            /*if (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) > 0){
                return ARGB2RGB565( (int)
                    ((int)(256 - (row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE) ) ) << 8) | 
                    ((int)(row * (256.0 / SWITCHBLADE_TOUCHPAD_Y_SIZE)) << 16)
                );
            }
            return ARGB2RGB565(0);
            */
            // Red looks cooler, leave it red.
        } else {        
            // Demo of tri-color wheel.
            int wheel = 160;            
            int wheelie = wheel + wheelrotate;
            switch (row / wheel)
            {            
                case 0:
                    return ARGB2RGB565( (int)
                        wheel - (row % wheel) |        // red down
                        (row % wheel) << 8             // Green up      
                        );
                    break;
                case 1:                
                    return ARGB2RGB565( (int)
                        (wheel - (row % wheel)) << 8 |  // green down
                        (row % wheel) << 16);           // blue up
                    break;
                case 2:
                    return ARGB2RGB565( (int)
                        (row % wheel) |                 // red up                
                        (wheel - (row % wheel)) << 16); // blue down 
                    break;
            }
            wheelrotate += 1;
        }
    }
    // Return black.
    return ARGB2RGB565(0);
}
/**
 * visRender
 * This is the main loop that renders visualizations to the display. In the demo implementation
 * the custom data inputs for directly rendering pixels is used. Alternatively, you could use
 * images or could directly interface with the hWnd for the switchblade screen.
 * 
 * @param this_mod The current visualization module with spectrum analysis.
 */ 
int visRender(struct winampVisModule *this_mod)
{
    // C - Counter for pixels
    // row - counter for screen rows
    // col - counter for screen cols
    // amplitude - scale for wave drawn
    // DIVSCALE - calculated scale for mapping winamp waveform data (higher values = higher amplitude response)
    // DIVS - number of ?? unused?
    // divCount - counter for number of columns traversed
    // divLimit - Number of columns
    // blkAreaStep - step counter for blank area between bars
    // BLK_LIMIT - the limit in pixels for the blank area.
    int c=0, row=0, col=0, DIVSCALE=57, DIVS=1, divCount=0, divLimit=200, blkAreaStep=0, BLK_LIMIT=3;
    
    // Adjust the amplitude based on divLimit values
    // .6 works well at divLimit 200
    // .7 will keep things interesting on the high end
    double AMPLITUDE=.75;


    // step - counter for speed regulation
    // rows - limiter for drawing to rows
    // rowsDir - direction to move rows
    // stepSpeed - speed for redrawing the bars, higher value = lower speed, smoother
    // speed - rate of drawing the columns, higher value = faster motion
    //         note: should be a factor of 576, e.g. 1,2,3,4,6,8,16,18,24, ... 576
    static int step = 0, rows = 0, speed = 32, rowsDir = 50, stepSpeed = 2;

    // stores cached waveform data
    int* limitBuffer;

    // used to trigger blank / nonblank areas
    bool drawNextPixels = true;
    // RGB buffer for keyboard screen
    unsigned short* g_rgb565;
    RZSBSDK_BUFFERPARAMS bp;
    HRESULT ret = S_OK;
    size_t sNumPixels;

    //divLimit = SWITCHBLADE_TOUCHPAD_X_SIZE / DIVS;
    limitBuffer = (int*)malloc(sizeof(int) * divLimit);
    rows += rowsDir;
    DIVSCALE = 576 / divLimit;

	// start OpenGL rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
    // RENDERING CODE GOES HERE d(-_-)b

	// Buffer size--how many pixels in the buffers
    sNumPixels = SWITCHBLADE_TOUCHPAD_X_SIZE * SWITCHBLADE_TOUCHPAD_Y_SIZE;
    g_rgb565 = (unsigned short*)malloc(sizeof(unsigned short) * sNumPixels);

        
    for (divCount = 0; divCount < divLimit; divCount++)
    {
        // TODO: smooth amplitude based on average window.
        limitBuffer[divCount] = 
            (int)((this_mod->spectrumData[0][divCount] * DIVSCALE + 
            this_mod->spectrumData[1][divCount] * DIVSCALE)  * AMPLITUDE);
    }
        
    drawNextPixels = limitBuffer[divCount] > row;

    // Traverse the display space and set pixels.
    for (row = SWITCHBLADE_TOUCHPAD_Y_SIZE - 1; row >= 0; row--) 
    {          
        for (col=0; col < SWITCHBLADE_TOUCHPAD_X_SIZE; col++)
        {
            if ((col % (SWITCHBLADE_TOUCHPAD_X_SIZE / divLimit) == 0))
            {
                if (divCount >= (divLimit-1))
                {
                    divCount = 0;                
                }
                else
                {
                    divCount++;
                }                
                drawNextPixels = limitBuffer[divCount] > row;
                for (blkAreaStep = 0; blkAreaStep < BLK_LIMIT; blkAreaStep++)
                {
                    if (col < SWITCHBLADE_TOUCHPAD_X_SIZE){
                        g_rgb565[c++] = ARGB2RGB565(0x00000000);
                        col++;
                    }                        
                }
            }

            // Set blank pixels in the RGB buffer for values out of range or draw the current pixel color.
            if (drawNextPixels)
            {
                g_rgb565[c++] = COLORFROMROW(row);
            }
            else
            {
                g_rgb565[c++] = ARGB2RGB565(0x00000000);
            }
        }

        // Reverse directions when reaching ends of the display.
        if (rows < 1)
        {
            rowsDir = speed;
        }
        if (rows > SWITCHBLADE_TOUCHPAD_Y_SIZE)
        {
            rowsDir = -1*speed;
        }
	}

    free(limitBuffer);

    // Set the buffer parameters for SwitchBlade LCD
	memset(&bp, 0, sizeof(RZSBSDK_BUFFERPARAMS));
	bp.pData = (BYTE *)g_rgb565;
	bp.DataSize = sNumPixels * sizeof(WORD);
	bp.PixelType = RGB565;

	// Send the stream and render the buffer
    ret = RzSBRenderBuffer(RZSBSDK_DISPLAY_WIDGET, &bp);

    //TODO: render stuff to the keys!
    //ret = RzSBRenderBuffer(RZSBSDK_DISPLAY_DK_1, &bp);
    
    free(g_rgb565);
  
	return 0;
}

void visQuit(struct winampVisModule *this_mod)
{
	// disable OpenGL
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(getVisInstance()->hRC);
	ReleaseDC(getVisInstance()->hWnd,getVisInstance()->hDC);

	getVisInstance()->hDC = NULL;
	getVisInstance()->hRC = NULL;    

	// de-init Win32 stuff
	SendMessage(this_mod->hwndParent, WM_WA_IPC, 0, IPC_SETVISWND);

	// delete our window
	if (getVisInstance()->myWindowState.me) 
	{
		SetForegroundWindow(getVisInstance()->this_mod.hwndParent);
		DestroyWindow(getVisInstance()->myWindowState.me);
	}
    
    RzSBStop();
	UnregisterClass(VIS_USER_CLASS,this_mod->hDllInstance); // unregister window class
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//TODO: handle more specific messages as needed

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0); 
			return 0;
		}

		case WM_KEYDOWN:
		{
			//winampVisModule *this_mod = (winampVisModule *) GetWindowLong(hWnd,GWL_USERDATA);
			//PostMessage(this_mod->hwndParent,message,wParam,lParam);

			getVisInstance()->keys[ wParam ] = true;
			PostMessage(getVisInstance()->this_mod.hwndParent,message,wParam,lParam);
			return 0;	
		}

        case WM_KEYUP:
		{
			getVisInstance()->keys[ wParam ] = false;
			PostMessage(getVisInstance()->this_mod.hwndParent,message,wParam,lParam);
			return 0;
		}

		case WM_SIZE:
		{
			//resizeGLWindow(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}