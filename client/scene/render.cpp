
#include <stdio.h>
#include <algorithm>
#include "scene.h"

void drawBox(float,float,float,float,float,float,bool);

void scene::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    //glLoadIdentity();

    //spin the camera
    //vec3f the_light = mainLighting.getPosition(0) - mainCamera.getArcballPosition();
    //quaternion light_rot;
    //light_rot.createFromAxisAngle(vec3f(1.0, 1.0, 0.5).normalize(), 1);
    //the_light = light_rot.mult(the_light);
    //the_light += mainCamera.getArcballPosition();
    //mainLighting.setPosition(0, the_light.x, the_light.y, the_light.z);

    //first thing is the background
    begin2D();
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, background_texture );
    glBegin(GL_QUADS);
        glColor4f(1.0,1.0,1.0,1.0);
        for (int i=0; i < res_cur_x; i+=1024) {
         for (int j=0; j < res_cur_y; j+=1024) {
            glTexCoord2f(0,0); glVertex2f(i,j);
            glTexCoord2f(0,1); glVertex2f(i,j+1024);
            glTexCoord2f(1,1); glVertex2f(i+1024,j+1024);
            glTexCoord2f(1,0); glVertex2f(i+1024,j);
         }
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glColor4f(0.5,0.5,0.5,0.8);
        glColor4f(0.5,0.5,0.5,0.8);
        glVertex2f(0,0);
        glVertex2f(0,res_cur_y);
        glVertex2f(res_cur_x,res_cur_y);
        glVertex2f(res_cur_x,0);
    glEnd();
    glEnable(GL_LIGHTING);


    begin3D();
    mainCamera.doPerspective();
    mainLighting.doLighting();

/*
    for ( int i=0; i < 1; ++i) {
        vec3f da_light = mainLighting.getPosition(i);
        glBegin(GL_QUADS);
        drawBox(da_light.x, da_light.y, da_light.z, 0.5, 0.5, 0.5, 0);
        glEnd();
    }
*/

    //render the selected cube

    static std::vector<collision3f> sorted_blocks;
    sorted_blocks.clear();

    for ( int i=0; i<piece_x_size;++i )
     for ( int j=0; j<piece_y_size;++j )
      for ( int k=0; k<piece_z_size;++k )
        if ( built_list[i+j*piece_x_size+k*piece_y_size*piece_x_size] )
            sorted_blocks.push_back( collision3f( vec3f(i+piece_x_size+0.5,j+piece_y_size+0.5,k+piece_z_size+0.5), mainCamera.getPosition().distance( vec3f(i+piece_x_size+0.5,j+piece_y_size+0.5,k+piece_z_size+0.5) ) ) );

    if ( sorted_blocks.size() ) {
        if ( view_method ) sort(sorted_blocks.begin(), sorted_blocks.end(), collision3f::greaterThan);
        else sort(sorted_blocks.begin(), sorted_blocks.end());
        glColor4f(1.0,1.0,1.0,0.7);
        //glEnable(GL_TEXTURE_2D);
        //glBindTexture( GL_TEXTURE_2D, noise_texture );
        //glBegin(GL_QUADS);
        //for ( std::vector<collision3f>::iterator it=sorted_blocks.begin(); it != sorted_blocks.end(); it++ )
        //    drawBox((*it).pos.x,(*it).pos.y,(*it).pos.z,0.5,1);
        //glEnd();
        //glDisable(GL_TEXTURE_2D);
    }

    box boxes;
    if ( sorted_blocks.size() ) {
        //temporary, until i use box objects permanently
        for ( std::vector<collision3f>::iterator it=sorted_blocks.begin(); it != sorted_blocks.end(); it++ )
            boxes.draw((*it).pos.x, (*it).pos.y, (*it).pos.z, 0.5);
        boxes.optimize();

        shadows.generate_edges(0, boxes.vert, 100);
        //shadows.generate_edges(1, boxes.vert, 100);
        //shadows.generate_edges(2, boxes.vert, 100);
        //shadows.generate_edges(3, boxes.vert, 100);

    }


glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
glPushAttrib(GL_ALL_ATTRIB_BITS);
  glEnable(GL_TEXTURE_2D);
  glBindTexture( GL_TEXTURE_2D, cube_texture );
    //first draw the scene unlit
    mainLighting.flipOff();
    render_cubes(boxes);
    //now layer the lit parts on top of eachother
    shadows.startShadowVodou();
    while ( shadows.doingShadows() )
        render_cubes(boxes);
    shadows.endShadowVodou();
    //turn the lights back on
    mainLighting.flipOn();
glPopAttrib();
glPopClientAttrib();

/*
    //draw shadows for debugging
    glColor4f(1.0,1.0,1.0,1.0);
    glPolygonMode(GL_FRONT, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &shadows.triangles[0][0] );
        //glDrawArrays(GL_TRIANGLES, 0, shadows.triangles[0].size()/3 );
    glDisableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT, GL_FILL);
*/
    static std::vector<collision3f> sorted_selection_blocks;
    static vec3f temp_vec;
    sorted_selection_blocks.clear();

    glDisable(GL_LIGHTING);
    if ( hovering_piece || placing_piece ) {
        switch ( selected_face ) {
            case CUBE_UP: case CUBE_DOWN:
                for (int i=0; i<piece_y_size; ++i) {
                    if ( placing_piece && i == selected_piece.y ) glColor4f(1.0,0.0,0.0,0.6);
                    else glColor4f(1.0,0.0,0.0,0.3);
                    temp_vec.set(selected_piece.x+piece_x_size+0.5, i+piece_y_size+0.5, selected_piece.z+piece_z_size+0.5 );
                    sorted_selection_blocks.push_back( collision3f( temp_vec, mainCamera.getPosition().distance( temp_vec ) ) );
                    //drawBox(selected_piece.x+piece_x_size+0.5,i+piece_y_size+0.5,selected_piece.z+piece_z_size+0.5,0.55,0);
                }
                break;
            case CUBE_LEFT: case CUBE_RIGHT:
                for (int i=0; i<piece_x_size; ++i) {
                    if ( placing_piece && i == selected_piece.x ) glColor4f(1.0,0.0,0.0,0.6);
                    else glColor4f(1.0,0.0,0.0,0.3);
                    temp_vec.set(i+piece_x_size+0.5, selected_piece.y+piece_y_size+0.5, selected_piece.z+piece_z_size+0.5);
                    sorted_selection_blocks.push_back( collision3f( temp_vec, mainCamera.getPosition().distance( temp_vec ) ) );
                    //drawBox(i+piece_x_size+0.5,selected_piece.y+piece_y_size+0.5,selected_piece.z+piece_z_size+0.5,0.55,0);
                }
                break;
            case CUBE_FRONT: case CUBE_BACK:
                for (int i=0; i<piece_z_size; ++i) {
                    if ( placing_piece &&  i == selected_piece.z ) glColor4f(1.0,0.0,0.0,0.6);
                    else glColor4f(1.0,0.0,0.0,0.3);
                    temp_vec.set(selected_piece.x+piece_x_size+0.5, selected_piece.y+piece_y_size+0.5, i+piece_z_size+0.5);
                    sorted_selection_blocks.push_back( collision3f( temp_vec, mainCamera.getPosition().distance( temp_vec ) ) );
                    //drawBox(selected_piece.x+piece_x_size+0.5,selected_piece.y+piece_y_size+0.5,i+piece_z_size+0.5,0.55,0);
                }
                break;
        }

    glEnable( GL_POLYGON_OFFSET_FILL );
    glPolygonOffset( -1.0f, 1.0f );

        //sort then display the cubes
        sort(sorted_selection_blocks.begin(), sorted_selection_blocks.end());
        //sort(sorted_selection_blocks.begin(), sorted_selection_blocks.end(), collision3f::greaterThan);
        //glDisable(GL_DEPTH_TEST);
        glBegin(GL_QUADS);
            for (uint32_t i=0; i<sorted_selection_blocks.size(); ++i) {
                if ( placing_piece &&
                    (((selected_face==CUBE_UP||selected_face==CUBE_DOWN)    && sorted_selection_blocks[i].pos.y-piece_y_size-0.5 == selected_piece.y) ||
                     ((selected_face==CUBE_LEFT||selected_face==CUBE_RIGHT) && sorted_selection_blocks[i].pos.x-piece_x_size-0.5 == selected_piece.x) ||
                     ((selected_face==CUBE_FRONT||selected_face==CUBE_BACK) && sorted_selection_blocks[i].pos.z-piece_z_size-0.5 == selected_piece.z)) ) {
                        glColor4f(1.0,0.0,0.0,0.6);
                } else {
                    switch ( selected_face ) {
                        case CUBE_UP: case CUBE_DOWN: glColor4f(1.0,0.0,0.0,0.4-((float)i/(float)piece_y_size)*0.3); break;
                        case CUBE_LEFT: case CUBE_RIGHT: glColor4f(1.0,0.0,0.0,0.4-((float)i/(float)piece_x_size)*0.3); break;
                        case CUBE_FRONT: case CUBE_BACK: glColor4f(1.0,0.0,0.0,0.4-((float)i/(float)piece_z_size)*0.3); break;
                        default: glColor4f(1.0,0.0,0.0,0.3); break;
                    }
                }
                switch ( selected_face ) {
                    case CUBE_UP: case CUBE_DOWN:
                        drawBox(sorted_selection_blocks[i].pos.x, sorted_selection_blocks[i].pos.y, sorted_selection_blocks[i].pos.z, 0.55, 0.50, 0.55, 0);
                        break;
                    case CUBE_LEFT: case CUBE_RIGHT:
                        drawBox(sorted_selection_blocks[i].pos.x, sorted_selection_blocks[i].pos.y, sorted_selection_blocks[i].pos.z, 0.50, 0.55, 0.55, 0);
                        break;
                    case CUBE_FRONT: case CUBE_BACK:
                        drawBox(sorted_selection_blocks[i].pos.x, sorted_selection_blocks[i].pos.y, sorted_selection_blocks[i].pos.z, 0.55, 0.55, 0.50, 0);
                        break;
                    default: break;
                }
            }
    //} else {
    //    if ( hovering_piece ) {
    //        glColor4f(1.0,0.0,0.0,0.1);
    //        drawBox(selected_piece.x+piece_x_size+0.5,selected_piece.y+piece_y_size+0.5,selected_piece.z+piece_z_size+0.5,0.5);
    //    }
        glEnd();
        //glEnable(GL_DEPTH_TEST);
    }

    glDisable( GL_POLYGON_OFFSET_FILL );



    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_NORMAL_ARRAY);
    //glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

        glDisable(GL_DEPTH_TEST);
        for ( int i=0; i < 6; ++i ) {
          if ( show_face[i] ) {
              glVertexPointer(3, GL_FLOAT, 0, &vec_grid_lines[i][0] );
              glColorPointer(4, GL_FLOAT, 0, &vec_grid_lines_color[i][0] );
              //glNormalPointer(GL_FLOAT, 0, &cavern_mesh_norm[0] );
              //glDrawElements(GL_LINES, vec_grid_lines.size(), GL_UNSIGNED_INT, &vec_grid_lines[0] );
              glDrawArrays(GL_LINES, 0, vec_grid_lines[i].size()/3);
          }
        }
        glEnable(GL_DEPTH_TEST);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    //glPopClientAttrib();

    begin2D();

    glColor4f(1.0,1.0,1.0,1.0);
    mainGui.render();

    glfwSwapBuffers();

    FPS();

}

