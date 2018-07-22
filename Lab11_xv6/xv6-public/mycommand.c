// Three files are included.
// None of which are the usual
// '<stdio.h>' we would use.
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){

    int i;
    for(i = 1; i < argc; i++){
        // Remember what the '1' is as the first argument?
        printf(1, "%s%s", argv[i], i+1 < argc ? " " : "\n");
    }
    // An exit call rather than return statement
    exit();
}
