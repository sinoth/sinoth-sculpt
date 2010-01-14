
#include <GL/glfw.h>
#include <sincamera.h>
#include <stdio.h>

#include "scene.h"

//ugh i hate this crap
scene *scene::myself;


void scene::keyboardInput( int key, int action ) {

    if ( mainGui.insertKey(key,action) ) return;

    switch (action) {
        case GLFW_PRESS:
            switch (key) {
                case 'E': mainCamera.changeVelocity(1*keyboardMoveSpeed); break;
                case 'D': mainCamera.changeVelocity(-1*keyboardMoveSpeed); break;
                case 'S': mainCamera.changeStrafeVelocity(-1*keyboardMoveSpeed); break;
                case 'F': mainCamera.changeStrafeVelocity(1*keyboardMoveSpeed); break;

                case 'Q':
                    if ( alt_status ) { quit = true; glfwTerminate(); }
                    break;

                case GLFW_KEY_TAB:
                    //if ( !mouseGrab ) { mouseGrab = !mouseGrab; glfwDisable( GLFW_MOUSE_CURSOR ); }
                    //else { glfwEnable( GLFW_MOUSE_CURSOR ); glfwSetMousePos(mouseX, mouseY); mouseGrab = !mouseGrab; }
                    //printf("mousegrab: %d\n", mouseGrab );
                    break;

                case GLFW_KEY_LALT: case GLFW_KEY_RALT:
                    alt_status = true;
                    break;

            }
            break;

        case GLFW_RELEASE:
            switch (key) {
                case 'E': mainCamera.changeVelocity(-1*keyboardMoveSpeed); break;
                case 'D': mainCamera.changeVelocity(1*keyboardMoveSpeed); break;
                case 'S': mainCamera.changeStrafeVelocity(1*keyboardMoveSpeed); break;
                case 'F': mainCamera.changeStrafeVelocity(-1*keyboardMoveSpeed); break;

                case GLFW_KEY_ESC:
                    if ( !confirm_quit ) {
                        confirm_quit = true;
                        mainGui.getWindow("ConfirmQuit")->doFade(UI_FADE_IN, 10);
                        mainGui.bringToFront(mainGui.getWindow("ConfirmQuit"));
                    } else {
                        printf("* MAIN: Received ESC key, quitting...\n");
                        quit = true;
                    }
                    break;
                case GLFW_KEY_F1:
                    mainGui.getWindow("MainMenu")->doFade(UI_FADE_IN, 10);
                    break;

                case GLFW_KEY_LALT: case GLFW_KEY_RALT:
                    alt_status = false;
                    break;
            }
            break;
    }
}

void scene::keyboardCharInput(int inchar, int instate) {
    mainGui.insertKeyChar(inchar,instate);
}


