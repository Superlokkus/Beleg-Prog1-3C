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
#include "vocalist.h"
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
#define bufflen 1024

void printMenu(enum language menu_lang);

void printsomeemptylines(void); //Can't use posix or >C90 functions or curses, because task is  to be portable code even on windows
/*! @brief Get user input and call acording function
 @param menu_lang Language for errors and called functions
 @param *dict Dictionary to be used by the called functions
 @returns False if User wants to quit, else true.
 */
_Bool AwtProcCommand(enum language menu_lang,vocalist *dict);

/*! @brief Querys user to type in a new translation and adds it to the given dictionary
 @returns False iff adding fails, otherwise true.
 @param menu_lang Language for query interaction text with user
 @param *dict Dictionary aka vocalist in which the new translation should be added to
 */
_Bool readAndInsertTrans(enum language menu_lang,vocalist *dict);

void printListGer(enum language menu_lang, const vocalist *toprint);
void printListEng(enum language menu_lang, const vocalist *toprint);
void searchGer(enum language menu_lang,const vocalist *tosearchin);
void searchEng(enum language menu_lang,const vocalist *tosearchin);
void searchinseekndestroyGer(enum language menu_lang, vocalist *tokkndin);
void searchinseekndestroyEng(enum language menu_lang, vocalist *tokkndin);




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
    }
    printsomeemptylines();
        
    //Init. of UI done
        
    //Dictionary/Filehandling
    vocalist *dictionary = newVocaList();
    printMenu(menu_lang);
    _Bool Quit = true;
    do { //main UI Loop
        
        if (AwtProcCommand(menu_lang, dictionary))
            Quit = false;
        else
            Quit = true;
        printsomeemptylines();
    } while (!Quit);
    
    if (!deleteVocaList(dictionary))
    {
        //Todo delete remaining vocas and delete again
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
        printf("(D..)Lösche Übersetzung anhand:\n");
        printf("    (..G)Deutscher Begriffe\n");
        printf("    (..E)nglischer Begriffe\n");
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
        printf("(D..)elete translation\n");
        printf("    (..G)erman words\n");
        printf("    (..E)nglish words\n");
        printf("(Q)uit and Save\n");
    }
}
_Bool AwtProcCommand(enum language menu_lang, vocalist *dict)
{
    int i;
    for (i=0; i<5; i++) {
        printf("        -> ");
        char rawbuff[32]; fgets(rawbuff, 32, stdin);
        char *buff = strpbrk(rawbuff, "IiSsGgEeLlDdQqMm");
        if (buff == NULL) {
            if (menu_lang == german) {
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
                    printMenu(menu_lang);
                    return true;
                    break;
                case 'I':
                case 'i':
                    if (!readAndInsertTrans(menu_lang, dict)) {
                        exit(EXIT_FAILURE);
                    }
                    return true;
                    break;
                case 'S':
                case 's':
                    switch (flag[1]) {
                        case 'G':
                        case 'g':
                            searchGer(menu_lang, dict);
                            return true;
                            break;
                        case 'E':
                        case 'e':
                            searchEng(menu_lang, dict);
                            return true;
                            break;
                        default:
                            printf((menu_lang ==german)?"Geben Sie bitte \"SG\" oder \"SE\" ein\n":"Please type either \"SG\" or \"SE\"\n");
                            return true;
                            break;
                    }
                case 'L':
                case 'l':
                    switch (flag[1]) {
                        case 'G':
                        case 'g':
                            printListGer(menu_lang, dict);
                            return true;
                            break;
                        case 'E':
                        case 'e':
                            printListEng(menu_lang, dict);
                            return true;
                            break;
                            
                        default:
                            printf((menu_lang ==german)?"Geben Sie bitte \"LG\" oder \"LE\" ein\n":"Please type either \"LG\" or \"LE\"\n");
                            return true;
                            break;
                    }
                case 'D':
                case 'd':
                    switch (flag[1]) {
                        case 'G':
                        case 'g':
                            searchinseekndestroyGer(menu_lang, dict);
                            return true;
                            break;
                        case 'E':
                        case 'e':
                            searchinseekndestroyEng(menu_lang, dict);
                            return true;
                            break;
                        default:
                            printf((menu_lang ==german)?"Geben Sie bitte \"DG\" oder \"DE\" ein\n":"Please type either \"DG\" or \"DE\"\n");
                            return true;
                            break;
                    }
            
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
    printf("\n\n");
}
_Bool readAndInsertTrans(enum language menu_lang,vocalist *dict)
{
    printf((menu_lang == german)?"Bitte geben Sie das englische Wort ein: ":"Please type in the english word: ");
    char buffEng[bufflen];
    fgets(buffEng, bufflen, stdin);
    printf((menu_lang == german)?"Bitte geben Sie das deutsche Übersetzung ein: ":"Please type in the german translation: ");
    char buffGer[bufflen];
    fgets(buffGer, bufflen, stdin);
    buffEng[strlen(buffEng)-1] = '\0'; buffGer[strlen(buffGer)-1] = '\0';
    if (!insertVoca(dict, buffEng, buffGer)) {
        return false;
    }
    return true;
}
void printListGer(enum language menu_lang, const vocalist *toprint)
{
    char seperator[] = {"   --   "};
    printf((menu_lang == german)?"Deutsch%sEnglisch\n":"German%sEnglish\n" ,seperator);
    char *list = createSortedListGerman(toprint, seperator, "\n");
    printf("%s",list);
    free(list);
}
void printListEng(enum language menu_lang, const vocalist *toprint)
{
    char seperator[] = {"   --   "};
    printf((menu_lang == german)?"Englisch%sDeutsch\n":"English%sGerman\n" ,seperator);
    char *list = createSortedListEnglish(toprint, seperator, "\n");
    printf("%s",list);
    free(list);

}
void searchGer(enum language menu_lang,const vocalist *tosearchin)
{
    printf((menu_lang==german)?"Bitte geben Sie das englische Wort ein, dessen deutsche Entsprechung Sie suchen: ":"Please type in the english word which german translation you're looking for: ");
    char buffeng[bufflen];
    fgets(buffeng, bufflen, stdin); buffeng[strlen(buffeng)-1] = '\0';
    char *gerbuff = getGerman(tosearchin, buffeng);
    if (gerbuff == NULL)
    {
        printf((menu_lang == german)?"Übersetzung leider nicht gefunden\n":"Translation unfortunately not found\n");
        return;
    }
    printf("%s\n",gerbuff);
    
}
void searchEng(enum language menu_lang,const vocalist *tosearchin)
{
    printf((menu_lang==german)?"Bitte geben Sie das deutsche Wort ein, dessen englische Entsprechung Sie suchen: ":"Please type in the german word which english translation you're looking for: ");
    char buffger[bufflen];
    fgets(buffger, bufflen, stdin); buffger[strlen(buffger)-1] = '\0';
    char *engbuff = getEnglish(tosearchin, buffger);
    if (engbuff == NULL)
    {
        printf((menu_lang == german)?"Übersetzung leider nicht gefunden\n":"Translation unfortunately not found\n");
        return;
    }
    printf("%s\n",engbuff);
}
void searchinseekndestroyGer(enum language menu_lang, vocalist *tokkndin)
{
    printf((menu_lang==german)?"Bitte geben Sie das deutsche Wort ein, anhand dessen Sie dieses und die Übersetzung löschen wollen: ":"Please type in the german word which translation and itself you want to delete: ");
    char buffger[bufflen];
    fgets(buffger, bufflen, stdin); buffger[strlen(buffger)-1] = '\0';
    if (getEnglish(tokkndin, buffger) == NULL || !deleteVoca(tokkndin, getEnglish(tokkndin, buffger), buffger))
    {
        printf((menu_lang == german)?"Übersetzung leider nicht gefunden\n":"Translation unfortunately not found\n");
    }
    
}
void searchinseekndestroyEng(enum language menu_lang, vocalist *tokkndin)
{
    printf((menu_lang==german)?"Bitte geben Sie das englische Wort ein, anhand dessen Sie dieses und die Übersetzung löschen wollen: ":"Please type in the english word which translation and itself you want to delete: ");
    char buffeng[bufflen];
    fgets(buffeng, bufflen, stdin); buffeng[strlen(buffeng)-1] = '\0';
    if (getGerman(tokkndin, buffeng) == NULL || !deleteVoca(tokkndin, buffeng, getGerman(tokkndin, buffeng)))
    {
        printf((menu_lang == german)?"Übersetzung leider nicht gefunden\n":"Translation unfortunately not found\n");
    }
}

