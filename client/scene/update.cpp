
#include <sintimer.h>

#include "scene.h"


void scene::update() {

    static sinTimerCounter physicsTimer;

    dynamicsWorld->stepSimulation(physicsTimer.timeSinceLastCall(),64, 1.0/120.0);
    //softBodyWorldInfo->m_sparsesdf.GarbageCollect();

    mainPlayer.updateVectors( &mainCamera.v_direction, &mainCamera.v_strafe_direction );
    mainPlayer.update();
    mainCamera.setPosition( mainPlayer.getPosition().getX(), mainPlayer.getPosition().getY(), mainPlayer.getPosition().getZ() );

    light_pos1[0] = mainPlayer.current_pos.getX();
    light_pos1[1] = mainPlayer.current_pos.getY();
    light_pos1[2] = mainPlayer.current_pos.getZ();

}
