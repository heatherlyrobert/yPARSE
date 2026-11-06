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
#define     P_SUBJECT   "ansi-text file record processing library"
#define     P_PURPOSE   "text file parsing and aggregating library"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "jupiter-terminalis (boundaries)"
#define     P_PRONOUNCE "·"
#define     P_HERITAGE  "roman god of boundaries, milestones, division, and boundary markers"
#define     P_BRIEFLY   "god to boundaries, milestones, and markers"
#define     P_IMAGERY   "head and torso of a man, connected to a boundary stone as a base"
#define     P_REASON    "records are the ultimate boundary layouts"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
#define     P_FORMAL    P_NAMESAKE " " P_BRIEFLY
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
#define     P_VERNUM    "0.5k"
#define     P_VERTXT    "created and unit-tested new, cleaner output variadic and push functions"
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
   /*> char        y_recd        [LEN_RECD];                                          <*/
   /*> char        y_verb        [LEN_LABEL];                                         <*/
   /*> char        y_good;                                                            <*/
   /*> char        y_nfield;                                                          <*/
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
   /*---(verb)--------------*/
   char        q_iverb;                   /* verb index                       */
   char        q_verb      [LEN_LABEL];   /* current verb                     */
   char        q_spec      [LEN_TITLE];   /* current verb specs               */
   char        q_nspec;                   /* count of verb spec entries       */
   char      (*q_handler)  (int n, char *a_verb);
   /*---(status)------------*/
   char        q_good;
   char        q_hidden;
   /*---(file)--------------*/
   char        q_loc       [LEN_PATH];    /* attached file name               */
   FILE       *q_file;                    /* attached file pointer            */
   /*---(statistics)--------*/
   int         q_nfull;                   /* number of lines read/wrote       */
   int         q_nused;                   /* number of lines used/accepted    */
   int         q_ncurr;                   /* line number of current record    */
   /*---(record)------------*/
   char        q_recd      [LEN_RECD];    /* current record text              */
   int         q_len;                     /* current record length            */
   char        q_nfield;                  /* count of current fields          */
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



typedef     struct      cREUSE      tREUSE;
struct      cREUSE {
   int          l_line;
   char         l_recd        [LEN_RECD];
   int          l_uses;
   tREUSE      *l_next;
   tREUSE      *l_prev;
};


#define     MAX_COLS      29
#define     MAX_VERBS     98 
typedef     struct cVERBS   tVERBS;
struct cVERBS {
   /*---(master)------------*/
   char        v_verb      [LEN_LABEL];     /* verb name as used in files     */
   char        v_specs     [LEN_TITLE];     /* field specifications           */
   char        v_mode;                      /* one char yvikeys mode id       */
   char        v_mask;                      /* field for reload/change        */
   /*---(handlers)----------*/
   int         (*v_reader)   (int n, char a_verb [LEN_LABEL]);  /* auto-processing       */
   int         (*v_writer)   (int n, char a_verb [LEN_LABEL]);  /* auto-processing       */
   float       v_seq;                       /* writing sequence               */
   char        v_done;                      /* written (y/n)                  */
   /*---(descriptive)-------*/
   char        v_flags     [LEN_TITLE];     /* flags for source-program       */
   char        v_labels    [LEN_RECD];      /* field labels for headers       */
   char        v_desc      [LEN_DESC ];     /* long verb description          */
   /*---(done)--------------*/
};
extern tVERBS      G_verbs   [MAX_VERBS];
extern int         G_nverb;
extern int         G_cverb;
extern char       *G_nada;



/*===[[ yPARSE_base.c ]]======================================================*/
/*········´ ´·············utility·´ ´·········································*/
char       *yPARSE_version          (void);
/*········´ ´·············program·´ ´·········································*/
char        yparse_init             (void);
char        yparse_wrap             (char a_type);
char        yPARSE_close_all        (void);
char        yPARSE_wrap             (void);
/*········´ ´··············config·´ ´·········································*/
char        yPARSE_delimiters       (char a_delim, char a_fill);
char        yPARSE_verber           (char a_auto, void *a_verber, char a_reusing);
/*········´ ´···········unit-test·´ ´·········································*/
char        yPARSE_force            (void);
/*········´ ´················DONE·´ ´·········································*/



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



