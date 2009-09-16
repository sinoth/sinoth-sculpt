#ifndef PLAYER_H
#define PLAYER_H

#include <btBulletDynamicsCommon.h>
#include <sinprim.h>


#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0,
    COL_PLAYER = BIT(1),
    COL_STATIC_LEVEL = BIT(2),
    COL_PLATFORM = BIT(3),
    COL_ROPE = BIT(4),
    COL_PLATFORM_FIELD = BIT(5),
    COL_LEVEL = BIT(6)
};


class player {
public:

    bool goFaster;
    bool goLeft;
    bool goRight;
    bool goForward;
    bool goBack;
    bool isJumping;

    int contactPoints;
    bool touchingSomething;

    btVector3 forward_vector;
    btVector3 forward_vector_real;
    btVector3 strafe_vector;
    btVector3 strafe_vector_real;
    btDiscreteDynamicsWorld *world;
    btRigidBody *my_body;

    btVector3 current_pos;
    btTransform transform;
    float tmatrix[16];


    player();
    void initPhys(btDiscreteDynamicsWorld*);
    void update();
    void updateVectors( vector *, vector * );
    void doJump();
    btVector3 getPosition();


};




#endif

