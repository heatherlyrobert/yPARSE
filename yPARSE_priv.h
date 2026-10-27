/*============================[[    beg-code    ]]============================*/
/*········´ ´···············guard·´ ´·········································*/
#ifndef     YPARSE_priv_guard
#define     YPARSE_priv_guard       loaded



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2018 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might "    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/

#include    "yPARSE.h"



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "fp (file parsing)"
#define     P_SUBJECT   "automated file parsing"
#define     P_PURPOSE   "text file parsing and aggregating library"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "jupiter-terminus (boundaries)"
#define     P_PRONOUNCE "·"
#define     P_HERITAGE  "roman god of boundaries, division, and boundary markers"
#define     P_BRIEFLY   "god to boundaries"
#define     P_IMAGERY   "head and torso of a man, connected to a boundary stone as a base"
#define     P_REASON    "records are the ultimate boundary layouts"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_BASENAME  "yPARSE"
#define     P_HOMEDIR   "/home/system/yPARSE.record_parsing"
#define     P_FULLPATH  "/usr/local/lib64/libyPARSE.so"
#define     P_SUFFIX    "´"
#define     P_CONTENT   "´"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"
/*········· ··········· ´·····························´········································*/
#define     P_DEPSTDC   "stdio,stdlib,string,stdarg,errno,error,time"
#define     P_DEPPOSIX  "unistd,sys/stat,termios"
#define     P_DEPSECURE "pwd,grp"
#define     P_DEPEXTEND "openssl/sha"
#define     P_DEPCORE   "yLOG,yURG,ySTR,yENV"
#define     P_DEPVIKEY  "´"
#define     P_DEPGRAPH  "´"
#define     P_DEPOTHER  "´"
#define     P_DEPSOLO   "yCOLOR_solo"
#define     P_DEPALIEN  "´"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2018-01"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "0.--, preparing for prime-time"
#define     P_VERMINOR  "0.5-, recreate to pull in latest standards and better unit testing"
#define     P_VERNUM    "0.5f"
#define     P_VERTXT    "cleaned_up verb data structure and created much better search/entry function"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
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
#include    <yENV.h>                /* CUSTOM heatherly string handling       */
#include    <yCOLOR_solo.h>
#include    <yDLST_solo.h>





/*---(string length)------------------*/
#define     LEN_RECD    2000
#define     LEN_STR     200
#define     LEN_LABEL   20


typedef struct tm        tTIME;


extern char yparse_print [LEN_RECD];  /* generic/debugging output holder */



typedef  struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(control)-----------*/
   char        y_logger;                        /* yURG debugging handle      */
   char        y_ready;
   /*---(verby)-------------*/
   char        y_verbs;
   char        (*y_verber) (int n, uchar *a_verb, char a_exist, void *a_handler);
   char        y_reusing;                       /* must lines be saved        */
   /*---(delimiters)--------*/
   char        y_deltype;
   char        y_dellist     [LEN_LABEL];
   char        y_fill;
   /*---(delimiters)--------*/
   char        y_recd        [LEN_RECD];
   char        y_verb        [LEN_LABEL];
   char        y_good;
   char        y_nfield;
   /*---(done)--------------*/
};
extern   tACCESSOR  myPARSE;

#define   MAX_NODE      20
typedef     struct      cNODE       tNODE;
struct      cNODE {
   int         n_ref;
   uchar      *n_item;
   tNODE      *n_next;
   tNODE      *n_prev;
};



typedef     struct      cQUEUE      tQUEUE;
struct      cQUEUE {
   /*---(master)------------*/
   char        q_dir;                     /* I=in, O=out                      */
   char        q_label     [LEN_SHORT];   /* queue descriptive label          */
   int         q_iverb;                   /* verb index                       */
   char      (*q_handler)  (int n, char *a_verb);
   /*---(status)------------*/
   char        q_good;
   char        q_hidden;
   /*---(file)--------------*/
   char        q_loc       [LEN_PATH];    /* attached file name               */
   FILE       *q_file;                    /* attached file pointer            */
   /*---(statistics)--------*/
   int         q_tline;                   /* line number in source            */
   int         q_nline;                   /* line number of accepted          */
   int         q_cline;                   /* current line in use              */
   /*---(record)------------*/
   uchar       q_recd      [LEN_RECD];    /* current record text              */
   int         q_len;                     /* current record length            */
   /*---(fields)------------*/
   tNODE      *q_head;
   tNODE      *q_tail;
   /*---(stats)-------------*/
   char        q_count;
   char        q_first;
   char        q_last;
   char        q_curr;
   /*---(done)--------------*/
};
extern     tQUEUE      s_qin;
extern     tQUEUE      s_qout;


typedef     struct      cLINE       tLINE;
struct      cLINE {
   int         l_line;
   char        l_recd        [LEN_RECD];
   int         l_uses;
   tLINE      *l_next;
   tLINE      *l_prev;
};


