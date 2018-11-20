/*============================[[    beg-code    ]]============================*/
#ifndef   YPARSE_HGUARD
#define   YPARSE_HGUARD       loaded



/*===[[ PUBLIC FUNCTIONS ]]===============================*/



/*---(yPARSE_shared.c)------*/
char       *yPARSE_version          (void);
char        yPARSE_init             (void *a_verber, char a_reusing);




/*---(yPARSE_line.c)--------*/
char        yPARSE_open             (void);
char        yPARSE_close            (void);
char        yPARSE_infile           (int *n, int *c);
char        yPARSE_stdin            (int *n, int *c);
char        yPARSE_load             (int *n, int *c, char *a_recd);
char        yPARSE_reload           (int *n, int *c, int a_line, char *a_label);
char        yPARSE_hidden           (int *n, int *c, char *a_recd);



/*---(yPARSE_queue.c)-------*/
char        yPARSE_purge_in         (void);
char        yPARSE_purge_out        (void);

/*---(yPARSE_in.c)----------*/

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
char        yPARSE_outfile          (int *n, int *c);
char        yPARSE_stdout           (int *n, int *c);
char        yPARSE_pushverb         (char  *a_verb);
char        yPARSE_pushempty        (void);
char        yPARSE_pushval          (double  a_val);
char        yPARSE_pushstr          (char   *a_str);
char        yPARSE_pushchar         (char    a_val);
char        yPARSE_pushint          (int     a_val);
char        yPARSE_pushfloat        (float   a_val);
char        yPARSE_pushdouble       (double  a_val);

char*       yPARSE_verb             (int a_num);
char        yPARSE_handler          (char a_mode, char *a_verb, char *a_specs, void *a_reader, void *a_writer, char *a_flags, char *a_labels, char *a_desc);



/*---(external testing)-----*/
char        yPARSE_force            (void);
char        yPARSE_push             (char *a_item);



#endif
/*============================[[    end-code    ]]============================*/
