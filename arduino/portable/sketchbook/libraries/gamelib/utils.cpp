#include "utils.h"

void softReset()
{
    asm volatile("jmp 0");
}
