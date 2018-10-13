/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"




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
#define   YPARSE_VER_NUM      "0.2b"
#define   YPARSE_VER_TXT      "create a record reading by-pass to test primatives"



/*---(string length)------------------*/
#define     LEN_RECD    2000
#define     LEN_STR     200
#define     LEN_LABEL   20




extern char yPARSE__unit_answer [ LEN_STR  ];


typedef  struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   char        logger;                          /* yURG debugging handle      */
   char        ready;                           /* flag init/config ready     */
   char        reusing;                         /* must lines be saved        */
   char        (*verber) (void);                /* verb lookup function       */
   int         nline;
   int         cline;
   char        orig        [LEN_RECD];
   char        recd        [LEN_RECD];
   char        verb        [LEN_LABEL];
   char        good;
   int         len;
   int         nfield;
   char        hidden;
};
extern   tACCESSOR  myPARSE;



char        yparse__main            (int *n, int *c, int a_line, char *a_recd, char *a_label);
char        yparse_reusable         (const char a_masked);
char        yparse_peek             (const int a_ref, char *a_item);

/*--------- ----------- ----------- ----------- ------------------------------*/
char        yparse__enqueue         (char *a_item);
char        yparse__dequeue         (char *a_item);
char        yparse_recd             (char *a_recd);

char        yparse__popable         (void);

/*---(saving)---------------*/
char        yparse_addline          (const int a_line, const char *a_recd);
char        yparse_getline          (const int a_line, char *a_recd);



char*       yparse__unit_queue      (char *a_question, int a_num);
char*       yparse__unit_line       (char *a_question, int a_num);
char        yparse__unit_quiet      (void);
char        yparse__unit_loud       (void);
char        yparse__unit_end        (void);