/*===[[ yPARSE_base.c ]]======================================================*/
/*········´ ´·····················´ ´·········································*/
char*       yPARSE_version          (void);



/*===[[ yPARSE_config.c ]]====================================================*/
/*········´ ´···············logic·´ ´·········································*/
char        yparse_config_clear     (void);
char        yparse_config__delimit  (char a_delim, char a_fill);
char        yparse_config__verber   (char a_auto, void *a_verber, char a_reusing);
char        yparse_config           (char a_1st, char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill);
/*········´ ´·········simplifiers·´ ´·········································*/
char        yPARSE_delimiters       (char a_delim, char a_fill);
char        yPARSE_verber           (char a_auto, void *a_verber, char a_reusing);
char        yPARSE_config           (char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill);
char        yPARSE_reconfig         (char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_queue.c ]]=====================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_queue__wipe      (tQUEUE *a_queue, char a_type);
char        yparse_queue_purge      (tQUEUE *a_queue);
char        yparse_queue_reset      (tQUEUE *a_queue);
char        yparse_queue_init       (tQUEUE *a_queue, char a_dir, char a_label [LEN_SHORT]);
/*········´ ´··············access·´ ´·········································*/
char        yparse_queue__defense   (tQUEUE *a_queue, char a_action);
char        yparse_queue_open       (tQUEUE *a_queue, char a_name [LEN_PATH]);
char        yparse_queue_close      (tQUEUE *a_queue);
/*········´ ´·············fieilds·´ ´·········································*/
char        yparse_queue_enqueue    (tQUEUE *a_queue, char *a_item);
char        yparse_queue_dequeue    (tQUEUE *a_queue, char *a_item);
/*········´ ´··············search·´ ´·········································*/
char        yparse_queue_count      (tQUEUE *a_queue);
char        yparse_queue_by_cursor  (tQUEUE *a_queue, char a_dir, char a_seq, tNODE **r_node, char r_item [LEN_RECD], char d_entry [LEN_RECD]);
char*       yparse_queue_entry      (tQUEUE *a_queue, char a_dir);
char        yparse_queue_top        (tQUEUE *a_queue, char r_item [LEN_RECD]);
char        yparse_queue_peek       (tQUEUE *a_queue, char a_seq, char r_item [LEN_RECD]);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_read.c ]]======================================================*/
/*········´ ´·············parsing·´ ´·········································*/
char        yparse_read_skip        (char a_recd [LEN_RECD]);
char        yparse_read_next        (FILE *a_file, int *b_tline, char r_recd [LEN_RECD], int *r_len);
char        yparse_read_parse       (char a_recd [LEN_RECD], char a_dellist [LEN_TERSE], char a_fill, char *r_nfield);
/*········´ ´············handling·´ ´·········································*/
char        yparse_read_lineno      (int a_line, int *b_nline, int *b_cline, char *r_hidden);
char        yparse_read_rollback    (int a_line);
char        yparse_read_source      (FILE *a_file, int a_line, char a_recd [LEN_RECD], char a_label [LEN_HUND], int *b_tline, char r_recd [LEN_RECD], int *r_len);
char        yparse_read             (char *a_func, int *t, int *n, int *c, int a_line, char *a_recd, char *a_label, char *a_verb);



/*===[[ yPARSE_line.c ]]======================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_line__purge      (void);
char        yparse_line_init        (void);
/*········´ ´··············saving·´ ´·········································*/
char        yparse_line__wipe       (tLINE *a_line);
char        yparse_line_add         (int a_line, char a_recd [LEN_RECD]);
/*········´ ´··············search·´ ´·········································*/
int         yparse_line__count      (void);
char        yparse_line__by_cursor  (char a_action, char a_dir, char a_line, tLINE **r_line, char r_recd [LEN_RECD], int *r_uses, char d_entry [LEN_RECD]);
char       *yparse_line__entry      (char a_dir);
/*········´ ´·············getting·´ ´·········································*/
char        yparse_line__get        (int a_line, char r_recd [LEN_RECD]);
char        yparse_line_existing    (int a_line, char a_label [LEN_HUND], char r_recd [LEN_RECD], int *r_len);
/*········´ ´·············reusing·´ ´·········································*/
char        yPARSE_set_reuse        (void);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_verb.c ]]======================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_verb__wipe       (char n);
char        yparse_verb__purge      (void);
char        yparse_verb_init        (void);
char        yparse_verb_wrap        (void);
/*········´ ´···········searching·´ ´·········································*/
char        yparse_verb_count       (void);
char        yparse_verb_by_name     (char a_verb [LEN_LABEL]);
char        yparse_verb__search     (char a_verb [LEN_LABEL], char a_dir, char a_index, char r_verb [LEN_LABEL], char r_specs [LEN_LABEL], uchar *r_mode, char *r_mask, void **r_reader, void **r_writer, float *r_seq, char *r_done, char r_flags [LEN_TITLE], char r_labels [LEN_RECD], char r_desc [LEN_DESC], char d_entry [LEN_RECD]);
char*       yparse_verb_entry       (char a_verb [LEN_LABEL], char a_dir, char a_index);
/*> char        yparse_verb_data        (char n, char r_verb [LEN_LABEL], char r_specs [LEN_LABEL], uchar *r_mode, char *r_mask, void **r_reader, void **r_writer, float *r_seq, char *r_done, char r_flags [LEN_TITLE], char r_labels [LEN_RECD], char r_desc [LEN_DESC], char d_entry [LEN_RECD]);   <*/
/*········´ ´················DONE·´ ´·········································*/







