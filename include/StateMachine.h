#ifndef STATEMACHINE_H
#define STATEMACHINE_H

typedef enum {
    INIT,
    RUNNING,
    PAUSED, // Differentiate between paused cycles/updates and rendering?
    HALT
} State;

#endif
