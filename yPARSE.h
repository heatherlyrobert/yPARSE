/*============================[[    beg-code    ]]============================*/
/*········´ ´···············guard·´ ´·········································*/
#ifndef     YPARSE_guard  
#define     YPARSE_guard            loaded



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



#include    <ySTR_solo.h> 

#define     YPARSE_NOREAD           '-'
#define     YPARSE_READALL          'y'


/*---(myPARSE.verbs)------------------*/
#define     YPARSE_MANUAL           '-'
#define     YPARSE_SIMPLE           's'
#define     YPARSE_AUTO             'y'
#define     YPARSE_VERBS            "-sy"

/*---(myPARSE.reusing)----------------*/
#define     YPARSE_ONETIME          '-'
#define     YPARSE_REUSING          'y'
#define     YPARSE_REUSES           "-y"

/*---(myPARSE.delimiters)-------------*/
#define     YPARSE_FUNCTION         'a'
#define     YPARSE_FUNCTIONS        "§(,)"
#define     YPARSE_FIELD            'f'
#define     YPARSE_FIELDS           "§"
#define     YPARSE_TRADITION        't'
#define     YPARSE_TRADITIONS       ""
#define     YPARSE_DELIMS           "-aft"
/*---(myPARSE.fill)-------------------*/
#define     YPARSE_NOFILL           '-'
#define     YPARSE_FILL             'y'
#define     YPARSE_PACK             'p'
#define     YPARSE_FILLS            "-yp"



typedef long long      llong;
typedef unsigned char  uchar;



/*===[[ yPARSE_base.c ]]======================================================*/
/*········´ ´·············utility·´ ´·········································*/
char       *yPARSE_version          (void);
/*········´ ´··············config·´ ´·········································*/
char        yPARSE_delimiters       (char a_delim, char a_fill);
char        yPARSE_verber           (char a_auto, void *a_verber, char a_reusing);
/*········´ ´·············program·´ ´·········································*/
char        yPARSE_config           (char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill);
char        yPARSE_wrap             (void);
/*········´ ´···········unit-test·´ ´·········································*/
char        yPARSE_force            (void);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ yPARSE_simple.c ]]====================================================*/
/*········´ ´··············config·´ ´·········································*/
char        yPARSE_uconfig          (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH]);
/*········´ ´···········incomming·´ ´·········································*/
char        yPARSE_uread            (int *r_ncurr, char r_verb [LEN_LABEL], char r_recd [LEN_RECD]);
char        yPARSE_uscanf           (char a_verb [LEN_LABEL], uchar *a_format, ...);
/*········´ ´············outgoing·´ ´·········································*/
char        yPARSE_uprintf          (char a_verb [LEN_LABEL], uchar *a_format, ...);
/*········´ ´··············finish·´ ´·········································*/
char        yPARSE_uwrap            (void);
/*········´ ´················DONE·´ ´·········································*/




/*===[[ SIMPLE ]]=========================================*/

/*---(simple interface)-----*/
char        yPARSE_simple           (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH]);
char        yPARSE_close            (void);
/*---(auto-read)------------*/
char        yPARSE_autoread         (uchar *a_in, uchar *a_out, void *a_verber);
/*---(planned)--------------*/
char        yPARSE_planned          (uchar *a_in, uchar *a_out, void *a_verber);
char        yPARSE_header           (char a_full [LEN_PATH], char a_vernum [LEN_TERSE], char a_vertxt [LEN_HUND], char a_oneline [LEN_HUND], char a_content [LEN_DESC], void (*a_additional) (void));
char        yPARSE_vscanf           (uchar *a_verb, ...);
char        yPARSE_vprintf          (int c, uchar *a_verb, ...);
/*---(planned)--------------*/
char        yPARSE_reusing          (uchar *a_in, uchar *a_out, void *a_verber);



/*===[[ yPARSE_reuse.c ]]=====================================================*/
/*········´ ´·····················´ ´·········································*/
char        yPARSE_reuse_set        (void);
/*········´ ´················DONE·´ ´·········································*/






/*---(yPARSE_shared.c)------*/
/*> char        yPARSE_init             (char a_verbs, void *a_verber, char a_reusing);   <*/
char        yPARSE_verber_stub      (int n, uchar *a_verb, char a_exist, void *a_handler);



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yPARSE_write_all        (void);


/*---(yPARSE_line.c)--------*/

char        yPARSE_stdin            (void);
char        yPARSE_tmpin            (void);
char        yPARSE_stdin_peek       (void);
char        yPARSE_open_in          (char a_name [LEN_PATH]);
char        yPARSE_close_in         (void);

