/*============================[[    beg-code    ]]============================*/
#ifndef   YPARSE_PGUARD
#define   YPARSE_PGUARD       loaded

#include    "yPARSE.h"



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "fp (file parsing)"
#define     P_SUBJECT   "automated file parsing"
#define     P_PURPOSE   "text file parsing and aggregating library"

#define     P_NAMESAKE  "jupiter-terminus (boundaries)"
#define     P_HERITAGE  "roman god of boundaries, division, and boundary markers"
#define     P_IMAGERY   "head and torso of a man, connected to a boundary stone as a base"
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2018-01"

#define     P_VERMAJOR  "0.--, preparing for prime-time"
#define     P_VERMINOR  "0.3-, support yKINE and arachne"
#define     P_VERNUM    "0.3t"
#define     P_VERTXT    "tiny, scary bug -- used char instead of int for counter in yPARSE_read_all ()"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
/*===[[ END_HEADER ]]=========================================================*/


/*===[[ library headers -- standard ]]========================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <stdio.h>               /* CLIBC   standard input/output          */
#include    <stdlib.h>              /* CLIBC   standard general purpose       */
#include    <string.h>              /* CLIBC   standard string handling       */
#include    <sys/stat.h>            /* CLIBC   standard file handling         */
#include    <unistd.h>              /* CLIBC   linux/unix standard env        */
#include    <stdarg.h>              /* CLIBC   variable argument handling     */
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <fcntl.h>             /* clibc standard file control              */
#include    <termios.h>           /* clibc standard terminal control          */
#include    <errno.h>
#include    <error.h>
#include    <time.h>


/*===[[ library headers -- heatherly ]]=======================================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
#include    <yURG.h>                /* CUSTOM heatherly urgent processing     */
#include    <yLOG.h>                /* CUSTOM heatherly program logging       */
#include    <ySTR.h>                /* CUSTOM heatherly string handling       */





/*---(string length)------------------*/
#define     LEN_RECD    2000
#define     LEN_STR     200
#define     LEN_LABEL   20




extern char yPARSE__unit_answer [ LEN_STR  ];



typedef  struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   char        logger;                          /* yURG debugging handle      */
   char        ready;
   char        verbs;
   char        reusing;                         /* must lines be saved        */
   char        delimiters  [LEN_LABEL];
   char        (*verber) (int n, uchar *a_verb, char a_exist, void *a_handler);
   char        orig        [LEN_RECD];
   char        recd        [LEN_RECD];
   char        verb        [LEN_LABEL];
   char        good;
   int         len;
   int         nfield;
   char        hidden;
};
extern   tACCESSOR  myPARSE;

typedef     struct      cNODE       tNODE;
struct      cNODE {
   int         ref;
   uchar      *item;
   tNODE      *next;
   tNODE      *prev;
};



typedef     struct      cQUEUE      tQUEUE;
struct      cQUEUE {
   /*---(master)------------*/
   char        label       [LEN_LABEL];   /* queue descriptive label          */
   int         iverb;                     /* verb index                       */
   char      (*handler)      (int n, char *a_verb);
   char        good;
   char        hidden;
   /*---(file)--------------*/
   char       *loc;
   FILE       *file;
   int         tline;                           /* line number in source      */
   int         nline;                           /* line number of accepted    */
   int         cline;                           /* current line in use        */
   /*---(record)------------*/
   uchar       recd        [LEN_RECD];
   int         len;
   /*---(fields)------------*/
   tNODE      *head;
   tNODE      *tail;
   int         first;
   int         count;
   /*---(done)--------------*/
};
extern     tQUEUE      s_qin;
extern     tQUEUE      s_qout;

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
typedef     struct      cMOCK       tMOCK;
struct cMOCK {
   char        recd        [LEN_RECD];
   char        x_ch;
   int         x_int;
   char        x_str       [LEN_LABEL];
   float       x_float;
   char        x_str2      [LEN_LABEL];
};
extern      tMOCK       g_mocks     [10];
extern      int         g_nmock;



char        yparse_in_variadic      (va_list a_vlist, int n);
char        yparse_out_variadic     (va_list a_vlist, int n);

char*       yparse_base__unit       (char *a_question, int a_num);


char        yparse_init_types       (void);


char        yparse__check           (char *a_name, char a_mode);
char        yparse_open             (tQUEUE *a_queue, char *a_name);
char        yparse_close            (tQUEUE *a_queue);
char        yparse_good_in          (void);
char        yparse_queue_tail       (tQUEUE *a_queue);