void scene::render_cubes(const box &inboxes) {

    if ( inboxes.vert.size() ) {

        glColor4f(1.0,1.0,1.0,1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, &inboxes.vert[0] );
            glTexCoordPointer(2, GL_FLOAT, 0, &inboxes.tex[0] );
            glNormalPointer(GL_FLOAT, 0, &inboxes.norm[0] );
            glDrawArrays(GL_TRIANGLES, 0, inboxes.vert.size()/3);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    }
/*
    glColor4f(1.0,1.0,1.0,1.0);
    glBegin(GL_QUADS);
        glVertex3f(-60,0,60);
        glVertex3f(-60,0,-60);
        glVertex3f(60,0,-60);
        glVertex3f(60,0,60);
    glEnd();
*/
}



void scene::resetCamera() {

    mainCamera.reset();

    float random_heading = ((float)rand()/(float)(RAND_MAX) * 360.0);
    float random_pitch = ((float)rand()/(float)(RAND_MAX) * mainCamera.getMaxPitch() * 2) - mainCamera.getMaxPitch();

    mainCamera.setHeading(random_heading);
    mainCamera.setPitch(random_pitch);

    mainCamera.recalculateAngle();
}

void scene::generateVA() {

    {
    //upper grid face
    for (int i=piece_x_size; i <= 2*piece_x_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_UP].push_back(1.0); vec_grid_lines_color[CUBE_UP].push_back(0.0); vec_grid_lines_color[CUBE_UP].push_back(0.0); vec_grid_lines_color[CUBE_UP].push_back(0.2); }
        vec_grid_lines[CUBE_UP].push_back(i); vec_grid_lines[CUBE_UP].push_back(piece_y_size*2); vec_grid_lines[CUBE_UP].push_back(piece_z_size);
        vec_grid_lines[CUBE_UP].push_back(i); vec_grid_lines[CUBE_UP].push_back(piece_y_size*2); vec_grid_lines[CUBE_UP].push_back(piece_z_size*2); }
    for (int i=piece_z_size; i <= 2*piece_z_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_UP].push_back(1.0); vec_grid_lines_color[CUBE_UP].push_back(0.0); vec_grid_lines_color[CUBE_UP].push_back(0.0); vec_grid_lines_color[CUBE_UP].push_back(0.2); }
        vec_grid_lines[CUBE_UP].push_back(piece_x_size); vec_grid_lines[CUBE_UP].push_back(piece_y_size*2); vec_grid_lines[CUBE_UP].push_back(i);
        vec_grid_lines[CUBE_UP].push_back(piece_x_size*2); vec_grid_lines[CUBE_UP].push_back(piece_y_size*2); vec_grid_lines[CUBE_UP].push_back(i); }
    //lower grid face
    for (int i=piece_x_size; i <= 2*piece_x_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_DOWN].push_back(1.0); vec_grid_lines_color[CUBE_DOWN].push_back(0.0); vec_grid_lines_color[CUBE_DOWN].push_back(0.0); vec_grid_lines_color[CUBE_DOWN].push_back(0.2); }
        vec_grid_lines[CUBE_DOWN].push_back(i); vec_grid_lines[CUBE_DOWN].push_back(piece_y_size); vec_grid_lines[CUBE_DOWN].push_back(piece_z_size);
        vec_grid_lines[CUBE_DOWN].push_back(i); vec_grid_lines[CUBE_DOWN].push_back(piece_y_size); vec_grid_lines[CUBE_DOWN].push_back(piece_z_size*2); }
    for (int i=piece_z_size; i <= 2*piece_z_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_DOWN].push_back(1.0); vec_grid_lines_color[CUBE_DOWN].push_back(0.0); vec_grid_lines_color[CUBE_DOWN].push_back(0.0); vec_grid_lines_color[CUBE_DOWN].push_back(0.2); }
        vec_grid_lines[CUBE_DOWN].push_back(piece_x_size); vec_grid_lines[CUBE_DOWN].push_back(piece_y_size); vec_grid_lines[CUBE_DOWN].push_back(i);
        vec_grid_lines[CUBE_DOWN].push_back(piece_x_size*2); vec_grid_lines[CUBE_DOWN].push_back(piece_y_size); vec_grid_lines[CUBE_DOWN].push_back(i); }
    //left grid face
    for (int i=piece_y_size; i <= 2*piece_y_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_LEFT].push_back(1.0); vec_grid_lines_color[CUBE_LEFT].push_back(0.0); vec_grid_lines_color[CUBE_LEFT].push_back(0.0); vec_grid_lines_color[CUBE_LEFT].push_back(0.2); }
        vec_grid_lines[CUBE_LEFT].push_back(piece_x_size); vec_grid_lines[CUBE_LEFT].push_back(i); vec_grid_lines[CUBE_LEFT].push_back(piece_z_size);
        vec_grid_lines[CUBE_LEFT].push_back(piece_x_size); vec_grid_lines[CUBE_LEFT].push_back(i); vec_grid_lines[CUBE_LEFT].push_back(piece_z_size*2); }
    for (int i=piece_z_size; i <= 2*piece_z_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_LEFT].push_back(1.0); vec_grid_lines_color[CUBE_LEFT].push_back(0.0); vec_grid_lines_color[CUBE_LEFT].push_back(0.0); vec_grid_lines_color[CUBE_LEFT].push_back(0.2); }
        vec_grid_lines[CUBE_LEFT].push_back(piece_x_size); vec_grid_lines[CUBE_LEFT].push_back(piece_y_size); vec_grid_lines[CUBE_LEFT].push_back(i);
        vec_grid_lines[CUBE_LEFT].push_back(piece_x_size); vec_grid_lines[CUBE_LEFT].push_back(piece_y_size*2); vec_grid_lines[CUBE_LEFT].push_back(i); }
    //right grid face
    for (int i=piece_y_size; i <= 2*piece_y_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_RIGHT].push_back(1.0); vec_grid_lines_color[CUBE_RIGHT].push_back(0.0); vec_grid_lines_color[CUBE_RIGHT].push_back(0.0); vec_grid_lines_color[CUBE_RIGHT].push_back(0.2); }
        vec_grid_lines[CUBE_RIGHT].push_back(piece_x_size*2); vec_grid_lines[CUBE_RIGHT].push_back(i); vec_grid_lines[CUBE_RIGHT].push_back(piece_z_size);
        vec_grid_lines[CUBE_RIGHT].push_back(piece_x_size*2); vec_grid_lines[CUBE_RIGHT].push_back(i); vec_grid_lines[CUBE_RIGHT].push_back(piece_z_size*2); }
    for (int i=piece_z_size; i <= 2*piece_z_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_RIGHT].push_back(1.0); vec_grid_lines_color[CUBE_RIGHT].push_back(0.0); vec_grid_lines_color[CUBE_RIGHT].push_back(0.0); vec_grid_lines_color[CUBE_RIGHT].push_back(0.2); }
        vec_grid_lines[CUBE_RIGHT].push_back(piece_x_size*2); vec_grid_lines[CUBE_RIGHT].push_back(piece_y_size); vec_grid_lines[CUBE_RIGHT].push_back(i);
        vec_grid_lines[CUBE_RIGHT].push_back(piece_x_size*2); vec_grid_lines[CUBE_RIGHT].push_back(piece_y_size*2); vec_grid_lines[CUBE_RIGHT].push_back(i); }
    //forward grid face
    for (int i=piece_x_size; i <= 2*piece_x_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_FRONT].push_back(1.0); vec_grid_lines_color[CUBE_FRONT].push_back(0.0); vec_grid_lines_color[CUBE_FRONT].push_back(0.0); vec_grid_lines_color[CUBE_FRONT].push_back(0.2); }
        vec_grid_lines[CUBE_FRONT].push_back(i); vec_grid_lines[CUBE_FRONT].push_back(piece_y_size); vec_grid_lines[CUBE_FRONT].push_back(piece_z_size);
        vec_grid_lines[CUBE_FRONT].push_back(i); vec_grid_lines[CUBE_FRONT].push_back(piece_y_size*2); vec_grid_lines[CUBE_FRONT].push_back(piece_z_size); }
    for (int i=piece_y_size; i <= 2*piece_y_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_FRONT].push_back(1.0); vec_grid_lines_color[CUBE_FRONT].push_back(0.0); vec_grid_lines_color[CUBE_FRONT].push_back(0.0); vec_grid_lines_color[CUBE_FRONT].push_back(0.2); }
        vec_grid_lines[CUBE_FRONT].push_back(piece_x_size); vec_grid_lines[CUBE_FRONT].push_back(i); vec_grid_lines[CUBE_FRONT].push_back(piece_z_size);
        vec_grid_lines[CUBE_FRONT].push_back(piece_x_size*2); vec_grid_lines[CUBE_FRONT].push_back(i); vec_grid_lines[CUBE_FRONT].push_back(piece_z_size); }
    //back grid face
    for (int i=piece_x_size; i <= 2*piece_x_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_BACK].push_back(1.0); vec_grid_lines_color[CUBE_BACK].push_back(0.0); vec_grid_lines_color[CUBE_BACK].push_back(0.0); vec_grid_lines_color[CUBE_BACK].push_back(0.2); }
        vec_grid_lines[CUBE_BACK].push_back(i); vec_grid_lines[CUBE_BACK].push_back(piece_y_size); vec_grid_lines[CUBE_BACK].push_back(piece_z_size*2);
        vec_grid_lines[CUBE_BACK].push_back(i); vec_grid_lines[CUBE_BACK].push_back(piece_y_size*2); vec_grid_lines[CUBE_BACK].push_back(piece_z_size*2); }
    for (int i=piece_y_size; i <= 2*piece_y_size; ++i) {
        for (int ii=0; ii < 2; ++ii ) { vec_grid_lines_color[CUBE_BACK].push_back(1.0); vec_grid_lines_color[CUBE_BACK].push_back(0.0); vec_grid_lines_color[CUBE_BACK].push_back(0.0); vec_grid_lines_color[CUBE_BACK].push_back(0.2); }
        vec_grid_lines[CUBE_BACK].push_back(piece_x_size); vec_grid_lines[CUBE_BACK].push_back(i); vec_grid_lines[CUBE_BACK].push_back(piece_z_size*2);
        vec_grid_lines[CUBE_BACK].push_back(piece_x_size*2); vec_grid_lines[CUBE_BACK].push_back(i); vec_grid_lines[CUBE_BACK].push_back(piece_z_size*2); }
    }



    //position camera facing the thing
    quaternion temp_q;
    temp_q.createFromAxisAngle(1,0,0,0);
    mainCamera.arcSetRotation(temp_q);
    mainCamera.arcSetCenter(vec3f(piece_x_size*1.5,piece_y_size*1.5,piece_z_size*1.5));
    mainCamera.arcSetRadius(3*piece_x_size);
    mainCamera.arcRecalculate();


}

