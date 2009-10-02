
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

                case GLFW_KEY_TAB:
                    if ( !mouseGrab ) { mouseGrab = !mouseGrab; glfwDisable( GLFW_MOUSE_CURSOR ); }
                    else { glfwEnable( GLFW_MOUSE_CURSOR ); glfwSetMousePos(mouseX, mouseY); mouseGrab = !mouseGrab; }
                    printf("mousegrab: %d\n", mouseGrab );
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
                    printf("* MAIN: Received ESC key, quitting...\n");
                    quit = 1;
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
        mainGui.insertMouseClick(button,state,mouseX,res_cur_y-mouseY);
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


