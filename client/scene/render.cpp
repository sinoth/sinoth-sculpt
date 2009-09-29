
#include <stdio.h>
#include "scene.h"


void scene::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    mainCamera.setPerspective();
    mainLighting.doLighting();


    glBegin(GL_TRIANGLES);
        glColor4f(1.0,0.0,0.0,1.0); glVertex3f(0,0,-5);
        glColor4f(0.0,1.0,0.0,1.0); glVertex3f(0,1,-5);
        glColor4f(0.0,0.0,1.0,1.0); glVertex3f(1,0,-5);
    glEnd();

    /*
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    //glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

      glVertexPointer(3, GL_FLOAT, 0, &cavern_mesh_vert[0] );
      glColorPointer(4, GL_FLOAT, 0, &cavern_mesh_color[0] );
      glNormalPointer(GL_FLOAT, 0, &cavern_mesh_norm[0] );
      glDrawArrays(GL_TRIANGLES, 0, cavern_mesh_vert.size()/3 );

      //for (unsigned int i = 0; i < vec_vertex.size(); i+=3 ) {
      //    printf("%f %f %f\n", vec_vertex[i], vec_vertex[i+1], vec_vertex[i+2] );
      //} printf("\n");

    //glPopClientAttrib();
    */

    begin2D();

    mainGui.render();


    glfwSwapBuffers();

    FPS();

}




