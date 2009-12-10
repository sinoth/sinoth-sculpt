
#include <stdio.h>
#include "scene.h"

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



void scene::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    begin3D();
    mainCamera.setPerspective();
    //mainLighting.doLighting();

    //glDisable(GL_TEXTURE_2D);

/*
    glTranslatef(0,0,-10);
    glBegin(GL_TRIANGLES);
        glColor4f(1.0,0.0,0.0,1.0); glVertex3f(0,0,0);
        glColor4f(0.0,1.0,0.0,1.0); glVertex3f(0,1,0);
        glColor4f(0.0,0.0,1.0,1.0); glVertex3f(1,0,0);
    glEnd();
*/

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
    quaternion temp_q;
    temp_q.createFromAxisAngle(1,0,0,0);
    mainCamera.arcSetRotation(temp_q);

    mainCamera.arcSetCenter(vec3f(piece_x_size*1.5,piece_y_size*1.5,piece_z_size*1.5));
    mainCamera.arcSetRadius(3*piece_x_size);

    //mainCamera.arcSetCenter(vec3f(0,0,0));
    //mainCamera.arcSetRadius(4);

    mainCamera.arcRecalculate();

}
