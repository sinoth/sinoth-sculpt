#ifndef SCENE_H
#define SCENE_H

#include <GL/glfw.h>
#include <vector>

#include <sincamera.h>
#include <sinlight.h>
#include <sinui.h>
#include "sinsocket.h"
//#include <sinprim.h>


#define UP     0
#define DOWN   1
#define LEFT   2
#define RIGHT  3
#define FRONT  4
#define BACK   5


typedef struct serverinfo_s {
    unsigned char server_id;
    char server_name[100];
    int total_pieces;
    int pieces_left;
    unsigned char player_total;
    unsigned char player_left;
} serverinfo;


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

    int total_vid_modes;
    int current_vid_mode;
    GLFWvidmode vid_modes[100];
    std::vector<std::string> vid_modes_strings;

    // input stuff
    bool mouseGrab;
    bool mouseL, mouseR, mouseM;
    int mouseX, mouseY;
    int mouseX_old, mouseY_old;
    float mouseSensitivity;
    float keyboardMoveSpeed;
    int mouseWheel;
    bool alt_status;
    bool shift_status;
    bool ctrl_status;

    // camera stuff
    sinCamera mainCamera;
    void resetCamera();

    // light stuff
    sinLighting mainLighting;

    //ui stuff
    GLuint theme_texture;
    SinUI mainGui;
    freetype_font_controller fontController;
    freetype_font font12,font18;

    //network stuff
    serverinfo servers[5];
    char my_hash[17];
    char *piece_blob;

    //edit mode stuff
    void generateVA();
    bool have_piece;
    unsigned char piece_x_size, piece_y_size, piece_z_size;
    std::vector<GLfloat> vec_grid_lines[6];
    std::vector<GLfloat> vec_grid_lines_color[6];
    bool show_face[6];

    //for selection
    std::vector<char> selection_list;

    //client stuff
    char username[30];
    bool loaded_username;
    bool mainmenu_visible;
    bool fullscreen_checkbox;

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
    bool reInit();
    void init_ui();
    void reInit_ui();
    void initLight();
    void input();

    void load_username();
    void save_username();

    //network stuff
    bool retrieveServerList();
    bool participateInServer(int);

    //input and callbacks
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
    bool static confirmquit_input_keycallback(int,int);
    bool static mainmenu_input_keycallback(int,int);
    bool static options_input_keycallback(int,int);
    bool static serverlist_input_keycallback(int,int);
    void static gui2closebutton();
    void static mainmenu_quit();
    void static mainmenu_list();
    void static mainmenu_options();
    void static mainmenu_close();
    void static confirmquit_YES();
    void static confirmquit_NO();
    void static options_res_left();
    void static options_res_right();
    void static options_full_checkbox();
    void static options_full_checkbox_text();
    void static options_username();
    void static options_close();
    void static options_res_apply();
    void static serverlist_refresh();
    void static serverlist_close();
    void static serverbutton_one();

    //self-reference variable
    //required for C callbacks
    static scene *myself;

    void perspectiveGL( GLdouble , GLdouble , GLdouble , GLdouble  );

};


#endif