char        yparse_verb_find        (tQUEUE *a_queue, char *a_verb);
char        yparse_verb_mask        (int n);
char        yparse_verb_init        (void);
char        yparse__verb_divider    (int a_iverb);
char*       yparse__unit_verb       (char *a_question, char *a_verb, int a_seq);

char        yparse_init             (tQUEUE *a_queue, char *a_label);
char        yparse_purge            (tQUEUE *a_queue);
char        yparse_enqueue          (tQUEUE *a_queue, char *a_item);
char        yparse_enqueue_full     (tQUEUE *a_queue, char *a_item);
char        yparse_dequeue          (tQUEUE *a_queue, char *a_item);
char        yparse_dequeue_full     (tQUEUE *a_queue, char *a_item);
char        yparse_topqueue         (tQUEUE *a_queue, char *a_item);
char        yparse_peek             (tQUEUE *a_queue, const int a_ref, char *a_item);
char        yparse_peek_verb        (int *a_index, char *a_verb);

char        yparse__main            (int *t, int *n, int *c, int a_line, char *a_recd, char *a_label, char *a_verb);
char        yparse_reusable         (char a_masked);

/*--------- ----------- ----------- ----------- ------------------------------*/
char        yparse_recd             (uchar *a_recd);

char        yparse_in_fakeready     (void);
char        yparse_enqueue_in       (char *a_item);
char        yparse_init_in          (void);
char        yparse_peek_in          (const int a_ref, char *a_item);

char        yparse__popable         (void);

char        yparse_init_out         (void);


/*---(saving)---------------*/
char        yparse_initline         (void);
char        yparse_addline          (const int a_line, const char *a_recd);
char        yparse_getline          (const int a_line, char *a_recd);

char        yparse_specs_len        (tQUEUE *a_queue);
char        yparse_specs_next_write (void);
char        yparse_specs_next_read  (void);

int         yparse_field_len        (char a_type);
char        yparse_aggregate        (void);
char        yparse_verb_goodname    (char *a_verb);

char*       yparse__unit_queue      (tQUEUE *a_queue, char *a_question, int a_num);
char*       yparse__unit_in         (char *a_question, int a_num);
char*       yparse__unit_out        (char *a_question, int a_num);
char*       yparse__unit_line       (char *a_question, int a_num);

char        yparse_mock__clear      (void);
char        yparse_mock__writer     (void);
char        yparse_mock__reader     (void);
char*       yparse_mock__unit       (char *a_question, int a_num);

char        yparse_in__count        (void);
char        yparse_out__count       (void);
char        yparse_handler_remove   (char *a_verb);

char        yparse__unit_verber     (void);
char        yparse__unit_quiet      (void);
char        yparse__unit_loud       (void);
char        yparse__unit_end        (void);


/*===[[ SIMPLE ]]=========================================*/
/*---(testing)--------------*/
char        yparse_autoread_manual  (uchar *a_in, uchar *a_out, void *a_verber);
char        yparse_planned_manual   (uchar *a_in, uchar *a_out, void *a_verber, uchar a_progname, uchar a_progdesc);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yparse__mock_clear      (void);
char        yparse__mock_external   (char *a_verb, char *a_label, char *a_terse, int *a_int, llong *a_long, float *a_float, double *a_double, char *a_char, double *a_exp, char *a_desc, char *a_str);
char        yparse__mock_internal   (void);
char        yparse__mock_verber     (int n, uchar *a_verb, char a_exist, void *a_handler);
char        yparse__mock_rtiny      (int n, uchar *a_verb);
char        yparse__mock_wtiny      (int n, uchar *a_verb);
char        yparse__mock_ftiny      (int n, uchar *a_verb);
char        yparse__mock_rsmall     (int n, uchar *a_verb);
char        yparse__mock_wsmall     (int n, uchar *a_verb);
char        yparse__mock_fsmall     (int n, uchar *a_verb);
char        yparse__mock_rmedium    (int n, uchar *a_verb);
char        yparse__mock_wmedium    (int n, uchar *a_verb);
char        yparse__mock_fmedium    (int n, uchar *a_verb);
char        yparse__mock_rlarge     (int n, uchar *a_verb);
char        yparse__mock_wlarge     (int n, uchar *a_verb);
char        yparse__mock_flarge     (int n, uchar *a_verb);
char        yparse__mock_header     (void);



char        yparse_fancy__write     (uchar *a_line);
char        yparse_fancy__columns   (uchar *a_specs, uchar *a_labels);
char        yparse_fancy__begin     (uchar *a_verb, uchar *a_specs, uchar *a_labels, uchar *a_desc);
char        yparse_fancy_begin      (int n);
char        yparse_fancy_end        (int c);
char        yparse_fancy_break      (int c);;



#endif
/*============================[[    end-code    ]]============================*/
