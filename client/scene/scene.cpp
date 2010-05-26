
#include <stdio.h>
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
    mouseX = 0; mouseY = 0; mouseM = 0;
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

    //initialize the selection bits
    built_list.resize(piece_x_size*piece_y_size*piece_z_size);
    for ( int i=0; i<piece_x_size*piece_y_size*piece_z_size; ++i)
        built_list[i] = 0;

    for (int i=0; i < 6; ++i) show_face[i] = 0;
    show_face[CUBE_BACK] = 1;

    placing_piece = false;
    hovering_piece = false;
    view_method = 0;
    selected_face = 0;

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