void drawBox(float x, float y, float z, float s_x, float s_y, float s_z, bool tex) {
    //top
    if (tex) glTexCoord2f(0,0); glNormal3f(0,1,0); glVertex3f(x-s_x,y+s_y,z+s_z);
    if (tex) glTexCoord2f(0,1); glNormal3f(0,1,0); glVertex3f(x-s_x,y+s_y,z-s_z);
    if (tex) glTexCoord2f(1,1); glNormal3f(0,1,0); glVertex3f(x+s_x,y+s_y,z-s_z);
    if (tex) glTexCoord2f(1,0); glNormal3f(0,1,0); glVertex3f(x+s_x,y+s_y,z+s_z);
    //bottom
    if (tex) glTexCoord2f(1,0); glNormal3f(0,-1,0); glVertex3f(x+s_x,y-s_y,z+s_z);
    if (tex) glTexCoord2f(1,1); glNormal3f(0,-1,0); glVertex3f(x+s_x,y-s_y,z-s_z);
    if (tex) glTexCoord2f(0,1); glNormal3f(0,-1,0); glVertex3f(x-s_x,y-s_y,z-s_z);
    if (tex) glTexCoord2f(0,0); glNormal3f(0,-1,0); glVertex3f(x-s_x,y-s_y,z+s_z);
    //left
    if (tex) glTexCoord2f(1,0); glNormal3f(-1,0,0); glVertex3f(x-s_x,y-s_y,z+s_z);
    if (tex) glTexCoord2f(0,0); glNormal3f(-1,0,0); glVertex3f(x-s_x,y-s_y,z-s_z);
    if (tex) glTexCoord2f(0,1); glNormal3f(-1,0,0); glVertex3f(x-s_x,y+s_y,z-s_z);
    if (tex) glTexCoord2f(1,1); glNormal3f(-1,0,0); glVertex3f(x-s_x,y+s_y,z+s_z);
    //right
    if (tex) glTexCoord2f(1,1); glNormal3f(1,0,0); glVertex3f(x+s_x,y+s_y,z+s_z);
    if (tex) glTexCoord2f(0,1); glNormal3f(1,0,0); glVertex3f(x+s_x,y+s_y,z-s_z);
    if (tex) glTexCoord2f(0,0); glNormal3f(1,0,0); glVertex3f(x+s_x,y-s_y,z-s_z);
    if (tex) glTexCoord2f(1,0); glNormal3f(1,0,0); glVertex3f(x+s_x,y-s_y,z+s_z);
    //front
    if (tex) glTexCoord2f(1,0); glNormal3f(0,0,-1); glVertex3f(x+s_x,y-s_y,z-s_z);
    if (tex) glTexCoord2f(1,1); glNormal3f(0,0,-1); glVertex3f(x+s_x,y+s_y,z-s_z);
    if (tex) glTexCoord2f(0,1); glNormal3f(0,0,-1); glVertex3f(x-s_x,y+s_y,z-s_z);
    if (tex) glTexCoord2f(0,0); glNormal3f(0,0,-1); glVertex3f(x-s_x,y-s_y,z-s_z);
    //back
    if (tex) glTexCoord2f(0,0); glNormal3f(0,0,1); glVertex3f(x-s_x,y-s_y,z+s_z);
    if (tex) glTexCoord2f(0,1); glNormal3f(0,0,1); glVertex3f(x-s_x,y+s_y,z+s_z);
    if (tex) glTexCoord2f(1,1); glNormal3f(0,0,1); glVertex3f(x+s_x,y+s_y,z+s_z);
    if (tex) glTexCoord2f(1,0); glNormal3f(0,0,1); glVertex3f(x+s_x,y-s_y,z+s_z);
}

