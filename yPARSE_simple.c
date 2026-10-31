/*============================[[    beg-code    ]]============================*/
/*········´ ´·····················´ ´·········································*/
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


static int    s_count = 0;
static int    s_last      =   -1;



/*====================------------------------------------====================*/
/*===----                   generalize functions                       ----===*/
/*====================------------------------------------====================*/
static void      o___GENERALIZED_____________o (void) {;}

static char
yparse_opener           (uchar a_auto, uchar *a_in, uchar *a_out, void *a_verber, char a_read, char a_reuse)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_complex ("args"      , "%p, %p, %p, %c, %c", a_in, a_out, a_verber, a_read, a_reuse);
   /*---(globals)------------------------*/
   s_count = -1;
   s_last  = -1;
   /*---(initialize)---------------------*/
   rc = yPARSE_reconfig (a_auto, a_verber, a_reuse, myPARSE.y_deltype, myPARSE.y_fill);
   DEBUG_YPARSE   yLOG_value   ("getready"  , rc);
   /*---(open)---------------------------*/
   --rce;  if (a_in != NULL && a_out != NULL) {
      if (strcmp (a_in, a_out) == 0) {
         DEBUG_YPARSE   yLOG_note    ("input and output file can not be the same");
         rc = rce;
      }
   }
   /*---(open in)------------------------*/
   if (rc == 1 && a_in  != NULL) {
      DEBUG_YPARSE   yLOG_note    ("openning reading file");
      rc = yPARSE_open_in  (a_in);
      DEBUG_YPARSE   yLOG_value   ("open in"   , rc);
   }
   /*---(open out)-----------------------*/
   if (rc == 1 && a_out != NULL) {
      DEBUG_YPARSE   yLOG_note    ("openning writing file");
      rc = yPARSE_out_open (a_out, NULL);
      DEBUG_YPARSE   yLOG_value   ("open out"  , rc);
   }
   /*---(read all)-----------------------*/
   if (rc == 1 && a_read == YPARSE_READALL) {
      rc = yPARSE_read_all ();
      DEBUG_YPARSE   yLOG_value   ("read all"  , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yPARSE_close            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   yPARSE_close_in  ();
   if (s_count >= 0)  yparse_fancy_end (s_count + 1);
   yPARSE_out_close ('y');
   yPARSE_wrap ();
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_uwrap            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   yPARSE_close_in  ();
   yPARSE_out_close ('-');
   yPARSE_wrap ();
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      simple interface                        ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE__________________o (void) {;}

char
yPARSE_uconfig          (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(configure)----------------------*/
   rc = yPARSE_config (YPARSE_MANUAL, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_NOFILL);
   DEBUG_YPARSE   yLOG_value   ("config"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open files)---------------------*/
   rc = yparse_opener (YPARSE_MANUAL, a_ifile, a_ofile, NULL, YPARSE_NOREAD, YPARSE_ONETIME);
   DEBUG_YPARSE   yLOG_value   ("opener"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return RC_POSITIVE;
}

char
yPARSE_simple           (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH])
{
   return yparse_opener (YPARSE_MANUAL, a_ifile, a_ofile, NULL, YPARSE_NOREAD, YPARSE_ONETIME);
}

char
yPARSE_uread            (int *r_ncurr, char r_verb [LEN_LABEL], char r_recd [LEN_RECD])
{
   return yparse_read (__FUNCTION__, -1    , NULL  , NULL   , NULL   , NULL   , r_ncurr, r_verb, r_recd);
}

char
yPARSE_uprintf          (char a_verb [LEN_LABEL], uchar *a_format, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(handler)------------------------*/
   rc = yPARSE_handler (a_verb, a_format, NULL);
   DEBUG_YPARSE   yLOG_value   ("handler"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verb)---------------------------*/
   rc = yPARSE_pushverb (a_verb);
   DEBUG_YPARSE   yLOG_value   ("verb"      , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(column count)-------------------*/
   n = yparse_spec_len (&s_qout);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   --rce;  if (n < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create variadic)----------------*/
   va_start (x_vlist, a_format);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   /*---(cycle fields)-------------------*/
   rc = yparse_out_variadic (x_vlist, n);
   DEBUG_YPARSE   yLOG_value   ("variadic"  , rc);
   --rce;  if (n < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(destroy variadic)---------------*/
   va_end (x_vlist);
   DEBUG_YPARSE   yLOG_note    ("va_end successful");
   /*---(write)--------------------------*/
   rc = yPARSE_write (NULL, NULL);
   DEBUG_YPARSE   yLOG_value   ("write"     , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_uscanf           (char a_verb [LEN_LABEL], uchar *a_format, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   rc = yPARSE_handler (a_verb, a_format, NULL);
   DEBUG_YPARSE   yLOG_value   ("handler"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(force verb)---------------------*/
   s_qin.q_iverb = yparse_verb_find (NULL, a_verb);
   DEBUG_YPARSE   yLOG_value   ("iverb"     , s_qin.q_iverb);
   --rce;  if (s_qin.q_iverb < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> yPARSE_toss ();                                                                <*/
   /*---(column count)-------------------*/
   n = yparse_spec_len (&s_qin);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   --rce;  if (n < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create variadic)----------------*/
   va_start (x_vlist, a_format);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   /*---(cycle fields)-------------------*/
   rc = yparse_in_variadic (x_vlist, n);
   DEBUG_YPARSE   yLOG_value   ("variadic"  , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(destroy variadic)---------------*/
   va_end (x_vlist);
   DEBUG_YPARSE   yLOG_note    ("va_end successful");
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     auto-read interface                      ----===*/
/*====================------------------------------------====================*/
static void      o___AUTO_READ_______________o (void) {;}

char
yPARSE_autoread         (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_MANUAL, a_in, a_out, a_verber, YPARSE_READALL, YPARSE_ONETIME);
}

char
yparse_autoread_manual  (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_MANUAL, a_in, a_out, a_verber, YPARSE_NOREAD, YPARSE_ONETIME);
}



/*====================------------------------------------====================*/
/*===----                      planned interface                       ----===*/
/*====================------------------------------------====================*/
static void      o___PLANNED_________________o (void) {;}

char
yPARSE_planned          (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_AUTO, a_in, a_out, a_verber, YPARSE_NOREAD , YPARSE_ONETIME);
}

char
yPARSE_handler          (uchar *a_verb, char *a_specs, void *a_reader)
{
   return yPARSE_handler_max ('-', a_verb, 0.0, a_specs, -1, a_reader, NULL, NULL, NULL, NULL);
}

char
yPARSE_handler_plus    (uchar *a_verb, uchar *a_specs, float a_seq, void *a_reader, void *a_writer, uchar *a_labels)
{
   return yPARSE_handler_max ('-', a_verb, a_seq, a_specs, -1, a_reader, a_writer, NULL, a_labels, NULL);
}

char
yPARSE_vscanf           (uchar *a_verb, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =  -10;
   char        n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check on verb)------------------*/
   --rce;  if (s_qin.q_first == 0) {
      s_qin.q_iverb = yparse_verb_find (NULL, a_verb);
      DEBUG_YPARSE   yLOG_value   ("iverb"     , s_qin.q_iverb);
      if (s_qin.q_iverb < 0)  {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yPARSE_toss ();
   }
   /*---(column count)-------------------*/
   n = yparse_spec_len (&s_qin);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   /*---(cycle columns)------------------*/
   va_start (x_vlist, a_verb);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   rc = yparse_in_variadic (x_vlist, n);
   va_end (x_vlist);
   s_qin.q_good = 'R';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yPARSE_vprintf        (int c, uchar *a_verb, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("c"         , c);
   /*---(verb)---------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   if (a_verb != NULL) DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
   rc = yPARSE_pushverb (a_verb);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(fancy)--------------------------*/
   DEBUG_YPARSE   yLOG_point   ("iverb"     , s_qout.q_iverb);
   if (c >= 0 && s_qout.q_iverb >= 0) {
      if (s_last != -1 && s_qout.q_iverb != s_last)   yparse_fancy_end  (s_count + 1);
      if (c == 0)  {
         yparse_fancy_begin (s_qout.q_iverb);
         s_count = -1;
      }
      yparse_fancy_break (c);
   }
   /*---(column count)-------------------*/
   n = yparse_spec_len (&s_qout);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   /*---(call variadic)------------------*/
   va_start (x_vlist, a_verb);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   yparse_out_variadic (x_vlist, n);
   va_end (x_vlist);
   /*---(write)--------------------------*/
   rc = yPARSE_write (NULL, NULL);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(save)---------------------------*/
   if (s_qout.q_iverb != -1) {
      s_last  = s_qout.q_iverb;
      s_count = c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      reusing interface                       ----===*/
/*====================------------------------------------====================*/
static void      o___REUSING_________________o (void) {;}

char
yPARSE_reusing          (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_AUTO, a_in, a_out, a_verber, YPARSE_NOREAD , YPARSE_REUSING);
}
