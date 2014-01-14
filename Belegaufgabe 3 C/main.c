//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
//
//  main.c
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 10.12.13.
//  Copyright (c) 2013 Markus Klemm Enterprises. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "ui.h"
#include "vocalist.h"
#include "persist_vocalist.h"


int main(int argc, const char * argv[])
{
    //Handling flags/options
    int filenamepos = 1;
    int option;
    while ((option = getopt(argc, argv, "h")) != -1) {
#if DEBUG
        printf("%d\n",optind);
#endif
        switch (option) {
            case 'h':
                printf("%s [-h] [filename]\n \n ", argv[0]);
                printf("If filename is not given, it will use %s.dic",argv[0]);
                return EXIT_SUCCESS;
                break;
            default:
                fprintf(stderr, "Usage: %s [-h] [filename]\n Type %s -h for help\n ", argv[0],argv[0]);
                return EXIT_FAILURE;
                break;
        }
    }
    filenamepos = optind; //Filename is at the moment always last option, but maybe filename handling will be changed
    
    //Opening/Creating dictionary
    FILE *fdictionary;
    char *filename;
    if (argv[filenamepos] == NULL) {
        filename = malloc((strlen(argv[0])+strlen(".dic") +1) * sizeof(char));
        if (filename == NULL) {
            perror(NULL);
            return EXIT_FAILURE;
        }
        strcpy(filename, argv[0]); strcat(filename, ".dic");
    }
    else {
        filename = malloc((strlen(argv[filenamepos]) +1) * sizeof(char));
        if (filename == NULL) {
            perror(NULL);
            return EXIT_FAILURE;
        }
        strcpy(filename, argv[filenamepos]);
    }
    
    if ( (fdictionary = fopen(filename, "r+")) == NULL)
    {
        if (errno == ENOENT) {
            if ((fdictionary = fopen(filename, "w+")) == NULL) {
                perror("Could not open nor create a new file, because");
                return EXIT_FAILURE;
            }
        }
        else {
            fprintf(stderr,"%s\n",strerror(errno));
            return EXIT_FAILURE;
        }
    }

    vocalist *vdictionary = newVocaList();
    if (!readDictFromFile(fdictionary, vdictionary)) {
        fprintf(stderr, "Cant parse file\n");
        return EXIT_FAILURE;
    }
    
    
    //Main UI Loop
    UILoop(vdictionary);
    
    //Saveing
    if (!saveDictToFile(fdictionary, vdictionary)) {
        fprintf(stderr, "Cant save file\n");
        return EXIT_FAILURE;
    }
    
    //Cleanup
    if (!fclose(fdictionary))
        perror(NULL); //I wonder if that ever happens
    free(filename);
    
    if (!emptyAndDeleteVocalist(vdictionary))
        fprintf(stderr, "Deleting of Vocalist failed, but OS is cleaning anyway\n");
    
    
    
    return 0;
}