/*


    //cube
    glBegin(GL_QUADS);
        //top
        glColor4f(1.0,0.0,0.0,1.0);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5,-0.5);
        glVertex3f( 0.5, 0.5,-0.5);
        glVertex3f( 0.5, 0.5, 0.5);
        //bottom
        glColor4f(0.0,1.0,0.0,1.0);
        glVertex3f(-0.5,-0.5, 0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f( 0.5,-0.5,-0.5);
        glVertex3f( 0.5,-0.5, 0.5);
    glEnd();
    glBegin(GL_LINES);
        //four connecting lines
        glColor4f(0.0,0.0,1.0,1.0);
        glVertex3f(-0.5, 0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);

        glColor4f(1.0,1.0,0.0,1.0);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5,-0.5, 0.5);

        glColor4f(0.0,0.0,1.0,1.0);
        glVertex3f( 0.5, 0.5,-0.5);
        glVertex3f( 0.5,-0.5,-0.5);

        glColor4f(1.0,1.0,0.0,1.0);
        glVertex3f( 0.5, 0.5, 0.5);
        glVertex3f( 0.5,-0.5, 0.5);
    glEnd();


    //glTranslatef(mainCamera.p_position.x, mainCamera.p_position.y,  mainCamera.p_position.z);
    //glMultMatrixf(mainCamera.af_Matrix_pos);



    //cube
    glBegin(GL_QUADS);
        //top
        glColor4f(1.0,0.0,0.0,1.0);
        glVertex3f(-0.25, 0.25, 0.25);
        glVertex3f(-0.25, 0.25,-0.25);
        glVertex3f( 0.25, 0.25,-0.25);
        glVertex3f( 0.25, 0.25, 0.25);
        //bottom
        glColor4f(0.0,1.0,0.0,1.0);
        glVertex3f(-0.25,-0.25, 0.25);
        glVertex3f(-0.25,-0.25,-0.25);
        glVertex3f( 0.25,-0.25,-0.25);
        glVertex3f( 0.25,-0.25, 0.25);
    glEnd();
    glBegin(GL_LINES);
        //four connecting lines
        glColor4f(0.0,0.0,1.0,1.0);
        glVertex3f(-0.25, 0.25,-0.25);
        glVertex3f(-0.25,-0.25,-0.25);

        glColor4f(1.0,1.0,0.0,1.0);
        glVertex3f(-0.25, 0.25, 0.25);
        glVertex3f(-0.25,-0.25, 0.25);

        glColor4f(0.0,0.0,1.0,1.0);
        glVertex3f( 0.25, 0.25,-0.25);
        glVertex3f( 0.25,-0.25,-0.25);

        glColor4f(1.0,1.0,0.0,1.0);
        glVertex3f( 0.25, 0.25, 0.25);
        glVertex3f( 0.25,-0.25, 0.25);
    glEnd();

    //glTranslatef(-mainCamera.p_position.x, -mainCamera.p_position.y, -mainCamera.p_position.z);


*/