char        yparse_in_variadic      (va_list a_vlist, int n);
char        yparse_out_variadic     (va_list a_vlist, int n);

char*       yparse_base__unit       (char *a_question, int a_num);


char        yparse_init_types       (void);


char        yparse_good_in          (void);
/*> char        yparse_queue_tail       (tQUEUE *a_queue);                            <*/


char        yparse_verb_find        (tQUEUE *a_queue, char *a_verb);
char        yparse_verb_mask        (int n);
char        yparse_verb_init        (void);
char        yparse__verb_divider    (int a_iverb);
char*       yparse__unit_verb       (char *a_question, char *a_verb, int a_seq);

char        yparse_peek_verb        (int *a_index, char *a_verb);

char        yparse_reusable         (char a_masked);

/*--------- ----------- ----------- ----------- ------------------------------*/

char        yparse_in_fakeready     (void);
char        yparse_enqueue_in       (char *a_item);
char        yparse_init_in          (void);
char        yparse_peek_in          (const int a_ref, char *a_item);

char        yparse__popable         (void);

char        yparse_init_out         (void);


/*---(saving)---------------*/

char        yparse_specs_len        (tQUEUE *a_queue);
char        yparse_specs_next_write (void);
char        yparse_specs_next_read  (void);

int         yparse_field_len        (char a_type);
char        yparse_aggregate        (void);
char        yparse_verb_goodname    (char *a_verb);

char*       yparse__unit_in         (char *a_question, int a_num);
char*       yparse__unit_out        (char *a_question, int a_num);
char*       yparse__unit_line       (char *a_question, int a_num);

char        yparse_in__count        (void);
char        yparse_out__count       (void);
char        yparse_handler_remove   (char *a_verb);



/*===[[ SIMPLE ]]=========================================*/
/*---(testing)--------------*/
char        yparse_autoread_manual  (uchar *a_in, uchar *a_out, void *a_verber);
char        yparse_planned_manual   (uchar *a_in, uchar *a_out, void *a_verber, uchar a_progname, uchar a_progdesc);



char        yparse_fancy__write     (uchar *a_line);
char        yparse_fancy__columns   (uchar *a_specs, uchar *a_labels);
char        yparse_fancy__begin     (uchar *a_verb, uchar *a_specs, uchar *a_labels, uchar *a_desc);
char        yparse_fancy_begin      (int n);
char        yparse_fancy_end        (int c);
char        yparse_fancy_break      (int c);;



/*===[[ yPARSE_exim.c ]]======================================================*/
/*········´ ´···········interpret·´ ´·········································*/
char        yparse__exim_prepare    (char *a_parser, char r_feedback [LEN_RECD]);
char        yparse__exim_clear      (char *r_width, char *r_gap, char *r_dots, char *r_suffix, char r_field [LEN_RECD], char *r_delm, char *r_algn, char *r_form, char *r_decs, char *r_unit, char r_check [LEN_HUND]);
char        yparse__exim_title      (char a_ch, char a_curr [LEN_TERSE], char *b_width, char *b_gap, char *b_dots, char *b_suffix, char b_field [LEN_RECD], char r_check [LEN_HUND]);
char        yparse__exim_suffix     (char a_ch, char a_width, char *b_suffix, char *r_delm, char *r_algn, char *r_form, char *r_decs, char *r_unit, char r_check [LEN_HUND]);
char        yparse__exim_field      (char *b_count, char a_ch, char a_width, char a_gap, char a_field [LEN_FULL], char a_delm, char a_algn, char a_form, char a_decs, char a_unit, char b_header [LEN_RECD], char b_break [LEN_RECD], char b_control [LEN_RECD]);
char        yPARSE_interpret        (char *a_parser, char *r_header, char *r_break, int a_max, char r_control [LEN_RECD], char r_feedback [LEN_RECD]);
/*········´ ´··············export·´ ´·········································*/
/*········´ ´··············import·´ ´·········································*/
/*········´ ´················DONE·´ ´·········································*/



#endif
/*============================[[    end-code    ]]============================*/
