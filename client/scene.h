#ifndef SCENE_H
#define SCENE_H

#include <GL/glfw.h>
#include <vector>

#include <sincamera.h>
#include <sinlight.h>
#include <sinui.h>
//#include <sinprim.h>


class scene
{
public:

    /////////////////////////////////////////////////////
    // variables!

    // screen stuff
    bool fullscreen;
    bool quit;
    bool confirm_quit;
    int res_win_x, res_win_y;
    int res_full_x, res_full_y;
    int res_cur_x, res_cur_y;

    // input stuff
    bool mouseGrab;
    bool mouseL, mouseR;
    int mouseX, mouseY;
    int mouseX_old, mouseY_old;
    float mouseSensitivity;
    float keyboardMoveSpeed;
    int mouseWheel;

    // camera stuff
    sinCamera mainCamera;

    // light stuff
    sinLighting mainLighting;

    //ui stuff
    GLuint theme_texture;
    SinUI mainGui;
    freetype_font_controller fontController;
    freetype_font font12;
    void static gui2closebutton();
    void static quitbutton();

    //client stuff
    void load_username();
    void save_username();
    char username[30];
    bool loaded_username;

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
    void init_ui();
    void initLight();
    void input();

	void keyboardInput(int, int);
    void keyboardCharInput(int,int);
	void mousePosInput(int, int);
	void mouseClickInput(int, int);
	void mouseWheelInput(int);
	bool windowClose();
	void static GLFWCALL wrapper_keyboard( int, int );
	void static GLFWCALL wrapper_keyboard_char( int, int );
	void static GLFWCALL wrapper_mouse_pos( int, int );
	void static GLFWCALL wrapper_mouse_click( int, int );
	void static GLFWCALL wrapper_mouse_wheel( int );
	 int static GLFWCALL wrapper_window_close( void );
	void static GLFWCALL wrapper_window_size( int, int );

	//UI functions
    void static username_OK();
    bool static username_input_keycallback(int,int);

    //self-reference variable
    //required for C callbacks
    static scene *myself;

    void perspectiveGL( GLdouble , GLdouble , GLdouble , GLdouble  );

};


#endif
