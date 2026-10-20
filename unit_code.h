
/*===[[ unit_code.c ]]========================================================*/
/*········´ ´·············endcaps·´ ´·········································*/
char        yparse__unit_quiet      (void);
char        yparse__unit_loud       (void);
char        yparse__unit_end        (void);
/*········´ ´················data·´ ´·········································*/
char       *yparse_config_status    (void);
char        yparse_queue_rando      (tQUEUE *a_queue);
char       *yparse_queue_status     (tQUEUE *a_queue);
/*> char       *yparse_queue_by_cursor  (tQUEUE *a_queue, char a_dir);                <*/
/*········´ ´········mock·support·´ ´·········································*/
char        yparse_mock_clear       (void);
/*········´ ´·········mock·shared·´ ´·········································*/
char        yparse_mock_internal    (void);
char        yparse_mock_external    (char *a_verb, char *a_label, char *a_terse, int *a_int, llong *a_long, float *a_float, double *a_double, char *a_char, double *a_exp, char *a_desc, char *a_str);
char        yparse_mock_handler     (int n, uchar *a_verb, char a_exist, void *a_handler);
char        yparse_mock_verber      (void);
char        yparse_mock_header      (void);
/*········´ ´···········mock·tiny·´ ´·········································*/
char        yparse_mock_rtiny       (int n, uchar *a_verb);
char        yparse__mock__wtiny     (char a_fancy, int n, uchar *a_verb);
char        yparse_mock_wtiny       (int n, uchar *a_verb);
char        yparse_mock_ftiny       (int n, uchar *a_verb);
/*········´ ´··········mock·small·´ ´·········································*/
char        yparse_mock_rsmall      (int n, uchar *a_verb);
char        yparse_mock__wsmall      (char a_fancy, int n, uchar *a_verb);
char        yparse_mock_wsmall      (int n, uchar *a_verb);
char        yparse_mock_fsmall      (int n, uchar *a_verb);
/*········´ ´·········mock·medium·´ ´·········································*/
char        yparse_mock_rmedium     (int n, uchar *a_verb);
char        yparse_mock__wmedium     (char a_fancy, int n, uchar *a_verb);
char        yparse_mock_wmedium     (int n, uchar *a_verb);
char        yparse_mock_fmedium     (int n, uchar *a_verb);
/*········´ ´··········mock·large·´ ´·········································*/
char        yparse_mock_rlarge      (int n, uchar *a_verb);
char        yparse_mock__wlarge      (char a_fancy, int n, uchar *a_verb);
char        yparse_mock_wlarge      (int n, uchar *a_verb);
char        yparse_mock_flarge      (int n, uchar *a_verb);
/*········´ ´···········mock·exim·´ ´·········································*/
char        yparse_mock_writer      (void);
char        yparse_mock_reader      (void);
/*········´ ´·······mock·accessor·´ ´·········································*/
char*       yparse_mock__unit       (char *a_question, int a_num);
/*········´ ´················DONE·´ ´·········································*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*> typedef     struct      cMOCK       tMOCK;                                        <* 
 *> struct cMOCK {                                                                    <* 
 *>    char        recd        [LEN_RECD];                                            <* 
 *>    char        x_ch;                                                              <* 
 *>    int         x_int;                                                             <* 
 *>    char        x_str       [LEN_LABEL];                                           <* 
 *>    float       x_float;                                                           <* 
 *>    char        x_str2      [LEN_LABEL];                                           <* 
 *> };                                                                                <* 
 *> extern      tMOCK       g_mocks     [10];                                         <* 
 *> extern      int         g_nmock;                                                  <*/


