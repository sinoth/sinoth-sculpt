
#include <dsfmt.c>
#include <stdio.h>

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

    //constrict mouse to the window
    glfwDisable( GLFW_MOUSE_CURSOR );
    //glfwEnable( GLFW_MOUSE_CURSOR );

    glfwSetWindowTitle( "small!" );

    // Enable sticky keys
    glfwEnable( GLFW_STICKY_KEYS );
    //glfwDisable( GLFW_AUTO_POLL_EVENTS );

    glViewport(0,0,res_cur_x, res_cur_y);

    //seed the holy RNG
    //init_gen_rand(time((time_t *)0));


	//background color
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glFrontFace(GL_CW);
	glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(5.0);
    glLineWidth(2.0);
    begin3D();

    init_gen_rand(0);

    glfwSetKeyCallback( wrapper_keyboard );
    glfwSetMousePosCallback( wrapper_mouse_pos );
    glfwSetMouseWheelCallback( wrapper_mouse_wheel );

    generateCavern();
    initPhys();

    printf("* init: Scene initalization complete. [%fs]\n", glfwGetTime()-elapsed_time);

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

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //*colorLight = ( 1.0, 1.0, 1.0, 1.0 );
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorLight);

    //////////////////////////////////////////
    // ambient light
    //////////////////////////////////////////
    global_ambient[0] = 0.2f;
    global_ambient[1] = 0.2f;
    global_ambient[2] = 0.2f;
    global_ambient[3] = 0.21f;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //////////////////////////////////////////
    // light0
    //////////////////////////////////////////

    light_ambient0[0] = 0.0f;
    light_ambient0[1] = 0.0f;
    light_ambient0[2] = 0.0f;
    light_ambient0[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);

    light_diffuse0[0] = 0.8f;
    light_diffuse0[1] = 0.8f;
    light_diffuse0[2] = 0.8f;
    light_diffuse0[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);

    //specularLight[0] = 0.4f;
    //specularLight[1] = 0.4f;
    //specularLight[2] = 0.4f;
    //specularLight[3] = 1.0f;
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light_info);

    light_pos0[0] = 48.0f;
    light_pos0[1] = 12.0f;
    light_pos0[2] = 48.0f;
    light_pos0[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);

    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, .001);
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02f);
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.008f);


    //////////////////////////////////////////
    // light1
    //////////////////////////////////////////

    light_ambient1[0] = 0.0f;
    light_ambient1[1] = 0.0f;
    light_ambient1[2] = 0.0f;
    light_ambient1[3] = 1.0f;
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);

    light_diffuse1[0] = 0.4f;
    light_diffuse1[1] = 0.4f;
    light_diffuse1[2] = 0.4f;
    light_diffuse1[3] = 1.0f;
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);

    //specularLight[0] = 0.4f;
    //specularLight[1] = 0.4f;
    //specularLight[2] = 0.4f;
    //specularLight[3] = 1.0f;
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light_info);

    light_pos1[0] = 0.0f;
    light_pos1[1] = 100.0f;
    light_pos1[2] = 0.0f;
    light_pos1[3] = 1.0f;
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, .001);
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02f);
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.008f);




    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

/*
        GLfloat fogcolor[4];
        fogcolor[0] = 0.0;
        fogcolor[1] = 0.0;
        fogcolor[2] = 0.0;
        fogcolor[3] = 0.0;

        glFogi(GL_FOG_MODE, GL_LINEAR );		// Fog Mode
        glFogfv(GL_FOG_COLOR, fogcolor);			// Set Fog Color
        glFogf(GL_FOG_DENSITY, 0.1f);				// How Dense Will The Fog Be
        glHint(GL_FOG_HINT, GL_NICEST);			// Fog Hint Value
        glFogf(GL_FOG_START, 5.0f);				// Fog Start Depth
        glFogf(GL_FOG_END, 20.0f);				// Fog End Depth
        glEnable(GL_FOG);					// Enables GL_FOG
*/

}
