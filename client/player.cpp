
#include <stdio.h>
#include "player.h"

player::player() {
    goFaster = false;
    goForward = false;
    goBack = false;
    goLeft = false;
    goRight = false;
    isJumping = false;
    touchingSomething = false;

    contactPoints = 0;
}


void player::initPhys(btDiscreteDynamicsWorld *inworld) {

    world = inworld;

    //main player
        btCollisionShape* fallShape = new btSphereShape(1.0); //radius
        btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(48,15,48)));

        btScalar mass = 5;
        btVector3 fallInertia(0,0,0);
        fallShape->calculateLocalInertia(mass,fallInertia);

        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape);
        fallRigidBodyCI.m_friction = 0.5;
        fallRigidBodyCI.m_linearDamping = 0.80;
        fallRigidBodyCI.m_angularDamping = 1.0;
        btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
        fallRigidBody->setRestitution(0.2);
        fallRigidBody->setActivationState(DISABLE_DEACTIVATION);
        fallRigidBody->setCollisionFlags(fallRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

        world->addRigidBody(fallRigidBody, COL_PLAYER, COL_STATIC_LEVEL | COL_PLATFORM | COL_ROPE | COL_LEVEL);
        my_body = fallRigidBody;

}



void player::update() {

    //printf("contact: %d\n", contactPoints);

    if ( !goFaster ) {
        if ( goForward )
            my_body->applyCentralForce( forward_vector_real*80 );
        if ( goBack )
            my_body->applyCentralForce( forward_vector_real*-80 );
        if ( goLeft )
            my_body->applyCentralForce( strafe_vector_real*-80 );
        if ( goRight )
            my_body->applyCentralForce( strafe_vector_real*80 );
    } else {
        if ( goForward )
            my_body->applyCentralForce( forward_vector_real*130 );
        if ( goBack )
            my_body->applyCentralForce( forward_vector_real*-130 );
        if ( goLeft )
            my_body->applyCentralForce( strafe_vector_real*-130 );
        if ( goRight )
            my_body->applyCentralForce( strafe_vector_real*130 );
    }


    //get the transform from physics object
    my_body->getMotionState()->getWorldTransform(transform);
    transform.getOpenGLMatrix(tmatrix);
    current_pos = transform.getOrigin();

    touchingSomething = contactPoints ? true : false;

    if ( touchingSomething && isJumping ) isJumping = false;


}

btVector3 player::getPosition() {
    //return my_body->getCenterOfMassPosition();
    return transform.getOrigin();
}

void player::updateVectors( vector *f, vector *s ) {

    forward_vector_real.setValue( f->x, f->y, f->z );
    forward_vector.setValue( f->x, f->y, f->z );
    forward_vector.setY(0);
    forward_vector.normalize();

    strafe_vector_real.setValue( s->x, s->y, s->z );
    strafe_vector.setValue( s->x, s->y, s->z );
    strafe_vector.setY(0);
    strafe_vector.normalize();

}


void player::doJump() {

    if ( !isJumping ) {
        isJumping = true;
        my_body->applyCentralImpulse( btVector3(0,75,0) );
    }
}




