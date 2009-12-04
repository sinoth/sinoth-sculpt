
#include <stdio.h>
#include <sintimer.h>
#include <math.h>

#include "scene.h"


scene::scene() {

    // screen stuff
    fullscreen = false;
    fullscreen_checkbox = fullscreen;
    res_win_x = 640; res_win_y = 480;
    res_full_x = 640; res_full_y = 480;

    // input stuff
    mouseGrab = false;
    mouseL = mouseR = false;
    mouseX = 0; mouseY = 0;
    mouseSensitivity = 1.0;
    keyboardMoveSpeed = 0.1;
    mouseWheel = 0;
    alt_status = false;
    shift_status = false;
    ctrl_status = false;

    //ui stuff
    loaded_username = false;

    myself = this;
    quit = false;
    confirm_quit = false;
    mainmenu_visible = true;
    current_vid_mode = 0;
    have_piece = false;

    piece_x_size = piece_y_size = piece_z_size = 5;

}

scene::~scene() {}





////////////////////////////////////////////////////////////////////////////////
// calculate and display fps
//
void scene::FPS()
{
	static int frames=0;
	static sinTimer fpsTimer(1);

    frames++;
    if( fpsTimer.needUpdateNoCarry() )
    {
		//printf("FPS: %d\n",frames);//,settings.ull_counter);
        frames = 0;
    }
}



// Replaces gluPerspective. Sets the frustum to perspective mode.
// fovY		- Field of vision in degrees in the y direction
// aspect	- Aspect ratio of the viewport
// zNear	- The near clipping distance
// zFar		- The far clipping distance
void scene::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
	//static const GLdouble pi = 3.1415926535897932384626433832795;
	//static const GLdouble pi = 3.14159265;
    static const GLdouble PI_360 = 0.008726646259; //9716388888888888888889
	static GLdouble fW, fH;

	//fH = tan( fovY / 360.0 * 3.14159 ) * zNear;
	fH = tan( fovY * PI_360 ) * zNear;
	fW = fH * aspect;

	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}





