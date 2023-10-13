#include "samples/prototypes.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>


int main(int argc, char *argv[], const char *envp[]) {
    //use the path the returned by get_env_value
    const char *searchpath = get_env_value(envp, "MYPATH");
    //UNLESS its NULL in which case just use PATH instead of MYPATH
    if (searchpath == NULL) {
        searchpath = get_env_value(envp, "PATH");
    }

    //if there are no arguments provided
    if (argc == 1) {
        char dir[PATH_MAX];
        const char *remaining = searchpath;

        //just print out all of the search paths
        printf("Directories in search path:\n");
        while (scan_token(&remaining, ":", dir, sizeof(dir))) {
            printf("%s\n", dir);
        }

    //if there are arguments passed in...
    } else {
        char buf[PATH_MAX];    //make a buffer that can take the tokenized searchpath

        //for each argument passed in
        for (int i = 1; i < argc; i++) {
            const char *paths = searchpath;    //represents the list of paths deilimited by ":"
            //tokenize the paths to get one singular path
            while (scan_token(&paths, ":", buf, sizeof(buf))) {
                //concatenate the path with "/ARGUMENT"
                char *filepath = strcat(buf, "/");
                filepath = strcat(filepath, argv[i]);
                
                //if we find a readable, executable path then we print it out
                if(access(filepath, R_OK | X_OK) == 0) {
                    printf("%s\n", filepath);
                    paths = strrchr(paths, 0);  //point to the end of paths to get out of the loop
                }
            }
        }
    }
    
    return 0;
}
