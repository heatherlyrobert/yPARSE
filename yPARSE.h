/*============================[[    beg-code    ]]============================*/
#ifndef   YPARSE_HGUARD
#define   YPARSE_HGUARD       loaded



/*===[[ PUBLIC FUNCTIONS ]]===============================*/



/*---(yPARSE_shared.c)------*/
char       *yPARSE_version          (void);
char        yPARSE_init             (void *a_verber, char a_reusing);
char        yPARSE_force            (void);



/*---(yPARSE_line.c)--------*/
char        yPARSE_stdin            (int *n, int *c);
char        yPARSE_load             (int *n, int *c, char *a_recd);
char        yPARSE_reload           (int *n, int *c, int a_line, char *a_label);
char        yPARSE_hidden           (int *n, int *c, char *a_recd);



/*---(yPARSE_queue.c)-------*/
char        yPARSE_purge            (void);
char        yPARSE_toss             (void);
char        yPARSE_popstr           (char *a_item);
char        yPARSE_adjval           (float a_old, const char *a_entry, float *a_new);
char        yPARSE_adjfrom          (float a_old, const char *a_entry, float *a_new);
char        yPARSE_popval           (float a_old, float *a_new);
char        yPARSE_popfrom          (float a_old, float *a_new);



/*---(external testing)-----*/
char        yPARSE_push             (char *a_item);



#endif
/*============================[[    end-code    ]]============================*/
