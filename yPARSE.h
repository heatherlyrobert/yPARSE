/*============================[[    beg-code    ]]============================*/
#ifndef   YPARSE_HGUARD
#define   YPARSE_HGUARD       loaded


/*===[[ PUBLIC FUNCTIONS ]]===============================*/
/*--------- ----------- ----------- ----------- ------------------------------*/
char       *yPARSE_version          (void);
char        yPARSE_init             (void *a_verber, char a_reusing);

/*---(parsing)--------------*/
char        yPARSE_stdin            (void);
/*> char        yPARSE_file             (FILE *a_file);                               <*/
char        yPARSE_load             (char *a_recd);
char        yPARSE_reload           (int a_line, char *a_label);
char        yPARSE_hidden           (char *a_recd);

/*---(pushing)--------------*/
char        yPARSE_purge            (void);

/*---(pop strings)----------*/
char        yPARSE_toss             (void);
char        yPARSE_popstr           (char *a_item);

/*---(pop values)-----------*/
char        yPARSE_adjval           (const float a_old, const char *a_entry, float *a_new);
char        yPARSE_adjfrom          (const float a_old, const char *a_entry, float *a_new);
char        yPARSE_popval           (const float a_old, float *a_new);
char        yPARSE_popfrom          (const float a_old, float *a_new);


#endif
/*============================[[    end-code    ]]============================*/