/*===[[ yPARSE_simple.c ]]====================================================*/
/*········´ ´·············support·´ ´·········································*/
char        yparse_opener           (char a_auto, char a_ifile [LEN_PATH], char a_ofile [LEN_PATH], void *a_verber, char a_read, char a_reuse);
/*········´ ´··············config·´ ´·········································*/
char        yPARSE_uconfig          (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH]);
char        yparse_uhandler         (char a_verb [LEN_LABEL], char a_specs [LEN_TITLE]);
/*········´ ´···········incomming·´ ´·········································*/
char        yPARSE_uread            (int *r_nread, char r_verb [LEN_LABEL], char r_recd [LEN_RECD]);
char        yPARSE_uscanf           (char a_verb [LEN_LABEL], char *a_specs, ...);
/*········´ ´············outgoing·´ ´·········································*/
char        yPARSE_uprintf          (char a_verb [LEN_LABEL], char *a_specs, ...);
/*········´ ´··············finish·´ ´·········································*/
char        yPARSE_uwrap            (void);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_enmass.c ]]====================================================*/
/*········´ ´··············config·´ ´·········································*/
char        yPARSE_autoread         (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH], void *a_verber);
char        yPARSE_justread         (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH], void *a_verber);
char        yPARSE_planned          (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH], void *a_verber);
/*········´ ´··················in·´ ´·········································*/
char        yPARSE_read_all         (void);
/*········´ ´·················out·´ ´·········································*/
char        yPARSE_write_all        (void);
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
char        yparse_read__nfield     (char b_recd [LEN_RECD], char a_dellist [LEN_TERSE], char *r_field);
char        yparse_read__parse      (tQUEUE *a_queue, char a_recd [LEN_RECD], char a_dellist [LEN_TERSE], char a_fill);
/*········´ ´············handling·´ ´·········································*/
char        yparse_read__lineno     (int a_line, int *b_nline, int *b_cline, char *r_hidden);
char        yparse_read__rollback   (tQUEUE *a_queue, int a_line);
char        yparse_read__source     (FILE *a_file, int a_line, char a_recd [LEN_RECD], char a_label [LEN_HUND], int *b_tline, char r_recd [LEN_RECD], int *r_len);
char        yparse_read             (char a_func [LEN_TITLE], tQUEUE *a_queue, int a_line, char a_recd [LEN_RECD], char a_label [LEN_HUND], int *r_nread, int *r_nused, int *r_ncurr, char r_verb [LEN_LABEL], char r_recd [LEN_RECD]);
/*········´ ´·········simplifier·´ ´·········································*/
char        yPARSE_read             (int *r_nfull, int *r_nused, int *r_ncurr, char r_verb [LEN_LABEL]);
char        yPARSE_read_one         (int *r_nused, char r_verb [LEN_LABEL]);
char        yPARSE_load             (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD]);
char        yPARSE_reload           (int *r_nused, int *r_ncurr, int a_line, char a_label [LEN_HUND]);
char        yPARSE_hidden           (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD]);
char        yPARSE_inrecd           (char r_recd [LEN_RECD]);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_reuse.c ]]=====================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_reuse__purge     (void);
char        yparse_reuse_init       (void);
char        yparse_reuse_wrap       (void);
/*········´ ´··············saving·´ ´·········································*/
char        yparse_reuse__wipe      (tREUSE *a_line);
char        yparse_reuse_add        (int a_line, char a_recd [LEN_RECD]);
/*········´ ´··············search·´ ´·········································*/
int         yparse_reuse__count     (void);
char        yparse_reuse__by_cursor (char a_action, char a_dir, char a_line, tREUSE **r_line, char r_recd [LEN_RECD], int *r_uses, char d_entry [LEN_RECD]);
char       *yparse_reuse__entry     (char a_dir);
/*········´ ´·············getting·´ ´·········································*/
char        yparse_reuse__get       (int a_line, char r_recd [LEN_RECD]);
char        yparse_reuse_existing   (int a_line, char a_label [LEN_HUND], char r_recd [LEN_RECD], int *r_len);
/*········´ ´·············reusing·´ ´·········································*/
char        yPARSE_reuse_set        (void);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_spec.c ]]======================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_spec_init        (void);
char        yparse_spec_wrap        (void);
/*········´ ´··············search·´ ´·········································*/
char        yparse_spec__search     (char a_func [LEN_TITLE], char a_spec, char a_dir, char a_index, char *r_spec, char r_name [LEN_LABEL], char *r_cat, char r_desc [LEN_LABEL], char *r_varg, char *r_save, char *r_size, char r_format [LEN_LABEL], char *r_ranged, llong *r_lmin, llong *r_lmax, double *r_dmin, double *r_dmax, char r_mask [LEN_TITLE], char d_entry [LEN_RECD]);
char*       yparse_spec_entry       (char a_spec, char a_dir, char a_index);
int         yparse_spec_size        (char a_spec);
/*········´ ´············checking·´ ´·········································*/
char        yparse_spec_string      (char a_spec);
char        yparse_spec_numeric     (char a_spec);
char        yparse_spec__in_next    (void);
char        yparse_spec_len         (tQUEUE *a_queue);
/*········´ ´···············input·´ ´·········································*/
char        yparse_spec__in_next    (void);
/*········´ ´··············output·´ ´·········································*/
char        yparse_spec__out_next   (void);
char        yparse_spec__out_int    (char a_spec, llong a_val, char r_out [LEN_RECD]);
char        yparse_spec__out_float  (char a_spec, double a_val, char r_out [LEN_RECD]);
char        yparse_spec__out_string (char a_spec, char a_string [LEN_RECD], char r_out [LEN_RECD]);
char        yparse_spec_output      (tQUEUE *a_queue, va_list a_vlist, char a_speclist [LEN_LABEL]);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_out.c ]]=======================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yPARSE_handler_max      (char a_verb [LEN_LABEL], char a_specs [LEN_TITLE], char a_mode, char a_mask, void *a_reader, void *a_writer, float a_seq, char a_flags [LEN_TITLE], char a_labels [LEN_RECD], char a_desc [LEN_DESC]);
char        yPARSE_handler          (char a_verb [LEN_LABEL], char a_specs [LEN_TITLE], void *a_reader);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_out.c ]]=======================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_out_init         (void);
char        yPARSE_out_purge        (void);
char        yPARSE_out_reset        (void);
char        yparse_out_wrap         (void);
/*········´ ´················file·´ ´·········································*/
char        yPARSE_out_open         (char a_name [LEN_PATH], char a_prog [LEN_PATH]);
char        yPARSE_out_close        (char a_fancy);
/*········´ ´··············shared·´ ´·········································*/
char        yparse_out__defense     (char a_type);
/*········´ ´··············string·´ ´·········································*/
char        yparse__push_string     (char a_func [LEN_TITLE], char a_str [LEN_RECD]);
char        yPARSE_pushempty        (void);
char        yPARSE_pushstr          (char a_str [LEN_RECD]);
/*········´ ´·············numeric·´ ´·········································*/
char        yparse__push_numeric    (char a_func [LEN_TITLE], double a_val);
char        yPARSE_pushchar         (uchar  a_val);
char        yPARSE_pushint          (llong  a_val);
char        yPARSE_pushfloat        (double a_val);
/*········´ ´···········aggregate·´ ´·········································*/
/*········´ ´··············output·´ ´·········································*/
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_in.c ]]========================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_in_init          (void);
char        yPARSE_in_purge         (void);
char        yPARSE_in_reset         (void);
char        yparse_in_wrap          (void);



