
#include "scene.h"


////////////////////////////////////////////////////////////////////////////////
void scene::username_OK() {

    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("Username");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    ui_textinput *temp_textinput;
    temp_textinput = (ui_textinput*)myself->mainGui.getWidget("username_input");
    strcpy(myself->username, temp_textinput->getText() );

    printf("Setting username to : [%s]\n", temp_textinput->getText() );

}

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
bool scene::options_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                //scene::username_OK();
                break;
        }
      break;
      case GLFW_RELEASE:
        switch ( key ) {
            case GLFW_KEY_ESC:
                scene::options_close();
                return true;
                break;
        }
      break;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool scene::infowindow_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                break;
        }
      break;
      case GLFW_RELEASE:
        switch ( key ) {
            case GLFW_KEY_ESC:
                scene::infowindow_close();
                return true;
                break;
        }
      break;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool scene::connectmenu_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                break;
        }
      break;
      case GLFW_RELEASE:
        switch ( key ) {
            case GLFW_KEY_ESC:
                scene::connectmenu_close();
                return true;
                break;
        }
      break;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool scene::currentmap_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                break;
        }
      break;
      case GLFW_RELEASE:
        switch ( key ) {
            case GLFW_KEY_ESC:
                scene::currentmapmenu_close();
                return true;
                break;
        }
      break;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool scene::currentmapsubmit_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                break;
        }
      break;
      case GLFW_RELEASE:
        switch ( key ) {
            case GLFW_KEY_ESC:
                scene::currentmapsubmit_close();
                return true;
                break;
        }
      break;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool scene::serverlist_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                //scene::username_OK();
                break;
        }
      break;
      case GLFW_RELEASE:
        switch ( key ) {
            case GLFW_KEY_ESC:
                scene::serverlist_close();
                return true;
                break;
        }
      break;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool scene::mainmenu_input_keycallback(int key, int state) {
    switch ( state ) {
      case GLFW_PRESS:
        switch ( key ) {
            case GLFW_KEY_ENTER:
                //scene::username_OK();
                break;
        }
      break;
      case GLFW_RELEASE:
        switch ( key ) {
            case GLFW_KEY_ESC:
                scene::mainmenu_close();
                return true;
                break;
        }
      break;
    }
    return false;
}

//bool confirmquit_input_keycallback(int,int);
//bool mainmenu_input_keycallback(int,int);
//bool options_input_keycallback(int,int);

////////////////////////////////////////////////////////////////////////////////
void scene::mainmenu_close() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);
}

////////////////////////////////////////////////////////////////////////////////
void scene::mainmenu_quit() {
    if ( myself->confirm_quit ) { myself->quit = true; return; }
    myself->confirm_quit = true;
    //show the confirm dialog here
    myself->mainGui.getWindow("ConfirmQuit")->doFade(UI_FADE_IN, 10);
    myself->mainGui.bringToFront(myself->mainGui.getWindow("ConfirmQuit"));
}

////////////////////////////////////////////////////////////////////////////////
//
void scene::mainmenu_options() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("Options");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::mainmenu_connect() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("ConnectMenu");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::mainmenu_info() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("Info");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::confirmquit_YES() {
    myself->quit = true;
}

////////////////////////////////////////////////////////////////////////////////
void scene::confirmquit_NO() {
    myself->mainGui.getWindow("ConfirmQuit")->doFade(UI_FADE_OUT, 10);
    myself->confirm_quit = false;
}

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
void scene::options_res_left() {
    myself->current_vid_mode--;
    if ( myself->current_vid_mode < 0 )
        myself->current_vid_mode = 0;

    myself->mainGui.getWidget("res_display")->my_font.setText(myself->vid_modes_strings[myself->current_vid_mode].c_str());
    myself->mainGui.getWidget("res_display")->my_font.cook();
}

////////////////////////////////////////////////////////////////////////////////
void scene::options_res_right() {
    myself->current_vid_mode++;
    if ( myself->current_vid_mode >= myself->total_vid_modes )
        myself->current_vid_mode = myself->total_vid_modes-1;

    myself->mainGui.getWidget("res_display")->my_font.setText(myself->vid_modes_strings[myself->current_vid_mode].c_str());
    myself->mainGui.getWidget("res_display")->my_font.cook();
}

