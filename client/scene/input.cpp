
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

                case GLFW_KEY_TAB:
                    switch ( view_method ) {
                        case 0: view_method = 1; break;
                        case 1: view_method = 0; break;
                    }
                    break;

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
                if ( placing_piece ) {
                    bool valid = false;
                    switch ( selected_face ) {
                        case CUBE_UP: case CUBE_DOWN: if ( i == outside_piece.x && k == outside_piece.z ) valid = true; break;
                        case CUBE_LEFT: case CUBE_RIGHT: if ( j == outside_piece.y && k == outside_piece.z ) valid = true; break;
                        case CUBE_FRONT: case CUBE_BACK: if ( i == outside_piece.x && j == outside_piece.y ) valid = true; break;
                    }
                    if ( valid ) {
                        nearest_collision = temp_collision;
                        nearest_collision.pos.set(i,j,k);
                        found_collision = true;
                    }
                } else {
                    nearest_collision = temp_collision;
                    nearest_collision.pos.set(i,j,k);
                    found_collision = true;
                }
            }
        }
        //selection_list[i+j*piece_x_size+k*piece_y_size*piece_x_size] = 0;
      }

    if ( found_collision ) {
        if ( placing_piece ) {
            selected_piece = nearest_collision.pos;
        } else {
            //selection_list[nearest_collision.pos.x+nearest_collision.pos.y*piece_x_size+nearest_collision.pos.z*piece_y_size*piece_x_size] = 1;
            selected_piece = nearest_collision.pos;
            vec3f col;
            col = temp_ray.pos + temp_ray.dir * nearest_collision.dist;
            //printf("col: %f, %f, %f -- %d, %d\n", col.x, col.y, col.z, piece_x_size, piece_x_size*2);
            //printf("col: %.17f, %.17f, %.17f -- %d, %d\n", col.x, col.y, col.z, piece_x_size, piece_x_size*2);

            if ( fabs(col.x - piece_x_size) < 0.0001 ) selected_face = CUBE_LEFT;
            if ( fabs(col.x - piece_x_size*2) < 0.0001 ) selected_face = CUBE_RIGHT;
            if ( fabs(col.y - piece_y_size) < 0.0001 ) selected_face = CUBE_DOWN;
            if ( fabs(col.y - piece_y_size*2) < 0.0001 ) selected_face = CUBE_UP;
            if ( fabs(col.z - piece_z_size) < 0.0001 ) selected_face = CUBE_FRONT;
            if ( fabs(col.z - piece_z_size*2) < 0.0001 ) selected_face = CUBE_BACK;

            //printf("%d\n", selected_face);

        }
        hovering_piece = true;
    } else {
        hovering_piece = false;
    }


    if ( mouseM ) {

        mainCamera.arcZoom( (y-mouseY)*0.2 );

    }

    if (mouseR) {

        mainCamera.arcSpinMouseX( -(x-mouseX)*0.4 );
        mainCamera.arcSpinMouseY( (y-mouseY)*0.4 );

        vec3f cam_position = mainCamera.getPosition();

        if ( vec3f(-1,0,0) * ( vec3f(piece_x_size,piece_y_size*1.5,piece_z_size*1.5) - cam_position) < 0 ) show_face[CUBE_LEFT] = true; else show_face[CUBE_LEFT] = false;
        if ( vec3f(1,0,0) * ( vec3f(piece_x_size*2,piece_y_size*1.5,piece_z_size*1.5) - cam_position) < 0 ) show_face[CUBE_RIGHT] = true; else show_face[CUBE_RIGHT] = false;
        if ( vec3f(0,-1,0) * ( vec3f(piece_x_size*1.5,piece_y_size,piece_z_size*1.5) - cam_position) < 0 ) show_face[CUBE_DOWN] = true; else show_face[CUBE_DOWN] = false;
        if ( vec3f(0,1,0) * ( vec3f(piece_x_size*1.5,piece_y_size*2,piece_z_size*1.5) - cam_position) < 0 ) show_face[CUBE_UP] = true; else show_face[CUBE_UP] = false;
        if ( vec3f(0,0,-1) * ( vec3f(piece_x_size*1.5,piece_y_size*1.5,piece_z_size) - cam_position) < 0 ) show_face[CUBE_FRONT] = true; else show_face[CUBE_FRONT] = false;
        if ( vec3f(0,0,1) * ( vec3f(piece_x_size*1.5,piece_y_size*1.5,piece_z_size*2) - cam_position) < 0 ) show_face[CUBE_BACK] = true; else show_face[CUBE_BACK] = false;

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
                        outside_piece = selected_piece;
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
                    if ( placing_piece ) {
                        if ( hovering_piece ) {
                            built_list[selected_piece.x+selected_piece.y*piece_x_size+selected_piece.z*piece_y_size*piece_x_size] ^= 1;
                            //hovering_piece = false;
                        }
                        placing_piece = false;
                        selected_piece = outside_piece;
                    }
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

void GLFWCALL scene::wrapper_window_size( int , int  ) {
//\/    myself->initResize(xres,yres);
}



