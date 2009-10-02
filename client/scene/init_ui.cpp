
#include "scene.h"


void scene::init_ui() {



    //yep
    ui_window *username_window;
    np_style default_np_style;
    np_style default_style_a;

    username_window = mainGui.addWindow("Username");

    username_window->setThemeTextureID(theme_texture);

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
    username_window->titlebar.my_style.normal.setNP( UI_9P_TL, 128, 128, 1, 1, 3, 5 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_TM, 128, 128, 5, 1, 1, 5 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_TR, 128, 128, 7, 1, 3, 5 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_ML, 128, 128, 1, 7, 3, 1 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_MM, 128, 128, 5, 7, 1, 1 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_MR, 128, 128, 7, 7, 3, 1 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_BL, 128, 128, 1, 9, 3, 6 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_BM, 128, 128, 5, 9, 1, 6 );
    username_window->titlebar.my_style.normal.setNP( UI_9P_BR, 128, 128, 7, 9, 3, 6 );
    username_window->titlebar.my_style.cook();
    //
    username_window->window_style.hover.setNP( UI_9P_TL, 128, 128, 1, 17, 0, 0 );
    username_window->window_style.hover.setNP( UI_9P_TM, 128, 128, 4, 17, 0, 0 );
    username_window->window_style.hover.setNP( UI_9P_TR, 128, 128, 6, 17, 0, 0 );
    username_window->window_style.hover.setNP( UI_9P_ML, 128, 128, 1, 20, 2, 1 );
    username_window->window_style.hover.setNP( UI_9P_MM, 128, 128, 4, 20, 1, 1 );
    username_window->window_style.hover.setNP( UI_9P_MR, 128, 128, 6, 20, 2, 1 );
    username_window->window_style.hover.setNP( UI_9P_BL, 128, 128, 1, 22, 2, 2 );
    username_window->window_style.hover.setNP( UI_9P_BM, 128, 128, 4, 22, 1, 2 );
    username_window->window_style.hover.setNP( UI_9P_BR, 128, 128, 6, 22, 2, 2 );
    //
    username_window->window_style.normal.setNP( UI_9P_TL, 128, 128, 11, 17, 0, 0 );
    username_window->window_style.normal.setNP( UI_9P_TM, 128, 128, 14, 17, 0, 0 );
    username_window->window_style.normal.setNP( UI_9P_TR, 128, 128, 16, 17, 0, 0 );
    username_window->window_style.normal.setNP( UI_9P_ML, 128, 128, 11, 20, 2, 1 );
    username_window->window_style.normal.setNP( UI_9P_MM, 128, 128, 14, 20, 1, 1 );
    username_window->window_style.normal.setNP( UI_9P_MR, 128, 128, 16, 20, 2, 1 );
    username_window->window_style.normal.setNP( UI_9P_BL, 128, 128, 11, 22, 2, 2 );
    username_window->window_style.normal.setNP( UI_9P_BM, 128, 128, 14, 22, 1, 2 );
    username_window->window_style.normal.setNP( UI_9P_BR, 128, 128, 16, 22, 2, 2 );
    username_window->window_style.cook();
    //
    username_window->closebutton.my_style.normal.setTex(  128, 128, 32, 40, 19, 19 );
    username_window->closebutton.my_style.hover.setTex(   128, 128, 32, 20, 19, 19 );
    username_window->closebutton.my_style.pressed.setTex( 128, 128, 32, 00, 19, 19 );
    username_window->closebutton.my_style.cook();
    //
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

    ui_button_np *t_np = (ui_button_np*)mainGui.addWidget("username_ok", UI_WIDGET_BUTTON_NP);
    //username_window->addChild(t_np, "username_ok_button");
    t_np->setStyle(default_np_style);
    t_np->setXY(155,30);
    t_np->setWH(35,30);
    t_np->my_font.setFont(&font12);
    t_np->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setStretch(false);
    t_np->my_font.setColor(0.0,0.0,0.0,1.0);
    t_np->my_font.setText("OK!");
    t_np->my_font.cook();


    ui_textinput *t_ti = (ui_textinput*)mainGui.addWidget("username_input", UI_WIDGET_TEXTINPUT);
    //username_window->addChild(t_ti,"username_input");
    t_ti->setStyle(default_style_a);
    t_ti->setXY(10,30);
    t_ti->setWH(140,30);
    t_ti->setMaxTextLength(10);
    t_ti->setText("input");
    t_ti->my_font.setFont(&font12, FONT_HINT_DYNAMIC);
    t_ti->my_font.setColor(0.0,0.0,0.0,1.0);
    t_ti->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_ti->my_font.setStretch(false);
    t_ti->my_font.cook();




    username_window->cook();

    mainGui.bringToFront( mainGui.getWindow("Username") );
    mainGui.getWidget("username_input")->setActive( true);

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