////////////////////////////////////////////////////////////////////////////////
void scene::options_res_apply() {
    int tw, th;
    int cw, ch;

    cw = myself->res_cur_x;
    ch = myself->res_cur_y;

    tw = myself->vid_modes[myself->current_vid_mode].Width;
    th = myself->vid_modes[myself->current_vid_mode].Height;

    myself->res_cur_x = tw;
    myself->res_cur_y = th;

    if ( myself->fullscreen_checkbox != myself->fullscreen ) {
        myself->fullscreen = myself->fullscreen_checkbox;
        myself->reInit();
    } else { //just change window size
        glfwSetWindowSize( tw, th );
    }


    glfwGetWindowSize(&tw, &th);
    //printf("New size: %d x %d\n", tw, th );

    glViewport(0,0,tw,th);

    myself->mainGui.globalResize(cw, ch, tw, th );

    myself->res_cur_x = tw;
    myself->res_cur_y = th;

}

////////////////////////////////////////////////////////////////////////////////
void scene::options_full_checkbox() {
    ui_checkbox *full_checkbox = (ui_checkbox*)myself->mainGui.getWidget("full_checkbox");
    myself->fullscreen_checkbox = full_checkbox->isChecked();
    //printf("Fullscreen checkbox is %d\n", myself->fullscreen_checkbox );
}

////////////////////////////////////////////////////////////////////////////////
void scene::options_full_checkbox_text() {
    ui_checkbox *full_checkbox = (ui_checkbox*)myself->mainGui.getWidget("full_checkbox");
    full_checkbox->flipChecked();
    myself->fullscreen_checkbox = full_checkbox->isChecked();
    //printf("Fullscreen checkbox is %d\n", myself->fullscreen_checkbox );
}

////////////////////////////////////////////////////////////////////////////////
void scene::options_close() {

    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("Options");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::options_username() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("Username");
    myself->mainGui.bringToFront(temp_window);
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::serverlist_close() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("ServerList");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}


/////////////////////////////////////////////////////////////////////
void scene::serverbutton_one()   { if ( myself->servers[0].server_id != -1 ) myself->retrieveEntireMap(myself->servers[0].server_id); }
void scene::serverbutton_two()   { if ( myself->servers[1].server_id != -1 ) myself->retrieveEntireMap(myself->servers[1].server_id); }
void scene::serverbutton_three() { if ( myself->servers[2].server_id != -1 ) myself->retrieveEntireMap(myself->servers[2].server_id); }
void scene::serverbutton_four()  { if ( myself->servers[3].server_id != -1 ) myself->retrieveEntireMap(myself->servers[3].server_id); }
void scene::serverbutton_five()  { if ( myself->servers[4].server_id != -1 ) myself->retrieveEntireMap(myself->servers[4].server_id); }

////////////////////////////////////////////////////////////////////////////////
void scene::infowindow_close() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("Info");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::connectmenu_close() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("ConnectMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("MainMenu");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::connectmenu_current() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("ConnectMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("CurrentMapMenu");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
    myself->retrieveCurrentMap();
}

////////////////////////////////////////////////////////////////////////////////
void scene::connectmenu_archive() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("ConnectMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("ServerList");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);

    myself->retrieveArchiveList(0);

    //myself->retrieveEntireMap(6);
}

////////////////////////////////////////////////////////////////////////////////
void scene::currentmapmenu_close() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("CurrentMapMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    temp_window = myself->mainGui.getWindow("ConnectMenu");
    temp_window->doFade(UI_FADE_IN, 10);
    temp_window->setActive(true);
}

////////////////////////////////////////////////////////////////////////////////
void scene::currentmapmenu_request() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("CurrentMapMenu");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    myself->retrievePiece();
}

////////////////////////////////////////////////////////////////////////////////
void scene::currentmapsubmit_submit() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("CurrentMapSubmit");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);

    myself->submitPiece();
}

////////////////////////////////////////////////////////////////////////////////
void scene::currentmapsubmit_discard() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("CurrentMapSubmit");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);
}

////////////////////////////////////////////////////////////////////////////////
void scene::currentmapsubmit_close() {
    ui_window *temp_window;
    temp_window = myself->mainGui.getWindow("CurrentMapSubmit");
    temp_window->doFade(UI_FADE_OUT, 10);
    temp_window->setActive(false);
}


void scene::serverlist_prev() {
    myself->retrieveArchiveList(0);
}

void scene::serverlist_next() {
    myself->retrieveArchiveList(0);
}
