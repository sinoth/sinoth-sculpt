
#include <stdio.h>
#include "scene.h"


void scene::render() {


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();



    mainCamera.setPerspective();
    //glTranslatef(0,0,-20);


    glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

/*
    glPushMatrix();
    glTranslatef(mainPlayer.my_body->getCenterOfMassPosition().getX(),mainPlayer.my_body->getCenterOfMassPosition().getY(),mainPlayer.my_body->getCenterOfMassPosition().getZ());
        glBegin(GL_QUADS);
            //bottom,top,left,right,front,back
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-1,-1,-1);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-1,-1, 1);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 1,-1, 1);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 1,-1,-1);

            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-1, 1, 1);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-1, 1,-1);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 1, 1,-1);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 1, 1, 1);
            //
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-1,-1,-1);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-1, 1,-1);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f(-1, 1, 1);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f(-1,-1, 1);

            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 1,-1, 1);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f( 1, 1, 1);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 1, 1,-1);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 1,-1,-1);
            //
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 1,-1,-1);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f( 1, 1,-1);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f(-1, 1,-1);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f(-1,-1,-1);

            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-1,-1, 1);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-1, 1, 1);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 1, 1, 1);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 1,-1, 1);
        glEnd();
    glPopMatrix();
    glColor4f(1.0,1.0,1.0,1.0);


    glColor4f(1.0,1.0,1.0,1.0);


        glBegin(GL_TRIANGLES);
            glColor4f(1.0,0.0,0.0,1.0); glVertex3f(0,0,-5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(0,1,-5);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f(1,0,-5);

            glColor4f(0.0,0.0,1.0,1.0); glVertex3f(1,0,-5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(0,1,-5);
            glColor4f(1.0,0.0,0.0,1.0); glVertex3f(0,0,-5);
        glEnd();

//surrounding cube
        glBegin(GL_QUADS);
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f(-50,0, 50);
            glColor4f(0.7,0.7,0.7,1.0); glVertex3f(-50,0,-50);
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f( 50,0,-50);
            glColor4f(0.3,0.3,0.3,1.0); glVertex3f( 50,0, 50);
            //front,back,right,left,top
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f(-50, 0,-50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-50,50,-50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 50,50,-50);
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f( 50, 0,-50);

            glColor4f(0.5,0.5,0.5,1.0); glVertex3f( 50, 0, 50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 50,50, 50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-50,50, 50);
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f(-50, 0, 50);
            //
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f(-50, 0, 50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-50,50, 50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-50,50,-50);
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f(-50, 0,-50);

            glColor4f(0.5,0.5,0.5,1.0); glVertex3f( 50, 0,-50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 50,50,-50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 50,50, 50);
            glColor4f(0.5,0.5,0.5,1.0); glVertex3f( 50, 0, 50);
            //
            glColor4f(1.0,0.0,0.0,1.0); glVertex3f(-50,50,-50);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-50,50, 50);
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 50,50, 50);
            glColor4f(1.0,1.0,0.0,1.0); glVertex3f( 50,50,-50);
        glEnd();

//render the platform
        glBegin(GL_QUADS);
            //bottom,top,left,right,front,back
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-5,11,-5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-5,11, 5);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 5,11, 5);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 5,11,-5);

            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-5,15, 5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-5,15,-5);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 5,15,-5);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 5,15, 5);
            //
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-5,11,-5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-5,15,-5);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f(-5,15, 5);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f(-5,11, 5);

            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 5,11, 5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f( 5,15, 5);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 5,15,-5);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 5,11,-5);
            //
            glColor4f(0.0,0.0,0.0,1.0); glVertex3f( 5,11,-5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f( 5,15,-5);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f(-5,15,-5);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f(-5,11,-5);

            glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-5,11, 5);
            glColor4f(0.0,1.0,0.0,1.0); glVertex3f(-5,15, 5);
            glColor4f(0.0,0.0,1.0,1.0); glVertex3f( 5,15, 5);
            glColor4f(0.0,1.0,1.0,1.0); glVertex3f( 5,11, 5);
        glEnd();
*/

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

    glColor4f(1.0,1.0,1.0,1.0);
    renderTheFuckingRope();


    glfwSwapBuffers();

    FPS();

}



void DrawPoint(const btVector3& in1) {
    glBegin(GL_POINTS);
        glVertex3f(in1.getX(), in1.getY(), in1.getZ() );
    glEnd();
}

void DrawLine(const btVector3& in1, const btVector3& in2) {
    glBegin(GL_LINES);
        glVertex3f(in1.getX(), in1.getY(), in1.getZ() );
        glVertex3f(in2.getX(), in2.getY(), in2.getZ() );
    glEnd();
}

void DrawTriangle(const btVector3& in1, const btVector3& in2, const btVector3& in3 ) {
    glBegin(GL_TRIANGLES);
        glVertex3f(in1.getX(), in1.getY(), in1.getZ() );
        glVertex3f(in2.getX(), in2.getY(), in2.getZ() );
        glVertex3f(in3.getX(), in3.getY(), in3.getZ() );
    glEnd();
}

void scene::renderTheFuckingRope() {

   btSoftBodyArray &softbodies(((btSoftRigidDynamicsWorld*)dynamicsWorld)->getSoftBodyArray());

  for ( int i=0; i<softbodies.size(); ++i ) {
   btSoftBody *softbody(softbodies[i]);
   btSoftBody::tNodeArray&   nodes(softbody->m_nodes);
   btSoftBody::tLinkArray&   links(softbody->m_links);
   btSoftBody::tFaceArray&   faces(softbody->m_faces);



   /* Then, you can draw vertices...      */
   /* Node::m_x => position            */
   /* Node::m_n => normal (if meaningful)   */
   for(int j=0;j<nodes.size();++j)
      {
      glColor4f(1.0,0.0,0.0,1.0);
      DrawPoint(nodes[j].m_x);
      }
   /* Or edges (for ropes)               */
   /* Link::m_n[2] => pointers to nodes   */
   for(int j=0;j<links.size();++j)
      {
      btSoftBody::Node*   node_0=links[j].m_n[0];
      btSoftBody::Node*   node_1=links[j].m_n[1];
      glColor4f(1.0*(float)(j+1)/(float)links.size(),
                1.0*(float)(j+1)/(float)links.size(),
                1.0*(float)(j+1)/(float)links.size(),1.0);
      DrawLine(node_0->m_x,node_1->m_x);
      /* Or if you need indices...      */
      //const int         indices[]={   int(node_0-&nodes[0]),
      //                        int(node_1-&nodes[0])};
      }
   /* And even faces                  */
   /* Face::m_n[3] -> pointers to nodes   */
   for(int j=0;j<faces.size();++j)
      {
      btSoftBody::Node*   node_0=faces[j].m_n[0];
      btSoftBody::Node*   node_1=faces[j].m_n[1];
      btSoftBody::Node*   node_2=faces[j].m_n[2];
      DrawTriangle(node_0->m_x,node_1->m_x,node_2->m_x);
      /* Or if you need indices...      */
      //const int         indices[]={   int(node_0-&nodes[0]),
      //                        int(node_1-&nodes[0]),
      //                        int(node_2-&nodes[0])};
      }
  }
}




