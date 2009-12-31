
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
                    if ( !mouseGrab ) { mouseGrab = !mouseGrab; glfwDisable( GLFW_MOUSE_CURSOR ); }
                    else { glfwEnable( GLFW_MOUSE_CURSOR ); glfwSetMousePos(mouseX, mouseY); mouseGrab = !mouseGrab; }
                    printf("mousegrab: %d\n", mouseGrab );
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

    if ( mouseGrab ) {
            mainCamera.changePitch(-0.1*(y-mouseY)*mouseSensitivity);
            mainCamera.changeHeading(-0.2*(x-mouseX)*mouseSensitivity);
            mainCamera.recalculateAngle();
        //} else if ( !mouseL && mouseR ) {
            //mainCamera.updatePositionYPlane(event.motion.xrel, event.motion.yrel);
        //} else if ( mouseL && !mouseR ) {
            //mainCamera.updatePositionXPlane(.2*event.motion.xrel, .2*event.motion.yrel);
        //}

    } else {

        static vec3f mouse_ray_pos, mouse_ray_dir;
        mainCamera.getMouseRay(mouseX, mouseY, mouse_ray_pos, mouse_ray_dir);

        if ( mouseL ) {

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

        }
        if (mouseR) {
            mainCamera.arcZoom( (y-mouseY)*0.2 );
        }
        mainGui.insertMousePos(x,res_cur_y - y);
    }

    mouseX = x; mouseY = y;
}



void scene::mouseClickInput( int button, int state ) {

    if ( mouseGrab ) {
        switch ( state ) {
            case GLFW_PRESS:
                switch ( button ) {
                    case GLFW_MOUSE_BUTTON_LEFT:
                        mouseL=1;
                        break;

                    case GLFW_MOUSE_BUTTON_RIGHT:
                    case GLFW_MOUSE_BUTTON_MIDDLE:
                        break;
                }
                break;

            case GLFW_RELEASE:
                switch ( button ) {
                    case GLFW_MOUSE_BUTTON_LEFT:
                        mouseL=0;
                        break;

                    case GLFW_MOUSE_BUTTON_RIGHT:
                        break;
                    case GLFW_MOUSE_BUTTON_MIDDLE:
                        break;
                }
                break;
        }
    } else {
        if ( mainGui.insertMouseClick(button,state,mouseX,res_cur_y-mouseY) ) return;
        switch ( state ) {
            case GLFW_PRESS:
                switch ( button ) {
                    case GLFW_MOUSE_BUTTON_LEFT:
                        mouseL=1;
                        break;
                    case GLFW_MOUSE_BUTTON_RIGHT:
                        mouseR=1;
                        break;
                    case GLFW_MOUSE_BUTTON_MIDDLE:
                        break;
                }
                break;

            case GLFW_RELEASE:
                switch ( button ) {
                    case GLFW_MOUSE_BUTTON_LEFT:
                        mouseL=0;
                        break;
                    case GLFW_MOUSE_BUTTON_RIGHT:
                        mouseR=0;
                        break;
                    case GLFW_MOUSE_BUTTON_MIDDLE:
                        break;
                }
                break;
        }
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



