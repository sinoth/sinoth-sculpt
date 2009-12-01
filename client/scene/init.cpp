
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "scene.h"


bool scene::init() {

    double elapsed_time;
    printf("* init: Starting scene initalization...\n"); elapsed_time = glfwGetTime();

    if ( fullscreen ) { res_cur_x = res_full_x; res_cur_y = res_full_y; }
    else { res_cur_x = res_win_x; res_cur_y = res_win_y; }

	if ( !glfwInit() )
    { printf("ERROR: Unable to init glfw\n"); return 1; }

	glfwSwapInterval(1); //1 for vsync on

    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

    if (!glfwOpenWindow(
          res_cur_x, res_cur_y,    // Width and height of window
          8, 8, 8,           // Number of red, green, and blue bits for color buffer
          8,                 // Number of bits for alpha buffer
          24,                // Number of bits for depth buffer (Z-buffer)
          0,                 // Number of bits for stencil buffer
          GLFW_WINDOW        // We want a desktop window (could be GLFW_FULLSCREEN)
          ))
        { printf("ERROR: Unable to set resolution\n"); return 1; }


    //dump the usable video modes
    GLFWvidmode temp_vid_modes[100];
    total_vid_modes = glfwGetVideoModes(temp_vid_modes, 100);
    char temp_string[100];
    for ( int i=0; i < total_vid_modes; i++ ) {
        if ( temp_vid_modes[i].RedBits + temp_vid_modes[i].GreenBits + temp_vid_modes[i].BlueBits == 24 ) {
            sprintf(temp_string,"%d x %d", temp_vid_modes[i].Width, temp_vid_modes[i].Height );
            vid_modes[vid_modes_strings.size()] = temp_vid_modes[i];
            vid_modes_strings.push_back(temp_string);
        }
    }
    total_vid_modes = vid_modes_strings.size();

    //constrict mouse to the window
    if ( mouseGrab ) glfwDisable( GLFW_MOUSE_CURSOR );
    else glfwEnable( GLFW_MOUSE_CURSOR );
    //glfwEnable( GLFW_MOUSE_CURSOR );

    glfwSetWindowTitle( "sculpt" );

    // Enable sticky keys
    glfwEnable( GLFW_STICKY_KEYS );
    //glfwDisable( GLFW_AUTO_POLL_EVENTS );

    glViewport(0,0,res_cur_x, res_cur_y);

    //seed the holy RNG
    //init_gen_rand(time((time_t *)0));
    //init_gen_rand(0);

	//background color
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glFrontFace(GL_CW);
	glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(3.0);
    //glLineWidth(1.0);

    loadTextures();

    //grab the username
    load_username();

    //ui fun
    font12.init("dejavusansLGC.ttf",13);
    font18.init("dejavusansLGC.ttf",18);
    init_ui();

    begin3D();

    glfwSetKeyCallback( wrapper_keyboard );
    glfwSetCharCallback( wrapper_keyboard_char );
    glfwSetMousePosCallback( wrapper_mouse_pos );
    glfwSetMouseButtonCallback( wrapper_mouse_click );
    glfwSetMouseWheelCallback( wrapper_mouse_wheel );
    glfwSetWindowCloseCallback( wrapper_window_close );

    //seed the randomness
    srand(time(NULL));

    //\/for testing
    generateVA();

    printf("* init: Scene initalization complete. [%fs]\n", glfwGetTime()-elapsed_time);

    return 0;
}