void scene::mousePosInput( int x, int y ) {

    //printf("x: %d, y: %d, grab: %d\n", x, y, mouseGrab);

    static ray3f temp_ray;
    static collision3f temp_collision, nearest_collision;
    static bool found_collision;
    nearest_collision.dist = 1000000;
    found_collision = false;

    //static vec3f mouse_ray_pos, mouse_ray_dir;

    mainCamera.getMouseRay(x, y, temp_ray.pos, temp_ray.dir);
    for ( int i=0; i<piece_x_size;++i )
     for ( int j=0; j<piece_y_size;++j )
      for ( int k=0; k<piece_z_size;++k ) {
        temp_collision.pos.set( i+piece_x_size+0.5,j+piece_y_size+0.5,k+piece_z_size+0.5 );
        if ( temp_ray.collideWithCube(temp_collision, 0.5) ) {
            //if ( i==0 || i==piece_x_size-1 || j==0 || j==piece_y_size-1 || k==0 || k==piece_z_size-1 )
            if ( temp_collision.dist < nearest_collision.dist ) {
                nearest_collision = temp_collision;
                nearest_collision.pos.set(i,j,k);
                found_collision = true;
            }
        }
        //selection_list[i+j*piece_x_size+k*piece_y_size*piece_x_size] = 0;
      }

    if ( found_collision ) {
        //selection_list[nearest_collision.pos.x+nearest_collision.pos.y*piece_x_size+nearest_collision.pos.z*piece_y_size*piece_x_size] = 1;
        selected_piece = nearest_collision.pos;
        hovering_piece = true;
        vec3f col;
        col = temp_ray.pos + temp_ray.dir * nearest_collision.dist;
        if ( col.x == piece_x_size ) selected_face = LEFT;
        if ( col.x == piece_x_size*2 ) selected_face = RIGHT;
        if ( col.y == piece_y_size ) selected_face = DOWN;
        if ( col.y == piece_y_size*2 ) selected_face = UP;
        if ( col.z == piece_z_size ) selected_face = FRONT;
        if ( col.z == piece_z_size*2 ) selected_face = BACK;
    } else {
        hovering_piece = false;
    }


    if ( mouseM ) {

        //if (mouseR) {
            mainCamera.arcSpinMouseX( -(x-mouseX)*0.4 );
        //} else {
            mainCamera.arcSpinMouseY( (y-mouseY)*0.4 );
        //}
        //printf("* position: %f,%f,%f\nstrafe: %f, %f, %f\nup: %f, %f, %f\nfacing: %f, %f, %f\n", mainCamera.p_position.x, mainCamera.p_position.y, mainCamera.p_position.z,
        //                                                                         mainCamera.arc_strafe.x, mainCamera.arc_strafe.y, mainCamera.arc_strafe.z,
        //                                                                         mainCamera.arc_up.x, mainCamera.arc_up.y, mainCamera.arc_up.z,
        //                                                                         mainCamera.arc_facing.x, mainCamera.arc_facing.y, mainCamera.arc_facing.z );
        //printf("* position: %f,%f,%f\nfacing: %f, %f, %f\n", mainCamera.p_position.x, mainCamera.p_position.y, mainCamera.p_position.z,
        //                                                                         mainCamera.arc_facing.x, mainCamera.arc_facing.y, mainCamera.arc_facing.z );

        //only show sides that face camera
        if ( mainCamera.arc_facing.z <= -0.162847 ) show_face[BACK] = true; else show_face[BACK] = false;
        if ( mainCamera.arc_facing.y <= -0.162847 ) show_face[UP] = true; else show_face[UP] = false;
        if ( mainCamera.arc_facing.x <= -0.162847 ) show_face[RIGHT] = true; else show_face[RIGHT] = false;
        if ( mainCamera.arc_facing.z >=  0.162847 ) show_face[FRONT] = true; else show_face[FRONT] = false;
        if ( mainCamera.arc_facing.y >=  0.162847 ) show_face[DOWN] = true; else show_face[DOWN] = false;
        if ( mainCamera.arc_facing.x >=  0.162847 ) show_face[LEFT] = true; else show_face[LEFT] = false;


    }

    if (mouseR) {
        mainCamera.arcZoom( (y-mouseY)*0.2 );
    }

    mainGui.insertMousePos(x,res_cur_y - y);


    mouseX = x; mouseY = y;
}



void scene::mouseClickInput( int button, int state ) {

    if ( mainGui.insertMouseClick(button,state,mouseX,res_cur_y-mouseY) ) return;
    switch ( state ) {
        case GLFW_PRESS:
            switch ( button ) {
                case GLFW_MOUSE_BUTTON_LEFT:
                    mouseL=1;

                    //set selected cube if hovering over
                    if ( hovering_piece ) {
                        placing_piece = true;
                    }

                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    mouseR=1;
                    break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                    mouseM=1;
                    break;
            }
            break;

        case GLFW_RELEASE:
            switch ( button ) {
                case GLFW_MOUSE_BUTTON_LEFT:
                    mouseL=0;
                    if ( placing_piece ) placing_piece = false;
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    mouseR=0;
                    break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                    mouseM=0;
                    break;
            }
            break;
    }

}



void scene::mouseWheelInput( int pos ) {
    // i_mouseWheel - pos
    mouseWheel = pos;
    //printf("mouse wheel: %d\n",pos);
}

bool scene::windowClose() {
    quit = true;
    return true;
}


void GLFWCALL scene::wrapper_mouse_pos( int xpos, int ypos ) {
    myself->mousePosInput(xpos,ypos); }

void GLFWCALL scene::wrapper_keyboard( int key, int state ) {
    myself->keyboardInput(key,state); }

void GLFWCALL scene::wrapper_keyboard_char( int key, int state ) {
    myself->keyboardCharInput(key,state); }

void GLFWCALL scene::wrapper_mouse_click( int button, int state ) {
    myself->mouseClickInput(button,state); }

void GLFWCALL scene::wrapper_mouse_wheel( int pos ) {
    myself->mouseWheelInput(pos); }

int GLFWCALL scene::wrapper_window_close( void ) {
    return myself->windowClose();
    //return true;
}

void GLFWCALL scene::wrapper_window_size( int xres, int yres ) {
//\/    myself->initResize(xres,yres);
}



