
#include <stdio.h>
#include <sintimer.h>

#include "scene.h"


scene::scene() {

    // screen stuff
    fullscreen = false;
    res_win_x = 1024; res_win_y = 768;
    res_full_x = 640; res_full_y = 480;

    if ( fullscreen ) {
        res_cur_x = res_full_x; res_cur_y = res_full_y;
    } else {
        res_cur_x = res_win_x; res_cur_y = res_win_y; }

    // input stuff
    mouseGrab = true;
    mouseL = mouseR = false;
    mouseX = mouseY = 0;
    mouseSensitivity = 1.0;
    keyboardMoveSpeed = 0.1;
    mouseWheel = 0;

    dynamicsWorld = NULL;
    myself = this;
}

scene::~scene() {}











////////////////////////////////////////////////////////////////////////////////
// calculate and display fps
//
void scene::FPS()
{
	static int frames=0;
	//static char *frame_string = new char[20];
	static sinTimer fpsTimer(1);
    //fpsTimer.getTime();

    frames++;
    //printf("what");
    if( fpsTimer.needUpdate() )
    {
		//printf("FPS: %d [%lld]\n",frames);//,settings.ull_counter);
		printf("FPS: %d\n",frames);//,settings.ull_counter);
        //sprintf(frame_string, "FPS: %d", frames);
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






bool scene::playerContactAdd(btManifoldPoint& cp,
                      const btCollisionObject* colObj0,
                      int partId0,
                      int index0,
                      const btCollisionObject* colObj1,
                      int partId1,
                      int index1) {

    static const btRigidBody *body0, *body1;
    //static collision_data* col_data;
    //printf("wat\n");

    if ( cp.m_userPersistentData == NULL ) {
        //printf("new contact\n");
        body0 = static_cast<const btRigidBody *> (colObj0);
        body1 = static_cast<const btRigidBody *> (colObj1);

        if ( (body0 == myself->mainPlayer.my_body && body1 == myself->mainGround) ||
             (body1 == myself->mainPlayer.my_body && body0 == myself->mainGround)  ) {
            myself->mainPlayer.contactPoints++;
            //myself->mainPlayer.setPlaneLimit( -cp.m_normalWorldOnB, cp.getPositionWorldOnB() );
            cp.m_userPersistentData = static_cast<void*>(&myself->mainPlayer);
            //myself->collected_orb1 = true;
            //printf("added normal: %f, %f, %f\n", -cp.m_normalWorldOnB.getX(), -cp.m_normalWorldOnB.getY(), -cp.m_normalWorldOnB.getZ() );
         }

    }

    return false;
}


bool scene::playerContactDestroy(void* userPersistentData) {


    if ( userPersistentData != NULL ) {
        //static_cast<player*>(userPersistentData)->delContact();
        static_cast<player*>(userPersistentData)->contactPoints--;
        //printf("del, points: %d\n", myself->mainPlayer.getContacts() );

    }

    return false;
}