bool scene::reInit() {

    double elapsed_time;
    printf("* init: Starting scene reinitalization...\n"); elapsed_time = glfwGetTime();

    mainGui.storeControllers();

    glfwCloseWindow();

    if (!glfwOpenWindow(
          res_cur_x, res_cur_y,    // Width and height of window
          8, 8, 8,           // Number of red, green, and blue bits for color buffer
          8,                 // Number of bits for alpha buffer
          24,                // Number of bits for depth buffer (Z-buffer)
          0,                 // Number of bits for stencil buffer
                             // We want a desktop window (could be GLFW_FULLSCREEN)
          ( fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW )
          ))
        { printf("ERROR: Unable to set resolution\n"); return 1; }


    //constrict mouse to the window
    if ( mouseGrab ) glfwDisable( GLFW_MOUSE_CURSOR );
    else glfwEnable( GLFW_MOUSE_CURSOR );
    //glfwEnable( GLFW_MOUSE_CURSOR );

    glfwSetWindowTitle( "sculpt" );

    // Enable sticky keys
    glfwEnable( GLFW_STICKY_KEYS );
    //glfwDisable( GLFW_AUTO_POLL_EVENTS );

    glViewport(0,0,res_cur_x, res_cur_y);

    //seed the holy RNG
    //init_gen_rand(time((time_t *)0));
    //init_gen_rand(0);

	//background color
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glFrontFace(GL_CW);
	glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //glPointSize(5.0);
    //glLineWidth(5.0);

    loadTextures();

    //ui fun
    font18.init("dejavusansLGC.ttf",18);
    font12.init("dejavusansLGC.ttf",13);
    reInit_ui();

    begin3D();

    glfwSetKeyCallback( wrapper_keyboard );
    glfwSetCharCallback( wrapper_keyboard_char );
    glfwSetMousePosCallback( wrapper_mouse_pos );
    glfwSetMouseButtonCallback( wrapper_mouse_click );
    glfwSetMouseWheelCallback( wrapper_mouse_wheel );
    glfwSetWindowCloseCallback( wrapper_window_close );

    printf("* init: Scene reinitalization complete. [%fs]\n", glfwGetTime()-elapsed_time);

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// initialize 2D
//
void scene::begin2D()
{

    //can make this faster by only getting viewport and recalculating matrix
    //when the window size changes, need a toggle

	static int vPort[4];
	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

    //remember the row order is funny, it goes [0][4][8][12]
	GLfloat proj[] = {  2.0/(float)vPort[2],  0,                    0,    0,
                        0,                    2.0/(float)vPort[3],  0,    0,
                        0,                    0,                 -1.0,    0,
                       -1,                   -1,                    0,    1  };


	//glOrtho(0, vPort[2], vPort[3], 0, -1, 1);
	//left, right, bottom, top, near, far
    glLoadMatrixf( proj );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.375, 0.375, 0.0);
	//glTranslatef(0.5, 0.5, 0.0);

	glDisable(GL_DEPTH_TEST);

}


////////////////////////////////////////////////////////////////////////////////
// clean up 2D
//
void scene::end2D()
{
	//glPopAttrib(); // toss the depth buffer attrib
    glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
}


////////////////////////////////////////////////////////////////////////////////
// initialize 3D
//
void scene::begin3D()
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
              perspectiveGL(45.0f,((GLfloat)res_cur_x)/((GLfloat)res_cur_y),0.1f,1000.0f);
    mainCamera.setInternals(45.0f,((GLfloat)res_cur_x)/((GLfloat)res_cur_y),0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	//glEnable( GL_TEXTURE_2D );

    initLight();
}


////////////////////////////////////////////////////////////////////////////////
// clean up 3D
//
void scene::end3D()
{
	//glPopAttrib(); // toss the depth buffer attrib
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
}





void scene::initLight() {

    mainLighting.init();

    mainLighting.setAmbient(0, 0.3,0.3,0.3);
    mainLighting.setDiffuse(0, 0.6,0.6,0.6);
    mainLighting.setPosition(0, 0, 20, 0 );
    mainLighting.enableLight(0);

/*
        GLfloat fogcolor[4];
        fogcolor[0] = 0.0;
        fogcolor[1] = 0.0;
        fogcolor[2] = 0.0;
        fogcolor[3] = 0.0;

        glFogi(GL_FOG_MODE, GL_LINEAR );	// Fog Mode
        glFogfv(GL_FOG_COLOR, fogcolor);	// Set Fog Color
        glFogf(GL_FOG_DENSITY, 0.1f);		// How Dense Will The Fog Be
        glHint(GL_FOG_HINT, GL_NICEST);		// Fog Hint Value
        glFogf(GL_FOG_START, 5.0f);			// Fog Start Depth
        glFogf(GL_FOG_END, 20.0f);			// Fog End Depth
        glEnable(GL_FOG);					// Enables GL_FOG
*/

}



int scene::loadTextures() {


    glGenTextures( 1, &theme_texture );
    glBindTexture( GL_TEXTURE_2D, theme_texture );

    if ( !glfwLoadTexture2D("theme.tga",GLFW_NO_RESCALE_BIT) ) {
        printf("Unable to load theme.tga\n");
    } else {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST ); //GL_LINEAR
    }

    return 0;
}