/*
 void sinLookAt(const vec3f &eyePosition, const vec3f &center, const vec3f &upVector)
 {
    float forward[3], side[3], up[3];
    float matrix2[16], resultMatrix[16];
    //------------------
    forward[0] = center3D[0] - eyePosition3D[0];
    forward[1] = center3D[1] - eyePosition3D[1];
    forward[2] = center3D[2] - eyePosition3D[2];
    NormalizeVector(forward);
    //------------------
    //Side = forward x up
    ComputeNormalOfPlane(side, forward, upVector3D);
    NormalizeVector(side);
    //------------------
    //Recompute up as: up = side x forward
    ComputeNormalOfPlane(up, side, forward);
    //------------------
    matrix2[0] = side[0];
    matrix2[4] = side[1];
    matrix2[8] = side[2];
    matrix2[12] = 0.0;
    //------------------
    matrix2[1] = up[0];
    matrix2[5] = up[1];
    matrix2[9] = up[2];
    matrix2[13] = 0.0;
    //------------------
    matrix2[2] = -forward[0];
    matrix2[6] = -forward[1];
    matrix2[10] = -forward[2];
    matrix2[14] = 0.0;
    //------------------
    matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
    matrix2[15] = 1.0;
    //------------------
    MultiplyMatrices4by4OpenGL_FLOAT(resultMatrix, matrix, matrix2);
    glhTranslatef2(resultMatrix, -eyePosition3D[0], -eyePosition3D[1], -eyePosition3D[2]);
    //------------------
    memcpy(matrix, resultMatrix, 16*sizeof(float));
 }
*/

