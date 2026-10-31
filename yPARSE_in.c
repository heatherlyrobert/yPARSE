/*============================[[    beg-code    ]]============================*/
/*········´ ´·············headers·´ ´·········································*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



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



/*--------- ----------- ----------- ----------- ------------------------------*/
tQUEUE      s_qin;




/*====================------------------------------------====================*/
/*===----                      shared functions                        ----===*/
/*====================------------------------------------====================*/
static void      o___SHARED__________________o (void) {;};

char
yparse_in_defense       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (myPARSE.y_ready != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("must call yPARSE_config () first");
      return rce;
   }
   --rce;  if (s_qin.q_good != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("record processing was not successful");
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse_in_fakeready     (void)
{
   myPARSE.y_ready = 'y';
   s_qin.q_good  = 'y';
   return 0;
}


char
yparse__popable         (void)
{
   if (s_qin.q_head == NULL)  return 0;
   return 1;
}

char yparse_init_in          (void) { return yparse_queue_init  (&s_qin, 'I', "IN"); }
char yPARSE_purge_in         (void) { return yparse_queue_purge (&s_qin);            }
char yPARSE_reset_in         (void) { return yparse_queue_reset (&s_qin);            }
char yparse_good_in          (void) { s_qin.q_good = 'y'; return 0; }

char
yPARSE_ready            (int *a_count)
{
   if (a_count != NULL)  *a_count = s_qin.q_count;
   return s_qin.q_good;
}

char
yPARSE_qin_info          (char r_label [LEN_SHORT], char r_loc [LEN_PATH], void **r_file, int *r_nfull, int *r_nused, int *r_ncurr)
{
   if (r_label != NULL)  ystrlcpy (r_label, s_qin.q_label, LEN_SHORT);
   if (r_loc   != NULL)  ystrlcpy (r_loc  , s_qin.q_loc  , LEN_PATH);
   if (r_file  != NULL)  *r_file  =  s_qin.q_file;
   if (r_nfull != NULL)  *r_nfull =  s_qin.q_nfull;
   if (r_nused != NULL)  *r_nused =  s_qin.q_nused;
   if (r_ncurr != NULL)  *r_ncurr =  s_qin.q_ncurr;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          pop and toss                        ----===*/
/*====================------------------------------------====================*/
static void      o___TOSS____________________o (void) {;};

char
yPARSE_toss             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(check)--------------------------*/
   rc = yparse_queue_dequeue (&s_qin, NULL);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       popping actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___STRINGS_________________o (void) {;};

char
yPARSE_popstr           (char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_item != NULL)  ystrlcpy (a_item, "", LEN_LABEL);
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   DEBUG_YPARSE  yLOG_sint       (rc);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   --rce;  if (a_item == NULL) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(dequeue)------------------------*/
   rc = yparse_queue_dequeue (&s_qin, a_item);
   DEBUG_YPARSE  yLOG_sint    (rc);
   DEBUG_YPARSE  yLOG_snote   (a_item);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_top              (char *a_item)
{
   return yparse_queue_top (&s_qin, a_item);
}

char
yparse_peek_in          (const int a_ref, char *a_item)
{
   return yparse_queue_peek   (&s_qin, a_ref, a_item);
}

char
yparse_peek_verb        (int *a_index, char *a_verb)
{
   if (a_index != NULL)  *a_index = s_qin.q_iverb;
   if (a_verb  != NULL)  ystrlcpy (a_verb, yPARSE_verb (s_qin.q_iverb), LEN_LABEL);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    numerical adjustments                     ----===*/
/*====================------------------------------------====================*/
static void      o___ADJUSTMENTS_____________o (void) {;};

char
yPARSE_adjval           (double a_old, const char *a_item, double *a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_rel       =  '-';
   char        x_entry     [LEN_LABEL];
   char        x_suffix    =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_new != NULL)  *a_new = 0.0;
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_sdouble (a_old);
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   --rce;  if (a_item == NULL) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_item);
   DEBUG_YPARSE  yLOG_spoint  (a_new);
   --rce;  if (a_new   == NULL) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   *a_new = 0.0;
   ystrlcpy (x_entry, a_item, LEN_LABEL);
   x_len  = strlen (x_entry);
   DEBUG_YPARSE  yLOG_snote   (x_entry);
   DEBUG_YPARSE  yLOG_sint    (x_len);
   /*---(check empty)--------------------*/
   --rce;  if (x_len == 0) {
      DEBUG_YPARSE  yLOG_snote   ("empty");
      *a_new   = 0.0;
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rce;
   }
   /*---(zero degree markers)------------*/
   --rce;  if (strncmp (x_entry, "-.--", 4) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("zero degree");
      x_suffix = x_entry [4];
      if (x_suffix == ' ')  x_suffix = x_entry [5];
      switch (x_suffix) {
      case '\0' :
         DEBUG_YPARSE  yLOG_snote   ("implicit relative");
         *a_new  = a_old;
         break;
      case 'r'  :
         DEBUG_YPARSE  yLOG_snote   ("explicit relative");
         *a_new  = a_old;
         break;
      case 'a'  : case '='  :
         DEBUG_YPARSE  yLOG_snote   ("center absolute");
         *a_new  = 0.0;
         break;
      case 'g'  :
         DEBUG_YPARSE  yLOG_snote   ("ground absolute");
         *a_new  = 0.0;
         break;  /* absolute ground     */
      default   :
         DEBUG_YPARSE  yLOG_snote   ("unknown marker");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
         return rce;
      }
   }
   /*---(zero distance markers)----------*/
   else if (strncmp (x_entry, "-.-", 3) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("zero distance");
      x_suffix = x_entry [3];
      if (x_suffix == ' ')  x_suffix = x_entry [4];
      switch (x_suffix) {
      case '\0' :
         DEBUG_YPARSE  yLOG_snote   ("implicit relative");
         *a_new  = a_old;
         break;
      case 'r'  :
         DEBUG_YPARSE  yLOG_snote   ("explicit relative");
         *a_new  = a_old;
         break;
      case 'a'  : case '='  :
         DEBUG_YPARSE  yLOG_snote   ("center absolute");
         *a_new  = 0.0;
         break;
      case 'g'  :
         DEBUG_YPARSE  yLOG_snote   ("ground absolute");
         *a_new  = 0.0;
         break;
      default   :
         DEBUG_YPARSE  yLOG_snote   ("unknown marker");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
         return rce;
      }
   }
   /*---(no-change markers)--------------*/
   else if (x_len == 1 && strchr ("+-=&~.\"", x_entry [0]) != 0) {
      DEBUG_YPARSE  yLOG_snote   ("universal no-change");
      *a_new  = a_old;
   }
   /*---(filling marker)-----------------*/
   else if (x_len == 1 && x_entry [0] == '*') {
      DEBUG_YPARSE  yLOG_snote   ("universal fill passage/section");
      *a_new  = 10001;
   }
   /*---(check normal value)-------------*/
   else {
      DEBUG_YPARSE  yLOG_snote   ("normal entry");
      if (x_len > 1) {
         switch (x_entry [x_len - 1]) {
         case 'r' :
            DEBUG_YPARSE  yLOG_snote   ("explicit relative");
            x_entry [--x_len] = 0;
            x_rel = 'y';
            break;
         case 'a' : case '=' :
            DEBUG_YPARSE  yLOG_snote   ("center absolute");
            x_entry [--x_len] = 0;
            x_rel = '-';
            break;
         case 'g'  :
            DEBUG_YPARSE  yLOG_snote   ("ground absolute");
            x_entry [--x_len] = 0;
            x_rel = '-';
            break;
         default  :
            DEBUG_YPARSE  yLOG_snote   ("implicit absolute");
            x_rel = '-';
            break;
         }
      } else {
         DEBUG_YPARSE  yLOG_snote   ("implicit absolute");
         x_rel = '-';
      }
      *a_new = atof (x_entry);
      DEBUG_YPARSE  yLOG_sint    (*a_new);
      DEBUG_YPARSE  yLOG_sdouble (a_old);
      DEBUG_YPARSE  yLOG_schar   (x_rel);
      if (x_rel == 'y')   *a_new += a_old;
   }
   /*---(output)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (*a_new);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_adjfrom          (double a_old, const char *a_item, double *a_new)
{
   char        rc          =    0;
   double      a_temp      =  0.0;
   rc = yPARSE_adjval (0.0, a_item, &a_temp);
   if (rc < 0)  return rc;
   *a_new = a_old + a_temp;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        numerical pops                        ----===*/
/*====================------------------------------------====================*/
static void      o___NUMBERS_________________o (void) {;};

char
yPARSE_popval           (double a_old, double *a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_rel       =  '-';
   uchar       x_item      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE  yLOG_sdouble (a_old);
   /*---(prepare)------------------------*/
   if (a_new != NULL)  *a_new = 0.0;
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   rc = yparse_queue_dequeue (&s_qin, x_item);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (x_item);
   /*---(cdefense)-----------------------*/
   --rce;  if (x_item [0] == (uchar) '¬') {
      if (a_new != NULL)  *a_new = -666.0;
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   /*---(run)----------------------------*/
   rc = yPARSE_adjval (a_old, x_item, a_new);
   if (rc < 0) return rc;
   /*---(complete)-----------------------*/
   return 0;
}

char
yPARSE_popfrom          (double a_old, double *a_new)
{
   char        rc          =    0;
   double      a_temp      =  0.0;
   rc = yPARSE_popval (0.0, &a_temp);
   if (a_new != NULL)  *a_new = a_old + a_temp;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     trivial simplifiers                      ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLIFIERS_____________o (void) {;};

char
yPARSE_popchar          (char *a_new)
{
   char        rc        =     0;
   uchar       t         [LEN_RECD];
   rc = yPARSE_popstr (t);
   DEBUG_YPARSE yLOG_info    ("t"         , t);
   DEBUG_YPARSE yLOG_point   ("a_new"     , a_new);
   if (a_new != NULL) {
      *a_new = t [0];
      DEBUG_YPARSE yLOG_char    ("*a_new"    , *a_new);
   }
   return rc;
}

char
yPARSE_popint           (int *a_new)
{
   char        rc        =     0;
   double      a         =   0.0;
   rc = yPARSE_popval (0.0, &a);
   DEBUG_YPARSE yLOG_value   ("a"         , a);
   if (a_new != NULL)  *a_new = (int) a;
   return rc;
}

char
yPARSE_poplong          (llong *a_new)
{
   char        rc        =     0;
   double      a         =   0.0;
   rc = yPARSE_popval (0.0, &a);
   if (a_new != NULL)  *a_new = (llong) a;
   return rc;
}

char
yPARSE_popfloat         (float *a_new)
{
   char        rc        =     0;
   double      a         =   0.0;
   rc = yPARSE_popval (0.0, &a);
   if (a_new != NULL)  *a_new = (float) a;
   return rc;
}

char
yPARSE_popdouble        (double *a_new)
{
   char        rc        =     0;
   rc = yPARSE_popval (0.0, a_new);
   return rc;
}

char
yPARSE_popexp           (double *a_new)
{
   char        rc        =     0;
   uchar       t         [LEN_RECD];
   double      a         =   0.0;
   rc = yPARSE_popstr (t);
   DEBUG_YPARSE yLOG_info    ("t"         , t);
   if (a_new != NULL) 
      if (t [0] == (uchar) '¬')  a = -666.0;
      else                       ystrl2real (t, &a, LEN_RECD);
   DEBUG_YPARSE yLOG_double  ("a"         , a);
   if (a_new != NULL)  *a_new = a;
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         full records                         ----===*/
/*====================------------------------------------====================*/
static void      o___RECORDS_________________o (void) {;};


/*====================------------------------------------====================*/
/*===----                       getting lines                          ----===*/
/*====================------------------------------------====================*/
static void      o___PARSING_________________o (void) {;};

char yPARSE_read        (int *r_nfull, int *r_nused, int *r_ncurr, char r_verb [LEN_LABEL]) { return yparse_read (__FUNCTION__, -1    , NULL  , NULL   , r_nfull, r_nused, r_ncurr, r_verb, NULL); }
char yPARSE_read_one    (int *r_nused, char r_verb [LEN_LABEL])                             { return yparse_read (__FUNCTION__, -1    , NULL  , NULL   , NULL   , r_nused, NULL   , r_verb, NULL); }
char yPARSE_load        (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD])                { return yparse_read (__FUNCTION__, -1    , a_recd, NULL   , NULL   , r_nused, r_ncurr, NULL  , NULL); }
char yPARSE_reload      (int *r_nused, int *r_ncurr, int a_line, char a_label [LEN_HUND])   { return yparse_read (__FUNCTION__, a_line, NULL  , a_label, NULL   , r_nused, r_ncurr, NULL  , NULL); }
char yPARSE_hidden      (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD])                { return yparse_read (__FUNCTION__, -1    , a_recd, NULL   , NULL   , r_nused, r_ncurr, NULL  , NULL); }

char yPARSE_inrecd      (char a_recd [LEN_RECD]) { ystrlcpy (a_recd, myPARSE.y_recd, LEN_RECD); }



/*====================------------------------------------====================*/
/*===----                           file control                       ----===*/
/*====================------------------------------------====================*/
static void      o___FILES___________________o (void) {;};

char yPARSE_stdin      (void)                    { return yparse_queue_open  (&s_qin, "stdin"); }
char yPARSE_tmpin      (void)                    { return yparse_queue_open  (&s_qin, "/tmp/yparse.txt"); };
char yPARSE_open_in    (char a_name [LEN_PATH])  { return yparse_queue_open  (&s_qin, a_name);  }
char yPARSE_close_in   (void)                    { return yparse_queue_close (&s_qin);          }

char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
yPARSE_stdin_peek       (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;
   int         x_flags     =    0;
   int         x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(set stdin to non-blocking)------*/
   DEBUG_INPT   yLOG_note    ("make stdin non-blocking");
   x_flags = fcntl (STDIN_FILENO, F_GETFL, 0);
   rc = fcntl (STDIN_FILENO,  F_SETFL, x_flags | O_NONBLOCK);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_value   ("errno"     , errno);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, non-blocking");
   }
   /*---(test stdin for input)-----------*/
   DEBUG_INPT   yLOG_note    ("test for input on stdin");
   x_ch = getc (stdin);
   ungetc (x_ch, stdin);
   /*---(put stdin back to normal)-------*/
   DEBUG_INPT   yLOG_note    ("put stdin back to blocking");
   rc = fcntl  (STDIN_FILENO, F_SETFL, x_flags);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_value   ("errno"     , errno);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, back to blocking");
   }
   /*---(test stdin for input)-----------*/
   DEBUG_INPT   yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch == -1) {
      DEBUG_INPT   yLOG_note    ("no input available");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, input found");
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   variadic interface                         ----===*/
/*====================------------------------------------====================*/
static void      o___VARIADIC________________o (void) {;};

char
yparse_in_variadic      (va_list a_vlist, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   uchar       x_type      =  '-';
   uchar      *x_char      = NULL;
   int        *x_short     = NULL;
   int        *x_int       = NULL;
   llong      *x_long      = NULL;
   float      *x_float     = NULL;
   double     *x_double    = NULL;
   uchar      *x_str       = NULL;
   uchar       x_work      [LEN_RECD] = "";
   int         a           =    0;
   int         c           =    0;
   uchar       t           [LEN_RECD] = "";
   double      x_val       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("n"         , n);
   DEBUG_YPARSE  yLOG_value   ("first"     , s_qin.q_first);
   /*---(check position)-----------------*/
   if (s_qin.q_first == 0)   yPARSE_toss ();
   /*---(walk fields)--------------------*/
   --rce;  for (i = 1; i < n; ++i) {
      x_type = yparse_spec__in_next  ();
      yparse_peek_in (i, &t);
      DEBUG_YPARSE   yLOG_complex ("FIELD"     , "%2d, %c, %2d, %s", i, x_type, s_qin.q_first, t);
      switch (x_type) {
      case 'c' :
         x_char    = (char *) va_arg (a_vlist, int*);
         if (x_char == NULL) {
            DEBUG_YPARSE   yLOG_note    ("char type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popchar   (x_char);
         DEBUG_YPARSE   yLOG_complex ("char"      , "%d, %c, %3d, %p, %d", i, x_type, rc, x_char, *x_char);
         break;
      case 's' :
         x_short   = (short *) va_arg (a_vlist, int*);
         if (x_short == NULL) {
            DEBUG_YPARSE   yLOG_note    ("short type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popint    (&a);
         *x_short = a;
         DEBUG_YPARSE   yLOG_complex ("short"     , "%d, %c, %3d, %p, %d", i, x_type, rc, x_short, *x_short);
         break;
      case 'i' :
         x_int     = va_arg (a_vlist, int*);
         if (x_int == NULL) {
            DEBUG_YPARSE   yLOG_note    ("int type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popint    (x_int);
         DEBUG_YPARSE   yLOG_complex ("int"       , "%d, %c, %3d, %p, %d", i, x_type, rc, x_int, *x_int);
         break;
      case ',' :
         x_int     = va_arg (a_vlist, int*);
         if (x_int == NULL) {
            DEBUG_YPARSE   yLOG_note    ("comma type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popstr    (x_work);
         if (x_work [0] == (uchar) '¬')  x_val = -666.0;
         else  ystrl2comma (x_work, &x_val, LEN_LABEL);
         *x_int = (int) x_val;
         DEBUG_YPARSE   yLOG_complex ("comma"     , "%d, %c, %3d, %s, %lf, %p, %d", i, x_type, rc, x_work, x_val, x_int, *x_int);
         break;
      case 'l' : case 'h' :
         x_long    = va_arg (a_vlist, llong*);
         if (x_long == NULL) {
            DEBUG_YPARSE   yLOG_note    ("long type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_poplong   (x_long);
         DEBUG_YPARSE   yLOG_complex ("long"      , "%d, %c, %3d, %p, %ld", i, x_type, rc, x_long, *x_long);
         break;
      case ';' :
         x_long    = va_arg (a_vlist, llong*);
         if (x_long == NULL) {
            DEBUG_YPARSE   yLOG_note    ("hcomma type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popstr    (x_work);
         if (x_work [0] == (uchar) '¬')  x_val = -666.0;
         else  ystrl2comma (x_work, &x_val, LEN_LABEL);
         *x_long = (llong) x_val;
         DEBUG_YPARSE   yLOG_complex ("hcomma"    , "%d, %c, %3d, %s, %lf, %p, %ld", i, x_type, rc, x_work, x_val, x_long, *x_long);
         break;
      case 'k' : case 'f' :
         x_float   = (float *) va_arg (a_vlist, float*);
         if (x_float == NULL) {
            DEBUG_YPARSE   yLOG_note    ("float type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popfloat  (x_float);
         DEBUG_YPARSE   yLOG_complex ("float"     , "%d, %c, %3d, %p, %f", i, x_type, rc, x_float, (x_float == NULL) ? -666.0 : *x_float);
         break;
      case 'd' : case 't' : 
         x_double  = va_arg (a_vlist, double*);
         if (x_double == NULL) {
            DEBUG_YPARSE   yLOG_note    ("double type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popdouble (x_double);
         DEBUG_YPARSE   yLOG_complex ("double"    , "%d, %c, %3d, %p, %lf", i, x_type, rc, x_double, *x_double);
         break;
      case 'e' : case 'm' : case 'b' :
         x_double  = va_arg (a_vlist, double*);
         if (x_double == NULL) {
            DEBUG_YPARSE   yLOG_note    ("exp type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popexp    (x_double);
         DEBUG_YPARSE   yLOG_complex ("exp"       , "%d, %c, %3d, %p, %lf", i, x_type, rc, x_double, *x_double);
         break;
      case 'C' : case 'S' : case 'T' : case 'U' : case 'L' :
      case '3' : case '4' : case 'D' : case '5' : case '6' :
      case '7' : case '8' : case 'H' : case 'F' : case 'R' : case 'O' :
         DEBUG_YPARSE  yLOG_note    ("string");
         x_str     = (char *) va_arg (a_vlist, int*);
         if (x_str == NULL) {
            DEBUG_YPARSE   yLOG_note    ("string type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popstr    (x_work);
         DEBUG_YPARSE  yLOG_value   ("popstr"    , rc);
         DEBUG_YPARSE  yLOG_info    ("x_work"    , x_work);
         if (x_str != NULL) {
            switch (x_type) {
            case 'C'  : *x_str = x_work [0];                  break;
            case 'S'  : ystrlcpy (x_str, x_work, LEN_SHORT);   break;
            case 'T'  : ystrlcpy (x_str, x_work, LEN_TERSE);   break;
            case 'U'  : ystrlcpy (x_str, x_work, LEN_USER );   break;
            case 'L'  : ystrlcpy (x_str, x_work, LEN_LABEL);   break;
            case '3'  : ystrlcpy (x_str, x_work, LEN_TITLE);   break;
            case '4'  : ystrlcpy (x_str, x_work, 40       );   break;
            case 'D'  : ystrlcpy (x_str, x_work, LEN_DESC );   break;
            case '6'  : ystrlcpy (x_str, x_work, 60       );   break;
            case '7'  : ystrlcpy (x_str, x_work, 70       );   break;
            case '8'  : ystrlcpy (x_str, x_work, 80       );   break;
            case 'H'  : ystrlcpy (x_str, x_work, LEN_HUND );   break;
            case 'F'  : ystrlcpy (x_str, x_work, LEN_FULL );   break;
            case 'R'  : ystrlcpy (x_str, x_work, LEN_RECD );   break;
            case 'O'  : strcpy  (x_str, x_work);              break;
            default   : ystrlcpy  (x_str, x_work, LEN_SHORT);  break;
            }
         }
         DEBUG_YPARSE   yLOG_complex ("string"    , "%d, %c, %3d, %s, %p, %s", i, x_type, rc, x_work, x_str, x_str);
         break;
      case '-' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "skipping field");
         rc = yPARSE_toss   ();
         break;
      default  :
         DEBUG_YPARSE   yLOG_bullet  (i           , "unknown type");
         va_end (a_vlist);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
      if (rc < 0)  {
         va_end (a_vlist);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_in         (char *a_question, int a_num)
{
   /*> return yparse__unit_queue (&s_qin, a_question, a_num);                         <*/
}

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_line       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(preprare)-----------------------*/
   ystrlcpy  (yparse_print, "LINE unit        : question not understood", LEN_STR);
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "stats"    ) == 0) {
      /*> sprintf (yparse_print, "LINE stats     : nline %2d, cline %2d, total %2d", s_qin.q_nused, s_qin.q_ncurr, s_count);   <*/
   }
   /*> else if (strcmp (a_question, "entry"    ) == 0) {                                            <* 
    *>    if (s_count < 1 || a_num >  s_qin.q_nused) {                                              <* 
    *>       sprintf (yparse_print, "LINE entry  %2d : null", a_num);                        <* 
    *>    } else {                                                                                  <* 
    *>       rc = yparse_line__get (a_num, t);                                                       <* 
    *>       if (rc < 0) {                                                                          <* 
    *>          sprintf (yparse_print, "LINE entry  %2d : not reusable", a_num);             <* 
    *>       } else {                                                                               <* 
    *>          sprintf (yparse_print, "LINE entry  %2d : %2d[%s]", a_num, strlen (t), t);   <* 
    *>       }                                                                                      <* 
    *>    }                                                                                         <* 
    *> }                                                                                            <*/
   /*---(complete)----------------------------------------*/
   return yparse_print;
}


char         /*-> add item to end of queue -----------[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_enqueue_in       (char *a_item)
{
   return yparse_queue_enqueue (&s_qin, a_item);
}

