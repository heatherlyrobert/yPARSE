/*============================[[    beg-code    ]]============================*/

#ifndef   YPARSE_HGUARD
#define   YPARSE_HGUARD       loaded



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
#define     YPARSE_AUTO             'y'
#define     YPARSE_NOAUTO           '-'
#define     YPARSE_REUSE            'y'
#define     YPARSE_NOREUSE          '-'


/*===[[ PUBLIC FUNCTIONS ]]===============================*/



/*---(yPARSE_shared.c)------*/
char       *yPARSE_version          (void);
char        yPARSE_init             (char a_verbs, void *a_verber, char a_reusing);
char        yPARSE_wrap             (void);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yPARSE_verb_begin       (char *a_verb);
char        yPARSE_verb_break       (int   a_count);
char        yPARSE_verb_end         (int   a_count);
char        yPARSE_write_all        (void);


/*---(yPARSE_line.c)--------*/

char        yPARSE_stdin            (void);
char        yPARSE_open_in          (char *a_name);
char        yPARSE_close_in         (void);

char        yPARSE_stdout           (void);
char        yPARSE_open_out         (char *a_name, char *a_prog, char *a_desc);
char        yPARSE_close_out        (void);
char        yPARSE_section          (char *a_title);


char        yPARSE_write            (int *n, int *c);
char        yPARSE_dump             (int *n, int *c);
char        yPARSE_read             (int *n, int *c);
char        yPARSE_load             (int *n, int *c, char *a_recd);
char        yPARSE_reload           (int *n, int *c, int a_line, char *a_label);
char        yPARSE_hidden           (int *n, int *c, char *a_recd);
char        yPARSE_read_all         (void);
int         yPARSE_recdno           (void);



/*---(yPARSE_queue.c)-------*/
char        yPARSE_purge_in         (void);
char        yPARSE_purge_out        (void);

/*---(yPARSE_in.c)----------*/
char        yPARSE_ready            (int *a_count);
char        yPARSE_delimiters       (char *a_list);
char        yPARSE_toss             (void);
char        yPARSE_popstr           (char *a_item);
char        yPARSE_adjval           (double a_old, const char *a_entry, double *a_new);
char        yPARSE_adjfrom          (double a_old, const char *a_entry, double *a_new);
char        yPARSE_popval           (double a_old, double *a_new);
char        yPARSE_popfrom          (double a_old, double *a_new);
char        yPARSE_popchar          (char   *a_new);
char        yPARSE_popint           (int    *a_new);
char        yPARSE_popfloat         (float  *a_new);
char        yPARSE_popdouble        (double *a_new);



/*---(yPARSE_out.c)---------*/
char        yPARSE_pushverb         (char  *a_verb);
char        yPARSE_pushempty        (void);
char        yPARSE_pushval          (double  a_val);
char        yPARSE_pushstr          (char   *a_str);
char        yPARSE_pushchar         (char    a_val);
char        yPARSE_pushint          (int     a_val);
char        yPARSE_pushfloat        (float   a_val);
char        yPARSE_pushdouble       (double  a_val);

char*       yPARSE_verb             (int a_num);
char        yPARSE_handler          (char a_mode, char *a_verb, float a_seq, char *a_specs, char a_mask, void *a_reader, void *a_writer, char *a_flags, char *a_labels, char *a_desc);

char        yPARSE_fullwrite        (char *a_verb, ...);
char        yPARSE_fullread         (char *a_verb, ...);
char        yPARSE_outclear         (void);
char*       yPARSE_outrecd          (void);


/*---(external testing)-----*/
char        yPARSE_force            (void);
char        yPARSE_push             (char *a_item);



#endif
/*============================[[    end-code    ]]============================*/
