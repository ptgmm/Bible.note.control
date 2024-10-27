#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>



int main (int argc, char *argv[]) {

    int check;
    int addcheck;
    int config;
    int bncfolder;
    int commitfolder;
    
    char notefolderpath[256];
    char fullpathconfig[256];
    char addpath[256];
    char folderCheck[256];
    char add[256];
    char foldercommit[256];
    char cwd[PATH_MAX];
    char commit[256];

    const char *username = getenv("USER"); //Getting user name
    const char *pwd = getcwd(cwd, sizeof(cwd));


    snprintf(notefolderpath, sizeof(notefolderpath), "/home/%s/.config/BNC/", username);
    snprintf(foldercommit, sizeof(foldercommit), "/home/%s/.config/BNC/.commit/", username);
    snprintf(fullpathconfig, sizeof(fullpathconfig), "/home/%s/.config/BNC/%s", username, argv[2]); //create full path to .config
    snprintf(addpath, sizeof(addpath), "/home/%s/.config/BNC/%s/%s", username, argv[3], argv[2]); //create full path to .config
    snprintf(folderCheck, sizeof(folderCheck), "/home/%s/.config/", username); //path to .config
    snprintf(commit, sizeof(commit), "/home/%s/.config/BNC/.commit/%s", username, argv[2]);
    snprintf(add, sizeof(add), "%s/%s", pwd, argv[2]);
    

    struct stat statbuf;
    if (stat(folderCheck, &statbuf) != 0) {                         //Check if .config exist
        config = mkdir(folderCheck, 0777);     //If .config doesn't exist it will be created
    } else if (stat(folderCheck, &statbuf) == 0 && (stat(notefolderpath, &statbuf) == 0) && argc > 1 || (stat(notefolderpath, &statbuf) != 0)) {  
        bncfolder = mkdir(notefolderpath, 0777);                                                                                               //Basically checking if the user entered "init" and folder name 
        if (strcmp(argv[1], "init") == 0 && argc == 3){             //
            check = mkdir(fullpathconfig, 0777);                          // 
            if (check == 0) {                                       //
                printf("Directory created\n");                      //
            } else {                                                //
                perror("Unable to create directory");               //
                exit(1);                                            //
            }                                                       //
        } else if (strcmp(argv[1], "add") == 0 && argc == 4){
            addcheck = rename(add, addpath);
            commitfolder = mkdir(foldercommit, 0777);
            if (addcheck == 0){
                 printf("Note added to %s\n", argv[3]);
            } else {
                printf("Unable to add note to %s\n", argv[3]);
             } 
        } else if (strcmp(argv[1], "commit") == 0 && argc == 4){
            FILE *commopen = fopen(commit, "w");
            fprintf(commopen, "%s\n", argv[3]);
            fclose(commopen);
        }

    }
 



    return 0;
}
