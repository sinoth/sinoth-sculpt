
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
    tex_style list_button_style;
    tex_style separator_style;
    {
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
    //
    list_button_style.normal.setTex(  128, 128, 14, 29, 1, 1 );
    list_button_style.hover.setTex(   128, 128,  4, 29, 1, 1 );
    list_button_style.pressed.setTex( 128, 128, 24, 29, 1, 1 );
    list_button_style.cook();
    //
    separator_style.normal.setTex(  128, 128, 1, 17, 1, 1 );
    separator_style.cook();
    }

    /////////////////////////////////////////////////////////////////
    // username window
    /////////////////////////////////////////////////////////////////
    {
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
    }

    /////////////////////////////////////////////////////////////////
    // main menu
    /////////////////////////////////////////////////////////////////
    {
    ui_window *mainmenu_window = mainGui.addWindow("MainMenu");
    mainmenu_window->setThemeTextureID(theme_texture);
    mainmenu_window->window_style = default_win_style;
    mainmenu_window->titlebar.setStyle(default_win_titlebar_style);
    mainmenu_window->closebutton.setStyle(default_win_closebutton_style);
    mainmenu_window->setCustomKeyCallback(mainmenu_input_keycallback);

    mainmenu_window->setXY(res_cur_x/2-75,res_cur_y/2+115);
    mainmenu_window->setWH(150,230);
    mainmenu_window->titlebar.setWH(150,20);
    //mainmenu_window->titlebar.can_drag_parent = true;
    mainmenu_window->enableFontController();
    mainmenu_window->enableCloseButton();
    mainmenu_window->closebutton.setPayload(mainmenu_close);
    mainmenu_window->enableTitlebar();
    mainmenu_window->titlebar.my_font.setFont(&font12);
    mainmenu_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_window->titlebar.my_font.setStretch(true);
    mainmenu_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    mainmenu_window->titlebar.my_font.setText("Main Menu");
    mainmenu_window->titlebar.my_font.cook();


    ui_button_np *mainmenu_list_button = (ui_button_np*)mainGui.addWidget("main_connect", UI_WIDGET_BUTTON_NP);
    mainmenu_list_button->setStyle(default_np_style);
    mainmenu_list_button->setXY(10,30);
    mainmenu_list_button->setWH(130,40);
    mainmenu_list_button->my_font.setFont(&font12);
    mainmenu_list_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_list_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_list_button->my_font.setStretch(false);
    mainmenu_list_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_list_button->my_font.setText("Connect to Server");
    mainmenu_list_button->my_font.cook();
    mainmenu_list_button->setPayload(mainmenu_connect);

    ui_button_np *mainmenu_archive_button = (ui_button_np*)mainGui.addWidget("main_options", UI_WIDGET_BUTTON_NP);
    mainmenu_archive_button->setStyle(default_np_style);
    mainmenu_archive_button->setXY(10,80);
    mainmenu_archive_button->setWH(130,40);
    mainmenu_archive_button->my_font.setFont(&font12);
    mainmenu_archive_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_archive_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_archive_button->my_font.setStretch(false);
    mainmenu_archive_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_archive_button->my_font.setText("Options");
    mainmenu_archive_button->my_font.cook();
    mainmenu_archive_button->setPayload(mainmenu_options);

    ui_button_np *mainmenu_options_button = (ui_button_np*)mainGui.addWidget("main_help", UI_WIDGET_BUTTON_NP);
    mainmenu_options_button->setStyle(default_np_style);
    mainmenu_options_button->setXY(10,130);
    mainmenu_options_button->setWH(130,40);
    mainmenu_options_button->my_font.setFont(&font12);
    mainmenu_options_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_options_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_options_button->my_font.setStretch(false);
    mainmenu_options_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_options_button->my_font.setText("What is Sculpt?");
    mainmenu_options_button->my_font.cook();
    mainmenu_options_button->setPayload(mainmenu_info);

    ui_button_np *mainmenu_exit_button = (ui_button_np*)mainGui.addWidget("main_quit", UI_WIDGET_BUTTON_NP);
    mainmenu_exit_button->setStyle(default_np_style);
    mainmenu_exit_button->setXY(10,180);
    mainmenu_exit_button->setWH(130,40);
    mainmenu_exit_button->my_font.setFont(&font12);
    mainmenu_exit_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    mainmenu_exit_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    mainmenu_exit_button->my_font.setStretch(false);
    mainmenu_exit_button->my_font.setColor(0.0,0.0,0.0,1.0);
    mainmenu_exit_button->my_font.setText("Quit");
    mainmenu_exit_button->my_font.cook();
    mainmenu_exit_button->setPayload(mainmenu_quit);

    mainmenu_window->setVisible(false);
    mainmenu_window->cook();
    }


    /////////////////////////////////////////////////////////////////
    // connect menu
    /////////////////////////////////////////////////////////////////
    {
    ui_window *connect_window = mainGui.addWindow("ConnectMenu");
    connect_window->setThemeTextureID(theme_texture);
    connect_window->window_style = default_win_style;
    connect_window->titlebar.setStyle(default_win_titlebar_style);
    connect_window->closebutton.setStyle(default_win_closebutton_style);
    connect_window->setCustomKeyCallback(connectmenu_input_keycallback);

    connect_window->setXY(res_cur_x/2-75,res_cur_y/2+90);
    connect_window->setWH(150,180);
    connect_window->titlebar.setWH(150,20);
    //connect_window->titlebar.can_drag_parent = true;
    connect_window->enableFontController();
    connect_window->enableCloseButton();
    connect_window->closebutton.setPayload(connectmenu_close);
    connect_window->enableTitlebar();
    connect_window->titlebar.my_font.setFont(&font12);
    connect_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    connect_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    connect_window->titlebar.my_font.setStretch(true);
    connect_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    connect_window->titlebar.my_font.setText("Connect Menu");
    connect_window->titlebar.my_font.cook();


    ui_button_np *connect_current_button = (ui_button_np*)mainGui.addWidget("connect_current", UI_WIDGET_BUTTON_NP);
    connect_current_button->setStyle(default_np_style);
    connect_current_button->setXY(10,30);
    connect_current_button->setWH(130,40);
    connect_current_button->my_font.setFont(&font12);
    connect_current_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    connect_current_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    connect_current_button->my_font.setStretch(false);
    connect_current_button->my_font.setColor(0.0,0.0,0.0,1.0);
    connect_current_button->my_font.setText("Current Map");
    connect_current_button->my_font.cook();
    connect_current_button->setPayload(connectmenu_current);

    ui_button_np *connect_archive_button = (ui_button_np*)mainGui.addWidget("connect_archive", UI_WIDGET_BUTTON_NP);
    connect_archive_button->setStyle(default_np_style);
    connect_archive_button->setXY(10,80);
    connect_archive_button->setWH(130,40);
    connect_archive_button->my_font.setFont(&font12);
    connect_archive_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    connect_archive_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    connect_archive_button->my_font.setStretch(false);
    connect_archive_button->my_font.setColor(0.0,0.0,0.0,1.0);
    connect_archive_button->my_font.setText("Map Archive");
    connect_archive_button->my_font.cook();
    connect_archive_button->setPayload(connectmenu_archive);

    ui_button_np *connect_back_button = (ui_button_np*)mainGui.addWidget("connect_back", UI_WIDGET_BUTTON_NP);
    connect_back_button->setStyle(default_np_style);
    connect_back_button->setXY(10,130);
    connect_back_button->setWH(130,40);
    connect_back_button->my_font.setFont(&font12);
    connect_back_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    connect_back_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    connect_back_button->my_font.setStretch(false);
    connect_back_button->my_font.setColor(0.0,0.0,0.0,1.0);
    connect_back_button->my_font.setText("Back");
    connect_back_button->my_font.cook();
    connect_back_button->setPayload(connectmenu_close);
    connect_window->setVisible(false);
    connect_window->cook();
    }


    /////////////////////////////////////////////////////////////////
    // confirm quit menu
    /////////////////////////////////////////////////////////////////
    {
    ui_window *confirmquit_window = mainGui.addWindow("ConfirmQuit");
    confirmquit_window->setThemeTextureID(theme_texture);
    confirmquit_window->window_style = default_win_style_notitlebar;

    confirmquit_window->setXY(res_cur_x/2-150,res_cur_y/2+70);
    confirmquit_window->setWH(300,140);
    confirmquit_window->enableFontController();

    ui_label *confirmquit_text = (ui_label*)mainGui.addWidget("quit_text", UI_WIDGET_LABEL);
    confirmquit_text->setXY(10,25);
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
    confirmquit_yes_button->setXY(70,70);
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
    confirmquit_no_button->setXY(160,70);
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
    }

    /////////////////////////////////////////////////////////////////
    // options window
    /////////////////////////////////////////////////////////////////
    {
    ui_window *options_window = mainGui.addWindow("Options");
    options_window->setThemeTextureID(theme_texture);
    options_window->window_style = default_win_style;
    options_window->titlebar.setStyle(default_win_titlebar_style);
    options_window->closebutton.setStyle(default_win_closebutton_style);
    options_window->setCustomKeyCallback(options_input_keycallback);

    options_window->setXY(res_cur_x/2-70,res_cur_y/2+85);
    options_window->setWH(140,170);
    options_window->titlebar.setWH(140,20);
    options_window->titlebar.can_drag_parent = false;
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
    options_window->closebutton.setPayload(options_close);

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


    ui_checkbox *full_checkbox = (ui_checkbox*) mainGui.addWidget("full_checkbox", UI_WIDGET_CHECKBOX);
    full_checkbox->setStyle(default_np_style);
    full_checkbox->setXY(20,61);
    full_checkbox->setWH(15,15);
    full_checkbox->checkmark.setTex( 128, 128, 32, 00, 19, 19 );
    full_checkbox->setPayload(options_full_checkbox);

    ui_label *full_text = (ui_label*)mainGui.addWidget("full_text", UI_WIDGET_LABEL);
    full_text->setXY(45,60);
    full_text->setWH(100,20);
    full_text->my_font.setFont(&font12);
    full_text->my_font.setColor(0.7,0.0,0.0,1.0);
    full_text->my_font.setVertAlign(FONT_ALIGN_CENTER);
    //full_text->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    //full_text->my_font.setStretch(true);
    full_text->my_font.setText("Fullscreen");
    full_text->my_font.cook();
    full_text->setPayload(options_full_checkbox_text);


    ui_button_np *options_username_button = (ui_button_np*)mainGui.addWidget("options_username", UI_WIDGET_BUTTON_NP);
    options_username_button->setStyle(default_np_style);
    options_username_button->setXY(10,90); options_username_button->setWH(120,30);
    options_username_button->my_font.setFont(&font12);
    options_username_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    options_username_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    options_username_button->my_font.setStretch(false);
    options_username_button->my_font.setColor(0.0,0.0,0.0,1.0);
    options_username_button->my_font.setText("Edit Username");
    options_username_button->my_font.cook();
    options_username_button->setPayload(options_username);

    ui_button_np *options_cancel_button = (ui_button_np*)mainGui.addWidget("options_cancel", UI_WIDGET_BUTTON_NP);
    options_cancel_button->setStyle(default_np_style);
    options_cancel_button->setXY(10,130); options_cancel_button->setWH(55,30);
    options_cancel_button->my_font.setFont(&font12);
    options_cancel_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    options_cancel_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    options_cancel_button->my_font.setStretch(false);
    options_cancel_button->my_font.setColor(0.0,0.0,0.0,1.0);
    options_cancel_button->my_font.setText("Back");
    options_cancel_button->my_font.cook();
    options_cancel_button->setPayload(options_close);

    ui_button_np *options_apply_button = (ui_button_np*)mainGui.addWidget("options_apply", UI_WIDGET_BUTTON_NP);
    options_apply_button->setStyle(default_np_style);
    options_apply_button->setXY(75,130); options_apply_button->setWH(55,30);
    options_apply_button->my_font.setFont(&font12);
    options_apply_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    options_apply_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    options_apply_button->my_font.setStretch(false);
    options_apply_button->my_font.setColor(0.0,0.0,0.0,1.0);
    options_apply_button->my_font.setText("Apply");
    options_apply_button->my_font.cook();
    options_apply_button->setPayload(options_res_apply);

    options_window->cook();
    options_window->setVisible(false);
    }

    /////////////////////////////////////////////////////////////////
    // server list menu
    /////////////////////////////////////////////////////////////////
    {
    ui_window *serverlist_window = mainGui.addWindow("ServerList");
    serverlist_window->setThemeTextureID(theme_texture);
    serverlist_window->setCustomKeyCallback(serverlist_input_keycallback);
    serverlist_window->window_style = default_win_style_notitlebar;

    serverlist_window->setXY(res_cur_x/2-250,res_cur_y/2+110);
    serverlist_window->setWH(500,220);
    serverlist_window->enableFontController();

    ui_label *serverlabel_name = (ui_label*)mainGui.addWidget("serverlabel_name", UI_WIDGET_LABEL);
    serverlabel_name->setXY(15,10); serverlabel_name->setWH(240,20);
    serverlabel_name->my_font.setFont(&font12);
    serverlabel_name->my_font.setColor(0.2,0.2,0.2,1.0);
    serverlabel_name->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlabel_name->my_font.setText("Map Name:");
    serverlabel_name->my_font.cook();


    ui_label *serverlabel_complete = (ui_label*)mainGui.addWidget("serverlabel_size", UI_WIDGET_LABEL);
    serverlabel_complete->setXY(250,10); serverlabel_complete->setWH(200,20);
    serverlabel_complete->my_font.setFont(&font12);
    serverlabel_complete->my_font.setColor(0.2,0.2,0.2,1.0);
    serverlabel_complete->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlabel_complete->my_font.setText("Size:");
    serverlabel_complete->my_font.cook();

    ui_label *serverlabel_time = (ui_label*)mainGui.addWidget("serverlabel_completed", UI_WIDGET_LABEL);
    serverlabel_time->setXY(330,10); serverlabel_time->setWH(200,20);
    serverlabel_time->my_font.setFont(&font12);
    serverlabel_time->my_font.setColor(0.2,0.2,0.2,1.0);
    serverlabel_time->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlabel_time->my_font.setText("Complete Date:");
    serverlabel_time->my_font.cook();

    ui_button *separator_button = (ui_button*)mainGui.addWidget("list_separator", UI_WIDGET_BUTTON);
    separator_button->setStyle(separator_style);
    separator_button->setXY(10,30); separator_button->setWH(480,1);

    ////////////////

    ui_button *server1_button = (ui_button*)mainGui.addWidget("serverbutton_1", UI_WIDGET_BUTTON);
    server1_button->setStyle(list_button_style);
    server1_button->setXY(10,40); server1_button->setWH(480,20);
    server1_button->setPayload(serverbutton_one);
    ui_button *server2_button = (ui_button*)mainGui.addWidget("serverbutton_2", UI_WIDGET_BUTTON);
    server2_button->setStyle(list_button_style);
    server2_button->setXY(10,60); server2_button->setWH(480,20);
    //server2_button->setPayload(options_res_right);
    ui_button *server3_button = (ui_button*)mainGui.addWidget("serverbutton_3", UI_WIDGET_BUTTON);
    server3_button->setStyle(list_button_style);
    server3_button->setXY(10,80); server3_button->setWH(480,20);
    //server1_button->setPayload(options_res_right);
    ui_button *server4_button = (ui_button*)mainGui.addWidget("serverbutton_4", UI_WIDGET_BUTTON);
    server4_button->setStyle(list_button_style);
    server4_button->setXY(10,100); server4_button->setWH(480,20);
    //server1_button->setPayload(options_res_right);
    ui_button *server5_button = (ui_button*)mainGui.addWidget("serverbutton_5", UI_WIDGET_BUTTON);
    server5_button->setStyle(list_button_style);
    server5_button->setXY(10,120); server5_button->setWH(480,20);
    //server1_button->setPayload(options_res_right);

    for (int i=0; i < 5; ++i ) {
        char widget_name[30];
        sprintf(widget_name, "server%d_name", i);
        ui_label *server1_name = (ui_label*)mainGui.addWidget(widget_name, UI_WIDGET_LABEL);
        server1_name->setXY(15,44+i*20); server1_name->setWH(240,20);
        server1_name->my_font.setFont(&font12, FONT_HINT_DYNAMIC); server1_name->my_font.setColor(0.2,0.2,0.2,1.0);
        server1_name->my_font.setText("Server Name Here"); server1_name->my_font.cook();
        sprintf(widget_name, "server%d_size", i);
        ui_label *server1_complete = (ui_label*)mainGui.addWidget(widget_name, UI_WIDGET_LABEL);
        server1_complete->setXY(230,44+i*20); server1_complete->setWH(75,20);
        server1_complete->my_font.setHorizAlign(FONT_ALIGN_CENTER);
        server1_complete->my_font.setFont(&font12, FONT_HINT_DYNAMIC); server1_complete->my_font.setColor(0.2,0.2,0.2,1.0);
        server1_complete->my_font.setText("15 * 15 * 15"); server1_complete->my_font.cook();
        sprintf(widget_name, "server%d_date", i);
        ui_label *server1_available = (ui_label*)mainGui.addWidget(widget_name, UI_WIDGET_LABEL);
        server1_available->setXY(330,44+i*20); server1_available->setWH(160,20);
        server1_available->my_font.setHorizAlign(FONT_ALIGN_LEFT);
        server1_available->my_font.setFont(&font12, FONT_HINT_DYNAMIC); server1_available->my_font.setColor(0.2,0.2,0.2,1.0);
        server1_available->my_font.setText("2010-06-07 15:12:32"); server1_available->my_font.cook();
    }

    ui_button *separator_button2 = (ui_button*)mainGui.addWidget("list_separator2", UI_WIDGET_BUTTON);
    separator_button2->setStyle(separator_style);
    separator_button2->setXY(10,150);
    separator_button2->setWH(370,1);

    ui_label *serverlabel_pages = (ui_label*)mainGui.addWidget("serverlabel_pages", UI_WIDGET_LABEL);
    serverlabel_pages->setXY(390,140); serverlabel_pages->setWH(70,20);
    serverlabel_pages->my_font.setFont(&font12);
    serverlabel_pages->my_font.setColor(0.2,0.2,0.2,1.0);
    serverlabel_pages->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlabel_pages->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    serverlabel_pages->my_font.setText("Page 1/2");
    serverlabel_pages->my_font.cook();

    ui_button *separator_button3 = (ui_button*)mainGui.addWidget("list_separator3", UI_WIDGET_BUTTON);
    separator_button3->setStyle(separator_style);
    separator_button3->setXY(470,150);
    separator_button3->setWH(20,1);

    /////////////////

    ui_button_np *serverlist_prev_button = (ui_button_np*)mainGui.addWidget("list_prev", UI_WIDGET_BUTTON_NP);
    serverlist_prev_button->setStyle(default_np_style);
    serverlist_prev_button->setXY(255,165);
    serverlist_prev_button->setWH(70,40);
    serverlist_prev_button->my_font.setFont(&font12);
    serverlist_prev_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlist_prev_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    serverlist_prev_button->my_font.setStretch(false);
    serverlist_prev_button->my_font.setColor(0.0,0.0,0.0,1.0);
    serverlist_prev_button->my_font.setText("<< Prev");
    serverlist_prev_button->my_font.cook();
    serverlist_prev_button->setPayload(serverlist_prev);

    ui_button_np *serverlist_next_button = (ui_button_np*)mainGui.addWidget("list_next", UI_WIDGET_BUTTON_NP);
    serverlist_next_button->setStyle(default_np_style);
    serverlist_next_button->setXY(335,165);
    serverlist_next_button->setWH(70,40);
    serverlist_next_button->my_font.setFont(&font12);
    serverlist_next_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlist_next_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    serverlist_next_button->my_font.setStretch(false);
    serverlist_next_button->my_font.setColor(0.0,0.0,0.0,1.0);
    serverlist_next_button->my_font.setText("Next >>");
    serverlist_next_button->my_font.cook();
    serverlist_next_button->setPayload(serverlist_next);

    ui_button_np *serverlist_no_button = (ui_button_np*)mainGui.addWidget("list_close", UI_WIDGET_BUTTON_NP);
    serverlist_no_button->setStyle(default_np_style);
    serverlist_no_button->setXY(425,165);
    serverlist_no_button->setWH(60,40);
    serverlist_no_button->my_font.setFont(&font12);
    serverlist_no_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlist_no_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    serverlist_no_button->my_font.setStretch(false);
    serverlist_no_button->my_font.setColor(0.0,0.0,0.0,1.0);
    serverlist_no_button->my_font.setText("Close");
    serverlist_no_button->my_font.cook();
    serverlist_no_button->setPayload(serverlist_close);

    ui_label *serverlabel_status = (ui_label*)mainGui.addWidget("serverlabel_status", UI_WIDGET_LABEL);
    serverlabel_status->setXY(10,170);
    serverlabel_status->setWH(200,20);
    serverlabel_status->my_font.setFont(&font12);
    serverlabel_status->my_font.setColor(0.2,0.2,0.2,1.0);
    //serverlabel_status->my_font.setVertAlign(FONT_ALIGN_CENTER);
    serverlabel_status->my_font.setText("Communication status:");
    serverlabel_status->my_font.cook();

    ui_label *comm_status = (ui_label*)mainGui.addWidget("comm_status", UI_WIDGET_LABEL);
    comm_status->setXY(10,190);
    comm_status->setWH(400,20);
    comm_status->my_font.setFont(&font12, FONT_HINT_DYNAMIC);
    comm_status->my_font.setColor(0.2,0.2,0.2,1.0);
    //comm_status->my_font.setVertAlign(FONT_ALIGN_CENTER);
    comm_status->my_font.setText("No connection");
    comm_status->my_font.cook();

    serverlist_window->cook();
    serverlist_window->setVisible(false);
    }


    /////////////////////////////////////////////////////////////////
    // current map menu
    /////////////////////////////////////////////////////////////////
    {
    ui_window *currentmap_window = mainGui.addWindow("CurrentMapMenu");
    currentmap_window->setThemeTextureID(theme_texture);
    currentmap_window->setCustomKeyCallback(currentmap_input_keycallback);
    currentmap_window->window_style = default_win_style;
    currentmap_window->titlebar.setStyle(default_win_titlebar_style);
    currentmap_window->closebutton.setStyle(default_win_closebutton_style);

    currentmap_window->setXY(res_cur_x/2-250,res_cur_y/2+110);
    currentmap_window->setWH(500,220);
    currentmap_window->titlebar.setWH(500,20);
    currentmap_window->titlebar.can_drag_parent = false;
    currentmap_window->enableFontController();
    currentmap_window->enableCloseButton();
    currentmap_window->enableTitlebar();
    currentmap_window->titlebar.my_font.setFont(&font12);
    currentmap_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    currentmap_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    currentmap_window->titlebar.my_font.setStretch(true);
    currentmap_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    currentmap_window->titlebar.my_font.setText("Current Map");
    currentmap_window->titlebar.my_font.cook();
    currentmap_window->closebutton.setPayload(currentmapmenu_close);

    ui_label *currentmaplabel_name = (ui_label*)mainGui.addWidget("currentmaplabel_name", UI_WIDGET_LABEL);
    currentmaplabel_name->setXY(15,30); currentmaplabel_name->setWH(470,30);
    currentmaplabel_name->my_font.setFont(&font18);
    currentmaplabel_name->my_font.setColor(1.0,1.0,1.0,1.0);
    currentmaplabel_name->my_font.setText("Map Name:");
    currentmaplabel_name->my_font.cook();

    ui_label *currentmaplabel_completion = (ui_label*)mainGui.addWidget("currentmaplabel_completion", UI_WIDGET_LABEL);
    currentmaplabel_completion->setXY(15,70); currentmaplabel_completion->setWH(240,20);
    currentmaplabel_completion->my_font.setFont(&font18);
    currentmaplabel_completion->my_font.setColor(1.0,1.0,1.0,1.0);
    currentmaplabel_completion->my_font.setText("Completion:");
    currentmaplabel_completion->my_font.cook();

    ui_label *currentmaplabel_available = (ui_label*)mainGui.addWidget("currentmaplabel_available", UI_WIDGET_LABEL);
    currentmaplabel_available->setXY(15,110); currentmaplabel_available->setWH(240,20);
    currentmaplabel_available->my_font.setFont(&font18);
    currentmaplabel_available->my_font.setColor(1.0,1.0,1.0,1.0);
    currentmaplabel_available->my_font.setText("Available to you:");
    currentmaplabel_available->my_font.cook();

    ui_label *cmap_name = (ui_label*)mainGui.addWidget("cmap_name", UI_WIDGET_LABEL);
    cmap_name->setXY(130,30); cmap_name->setWH(355,30);
    cmap_name->my_font.setFont(&font18, FONT_HINT_DYNAMIC); cmap_name->my_font.setColor(0.2,0.2,0.2,1.0);
    cmap_name->my_font.setText(" "); cmap_name->my_font.cook();

    ui_label *cmap_complete = (ui_label*)mainGui.addWidget("cmap_complete", UI_WIDGET_LABEL);
    cmap_complete->setXY(140,70); cmap_complete->setWH(345,30);
    cmap_complete->my_font.setFont(&font18, FONT_HINT_DYNAMIC); cmap_complete->my_font.setColor(0.2,0.2,0.2,1.0);
    cmap_complete->my_font.setText(" "); cmap_complete->my_font.cook();

    ui_label *cmap_available = (ui_label*)mainGui.addWidget("cmap_available", UI_WIDGET_LABEL);
    cmap_available->setXY(180,110); cmap_available->setWH(305,30);
    cmap_available->my_font.setFont(&font18, FONT_HINT_DYNAMIC); cmap_available->my_font.setColor(0.2,0.2,0.2,1.0);
    cmap_available->my_font.setText(" "); cmap_available->my_font.cook();

    ui_button_np *request_piece_button = (ui_button_np*)mainGui.addWidget("current_request_button", UI_WIDGET_BUTTON_NP);
    request_piece_button->setStyle(default_np_style);
    request_piece_button->setXY(370,180);
    request_piece_button->setWH(120,30);
    request_piece_button->my_font.setFont(&font12);
    request_piece_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    request_piece_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    request_piece_button->my_font.setStretch(false);
    request_piece_button->my_font.setColor(0.0,0.0,0.0,1.0);
    request_piece_button->my_font.setText("Request Piece");
    request_piece_button->my_font.cook();
    request_piece_button->setPayload(currentmapmenu_request);

    currentmap_window->cook();
    currentmap_window->setVisible(false);
    }


    /////////////////////////////////////////////////////////////////
    // current map submit menu
    /////////////////////////////////////////////////////////////////
    {
    ui_window *currentmapsubmit_window = mainGui.addWindow("CurrentMapSubmit");
    currentmapsubmit_window->setThemeTextureID(theme_texture);
    currentmapsubmit_window->window_style = default_win_style;
    currentmapsubmit_window->titlebar.setStyle(default_win_titlebar_style);
    currentmapsubmit_window->closebutton.setStyle(default_win_closebutton_style);
    currentmapsubmit_window->setCustomKeyCallback(currentmapsubmit_input_keycallback);

    currentmapsubmit_window->setXY(res_cur_x/2-75,res_cur_y/2+90);
    currentmapsubmit_window->setWH(150,180);
    currentmapsubmit_window->titlebar.setWH(150,20);
    //currentmapsubmit_window->titlebar.can_drag_parent = true;
    currentmapsubmit_window->enableFontController();
    currentmapsubmit_window->enableCloseButton();
    currentmapsubmit_window->closebutton.setPayload(currentmapsubmit_close);
    currentmapsubmit_window->enableTitlebar();
    currentmapsubmit_window->titlebar.my_font.setFont(&font12);
    currentmapsubmit_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_window->titlebar.my_font.setStretch(true);
    currentmapsubmit_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    currentmapsubmit_window->titlebar.my_font.setText("Current Map");
    currentmapsubmit_window->titlebar.my_font.cook();


    ui_button_np *currentmapsubmit_submit_button = (ui_button_np*)mainGui.addWidget("currentmap_submit", UI_WIDGET_BUTTON_NP);
    currentmapsubmit_submit_button->setStyle(default_np_style);
    currentmapsubmit_submit_button->setXY(10,30);
    currentmapsubmit_submit_button->setWH(130,40);
    currentmapsubmit_submit_button->my_font.setFont(&font12);
    currentmapsubmit_submit_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_submit_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_submit_button->my_font.setStretch(false);
    currentmapsubmit_submit_button->my_font.setColor(0.0,0.0,0.0,1.0);
    currentmapsubmit_submit_button->my_font.setText("Submit to Server");
    currentmapsubmit_submit_button->my_font.cook();
    currentmapsubmit_submit_button->setPayload(currentmapsubmit_submit);

    ui_button_np *currentmapsubmit_discard_button = (ui_button_np*)mainGui.addWidget("currentmap_discard", UI_WIDGET_BUTTON_NP);
    currentmapsubmit_discard_button->setStyle(default_np_style);
    currentmapsubmit_discard_button->setXY(10,80);
    currentmapsubmit_discard_button->setWH(130,40);
    currentmapsubmit_discard_button->my_font.setFont(&font12);
    currentmapsubmit_discard_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_discard_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_discard_button->my_font.setStretch(false);
    currentmapsubmit_discard_button->my_font.setColor(0.0,0.0,0.0,1.0);
    currentmapsubmit_discard_button->my_font.setText("Discard Piece");
    currentmapsubmit_discard_button->my_font.cook();
    currentmapsubmit_discard_button->setPayload(currentmapsubmit_discard);

    ui_button_np *currentmapsubmit_back_button = (ui_button_np*)mainGui.addWidget("currentmap_back", UI_WIDGET_BUTTON_NP);
    currentmapsubmit_back_button->setStyle(default_np_style);
    currentmapsubmit_back_button->setXY(10,130);
    currentmapsubmit_back_button->setWH(130,40);
    currentmapsubmit_back_button->my_font.setFont(&font12);
    currentmapsubmit_back_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_back_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    currentmapsubmit_back_button->my_font.setStretch(false);
    currentmapsubmit_back_button->my_font.setColor(0.0,0.0,0.0,1.0);
    currentmapsubmit_back_button->my_font.setText("Back to Editor");
    currentmapsubmit_back_button->my_font.cook();
    currentmapsubmit_back_button->setPayload(currentmapsubmit_close);

    currentmapsubmit_window->setVisible(false);
    currentmapsubmit_window->cook();
    }

    /////////////////////////////////////////////////////////////////
    // info window
    /////////////////////////////////////////////////////////////////
    {
    ui_window *info_window = mainGui.addWindow("Info");
    info_window->setThemeTextureID(theme_texture);
    info_window->window_style = default_win_style;
    info_window->titlebar.setStyle(default_win_titlebar_style);
    info_window->closebutton.setStyle(default_win_closebutton_style);
    info_window->setCustomKeyCallback(options_input_keycallback);

    info_window->setXY(res_cur_x/2-250,res_cur_y/2+200);
    info_window->setWH(500,400);
    info_window->titlebar.setWH(500,20);
    info_window->titlebar.can_drag_parent = false;
    info_window->enableFontController();
    info_window->enableCloseButton();
    info_window->enableTitlebar();
    info_window->titlebar.my_font.setFont(&font12);
    info_window->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    info_window->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    info_window->titlebar.my_font.setStretch(true);
    info_window->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    info_window->titlebar.my_font.setText("What is Sculpt?");
    info_window->titlebar.my_font.cook();
    info_window->closebutton.setPayload(infowindow_close);

    ui_button_np *info_close_button = (ui_button_np*)mainGui.addWidget("info_close", UI_WIDGET_BUTTON_NP);
    info_close_button->setStyle(default_np_style);
    info_close_button->setXY(250-55/2,400-40); info_close_button->setWH(55,30);
    info_close_button->my_font.setFont(&font12);
    info_close_button->my_font.setVertAlign(FONT_ALIGN_CENTER);
    info_close_button->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    info_close_button->my_font.setStretch(false);
    info_close_button->my_font.setColor(0.0,0.0,0.0,1.0);
    info_close_button->my_font.setText("Back");
    info_close_button->my_font.cook();
    info_close_button->setPayload(infowindow_close);

    ui_label *infomenu_text = (ui_label*)mainGui.addWidget("info_text", UI_WIDGET_LABEL);
    infomenu_text->setXY(10,25);
    infomenu_text->setWH(480,300);
    infomenu_text->my_font.setFont(&font18);
    infomenu_text->my_font.setColor(1.0,1.0,1.0,1.0);
    infomenu_text->my_font.setVertAlign(FONT_ALIGN_TOP);
    infomenu_text->my_font.setHorizAlign(FONT_ALIGN_LEFT);
    infomenu_text->my_font.setStretch(false);
    infomenu_text->my_font.setText("Are you sure you want to quit?\nYou will lose your current work.\nThis is a really long sentence that\nshould stretch further than the box.");
    infomenu_text->my_font.cook();

    info_window->cook();
    info_window->setVisible(false);
    }

    //if we haven't loaded a username, show the box
    if ( !loaded_username ) {
        mainGui.bringToFront( mainGui.getWindow("Username") );
        mainGui.getWidget("username_input")->setActive(true);
    } else { //else, just continue to main menu
        mainGui.getWindow("Username")->setVisible(false);
    }

}


void scene::reInit_ui() {

    mainGui.getWindow("MainMenu")->setThemeTextureID(theme_texture);
    mainGui.getWindow("Username")->setThemeTextureID(theme_texture);
    mainGui.getWindow("ConfirmQuit")->setThemeTextureID(theme_texture);
    mainGui.getWindow("Options")->setThemeTextureID(theme_texture);

    mainGui.restoreControllers();

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