char        yPARSE_stdout           (void);
char        yPARSE_tmpout           (void);
char        yPARSE_open_out         (char a_name [LEN_PATH], char a_prog [LEN_PATH]);
char        yPARSE_close_out        (char a_fancy);
char        yPARSE_section          (char *a_title);
char        yPARSE_columns          (int c, char *a_specs, char *a_labels);
char        yPARSE_footer           (int c);


char        yPARSE_write            (int *r_nused, int *r_ncurr);
char        yPARSE_dump             (int *r_nused, int *r_ncurr);

char        yPARSE_read             (int *r_nfull, int *r_nused, int *r_ncurr, char r_verb [LEN_LABEL]);
char        yPARSE_read_one         (int *r_nused, char r_verb [LEN_LABEL]);
char        yPARSE_load             (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD]);
char        yPARSE_reload           (int *r_nused, int *r_ncurr, int a_line, char a_label [LEN_HUND]);
char        yPARSE_hidden           (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD]);

char        yPARSE_read_all         (void);
char        yparse_peek_verb        (int *a_index, char *a_verb);
char        yPARSE_inrecd           (char a_recd [LEN_RECD]);



/*---(yPARSE_queue.c)-------*/
char        yPARSE_purge_in         (void);
char        yPARSE_reset_in         (void);
char        yPARSE_purge_out        (void);
char        yPARSE_reset_out        (void);

/*---(yPARSE_in.c)----------*/
char        yPARSE_ready            (int *a_count);
char        yPARSE_toss             (void);
char        yPARSE_top              (char *a_item);
char        yPARSE_popstr           (char *a_item);
char        yPARSE_adjval           (double a_old, const char *a_entry, double *a_new);
char        yPARSE_adjfrom          (double a_old, const char *a_entry, double *a_new);
char        yPARSE_popval           (double a_old, double *a_new);
char        yPARSE_popfrom          (double a_old, double *a_new);
char        yPARSE_popchar          (char   *a_new);
char        yPARSE_popint           (int    *a_new);
char        yPARSE_popfloat         (float  *a_new);
char        yPARSE_popdouble        (double *a_new);
char        yPARSE_popexp           (double *a_new);

char        yPARSE_qin_info          (char r_label [LEN_SHORT], char r_loc [LEN_PATH], void **r_file, int *r_nfull, int *r_nused, int *r_ncurr);
char        yPARSE_qout_info         (char r_label [LEN_SHORT], char r_loc [LEN_PATH], void **r_file, int *r_nrwote);


/*---(yPARSE_out.c)---------*/
char        yPARSE_pushverb         (char  *a_verb);
char        yPARSE_pushempty        (void);
char        yPARSE_pushval          (double  a_val);
char        yPARSE_pushstr          (uchar  *a_str);
char        yPARSE_pushchar         (uchar   a_val);
char        yPARSE_pushint          (llong   a_val);
char        yPARSE_pushfloat        (double  a_val);
char        yPARSE_spacer           (char a_lines);

char        yPARSE_sect_begin       (uchar *a_verb);
char        yPARSE_sect_break       (int c);
char        yPARSE_sect_end         (int c);


char*       yPARSE_verb             (int a_num);
char        yPARSE_handler          (uchar *a_verb, char *a_specs, void *a_reader);
char        yPARSE_handler_plus     (uchar *a_verb, uchar *a_specs, float a_seq, void *a_reader, void *a_writer, uchar *a_labels);
char        yPARSE_handler_max      (char a_mode, char *a_verb, float a_seq, uchar *a_specs, char a_mask, void *a_reader, void *a_writer, uchar *a_flags, uchar *a_labels, uchar *a_desc);

char        yPARSE_outclear         (void);
char*       yPARSE_outrecd          (void);


/*---(external testing)-----*/
char        yPARSE_push             (char *a_item);



/*===[[ yPARSE_exim.c ]]======================================================*/
/*········´ ´···········interpret·´ ´·········································*/
char        yPARSE_interpret        (char *a_parser, char *r_header, char *r_break, int a_max, char r_control [LEN_RECD], char r_feedback [LEN_RECD]);
/*········´ ´··············export·´ ´·········································*/
char        yPARSE_export_header    (char a_file [LEN_PATH], char a_fullname [LEN_HUND], char a_cmdline [LEN_HUND], char a_oneline [LEN_HUND], char a_vernum [LEN_TERSE], char a_vertxt [LEN_HUND], char a_report [LEN_HUND], char a_parser [LEN_RECD], char c_exim, char c_titles);
char        yPARSE_export_group     (char a_content [LEN_RECD]);
char        yPARSE_export_line      (char a_content [LEN_RECD]);
char        yPARSE_export_footer    (char a_total [LEN_RECD]);
/*········´ ´················DONE·´ ´·········································*/



#endif
/*============================[[    end-code    ]]============================*/
