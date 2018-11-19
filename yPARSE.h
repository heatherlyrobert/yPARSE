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
char        yPARSE_pushint          (char a_type, int    a_val);
char        yPARSE_pushreal         (char a_type, float  a_val);
char        yPARSE_pushstr          (char a_type, char  *a_str);



/*---(external testing)-----*/
char        yPARSE_force            (void);
char        yPARSE_push             (char *a_item);



#endif
/*============================[[    end-code    ]]============================*/
