
#include "scene.h"


void scene::init_ui() {

    /////////////////////////////////////////////////////////////////
    // style setup
    /////////////////////////////////////////////////////////////////

    np_style default_win_style;
    np_style default_win_style_notitlebar;
    np_style default_win_titlebar_style;
    tex_style default_win_closebutton_style;
    np_style default_np_style;
    np_style default_style_a;
    tex_style res_leftarrow_style;
    tex_style res_rightarrow_style;

    default_win_titlebar_style.normal.setNP( UI_9P_TL, 128, 128, 1, 1, 3, 5 );
    default_win_titlebar_style.normal.setNP( UI_9P_TM, 128, 128, 5, 1, 1, 5 );
    default_win_titlebar_style.normal.setNP( UI_9P_TR, 128, 128, 7, 1, 3, 5 );
    default_win_titlebar_style.normal.setNP( UI_9P_ML, 128, 128, 1, 7, 3, 1 );
    default_win_titlebar_style.normal.setNP( UI_9P_MM, 128, 128, 5, 7, 1, 1 );
    default_win_titlebar_style.normal.setNP( UI_9P_MR, 128, 128, 7, 7, 3, 1 );
    default_win_titlebar_style.normal.setNP( UI_9P_BL, 128, 128, 1, 9, 3, 6 );
    default_win_titlebar_style.normal.setNP( UI_9P_BM, 128, 128, 5, 9, 1, 6 );
    default_win_titlebar_style.normal.setNP( UI_9P_BR, 128, 128, 7, 9, 3, 6 );
    default_win_titlebar_style.cook();
    //
    default_win_style.hover.setNP( UI_9P_TL, 128, 128, 1, 17, 0, 0 );
    default_win_style.hover.setNP( UI_9P_TM, 128, 128, 4, 17, 0, 0 );
    default_win_style.hover.setNP( UI_9P_TR, 128, 128, 6, 17, 0, 0 );
    default_win_style.hover.setNP( UI_9P_ML, 128, 128, 1, 20, 2, 1 );
    default_win_style.hover.setNP( UI_9P_MM, 128, 128, 4, 20, 1, 1 );
    default_win_style.hover.setNP( UI_9P_MR, 128, 128, 6, 20, 2, 1 );
    default_win_style.hover.setNP( UI_9P_BL, 128, 128, 1, 22, 2, 2 );
    default_win_style.hover.setNP( UI_9P_BM, 128, 128, 4, 22, 1, 2 );
    default_win_style.hover.setNP( UI_9P_BR, 128, 128, 6, 22, 2, 2 );
    //
    default_win_style.normal.setNP( UI_9P_TL, 128, 128, 11, 17, 0, 0 );
    default_win_style.normal.setNP( UI_9P_TM, 128, 128, 14, 17, 0, 0 );
    default_win_style.normal.setNP( UI_9P_TR, 128, 128, 16, 17, 0, 0 );
    default_win_style.normal.setNP( UI_9P_ML, 128, 128, 11, 20, 2, 1 );
    default_win_style.normal.setNP( UI_9P_MM, 128, 128, 14, 20, 1, 1 );
    default_win_style.normal.setNP( UI_9P_MR, 128, 128, 16, 20, 2, 1 );
    default_win_style.normal.setNP( UI_9P_BL, 128, 128, 11, 22, 2, 2 );
    default_win_style.normal.setNP( UI_9P_BM, 128, 128, 14, 22, 1, 2 );
    default_win_style.normal.setNP( UI_9P_BR, 128, 128, 16, 22, 2, 2 );
    default_win_style.cook();
    //
    default_win_style_notitlebar.normal.setNP( UI_9P_TL, 128, 128, 11, 26, 2, 2 );
    default_win_style_notitlebar.normal.setNP( UI_9P_TM, 128, 128, 14, 26, 1, 2 );
    default_win_style_notitlebar.normal.setNP( UI_9P_TR, 128, 128, 16, 26, 2, 2 );
    default_win_style_notitlebar.normal.setNP( UI_9P_ML, 128, 128, 11, 29, 2, 1 );
    default_win_style_notitlebar.normal.setNP( UI_9P_MM, 128, 128, 14, 29, 1, 1 );
    default_win_style_notitlebar.normal.setNP( UI_9P_MR, 128, 128, 16, 29, 2, 1 );
    default_win_style_notitlebar.normal.setNP( UI_9P_BL, 128, 128, 11, 31, 2, 2 );
    default_win_style_notitlebar.normal.setNP( UI_9P_BM, 128, 128, 14, 31, 1, 2 );
    default_win_style_notitlebar.normal.setNP( UI_9P_BR, 128, 128, 16, 31, 2, 2 );
    default_win_style_notitlebar.cook();
    //
    default_win_closebutton_style.normal.setTex(  128, 128, 32, 40, 19, 19 );
    default_win_closebutton_style.hover.setTex(   128, 128, 32, 20, 19, 19 );
    default_win_closebutton_style.pressed.setTex( 128, 128, 32, 00, 19, 19 );
    default_win_closebutton_style.cook();
    //
    res_leftarrow_style.normal.setTex(  128, 128, 63, 00, 10, 20 );
    res_leftarrow_style.hover.setTex(   128, 128, 52, 00, 10, 20 );
    res_leftarrow_style.pressed.setTex( 128, 128, 74, 00, 10, 20 );
    res_leftarrow_style.cook();
    //
    res_rightarrow_style.normal.setTex(  128, 128, 63, 21, 10, 20 );
    res_rightarrow_style.hover.setTex(   128, 128, 52, 21, 10, 20 );
    res_rightarrow_style.pressed.setTex( 128, 128, 74, 21, 10, 20 );
    res_rightarrow_style.cook();
    //
    default_np_style.hover.setNP( UI_9P_TL, 128, 128, 1, 17, 2, 2 );
    default_np_style.hover.setNP( UI_9P_TM, 128, 128, 4, 17, 1, 2 );
    default_np_style.hover.setNP( UI_9P_TR, 128, 128, 6, 17, 2, 2 );
    default_np_style.hover.setNP( UI_9P_ML, 128, 128, 1, 20, 2, 1 );
    default_np_style.hover.setNP( UI_9P_MM, 128, 128, 4, 20, 1, 1 );
    default_np_style.hover.setNP( UI_9P_MR, 128, 128, 6, 20, 2, 1 );
    default_np_style.hover.setNP( UI_9P_BL, 128, 128, 1, 22, 2, 2 );
    default_np_style.hover.setNP( UI_9P_BM, 128, 128, 4, 22, 1, 2 );
    default_np_style.hover.setNP( UI_9P_BR, 128, 128, 6, 22, 2, 2 );
    //
    default_np_style.normal.setNP( UI_9P_TL, 128, 128, 11, 26, 2, 2 );
    default_np_style.normal.setNP( UI_9P_TM, 128, 128, 14, 26, 1, 2 );
    default_np_style.normal.setNP( UI_9P_TR, 128, 128, 16, 26, 2, 2 );
    default_np_style.normal.setNP( UI_9P_ML, 128, 128, 11, 29, 2, 1 );
    default_np_style.normal.setNP( UI_9P_MM, 128, 128, 14, 29, 1, 1 );
    default_np_style.normal.setNP( UI_9P_MR, 128, 128, 16, 29, 2, 1 );
    default_np_style.normal.setNP( UI_9P_BL, 128, 128, 11, 31, 2, 2 );
    default_np_style.normal.setNP( UI_9P_BM, 128, 128, 14, 31, 1, 2 );
    default_np_style.normal.setNP( UI_9P_BR, 128, 128, 16, 31, 2, 2 );
    //
    default_np_style.pressed.setNP( UI_9P_TL, 128, 128, 21, 26, 2, 2 );
    default_np_style.pressed.setNP( UI_9P_TM, 128, 128, 24, 26, 1, 2 );
    default_np_style.pressed.setNP( UI_9P_TR, 128, 128, 26, 26, 2, 2 );
    default_np_style.pressed.setNP( UI_9P_ML, 128, 128, 21, 29, 2, 1 );
    default_np_style.pressed.setNP( UI_9P_MM, 128, 128, 24, 29, 1, 1 );
    default_np_style.pressed.setNP( UI_9P_MR, 128, 128, 26, 29, 2, 1 );
    default_np_style.pressed.setNP( UI_9P_BL, 128, 128, 21, 31, 2, 2 );
    default_np_style.pressed.setNP( UI_9P_BM, 128, 128, 24, 31, 1, 2 );
    default_np_style.pressed.setNP( UI_9P_BR, 128, 128, 26, 31, 2, 2 );
    default_np_style.cook();

    default_style_a = default_np_style;

    default_style_a.active.setNP( UI_9P_TL, 128, 128,  1, 35, 2, 2 );
    default_style_a.active.setNP( UI_9P_TM, 128, 128,  4, 35, 1, 2 );
    default_style_a.active.setNP( UI_9P_TR, 128, 128,  6, 35, 2, 2 );
    default_style_a.active.setNP( UI_9P_ML, 128, 128,  1, 38, 2, 1 );
    default_style_a.active.setNP( UI_9P_MM, 128, 128,  4, 38, 1, 1 );
    default_style_a.active.setNP( UI_9P_MR, 128, 128,  6, 38, 2, 1 );
    default_style_a.active.setNP( UI_9P_BL, 128, 128,  1, 40, 2, 2 );
    default_style_a.active.setNP( UI_9P_BM, 128, 128,  4, 40, 1, 2 );
    default_style_a.active.setNP( UI_9P_BR, 128, 128,  6, 40, 2, 2 );
    default_style_a.cook();
    default_style_a.font_x = 4;


    /////////////////////////////////////////////////////////////////
    // username window
    /////////////////////////////////////////////////////////////////

    ui_window *username_window = mainGui.addWindow("Username");
    username_window->setThemeTextureID(theme_texture);
    username_window->window_style = default_win_style;
    username_window->titlebar.setStyle(default_win_titlebar_style);
    username_window->closebutton.setStyle(default_win_closebutton_style);

    username_window->setXY(res_cur_x/2-100,res_cur_y/2+35);
    username_window->setWH(200,70);
    username_window->titlebar.setWH(200,20);
    //username_window->titlebar.can_drag_parent = true;
    username_window->enableFontController();
    //username_window->enableCloseButton();
    username_window->enableTitlebar();
    username_window->titlebar.my_font.setFont(&font12);
    username_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    username_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    username_window->titlebar.my_font.setStretch(true);
    username_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    username_window->titlebar.my_font.setText("Username");
    username_window->titlebar.my_font.cook();
    //username_window->closebutton.setPayload(gui2closebutton);

    ui_button_np *username_ok_button = (ui_button_np*)mainGui.addWidget("username_ok", UI_WIDGET_BUTTON_NP);
    username_ok_button->setStyle(default_np_style);
    username_ok_button->setXY(155,30);
    username_ok_button->setWH(35,30);
    username_ok_button->my_font.setFont(&font12);
    username_ok_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    username_ok_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    username_ok_button->my_font.setStretch(false);
    username_ok_button->my_font.setColor(0.0,0.0,0.0,1.0);
    username_ok_button->my_font.setText("OK!");
    username_ok_button->my_font.cook();
    username_ok_button->setPayload(username_OK);

    ui_textinput *t_ti = (ui_textinput*)mainGui.addWidget("username_input", UI_WIDGET_TEXTINPUT);
    t_ti->setStyle(default_style_a);
    t_ti->setXY(10,30);
    t_ti->setWH(140,30);
    t_ti->setMaxTextLength(10);
    t_ti->setText(username);
    t_ti->my_font.setFont(&font12, FONT_HINT_DYNAMIC);
    t_ti->my_font.setColor(0.0,0.0,0.0,1.0);
    t_ti->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_ti->my_font.setStretch(false);
    t_ti->my_font.cook();
    t_ti->setCustomKeyCallback(username_input_keycallback);

    username_window->cook();


    /////////////////////////////////////////////////////////////////
    // main menu
    /////////////////////////////////////////////////////////////////

    ui_window *mainmenu_window = mainGui.addWindow("MainMenu");
    mainmenu_window->setThemeTextureID(theme_texture);
    mainmenu_window->window_style = default_win_style;
    mainmenu_window->titlebar.setStyle(default_win_titlebar_style);
    mainmenu_window->closebutton.setStyle(default_win_closebutton_style);

    mainmenu_window->setXY(res_cur_x/2-75,res_cur_y/2+90);
    mainmenu_window->setWH(150,180);
    mainmenu_window->titlebar.setWH(150,20);
    //mainmenu_window->titlebar.can_drag_parent = true;
    mainmenu_window->enableFontController();
    //mainmenu_window->enableCloseButton();
    mainmenu_window->enableTitlebar();
    mainmenu_window->titlebar.my_font.setFont(&font12);
    mainmenu_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_window->titlebar.my_font.setStretch(true);
    mainmenu_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    mainmenu_window->titlebar.my_font.setText("Main Menu");
    mainmenu_window->titlebar.my_font.cook();
    //mainmenu_window->closebutton.setPayload(gui2closebutton);

    ui_button_np *mainmenu_list_button = (ui_button_np*)mainGui.addWidget("main_list", UI_WIDGET_BUTTON_NP);
    mainmenu_list_button->setStyle(default_np_style);
    mainmenu_list_button->setXY(10,30);
    mainmenu_list_button->setWH(130,40);
    mainmenu_list_button->my_font.setFont(&font12);
    mainmenu_list_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_list_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_list_button->my_font.setStretch(false);
    mainmenu_list_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_list_button->my_font.setText("Server List");
    mainmenu_list_button->my_font.cook();
    //mainmenu_list_button->setPayload(username_OK);

    ui_button_np *mainmenu_options_button = (ui_button_np*)mainGui.addWidget("main_options", UI_WIDGET_BUTTON_NP);
    mainmenu_options_button->setStyle(default_np_style);
    mainmenu_options_button->setXY(10,80);
    mainmenu_options_button->setWH(130,40);
    mainmenu_options_button->my_font.setFont(&font12);
    mainmenu_options_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_options_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_options_button->my_font.setStretch(false);
    mainmenu_options_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_options_button->my_font.setText("Options");
    mainmenu_options_button->my_font.cook();
    //mainmenu_list_button->setPayload(username_OK);

    ui_button_np *mainmenu_exit_button = (ui_button_np*)mainGui.addWidget("main_quit", UI_WIDGET_BUTTON_NP);
    mainmenu_exit_button->setStyle(default_np_style);
    mainmenu_exit_button->setXY(10,130);
    mainmenu_exit_button->setWH(130,40);
    mainmenu_exit_button->my_font.setFont(&font12);
    mainmenu_exit_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_exit_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_exit_button->my_font.setStretch(false);
    mainmenu_exit_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_exit_button->my_font.setText("Quit");
    mainmenu_exit_button->my_font.cook();
    //mainmenu_list_button->setPayload(username_OK);

    mainmenu_window->cook();



    /////////////////////////////////////////////////////////////////
    // confirm quit menu
    /////////////////////////////////////////////////////////////////

    ui_window *confirmquit_window = mainGui.addWindow("ConfirmQuit");
    confirmquit_window->setThemeTextureID(theme_texture);
    confirmquit_window->window_style = default_win_style_notitlebar;

    confirmquit_window->setXY(res_cur_x/2-170,res_cur_y/2+70);
    confirmquit_window->setWH(340,140);
    confirmquit_window->enableFontController();

    ui_label *confirmquit_text = (ui_label*)mainGui.addWidget("quit_text", UI_WIDGET_LABEL);
    confirmquit_text->setXY(30,25);
    confirmquit_text->setWH(280,30);
    confirmquit_text->my_font.setFont(&font12);
    confirmquit_text->my_font.setColor(1.0,1.0,1.0,1.0);
    confirmquit_text->my_font.setVertAlign(FONT_ALIGN_CENTER);
    confirmquit_text->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    //confirmquit_text->my_font.setStretch(true);
    confirmquit_text->my_font.setText("Are you sure you want to quit?\nYou will lose your current work.");
    confirmquit_text->my_font.cook();


    ui_button_np *confirmquit_yes_button = (ui_button_np*)mainGui.addWidget("quit_yes", UI_WIDGET_BUTTON_NP);
    confirmquit_yes_button->setStyle(default_np_style);
    confirmquit_yes_button->setXY(90,70);
    confirmquit_yes_button->setWH(60,40);
    confirmquit_yes_button->my_font.setFont(&font12);
    confirmquit_yes_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    confirmquit_yes_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    confirmquit_yes_button->my_font.setStretch(false);
    confirmquit_yes_button->my_font.setColor(0.0,0.0,0.0,1.0);
    confirmquit_yes_button->my_font.setText("Yes");
    confirmquit_yes_button->my_font.cook();
    confirmquit_yes_button->setPayload(confirmquit_YES);

    ui_button_np *confirmquit_no_button = (ui_button_np*)mainGui.addWidget("quit_no", UI_WIDGET_BUTTON_NP);
    confirmquit_no_button->setStyle(default_np_style);
    confirmquit_no_button->setXY(180,70);
    confirmquit_no_button->setWH(60,40);
    confirmquit_no_button->my_font.setFont(&font12);
    confirmquit_no_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    confirmquit_no_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    confirmquit_no_button->my_font.setStretch(false);
    confirmquit_no_button->my_font.setColor(0.0,0.0,0.0,1.0);
    confirmquit_no_button->my_font.setText("No");
    confirmquit_no_button->my_font.cook();
    confirmquit_no_button->setPayload(confirmquit_NO);

    confirmquit_window->cook();
    confirmquit_window->setVisible(false);


    /////////////////////////////////////////////////////////////////
    // options window
    /////////////////////////////////////////////////////////////////

    ui_window *options_window = mainGui.addWindow("Options");
    options_window->setThemeTextureID(theme_texture);
    options_window->window_style = default_win_style;
    options_window->titlebar.setStyle(default_win_titlebar_style);
    options_window->closebutton.setStyle(default_win_closebutton_style);

    options_window->setXY(res_cur_x/2-100,res_cur_y/2+75);
    options_window->setWH(200,150);
    options_window->titlebar.setWH(200,20);
    //options_window->titlebar.can_drag_parent = true;
    options_window->enableFontController();
    options_window->enableCloseButton();
    options_window->enableTitlebar();
    options_window->titlebar.my_font.setFont(&font12);
    options_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    options_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    options_window->titlebar.my_font.setStretch(true);
    options_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    options_window->titlebar.my_font.setText("Options");
    options_window->titlebar.my_font.cook();
    //options_window->closebutton.setPayload(gui2closebutton);

    ui_button *options_res_button_left = (ui_button*)mainGui.addWidget("res_left", UI_WIDGET_BUTTON);
    options_res_button_left->setStyle(res_leftarrow_style);
    options_res_button_left->setXY(10,30);
    options_res_button_left->setWH(10,20);
    options_res_button_left->setPayload(options_res_left);

    ui_label *res_text = (ui_label*)mainGui.addWidget("res_display", UI_WIDGET_LABEL);
    res_text->setXY(30,30);
    res_text->setWH(80,20);
    res_text->my_font.setFont(&font12,FONT_HINT_DYNAMIC);
    res_text->my_font.setColor(0.7,0.0,0.0,1.0);
    res_text->my_font.setVertAlign(FONT_ALIGN_CENTER);
    res_text->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    res_text->my_font.setStretch(true);
    res_text->my_font.setText(vid_modes_strings[current_vid_mode].c_str());
    res_text->my_font.cook();

    ui_button *options_res_button_right = (ui_button*)mainGui.addWidget("res_right", UI_WIDGET_BUTTON);
    options_res_button_right->setStyle(res_rightarrow_style);
    options_res_button_right->setXY(120,30);
    options_res_button_right->setWH(10,20);
    options_res_button_right->setPayload(options_res_right);

    ui_button_np *options_apply_button = (ui_button_np*)mainGui.addWidget("options_apply", UI_WIDGET_BUTTON_NP);
    options_apply_button->setStyle(default_np_style);
    options_apply_button->setXY(140,30);
    options_apply_button->setWH(50,20);
    options_apply_button->my_font.setFont(&font12);
    options_apply_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    options_apply_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    options_apply_button->my_font.setStretch(false);
    options_apply_button->my_font.setColor(0.0,0.0,0.0,1.0);
    options_apply_button->my_font.setText("Apply");
    options_apply_button->my_font.cook();
    options_apply_button->setPayload(options_res_apply);
/*
    ui_button_np *mainmenu_exit_button = (ui_button_np*)mainGui.addWidget("options_username", UI_WIDGET_BUTTON_NP);
    mainmenu_exit_button->setStyle(default_np_style);
    mainmenu_exit_button->setXY(10,130);
    mainmenu_exit_button->setWH(130,40);
    mainmenu_exit_button->my_font.setFont(&font12);
    mainmenu_exit_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_exit_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_exit_button->my_font.setStretch(false);
    mainmenu_exit_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_exit_button->my_font.setText("Change Username");
    mainmenu_exit_button->my_font.cook();
    //mainmenu_list_button->setPayload(username_OK);
*/
    options_window->cook();





    //if we haven't loaded a username, show the box
    if ( !loaded_username ) {
        mainGui.bringToFront( mainGui.getWindow("Username") );
        mainGui.getWidget("username_input")->setActive(true);
    } else { //else, just continue to main menu
        mainGui.getWindow("Username")->setVisible(false);
    }

}


