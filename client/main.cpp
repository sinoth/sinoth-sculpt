
#include <stdio.h>
#include "scene.h"


int main(int, char **)
{

  #ifdef PTW32_STATIC_LIB
  pthread_win32_process_attach_np();
  #endif

  {

    scene mainScene;
    sinTimerGLFW updateTimer(60);

    if ( mainScene.init() ) {
        fprintf(stderr, "ERROR: Cannot init scene\n");
        return 1; }

    while ( !mainScene.quit ) {

        if ( updateTimer.needUpdateNoCarry() ) {
            mainScene.update();
            mainScene.render();
        }
        glfwSleep(0.001);
    }

    mainScene.save_username();

  }

  #ifdef PTW32_STATIC_LIB
  pthread_win32_thread_detach_np();
  pthread_win32_process_detach_np();
  #endif

    return 0;
}


