
#include <GL/glfw.h>
#include <sincamera.h>
#include <stdio.h>

#include "scene.h"

//ugh i hate this crap
scene *scene::myself;


void scene::keyboardInput( int key, int action ) {

    switch (action) {
        case GLFW_PRESS:
            switch (key) {
                case 'E': mainPlayer.goForward = true; break;
                case 'D': mainPlayer.goBack = true; break;
                case 'S': mainPlayer.goLeft = true; break;
                case 'F': mainPlayer.goRight = true; break;
                case GLFW_KEY_SPACE: mainPlayer.doJump(); break;
                //case 'Z': softBodyWorldInfo->m_sparsesdf.GarbageCollect(); break;
                case 'X':
                    mainRope->m_anchors.clear();
                    break;
                case 'Z':


                    break;

            }
            break;

        case GLFW_RELEASE:
            switch (key) {
                case 'E': mainPlayer.goForward = false; break;
                case 'D': mainPlayer.goBack = false; break;
                case 'S': mainPlayer.goLeft = false; break;
                case 'F': mainPlayer.goRight = false; break;
            }
            break;
    }
}


void scene::mousePosInput( int x, int y ) {

    if ( mouseGrab ) {
            mainCamera.changePitch(-0.1*(y-mouseY)*mouseSensitivity);
            mainCamera.changeHeading(-0.2*(x-mouseX)*mouseSensitivity);
            mainCamera.recalculateAngle();
        //} else if ( !mouseL && mouseR ) {
            //mainCamera.updatePositionYPlane(event.motion.xrel, event.motion.yrel);
        //} else if ( mouseL && !mouseR ) {
            //mainCamera.updatePositionXPlane(.2*event.motion.xrel, .2*event.motion.yrel);
        //}
        mouseX = x; mouseY = y;
    }

}



void scene::mouseClickInput( int button, int state ) {

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

}



void scene::mouseWheelInput( int pos ) {
    // i_mouseWheel - pos
    mouseWheel = pos;
    //printf("mouse wheel: %d\n",pos);

    if ( dynamicsWorld ) {
        //btSoftBody::tNodeArray &nodes(mainRope>m_nodes);
        //mainRope->cutLink(4, 5, 0.1 );
        static int lawl = mainRope->m_nodes.size()-2;
        mainRope->m_anchors.clear();

        //btMotionState *state = mainPlayer.my_body->getMotionState();
        //btMotionState tempms;
        btTransform tempt;
        tempt.setOrigin(mainRope->m_nodes[lawl].m_x);
        //tempt.setIdentity();
        //tempt.setOrigin(mainRope->m_nodes[lawl].m_x);
        //tempt.setOrigin(btVector3(30,10,10));
        //mainPlayer.my_body->setWorldTransform(tempt);
        mainPlayer.my_body->setCenterOfMassTransform(tempt);
        mainRope->appendAnchor(lawl,mainPlayer.my_body,true);
        lawl--;
    }
}




void GLFWCALL scene::wrapper_mouse_pos( int xpos, int ypos ) {
    myself->mousePosInput(xpos,ypos); }

void GLFWCALL scene::wrapper_keyboard( int key, int state ) {
    myself->keyboardInput(key,state); }

void GLFWCALL scene::wrapper_mouse_click( int button, int state ) {
    myself->mouseClickInput(button,state); }

void GLFWCALL scene::wrapper_mouse_wheel( int pos ) {
    myself->mouseWheelInput(pos); }

int GLFWCALL scene::wrapper_window_close( void ) {
//\/    return myself->window_close();
    return true;
}

void GLFWCALL scene::wrapper_window_size( int xres, int yres ) {
//\/    myself->initResize(xres,yres);
}