void scene::init_ui_resize() {




}




/*

    ui_button_np *t_np;
    t_np = new ui_button_np;

    username_window->addChild(t_np);
    t_np->setStyle(default_np_style);
    t_np->setXY(20,30);
    t_np->setWH(80,20);
    t_np->my_font.setFont(&font12);
    t_np->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setStretch(true);
    t_np->my_font.setColor(0.0,0.0,0.0,1.0);
    t_np->my_font.setText("sup, dude");
    t_np->my_font.cook();

    t_np = new ui_button_np;

    username_window->addChild(t_np);
    t_np->setStyle(default_np_style);
    t_np->setXY(20,60);
    t_np->setWH(80,20);
    t_np->my_font.setFont(&font12);
    t_np->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setStretch(true);
    t_np->my_font.setColor(0.0,0.0,0.0,1.0);
    t_np->my_font.setText("sup, dude2");
    t_np->my_font.cook();

    ui_textinput *t_ti = new ui_textinput;

    username_window->addChild(t_ti);
    t_ti->setStyle(default_style_a);
    t_ti->setXY(10,140);
    t_ti->setWH(90,25);
    t_ti->setMaxTextLength(10);
    t_ti->setText("input");
    t_ti->my_font.setFont(&font12, FONT_HINT_DYNAMIC);
    t_ti->my_font.setColor(0.0,0.0,0.0,1.0);
    //t_ti->my_font.setHint(FONT_HINT_DYNAMIC);
    t_ti->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_ti->my_font.setStretch(false);
    t_ti->my_font.cook();



    ui_label *lab;
    lab = new ui_label;

    username_window->addChild(lab);
    lab->setXY(20,100);
    lab->setWH(40,40);
    lab->my_font.setFont(&font12);
    lab->my_font.setColor(1.0,1.0,1.0,1.0);
    //lab->my_font.setVertAlign(FONT_ALIGN_CENTER);
    //lab->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    lab->my_font.setStretch(true);
    lab->my_font.setText("sup");
    lab->my_font.cook();

    ui_checkbox *check;
    check = new ui_checkbox;
    username_window->addChild(check);
    check->setStyle(default_np_style);
    check->setXY(80,100);
    check->setWH(15,15);
    check->checkmark.setTex( 128, 128, 32, 00, 19, 19 );
*/

/*
    //username_window->titlebar.my_style.normal.setNP( UI_9P_TL, 128, 128, 11, 1, 3, 5 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_TM, 128, 128, 15, 1, 1, 5 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_TR, 128, 128, 17, 1, 3, 5 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_ML, 128, 128, 11, 7, 3, 1 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_MM, 128, 128, 15, 7, 1, 1 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_MR, 128, 128, 17, 7, 3, 1 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_BL, 128, 128, 11, 9, 3, 6 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_BM, 128, 128, 15, 9, 1, 6 );
    //username_window->titlebar.my_style.normal.setNP( UI_9P_BR, 128, 128, 17, 9, 3, 6 );
    //
    //username_window->titlebar.my_style.hover.setNP( UI_9P_TL, 128, 128, 1, 1, 3, 5 );
*/