/*===[[ yPARSE_verb.c ]]======================================================*/
/*········´ ´·············program·´ ´·········································*/
char        yparse_verb__wipe       (char n);
char        yparse_verb__purge      (void);
char        yparse_verb_init        (void);
char        yparse_verb_wrap        (void);
/*········´ ´···········searching·´ ´·········································*/
char        yparse_verb_count       (void);
/*> char        yparse_verb_by_name     (char a_verb [LEN_LABEL]);                    <*/
char        yparse_verb__search     (char a_verb [LEN_LABEL], char a_dir, char a_index, char r_verb [LEN_LABEL], char r_specs [LEN_LABEL], uchar *r_mode, char *r_mask, void **r_reader, void **r_writer, float *r_seq, char *r_done, char r_flags [LEN_TITLE], char r_labels [LEN_RECD], char r_desc [LEN_DESC], char d_entry [LEN_RECD]);
char*       yparse_verb_entry       (char a_verb [LEN_LABEL], char a_dir, char a_index);
char        yparse_verb_find        (tQUEUE *a_queue, char a_verb [LEN_LABEL]);
/*········´ ´············handlers·´ ´·········································*/
char*       yPARSE_verb             (int a_num);
char        yPARSE_handler_max      (char a_verb [LEN_LABEL], char a_specs [LEN_TITLE], char a_mode, char a_mask, void *a_reader, void *a_writer, float a_seq, char a_flags [LEN_TITLE], char a_labels [LEN_RECD], char a_desc [LEN_DESC]);
char        yPARSE_handler_plus     (char a_verb [LEN_LABEL], char a_specs [LEN_TITLE], void *a_reader, void *a_writer, float a_seq, char a_labels [LEN_RECD]);
char        yPARSE_handler_min      (char a_verb [LEN_LABEL], char a_specs [LEN_TITLE], void *a_reader, void *a_writer);
char        yPARSE_handler          (char a_verb [LEN_LABEL], char a_specs [LEN_TITLE], void *a_reader);
/*········´ ´················DONE·´ ´·········································*/







char        yparse_in_variadic      (va_list a_vlist, int n);
char        yparse_out_variadic     (va_list a_vlist, int n);

char*       yparse_base__unit       (char *a_question, int a_num);




char        yparse_good_in          (void);
/*> char        yparse_queue_tail       (tQUEUE *a_queue);                            <*/


char        yparse_verb_mask        (int n);
char        yparse__verb_divider    (int a_iverb);
char*       yparse__unit_verb       (char *a_question, char *a_verb, int a_seq);

char        yparse_peek_verb        (int *a_index, char *a_verb);

char        yparse_reusable         (char a_masked);

/*--------- ----------- ----------- ----------- ------------------------------*/

char        yparse_in_fakeready     (void);
char        yparse_enqueue_in       (char *a_item);
char        yparse_peek_in          (const int a_ref, char *a_item);

char        yparse__popable         (void);



/*---(saving)---------------*/


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



char        yparse_fancy__write     (char a_line [LEN_RECD]);
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
