/*============================[[    beg-code    ]]============================*/
#ifndef   YPARSE_HGUARD
#define   YPARSE_HGUARD       loaded



/*===[[ library headers -- standard ]]========================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <stdio.h>               /* CLIBC   standard input/output          */
#include    <stdlib.h>              /* CLIBC   standard general purpose       */
#include    <string.h>              /* CLIBC   standard string handling       */



/*===[[ library headers -- heatherly ]]=======================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <yURG.h>                /* CUSTOM heatherly urgent processing     */
#include    <yLOG.h>                /* CUSTOM heatherly program logging       */
#include    <ySTR.h>                /* CUSTOM heatherly string handling       */



/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define   YPARSE_VER_NUM      "0.1a"
#define   YPARSE_VER_TXT      "convert yKINE record parsing to a libary"



/*---(string length)------------------*/
#define     LEN_RECD    2000
#define     LEN_STR     200
#define     LEN_LABEL   20



/*===[[ PUBLIC FUNCTIONS ]]===============================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
char       *yPARSE_version          (void);

char        yPARSE_addline          (const int a_line, const char *a_recd);
char        yPARSE_getline          (const int a_line, char *a_recd);

/*---(pushing)--------------*/
char        yPARSE_purge            (void);
char        yPARSE_recd             (char *a_recd);
char        yPARSE_reusable         (const int a_line, const char *a_verb);
/*---(pop strings)----------*/
char        yPARSE_toss             (void);
char        yPARSE_popstr           (char *a_item);
char        yPARSE_peek             (const int a_ref, char *a_item);
/*---(pop values)-----------*/
char        yPARSE_adjval           (const float a_old, const char *a_entry, float *a_new);
char        yPARSE_adjfrom          (const float a_old, const char *a_entry, float *a_new);
char        yPARSE_popval           (const float a_old, float *a_new);
char        yPARSE_popfrom          (const float a_old, float *a_new);


#endif
/*============================[[    end-code    ]]============================*/
