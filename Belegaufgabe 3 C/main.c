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
    insertVoca(foo, "Rindfleischetikettierungsüberwachungsaufgabenübertragungsgesetz", "Pneumonoultramicroscopicsilicovolcanoconiosis");
    
    
    printf("%s\n", getEnglish(foo, "Katze"));
    
    char *barger = createSortedListGerman(foo);
    printf("%s",barger);
    free(barger);
    
    deleteVoca(foo, "X-Ray", "Röntgen");
    
    char *bareng = createSortedListEnglish(foo);
    printf("%s",bareng);
    free(bareng);
    
    deleteVoca(foo, "House", getGerman(foo, "House"));
    deleteVoca(foo, "Cat", getGerman(foo, "Cat"));
    deleteVoca(foo, "append", getGerman(foo, "append"));
    deleteVoca(foo, "Fence", getGerman(foo, "Fence"));
    deleteVoca(foo, "Rindfleischetikettierungsüberwachungsaufgabenübertragungsgesetz", getGerman(foo, "Rindfleischetikettierungsüberwachungsaufgabenübertragungsgesetz"));
    
    deleteVocaList(foo);
    
    //void UILoop();
    
    return 0;
}

