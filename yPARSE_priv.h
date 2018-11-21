/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"




/*===[[ library headers -- standard ]]========================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <stdio.h>               /* CLIBC   standard input/output          */
#include    <stdlib.h>              /* CLIBC   standard general purpose       */
#include    <string.h>              /* CLIBC   standard string handling       */
#include    <sys/stat.h>          /* clibc  standard file handling            */
#include    <unistd.h>            /* clibc  linux/unix standard environment   */



/*===[[ library headers -- heatherly ]]=======================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <yURG.h>                /* CUSTOM heatherly urgent processing     */
#include    <yLOG.h>                /* CUSTOM heatherly program logging       */
#include    <ySTR.h>                /* CUSTOM heatherly string handling       */



/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define   YPARSE_VER_NUM      "0.3c"
#define   YPARSE_VER_TXT      "unit testing is solid, combo in/out through file successful"



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



typedef     struct      cSECTION    tSECTION;
struct cSECTION {
   /*---(master)------------*/
   cchar       abbr;                     
   cchar       label       [LEN_LABEL];
   cchar       specs       [LEN_LABEL];
   /*---(handlers)----------*/
   char        (*writer)   (void);
   char        (*reader)   (void);
   /*---(runtime)-----------*/
   int         try;
   int         bad;
   /*---(descriptive)-------*/
   cchar       column      [LEN_RECD];
   cchar       desc        [LEN_DESC ];
   /*---(done)--------------*/
};



typedef     struct      cNODE       tNODE;
struct      cNODE {
   int         ref;
   char       *item;
   tNODE      *next;
   tNODE      *prev;
};



typedef     struct      cQUEUE      tQUEUE;
struct      cQUEUE {
   /*---(master)------------*/
   char        label       [LEN_LABEL];   /* queue descriptive label          */
   int         iverb;                     /* verb index                       */
   char        good;
   char        hidden;
   /*---(file)--------------*/
   char       *loc;
   FILE       *file;
   int         nline;
   int         cline;
   /*---(record)------------*/
   char        recd        [LEN_RECD];
   int         len;
   /*---(fields)------------*/
   tNODE      *head;
   tNODE      *tail;
   int         first;
   int         count;
   /*---(done)--------------*/
};


char        yparse_open             (tQUEUE *a_queue, char *a_name);
char        yparse_close            (tQUEUE *a_queue);
char        yparse_good_in          (void);
char        yparse_queue_tail       (tQUEUE *a_queue);


char        yparse_verb_find        (tQUEUE *a_queue, char *a_verb);
char        yparse_verb_init        (void);
char*       yparse__unit_verb       (char *a_question, char *a_verb);

char        yparse_init             (tQUEUE *a_queue, char *a_label);
char        yparse_purge            (tQUEUE *a_queue);
char        yparse_enqueue          (tQUEUE *a_queue, char *a_item);
char        yparse_dequeue          (tQUEUE *a_queue, char *a_item);
char        yparse_peek             (tQUEUE *a_queue, const int a_ref, char *a_item);

char        yparse__main            (int *n, int *c, int a_line, char *a_recd, char *a_label);
char        yparse_reusable         (const char a_masked);

/*--------- ----------- ----------- ----------- ------------------------------*/
char        yparse_recd             (char *a_recd);

char        yparse_enqueue_in       (char *a_item);
char        yparse_init_in          (void);
char        yparse_peek_in          (const int a_ref, char *a_item);

char        yparse__popable         (void);

char        yparse_init_out         (void);


/*---(saving)---------------*/
char        yparse_addline          (const int a_line, const char *a_recd);
char        yparse_getline          (const int a_line, char *a_recd);

char        yparse_col_count        (tQUEUE *a_queue);
char        yparse_col_type         (tQUEUE *a_queue);

char        yparse_aggregate        (void);

char*       yparse__unit_queue      (tQUEUE *a_queue, char *a_question, int a_num);
char*       yparse__unit_in         (char *a_question, int a_num);
char*       yparse__unit_out        (char *a_question, int a_num);
char*       yparse__unit_line       (char *a_question, int a_num);
char        yparse__unit_quiet      (void);
char        yparse__unit_loud       (void);
char        yparse__unit_end        (void);
