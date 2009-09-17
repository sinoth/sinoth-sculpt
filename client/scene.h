#ifndef SCENE_H
#define SCENE_H

#include <GL/glfw.h>
#include <vector>

#include <sincamera.h>
#include <sinlight.h>
//#include <sinprim.h>


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

    // input stuff
    bool mouseGrab;
    bool mouseL, mouseR;
    int mouseX, mouseY;
    float mouseSensitivity;
    float keyboardMoveSpeed;
    int mouseWheel;

    // camera stuff
    sinCamera mainCamera;

    // light stuff
    sinLighting mainLighting;


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
    void update();
    bool init();
    void initLight();
    void input();

	void keyboardInput(int, int);
	void mousePosInput(int, int);
	void mouseClickInput(int, int);
	void mouseWheelInput(int);
	void static GLFWCALL wrapper_keyboard( int, int );
	void static GLFWCALL wrapper_mouse_pos( int, int );
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