/*
    for (int i=0; i < 3*piece_x_size+1; ++i) {
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(0); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(0); vec_grid_lines.push_back(3*piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(3*piece_z_size);

        vec_grid_lines.push_back(i); vec_grid_lines.push_back(0); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(0); vec_grid_lines.push_back(3*piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(3*piece_z_size);
    }

    for (int j=0; j < 3*piece_y_size+1; ++j) {
        vec_grid_lines.push_back(0); vec_grid_lines.push_back(j); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(0); vec_grid_lines.push_back(j); vec_grid_lines.push_back(3*piece_z_size);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(3*piece_z_size);

        vec_grid_lines.push_back(0); vec_grid_lines.push_back(j); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(0);
        vec_grid_lines.push_back(0); vec_grid_lines.push_back(j); vec_grid_lines.push_back(3*piece_z_size);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(3*piece_z_size);
    }

    for (int k=0; k < 3*piece_z_size+1; ++k) {
        vec_grid_lines.push_back(0); vec_grid_lines.push_back(0); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(0); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(0); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(k);

        vec_grid_lines.push_back(0); vec_grid_lines.push_back(0); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(0); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(0); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(3*piece_x_size); vec_grid_lines.push_back(3*piece_y_size); vec_grid_lines.push_back(k);
    }

    for (int ii=0; ii<8*(3*piece_x_size+1)+8*(3*piece_y_size+1)+8*(3*piece_z_size+1); ++ii) {
        vec_grid_lines_color.push_back(0.0);
        vec_grid_lines_color.push_back(0.0);
        vec_grid_lines_color.push_back(0.0);
        vec_grid_lines_color.push_back(0.1);
    }
*/
    ///////////////////
