//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
//
//  ui.c
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 11.01.14.
//  Copyright (c) 2014 Markus Klemm Enterprises. All rights reserved.
//

#include <stdio.h>
#include "ui.h"
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#else
typedef	int	_Bool;
#define	false	0
#define	true	1
#endif

enum language {
    english = 1,
    german = 0
};

void printMenu(enum language menu_lang);
void printsomeemptylines(void); //Can't use posix or >C90 functions or curses, because task is portable code even on windows
/*! @brief Get user input and call acording function
 @returns False if User wants to quit, else true.
 */
_Bool AwtProcCommand(enum language error_lang);

void UILoop(FILE *dic)
{
    printf("German English Dictionary using double linked lists\n Coded by MarkusKlemm.net\n");
    printf("Please select your language: (E)nglish or (D)eutsch ");
    
    enum language menu_lang;
    char raw_buff[32]; fgets(raw_buff, 32, stdin);
    char *buff = strpbrk(raw_buff, "EeDdGg");
    if (buff == NULL) {
        printf("\n Choosing default language: English\n");
        menu_lang = english;
    }
    else {
        char flag[2]; strncpy(flag, buff, 1);
    
        switch (flag[0]) {
            case 'E':
            case 'e':
                menu_lang = english;
                break;
            case 'D':
            case 'd':
            case 'G':
            case 'g':
                menu_lang = german;
                break;
            default:
                menu_lang = english;
                break;
        }
        printsomeemptylines();
        
        _Bool Quit = true;
        
        do {
            printMenu(menu_lang);
            if (AwtProcCommand(menu_lang))
                Quit = false;
            else
                Quit = true;
        } while (!Quit);
    }
}

void printMenu(enum language menu_lang)
{
    if (menu_lang == german) {
        printf("Deutsch Englisch Wörterbuch mithilfe doppelt verketteter Listen\n Programmiert von MarkusKlemm.net\n");
        printf("    (M)enü:\n");
        printf("(I)Füge Übersetzung hinzu\n");
        printf("(S..)uche Übersetzung:\n");
        printf("    (..G)Deutsch\n");
        printf("    (..E)nglisch\n");
        printf("(L..)iste Übersetzungen anhand:\n");
        printf("    (..G)Deutscher Begriffe\n");
        printf("    (..E)nglischer Begriffe\n");
        printf("(D)Lösche Übersetzung\n");
        printf("(Q)Beende und Speichere\n");
    }
    else {
        printf("German English Dictionary using double linked lists\n Coded by MarkusKlemm.net\n");
        printf("    (M)enu:\n");
        printf("(I)nput of a new translation\n");
        printf("(S..)earch translation:\n");
        printf("    (..G)erman\n");
        printf("    (..E)nglish\n");
        printf("(L..)ist translations by:\n");
        printf("    (..G)erman words\n");
        printf("    (..E)nglish words\n");
        printf("(D)elete translation\n");
        printf("(Q)uit and Save\n");
    }
}
_Bool AwtProcCommand(enum language error_lang)
{
    int i;
    for (i=0; i<5; i++) {
        printf("        -> ");
        char rawbuff[32]; fgets(rawbuff, 32, stdin);
        char *buff = strpbrk(rawbuff, "IiSsGgEeLlDdQqMm");
        if (buff == NULL) {
            if (error_lang == german) {
                printf("\a Ungültige Eingabe, Beende nach %d weiteren ungültigen Eingaben\n",4-i);
                printf("Geben Sie \"M\" ein um erneut das Menü aufzurufen.\n");
            }
            else {
                printf("\a Invalid input, exiting after %d further invalid inputs\n",4-i);
                printf("Type \"M\" to see the menu again.\n");
            }
            continue;
        }
        else{
            char flag[3]; strncpy(flag, buff, 2);
            switch (flag[0]) {
                case 'M':
                case 'm':
                    return true;
                    break;
                    
                default:
                    return false;
                    break;
            }
            
        }
    
    }
    return false;
}
void printsomeemptylines(void)
{
    printf("********************\n");
    printf("\n\n\n\n\n\n");
}