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


int main(int argc, const char * argv[])
{
    vocalist *foo = newVocaList();
    insertVoca(foo, "House", "Haus");
    insertVoca(foo, "Cat", "Katze");
    insertVoca(foo, "X-Ray", "Röntgen");
    insertVoca(foo, "append", "hinzufügen");
    insertVoca(foo, "Fence", "Zaun");
    
    printf("%s\n",getEnglish(foo, "Haus"));
    printf("%s\n",getEnglish(foo, "Katze"));
    printf("%s\n",getGerman(foo, "Cat"));
    printf("%s\n",getGerman(foo, "House"));
    
    printf("%s\n",getSortedListGerman(foo));
    
    //void UILoop();
    
    return 0;
}