/*
    for (int i=piece_x_size; i <= 2*piece_x_size; ++i) {
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(piece_z_size); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(piece_z_size); vec_grid_lines.push_back(2*piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(2*piece_z_size); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(2*piece_y_size); vec_grid_lines.push_back(2*piece_z_size);

        vec_grid_lines.push_back(i); vec_grid_lines.push_back(piece_y_size); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(2*piece_y_size); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(piece_y_size); vec_grid_lines.push_back(2*piece_z_size);
        vec_grid_lines.push_back(i); vec_grid_lines.push_back(2*piece_y_size); vec_grid_lines.push_back(2*piece_z_size);
    }

    for (int j=piece_y_size; j <= 2*piece_y_size; ++j) {
        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(2*piece_z_size);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(2*piece_z_size);

        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(piece_z_size);
        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(2*piece_z_size);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(j); vec_grid_lines.push_back(2*piece_z_size);
    }

    for (int k=piece_z_size; k <= 2*piece_z_size; ++k) {
        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(2*piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(2*piece_y_size); vec_grid_lines.push_back(k);

        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(piece_x_size); vec_grid_lines.push_back(2*piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(2*piece_y_size); vec_grid_lines.push_back(k);
        vec_grid_lines.push_back(2*piece_x_size); vec_grid_lines.push_back(piece_y_size); vec_grid_lines.push_back(k);
    }

    for (int ii=0; ii<8*(3*piece_x_size+1)+8*(3*piece_y_size+1)+8*(3*piece_z_size+1); ++ii) {
        vec_grid_lines_color.push_back(1.0);
        vec_grid_lines_color.push_back(0.0);
        vec_grid_lines_color.push_back(0.0);
        vec_grid_lines_color.push_back(0.1);
    }
*/
