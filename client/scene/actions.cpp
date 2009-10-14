
#include "scene.h"


void scene::username_OK() {

    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("Username");
    temp_window->doFade(UI_FADE_OUT, 20);
    temp_window->setActive(false);

    ui_textinput *temp_textinput;
    temp_textinput = (ui_textinput*)myself->mainGui.getWidget("username_input");
    strcpy(myself->username, temp_textinput->getText() );

    printf("Setting username to : [%s]\n", temp_textinput->getText() );

}


bool scene::username_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                scene::username_OK();
                break;
        }
      break;

      case GLFW_RELEASE:
      break;
    }

    return false;
}

//bool confirmquit_input_keycallback(int,int);
//bool mainmenu_input_keycallback(int,int);
//bool options_input_keycallback(int,int);

void scene::quitbutton() {
    if ( myself->confirm_quit ) { myself->quit = true; return; }

    myself->confirm_quit = true;
    //show the confirm dialog here
}

void scene::confirmquit_YES() {
    myself->quit = true;
}

void scene::confirmquit_NO() {
    myself->mainGui.getWindow("ConfirmQuit")->doFade(UI_FADE_OUT, 10);
    myself->confirm_quit = false;
}

void scene::load_username() {
    FILE *username_file;
    username_file = fopen("username.txt","r");

    if ( username_file == NULL ) {
        //no username has been picked
        sprintf(username,"anonymous");
        return;
    }

    fgets(username,30,username_file);
    fclose(username_file);
    loaded_username = true;
    return;
}


void scene::save_username() {

    FILE *username_file;
    username_file = fopen("username.txt","w");

    if ( username_file == NULL ) {
        printf("ERROR: cannot open username file for write.\n");
        return;
    }

    fwrite(username, 1, strlen(username)+1, username_file);
    fclose(username_file);
}



void scene::options_res_left() {
    myself->current_vid_mode--;
    if ( myself->current_vid_mode < 0 )
        myself->current_vid_mode = 0;

    myself->mainGui.getWidget("res_display")->my_font.setText(myself->vid_modes_strings[myself->current_vid_mode].c_str());
    myself->mainGui.getWidget("res_display")->my_font.cook();
}

void scene::options_res_right() {
    myself->current_vid_mode++;
    if ( myself->current_vid_mode >= myself->total_vid_modes )
        myself->current_vid_mode = myself->total_vid_modes-1;

    myself->mainGui.getWidget("res_display")->my_font.setText(myself->vid_modes_strings[myself->current_vid_mode].c_str());
    myself->mainGui.getWidget("res_display")->my_font.cook();
}

void scene::options_res_apply() {

    myself->mainGui.globalResize(myself->res_cur_x,
                                 myself->res_cur_y,
                                 myself->vid_modes[myself->current_vid_mode].Width,
                                 myself->vid_modes[myself->current_vid_mode].Height );

    myself->res_cur_x = myself->vid_modes[myself->current_vid_mode].Width;
    myself->res_cur_y = myself->vid_modes[myself->current_vid_mode].Height;

    glfwSetWindowSize(myself->res_cur_x, myself->res_cur_y);
    glViewport(0,0,myself->res_cur_x, myself->res_cur_y);

}
