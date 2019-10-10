#include "utils.h"

//#include <unistd.h>
#include <cstdlib>
//#include <cstdio>

void softReset()
{
    exit(0);
    // TODO execl does not call destructors on previous/replaced process???
//    if (execl(_global_main_argv[0], _global_main_argv[0], static_cast<char *>(nullptr)) < 0) {
//        perror("Failed to restart the game");
//        exit(1);
//    }
    // TODO
    // set FD_CLOEXEC to "EEEPROM memory" file
    // fork, exec, detach from parent, kill parent?
    //
    // TODO nope...just make games restartable? every game will have function resetState() or something?
}
