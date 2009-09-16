#ifndef SCENE_H
#define SCENE_H

#include <GL/glfw.h>
#include <vector>

#include <sincamera.h>
#include <sinprim.h>

#include "player.h"



class scene
{
public:

    /////////////////////////////////////////////////////
    // variables!

    // screen stuff
    bool fullscreen;
    int res_win_x, res_win_y;
    int res_full_x, res_full_y;
    int res_cur_x, res_cur_y;

    // render stuff
    std::vector<GLfloat> cavern_mesh_vert;
    std::vector<GLfloat> cavern_mesh_vert2;
    std::vector<GLfloat> cavern_mesh_color;
    std::vector<GLfloat> cavern_mesh_norm;

    // input stuff
    bool mouseGrab;
    bool mouseL, mouseR;
    int mouseX, mouseY;
    float mouseSensitivity;
    float keyboardMoveSpeed;
    int mouseWheel;

    // player stuff
    player mainPlayer;
    sinCamera mainCamera;
    //physics callback functions
    static bool playerContactAdd(btManifoldPoint&, const btCollisionObject*,int,int,const btCollisionObject*,int,int);
    static bool playerContactDestroy(void*);
    static void physicsTickCallback(btDynamicsWorld *, btScalar);

    //physics stuff
    btDiscreteDynamicsWorld *dynamicsWorld;
    btSoftBodyWorldInfo* softBodyWorldInfo;
    btRigidBody *mainGround;
    btRigidBody *mainPlatform;
    btSoftBody *mainRope;

    //sound
    //irrklang::ISoundEngine* sound_engine;

    //light
    GLfloat global_ambient[4];

    GLfloat light_ambient0[4];
    GLfloat light_diffuse0[4];
    GLfloat light_color0[4];
    GLfloat light_pos0[4];

    GLfloat light_ambient1[4];
    GLfloat light_diffuse1[4];
    GLfloat light_color1[4];
    GLfloat light_pos1[4];

    /////////////////////////////////////////////////////
    // functions!

	scene();
	~scene();

	 int loadTextures();
    void FPS();

	void begin2D();
	void end2D();
	void begin3D();
	void end3D();

    void render();
    void renderTheFuckingRope();
    void update();
    bool init();
    void initPhys();
    void initLight();
    void input();

    void generateCavern();
    void drawFace(int,btVector3);
    void marching_tet( unsigned char, btVector3[4] );


	void keyboardInput(int, int);
	void mousePosInput(int, int);
	void mouseClickInput(int, int);
	void mouseWheelInput(int);
	void static GLFWCALL wrapper_mouse_pos( int, int );
	void static GLFWCALL wrapper_keyboard( int, int );
	void static GLFWCALL wrapper_mouse_click( int, int );
	void static GLFWCALL wrapper_mouse_wheel( int );
	 int static GLFWCALL wrapper_window_close( void );
	void static GLFWCALL wrapper_window_size( int, int );

    //self-reference variable
    //required for C callbacks
    static scene *myself;

    void perspectiveGL( GLdouble , GLdouble , GLdouble , GLdouble  );

};


#endif
