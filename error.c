#include <stdio.h>
#include "error.h"

void error(const char* message)
{
    fprintf(stderr, "[ERROR] %s \n", message);
    exit(1);
}
