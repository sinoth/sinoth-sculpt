
#include <stdio.h>
#include "scene.h"


void scene::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    begin3D();
    mainCamera.setPerspective();
    mainLighting.doLighting();

    glDisable(GL_TEXTURE_2D);

    glBegin(GL_TRIANGLES);
        glColor4f(1.0,0.0,0.0,1.0); glVertex3f(0,0,-5);
        glColor4f(0.0,1.0,0.0,1.0); glVertex3f(0,1,-5);
        glColor4f(0.0,0.0,1.0,1.0); glVertex3f(1,0,-5);
    glEnd();


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_NORMAL_ARRAY);
    //glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

      glVertexPointer(3, GL_FLOAT, 0, &vec_grid_lines_indices[0] );
      glColorPointer(4, GL_FLOAT, 0, &vec_grid_lines_color_indices[0] );
      //glNormalPointer(GL_FLOAT, 0, &cavern_mesh_norm[0] );
      glDrawElements(GL_LINES, vec_grid_lines.size(), GL_UNSIGNED_INT, &vec_grid_lines[0] );

      //for (unsigned int i = 0; i < vec_vertex.size(); i+=3 ) {
      //    printf("%f %f %f\n", vec_vertex[i], vec_vertex[i+1], vec_vertex[i+2] );
      //} printf("\n");

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    //glPopClientAttrib();


    begin2D();

    glColor4f(1.0,1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, theme_texture);
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


    for (int i=0; i < 3*piece_x_size+1; ++i) {
      for (int j=0; j < 3*piece_y_size+1; ++j) {
        for (int k=0; k < 3*piece_z_size+1; ++k) {

            //first we'll generate the vertex index list
            //starts at the front, bottom, left corner
            //travels back, then up, then right
            vec_grid_lines_indices.push_back(i*3);
            vec_grid_lines_indices.push_back(j*3);
            vec_grid_lines_indices.push_back(k*3);

            //now for the color index list
            if ( i >=
            vec_grid_lines_color_indices.push_back(0.0);
            vec_grid_lines_color_indices.push_back(0.0);
            vec_grid_lines_color_indices.push_back(0.0);
            int max = (3*piece_x_size+1)*(3*piece_y_size+1)*(3*piece_z_size+1);
            float alpha = 0.333*fabs((((float)i/(3*piece_x_size+1)))  ) +

            vec_grid_lines_color_indices.push_back(alpha);

            //now the actual lines..

            if ( k < 3*piece_x_size ) { //xaxis
                vec_grid_lines.push_back(k   +  (j*(piece_z_size*3+1))  +  (i*((piece_y_size*3+1)*(piece_z_size*3+1))));
                vec_grid_lines.push_back(k+1 +  (j*(piece_z_size*3+1))  +  (i*((piece_y_size*3+1)*(piece_z_size*3+1)))); }
            if ( j < 3*piece_y_size ) { //yaxis
                vec_grid_lines.push_back(k +  ( j   *(piece_z_size*3+1))  +  (i*((piece_y_size*3+1)*(piece_z_size*3+1))));
                vec_grid_lines.push_back(k +  ((j+1)*(piece_z_size*3+1))  +  (i*((piece_y_size*3+1)*(piece_z_size*3+1)))); }
            if ( i < 3*piece_z_size ) { //zaxis
                vec_grid_lines.push_back(k +  (j*(piece_z_size*3+1))  +  (i    *((piece_y_size*3+1)*(piece_z_size*3+1))));
                vec_grid_lines.push_back(k +  (j*(piece_z_size*3+1))  +  ((i+1)*((piece_y_size*3+1)*(piece_z_size*3+1)))); }


            //lets try some points
            //vec_grid_lines.push_back(k+(j*(piece_z_size*3+1))+(i*((piece_y_size*3+1)*(piece_z_size*3+1))));

        }
      }
    }


}
