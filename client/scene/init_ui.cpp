
#include "scene.h"


void scene::init_ui() {



    //yep
    ui_window *test_win;
    np_style t_np_style;
    np_style t_np_style_a;

    test_win = mainGui.addWindow("lol");

    test_win->titlebar.my_style.normal.setNP( UI_9P_TL, 128, 128, 11, 1, 3, 5 );
    test_win->titlebar.my_style.normal.setNP( UI_9P_TM, 128, 128, 15, 1, 1, 5 );
    test_win->titlebar.my_style.normal.setNP( UI_9P_TR, 128, 128, 17, 1, 3, 5 );

    test_win->titlebar.my_style.normal.setNP( UI_9P_ML, 128, 128, 11, 7, 3, 1 );
    test_win->titlebar.my_style.normal.setNP( UI_9P_MM, 128, 128, 15, 7, 1, 1 );
    test_win->titlebar.my_style.normal.setNP( UI_9P_MR, 128, 128, 17, 7, 3, 1 );

    test_win->titlebar.my_style.normal.setNP( UI_9P_BL, 128, 128, 11, 9, 3, 6 );
    test_win->titlebar.my_style.normal.setNP( UI_9P_BM, 128, 128, 15, 9, 1, 6 );
    test_win->titlebar.my_style.normal.setNP( UI_9P_BR, 128, 128, 17, 9, 3, 6 );
    //
    //
    test_win->titlebar.my_style.hover.setNP( UI_9P_TL, 128, 128, 1, 1, 3, 5 );
    test_win->titlebar.my_style.hover.setNP( UI_9P_TM, 128, 128, 5, 1, 1, 5 );
    test_win->titlebar.my_style.hover.setNP( UI_9P_TR, 128, 128, 7, 1, 3, 5 );

    test_win->titlebar.my_style.hover.setNP( UI_9P_ML, 128, 128, 1, 7, 3, 1 );
    test_win->titlebar.my_style.hover.setNP( UI_9P_MM, 128, 128, 5, 7, 1, 1 );
    test_win->titlebar.my_style.hover.setNP( UI_9P_MR, 128, 128, 7, 7, 3, 1 );

    test_win->titlebar.my_style.hover.setNP( UI_9P_BL, 128, 128, 1, 9, 3, 6 );
    test_win->titlebar.my_style.hover.setNP( UI_9P_BM, 128, 128, 5, 9, 1, 6 );
    test_win->titlebar.my_style.hover.setNP( UI_9P_BR, 128, 128, 7, 9, 3, 6 );
    test_win->titlebar.my_style.cook();
    //
    //
    test_win->window_style.hover.setNP( UI_9P_TL, 128, 128, 1, 17, 0, 0 );
    test_win->window_style.hover.setNP( UI_9P_TM, 128, 128, 4, 17, 0, 0 );
    test_win->window_style.hover.setNP( UI_9P_TR, 128, 128, 6, 17, 0, 0 );

    test_win->window_style.hover.setNP( UI_9P_ML, 128, 128, 1, 20, 2, 1 );
    test_win->window_style.hover.setNP( UI_9P_MM, 128, 128, 4, 20, 1, 1 );
    test_win->window_style.hover.setNP( UI_9P_MR, 128, 128, 6, 20, 2, 1 );

    test_win->window_style.hover.setNP( UI_9P_BL, 128, 128, 1, 22, 2, 2 );
    test_win->window_style.hover.setNP( UI_9P_BM, 128, 128, 4, 22, 1, 2 );
    test_win->window_style.hover.setNP( UI_9P_BR, 128, 128, 6, 22, 2, 2 );
    //
    //
    test_win->window_style.normal.setNP( UI_9P_TL, 128, 128, 11, 17, 0, 0 );
    test_win->window_style.normal.setNP( UI_9P_TM, 128, 128, 14, 17, 0, 0 );
    test_win->window_style.normal.setNP( UI_9P_TR, 128, 128, 16, 17, 0, 0 );

    test_win->window_style.normal.setNP( UI_9P_ML, 128, 128, 11, 20, 2, 1 );
    test_win->window_style.normal.setNP( UI_9P_MM, 128, 128, 14, 20, 1, 1 );
    test_win->window_style.normal.setNP( UI_9P_MR, 128, 128, 16, 20, 2, 1 );

    test_win->window_style.normal.setNP( UI_9P_BL, 128, 128, 11, 22, 2, 2 );
    test_win->window_style.normal.setNP( UI_9P_BM, 128, 128, 14, 22, 1, 2 );
    test_win->window_style.normal.setNP( UI_9P_BR, 128, 128, 16, 22, 2, 2 );
    test_win->window_style.cook();
    //
    //
    test_win->closebutton.my_style.normal.setTex(  128, 128, 32, 40, 19, 19 );
    test_win->closebutton.my_style.hover.setTex(   128, 128, 32, 20, 19, 19 );
    test_win->closebutton.my_style.pressed.setTex( 128, 128, 32, 00, 19, 19 );
    test_win->closebutton.my_style.cook();
    //
    //
    t_np_style.hover.setNP( UI_9P_TL, 128, 128, 1, 17, 2, 2 );
    t_np_style.hover.setNP( UI_9P_TM, 128, 128, 4, 17, 1, 2 );
    t_np_style.hover.setNP( UI_9P_TR, 128, 128, 6, 17, 2, 2 );

    t_np_style.hover.setNP( UI_9P_ML, 128, 128, 1, 20, 2, 1 );
    t_np_style.hover.setNP( UI_9P_MM, 128, 128, 4, 20, 1, 1 );
    t_np_style.hover.setNP( UI_9P_MR, 128, 128, 6, 20, 2, 1 );

    t_np_style.hover.setNP( UI_9P_BL, 128, 128, 1, 22, 2, 2 );
    t_np_style.hover.setNP( UI_9P_BM, 128, 128, 4, 22, 1, 2 );
    t_np_style.hover.setNP( UI_9P_BR, 128, 128, 6, 22, 2, 2 );
    //
    //
    t_np_style.normal.setNP( UI_9P_TL, 128, 128, 11, 26, 2, 2 );
    t_np_style.normal.setNP( UI_9P_TM, 128, 128, 14, 26, 1, 2 );
    t_np_style.normal.setNP( UI_9P_TR, 128, 128, 16, 26, 2, 2 );

    t_np_style.normal.setNP( UI_9P_ML, 128, 128, 11, 29, 2, 1 );
    t_np_style.normal.setNP( UI_9P_MM, 128, 128, 14, 29, 1, 1 );
    t_np_style.normal.setNP( UI_9P_MR, 128, 128, 16, 29, 2, 1 );

    t_np_style.normal.setNP( UI_9P_BL, 128, 128, 11, 31, 2, 2 );
    t_np_style.normal.setNP( UI_9P_BM, 128, 128, 14, 31, 1, 2 );
    t_np_style.normal.setNP( UI_9P_BR, 128, 128, 16, 31, 2, 2 );
    //
    //
    t_np_style.pressed.setNP( UI_9P_TL, 128, 128, 21, 26, 2, 2 );
    t_np_style.pressed.setNP( UI_9P_TM, 128, 128, 24, 26, 1, 2 );
    t_np_style.pressed.setNP( UI_9P_TR, 128, 128, 26, 26, 2, 2 );

    t_np_style.pressed.setNP( UI_9P_ML, 128, 128, 21, 29, 2, 1 );
    t_np_style.pressed.setNP( UI_9P_MM, 128, 128, 24, 29, 1, 1 );
    t_np_style.pressed.setNP( UI_9P_MR, 128, 128, 26, 29, 2, 1 );

    t_np_style.pressed.setNP( UI_9P_BL, 128, 128, 21, 31, 2, 2 );
    t_np_style.pressed.setNP( UI_9P_BM, 128, 128, 24, 31, 1, 2 );
    t_np_style.pressed.setNP( UI_9P_BR, 128, 128, 26, 31, 2, 2 );
    t_np_style.cook();

    t_np_style_a = t_np_style;

    t_np_style_a.active.setNP( UI_9P_TL, 128, 128,  1, 35, 2, 2 );
    t_np_style_a.active.setNP( UI_9P_TM, 128, 128,  4, 35, 1, 2 );
    t_np_style_a.active.setNP( UI_9P_TR, 128, 128,  6, 35, 2, 2 );

    t_np_style_a.active.setNP( UI_9P_ML, 128, 128,  1, 38, 2, 1 );
    t_np_style_a.active.setNP( UI_9P_MM, 128, 128,  4, 38, 1, 1 );
    t_np_style_a.active.setNP( UI_9P_MR, 128, 128,  6, 38, 2, 1 );

    t_np_style_a.active.setNP( UI_9P_BL, 128, 128,  1, 40, 2, 2 );
    t_np_style_a.active.setNP( UI_9P_BM, 128, 128,  4, 40, 1, 2 );
    t_np_style_a.active.setNP( UI_9P_BR, 128, 128,  6, 40, 2, 2 );
    t_np_style_a.cook();
    t_np_style_a.font_x = 4;

    test_win->setXY(400,300);
    test_win->setWH(150,250);
    test_win->titlebar.setWH(150,20);
    test_win->titlebar.can_drag_parent = true;
    test_win->enableFontController();
    test_win->enableCloseButton();
    test_win->enableTitlebar();
    test_win->titlebar.my_font.setFont(&font18gui);
    test_win->titlebar.my_font.setVertAlign(FONT_ALIGN_CENTER);
    test_win->titlebar.my_font.setHorizAlign(FONT_ALIGN_CENTER);
    test_win->titlebar.my_font.setStretch(true);
    test_win->titlebar.my_font.setColor(1.0,1.0,1.0,1.0);
    test_win->titlebar.my_font.setText("Graphic Options");
    test_win->titlebar.my_font.cook();

    test_win->closebutton.setPayload(gui2closebutton);

    ui_button_np *t_np;
    t_np = new ui_button_np;

    test_win->addChild(t_np);
    t_np->setStyle(t_np_style);
    t_np->setXY(20,30);
    t_np->setWH(80,20);
    t_np->my_font.setFont(&font18gui);
    t_np->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setStretch(true);
    t_np->my_font.setColor(0.0,0.0,0.0,1.0);
    t_np->my_font.setText("sup, dude");
    t_np->my_font.cook();

    t_np = new ui_button_np;

    test_win->addChild(t_np);
    t_np->setStyle(t_np_style);
    t_np->setXY(20,60);
    t_np->setWH(80,20);
    t_np->my_font.setFont(&font18gui);
    t_np->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    t_np->my_font.setStretch(true);
    t_np->my_font.setColor(0.0,0.0,0.0,1.0);
    t_np->my_font.setText("sup, dude2");
    t_np->my_font.cook();

    ui_textinput *t_ti = new ui_textinput;

    test_win->addChild(t_ti);
    t_ti->setStyle(t_np_style_a);
    t_ti->setXY(10,140);
    t_ti->setWH(90,25);
    t_ti->setMaxTextLength(10);
    t_ti->setText("input");
    t_ti->my_font.setFont(&font18gui, FONT_HINT_DYNAMIC);
    t_ti->my_font.setColor(0.0,0.0,0.0,1.0);
    //t_ti->my_font.setHint(FONT_HINT_DYNAMIC);
    t_ti->my_font.setVertAlign(FONT_ALIGN_CENTER);
    t_ti->my_font.setStretch(false);
    t_ti->my_font.cook();



    ui_label *lab;
    lab = new ui_label;

    test_win->addChild(lab);
    lab->setXY(20,100);
    lab->setWH(40,40);
    lab->my_font.setFont(&font18gui);
    lab->my_font.setColor(1.0,1.0,1.0,1.0);
    //lab->my_font.setVertAlign(FONT_ALIGN_CENTER);
    //lab->my_font.setHorizAlign(FONT_ALIGN_CENTER);
    lab->my_font.setStretch(true);
    lab->my_font.setText("sup");
    lab->my_font.cook();

    ui_checkbox *check;
    check = new ui_checkbox;
    test_win->addChild(check);
    check->setStyle(t_np_style);
    check->setXY(80,100);
    check->setWH(15,15);
    check->checkmark.setTex( 128, 128, 32, 00, 19, 19 );


    test_win->cook();

}
