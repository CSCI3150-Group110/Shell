#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#include"wildcard.h"

glob_t wildcard(char *arg[]) {
    int i = 0;
    glob_t results;
    const char *name;
  
    name = arg[i++];
    glob(name, GLOB_NOCHECK|GLOB_TILDE, NULL, &results);

    while (arg[i] != NULL) {
        name = arg[i++];
        glob(name, GLOB_NOCHECK |GLOB_TILDE| GLOB_APPEND, NULL, &results);
    }
    return results;
}
