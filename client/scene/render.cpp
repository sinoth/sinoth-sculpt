
#include <stdio.h>
#include "scene.h"


void scene::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    begin3D();
    mainCamera.setPerspective();
    //mainLighting.doLighting();

    //glDisable(GL_TEXTURE_2D);

    glBegin(GL_TRIANGLES);
        glColor4f(1.0,0.0,0.0,1.0); glVertex3f(0,0,-5);
        glColor4f(0.0,1.0,0.0,1.0); glVertex3f(0,1,-5);
        glColor4f(0.0,0.0,1.0,1.0); glVertex3f(1,0,-5);
    glEnd();


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_NORMAL_ARRAY);
    //glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

      glVertexPointer(3, GL_FLOAT, 0, &vec_grid_lines[0] );
      glColorPointer(4, GL_FLOAT, 0, &vec_grid_lines_color[0] );
      //glNormalPointer(GL_FLOAT, 0, &cavern_mesh_norm[0] );
      //glDrawElements(GL_LINES, vec_grid_lines.size(), GL_UNSIGNED_INT, &vec_grid_lines[0] );
      glDrawArrays(GL_LINES, 0, vec_grid_lines.size()/3);

      //for (unsigned int i = 0; i < vec_vertex.size(); i+=3 ) {
      //    printf("%f %f %f\n", vec_vertex[i], vec_vertex[i+1], vec_vertex[i+2] );
      //} printf("\n");

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    //glPopClientAttrib();

    //glBegin(GL_LINES);
    //    glVertex3f(0,0,-1);
    //    glVertex3f(0,1,-1);
    //glEnd();


    begin2D();

    glColor4f(1.0,1.0,1.0,1.0);
    mainGui.render();


    glfwSwapBuffers();

    FPS();

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


    //position camera facing the thing
    //quaternion temp_q;
    //temp_q.createFromAxisAngle(0,1,0,0);
    //mainCamera.arcSetRotation(temp_q);
    mainCamera.arcSetCenter(vec3f(0,0,0));
    mainCamera.arcSetRadius(5.0);
    mainCamera.arcRecalculate();

}
