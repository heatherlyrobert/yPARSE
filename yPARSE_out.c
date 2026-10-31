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



tQUEUE      s_qout;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;};

char yparse_out_init         (void) { return yparse_queue_init  (&s_qout, 'O', "OUT"); }
char yPARSE_out_purge        (void) { return yparse_queue_purge (&s_qout);             }
char yPARSE_out_reset        (void) { return yparse_queue_reset (&s_qout);             }



/*====================------------------------------------====================*/
/*===----                      assigning files                         ----===*/
/*====================------------------------------------====================*/
static void      o___FILE____________________o (void) {;};

char
yPARSE_out_open         (char a_name [LEN_PATH], char a_prog [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_spacer    =  '-';
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_point   ("q_file"    , s_qout.q_file);
   --rce;  if (s_qout.q_file != NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("q_file"    , s_qout.q_file);
   /*---(open file)----------------------*/
   rc = yparse_queue_open  (&s_qout, a_name);
   DEBUG_YPARSE  yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(shebang)------------------------*/
   DEBUG_YPARSE  yLOG_point   ("a_prog"    , a_prog);
   if (a_prog != NULL) {
      DEBUG_YPARSE  yLOG_note    ("header block requested");
      fprintf  (s_qout.q_file, "#!%s\n", a_prog);
      fprintf  (s_qout.q_file, "##   written using %s [%s] %s\n", P_BASENAME, P_VERNUM, P_VERTXT);
      fprintf  (s_qout.q_file, "##   %s\n", P_ONELINE);
      fprintf  (s_qout.q_file, "##\n");
   }
   /*---(make sure written)--------------*/
   fflush   (s_qout.q_file);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yPARSE_out_close  (char a_fancy)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_point   ("q_file"    , s_qout.q_file);
   --rce;  if (s_qout.q_file == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("q_file"    , s_qout.q_file);
   /*---(footer)-------------------------*/
   if (a_fancy == 'y') {
      yPARSE_spacer  (1);
      fprintf (s_qout.q_file, "##\n");
      fprintf (s_qout.q_file, "## end-of-file.  fatto, completare, finito, morto, sepolta, y la signora grassa sta cantando ;)\n");
   }
   /*---(close)--------------------------*/
   rc = yparse_queue_close (&s_qout);
   DEBUG_YPARSE  yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                      shared functions                        ----===*/
/*====================------------------------------------====================*/
static void      o___SHARED__________________o (void) {;};

char
yparse_out__defense     (char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(major defenses)-----------------*/
   DEBUG_YPARSE   yLOG_char    ("y_ready"   , myPARSE.y_ready);
   --rce;  if (myPARSE.y_ready != 'y')  {
      DEBUG_YPARSE   yLOG_note    ("must call yPARSE_config () first");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_char    ("y_verbs"   , myPARSE.y_verbs);
   --rce;  if (myPARSE.y_verbs == YPARSE_SIMPLE) {
      DEBUG_YPARSE   yLOG_note    ("dose not handle YPARSE_SIMPLE");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_char    ("q_good"    , s_qout.q_good);
   --rce;  if (s_qout.q_good == 0 || strchr ("-y", s_qout.q_good) == NULL)  {
      DEBUG_YPARSE   yLOG_note    ("output queue not marked as good/ready");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(file check)---------------------*/
   DEBUG_YPARSE  yLOG_point   ("q_file"    , s_qout.q_file);
   --rce;  if (s_qout.q_file == NULL) {
      DEBUG_YPARSE   yLOG_note    ("output file not assigned");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(push defense)-------------------*/
   DEBUG_YPARSE  yLOG_char    ("a_type"    , a_type);
   DEBUG_YPARSE  yLOG_value   ("q_iverb"   , s_qout.q_iverb);
   --rce;  if (a_type == 'p' && s_qout.q_iverb < 0) {
      DEBUG_YPARSE   yLOG_note    ("verb number not assignt to queue");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_value   ("q_count"   , s_qout.q_count);
   --rce;  if (a_type == 'p' && s_qout.q_count < 1)  {
      DEBUG_YPARSE   yLOG_note    ("verb not pushed onto queue");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    formatting verbs                          ----===*/
/*====================------------------------------------====================*/
static void      o___VERB____________________o (void) {;};

char
yPARSE_pushverb         (char a_verb [LEN_LABEL])
{
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yPARSE_out_purge   ();
   DEBUG_YPARSE  yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   rc = yparse_out__defense ('-');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_point   ("a_verb"    , a_verb);
   --rce;  if (a_verb == NULL || a_verb [0] == '\0') {
      s_qout.q_good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
   /*---(find it)------------------------*/
   n = yparse_verb_find (&s_qout, a_verb);
   DEBUG_YPARSE  yLOG_value   ("n"         , n);
   if (n < 0) {
      s_qout.q_good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, n);
      return n;
   }
   sprintf (t, "%-12.12s"  , a_verb);
   /*---(enqueue)------------------------*/
   rc = yparse_queue_enqueue (&s_qout, t);
   DEBUG_YPARSE  yLOG_value   ("enqueue"   , rc);
   if (rc < 0) {
      s_qout.q_good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(mark good)----------------------*/
   s_qout.q_good = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   variadic driver                            ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;};

char
yparse_out_variadic    (va_list a_vlist, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        x_spec      =  '-';
   char        x_char      =    0;
   int         x_int       =    0;
   llong       x_long      =    0;
   float       x_float     =  0.0;
   double      x_double    =  0.0;
   uchar      *x_str       = NULL;
   int         c           =    0;
   double      x_val       =  0.0;
   int         x_end       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(walk fields)--------------------*/
   DEBUG_YPARSE  yLOG_value   ("n"         , n);
   --rce;  for (i = 1; i < n; ++i) {
      x_spec = yparse_spec__out_next ();
      DEBUG_YPARSE  yLOG_complex ("loop"      , "%2d %c", i, x_spec);
      switch (x_spec) {
      case 'c' :
         x_char    = va_arg (a_vlist, int);
         rc = yPARSE_pushchar   (x_char);
         DEBUG_YPARSE   yLOG_complex ("char"      , "%d, %c, %3d, %c", i, x_spec, rc, x_char);
         break;
      case 's' : case 'i' : case ',' :
         x_int     = va_arg (a_vlist, int);
         rc = yPARSE_pushint    (x_int);
         DEBUG_YPARSE   yLOG_complex ("int"       , "%d, %c, %3d, %ld", i, x_spec, rc, x_int);
         break;
      case 'l' : case 'h' : case ';' :
         x_long    = va_arg (a_vlist, llong);
         rc = yPARSE_pushint    (x_long);
         DEBUG_YPARSE   yLOG_complex ("long"      , "%d, %c, %3d, %ld", i, x_spec, rc, x_long);
         break;
      case 'k' : case 'f' : case 'd' : case 'r' : case 't' : case 'e' :
         x_double  = va_arg (a_vlist, double);
         rc = yPARSE_pushfloat  (x_double);
         DEBUG_YPARSE   yLOG_complex ("double"    , "%d, %c, %3d, %lf", i, x_spec, rc, x_double);
         break;
      case 'C' : case 'S' : case 'T' : case 'U' : case 'L' :
      case '3' : case '4' : case 'D' : case '5' : case '6' :
      case '7' : case '8' : case 'H' : case 'F' : case 'O' :
         x_str     = va_arg (a_vlist, char*);
         rc = yPARSE_pushstr    (x_str);
         DEBUG_YPARSE   yLOG_complex ("string"    , "%d, %c, %3d, %s", i, x_spec, rc, x_str);
         break;
      default  :
         DEBUG_YPARSE   yLOG_complex ("unknown"   , "%d, %c, ---, -", i, x_spec);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
      if (rc < 0)  {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++c;
   }
   /*---(check for end)------------------*/
   DEBUG_YPARSE   yLOG_value   ("c"         , c);
   /*> x_end = va_arg (a_vlist, int);                                                 <* 
    *> DEBUG_YPARSE  yLOG_value   ("x_end"     , x_end);                              <* 
    *> if (x_end != NULL) {                                                           <* 
    *>    DEBUG_YPARSE   yLOG_note    ("trailing argument beyond expected count");    <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);                            <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                       formatting strings                     ----===*/
/*====================------------------------------------====================*/
static void      o___STRING__________________o (void) {;};

char
yparse__push_string     (uchar a_str [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_spec      =  '-';
   uchar       s           [LEN_RECD];
   uchar       t           [LEN_RECD];
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out__defense ('p');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_point   ("a_str"     , a_str);
   --rce;  if (a_str == NULL) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("a_str"     , a_str);
   /*---(prepare field)------------------*/
   x_len = strlen (a_str);
   DEBUG_YPARSE  yLOG_info    ("x_len"     , x_len);
   ystrlcpy  (s, a_str, LEN_RECD);
   ystrlmark (s, ySTR_HEATH, LEN_RECD);
   DEBUG_YPARSE  yLOG_info    ("s"         , s);
   /*---(get the spec)-------------------*/
   x_spec = yparse_spec__out_next ();
   DEBUG_YPARSE   yLOG_char    ("x_spec"    , x_spec);
   rc = yparse_spec_string (x_spec);
   DEBUG_YPARSE   yLOG_value   ("check"     , rc);
   --rce;  if (rc < 0) {
      s_qout.q_good = 'n';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(format)-------------------------*/
   --rce;  switch (x_spec) {
   case  'C' :
      DEBUG_YPARSE   yLOG_snote   ("char");
      if (s [0] == 0)        ystrlcpy (t, "¬"   , 2);
      else                   sprintf (t, "%c"  , s [0]);
      break;
   case  'S' :
      DEBUG_YPARSE   yLOG_snote   ("short string");
      sprintf (t, "%-5.5s"    , s);
      break;
   case  'T' :
      DEBUG_YPARSE   yLOG_snote   ("terse string");
      sprintf (t, "%-10.10s"  , s);
      break;
   case  'U' :
      DEBUG_YPARSE   yLOG_snote   ("user string");
      sprintf (t, "%-12.12s"  , s);
      break;
   case  'L' :
      DEBUG_YPARSE   yLOG_snote   ("label/address string");
      sprintf (t, "%-20.20s"  , s);
      break;
   case  '3' :
      DEBUG_YPARSE   yLOG_snote   ("thirty string");
      sprintf (t, "%-30.30s"  , s);
      break;
   case  '4' :
      DEBUG_YPARSE   yLOG_snote   ("forty string");
      sprintf (t, "%-40.40s"  , s);
      break;
   case  'D' :
      DEBUG_YPARSE   yLOG_snote   ("description string");
      sprintf (t, "%-50.50s"  , s);
      break;
   case  '6' :
      DEBUG_YPARSE   yLOG_snote   ("sixty string");
      sprintf (t, "%-60.60s"  , s);
      break;
   case  '7' :
      DEBUG_YPARSE   yLOG_snote   ("seventy string");
      sprintf (t, "%-70.70s"  , s);
      break;
   case  '8' :
      DEBUG_YPARSE   yLOG_snote   ("eigthy string");
      sprintf (t, "%-80.80s"  , s);
      break;
   case  'H' :
      DEBUG_YPARSE   yLOG_snote   ("hundred string");
      sprintf (t, "%-100.100s", s);
      break;
   case  'F' :
      DEBUG_YPARSE   yLOG_snote   ("full string");
      sprintf (t, "%-200.200s", s);
      break;
   case  'R' :
      DEBUG_YPARSE   yLOG_snote   ("record string");
      sprintf (t, "%-2000.2000s", s);
      break;
   case  'O' :
      DEBUG_YPARSE   yLOG_snote   ("open string");
      sprintf (t, "%s"        , s);
      break;
   default    :
      DEBUG_YPARSE   yLOG_snote   ("unknown");
      s_qout.q_good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(encode)-------------------------*/
   rc = ystrlstore (t, x_len);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(enqueue)------------------------*/
   rc = yparse_queue_enqueue (&s_qout, t);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char yPARSE_pushempty   (void)          { return yparse__push_string  ("");    }
char yPARSE_pushstr     (uchar  *a_str) { return yparse__push_string  (a_str); }



/*====================------------------------------------====================*/
/*===----                       formatting numerics                    ----===*/
/*====================------------------------------------====================*/
static void      o___NUMERIC_________________o (void) {;};

char
yparse__push_numeric    (double a_val)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_spec      =  '-';
   char        t           [LEN_RECD];
   char        s           [LEN_RECD];
   llong       v           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_sdouble (a_val);
   /*---(defense)------------------------*/
   rc = yparse_out__defense ('p');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_point   ("q_file"    , s_qout.q_file);
   DEBUG_YPARSE  yLOG_value   ("q_iverb"   , s_qout.q_iverb);
   DEBUG_YPARSE  yLOG_value   ("q_count"   , s_qout.q_count);
   --rce;  if (s_qout.q_file == NULL || s_qout.q_iverb < 0 || s_qout.q_count < 1)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_spec = yparse_spec__out_next ();
   DEBUG_YPARSE   yLOG_char    ("x_spec"    , x_spec);
   rc = yparse_spec_numeric (x_spec);
   DEBUG_YPARSE   yLOG_value   ("check"     , rc);
   --rce;  if (rc < 0) {
      s_qout.q_good = 'n';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(format)-------------------------*/
   --rce;  switch (x_spec) {
   case  'c' :
      DEBUG_YPARSE   yLOG_snote   ("char");
      if      (a_val < 31)            ystrlcpy (t, "¬", LEN_RECD);
      else if (a_val > 255)           ystrlcpy (t, "¬", LEN_RECD);
      else                            sprintf (t, "%c"       , (uchar) a_val);
      break;
   case  's'  :
      DEBUG_YPARSE   yLOG_snote   ("short");
      if      (a_val < -99)           ystrlcpy (t, "¬¬¬", LEN_RECD);
      else if (a_val > 999)           ystrlcpy (t, "¬¬¬", LEN_RECD);
      else                            sprintf (t, "%3d"      , (int) a_val);
      break;
   case  'i'  :
      DEBUG_YPARSE   yLOG_snote   ("integer");
      if      (a_val < -99999)        ystrlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 999999)        ystrlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%6d"      , (int) a_val);
      break;
   case  'l'  :
      DEBUG_YPARSE   yLOG_snote   ("long");
      if      (a_val < -999999999LL)  ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 9999999999LL)  ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%10ld"    , (llong) a_val);
      break;
   case  'h'  :
      DEBUG_YPARSE   yLOG_snote   ("huge");
      if      (a_val < -999999999999998LL)  ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 9999999999999998LL)  ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else                                  sprintf (t, "%16ld"    , (llong) a_val);
      break;
   case  ','  :
      DEBUG_YPARSE   yLOG_snote   ("comma");
      if      (a_val < -9999999)      ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 99999999)      ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else  {
         ystrl4comma (a_val, s, 0, 'c', '-', LEN_LABEL);
         sprintf (t, "%10.10s", s);
      }
      break;
   case  ';'  :
      DEBUG_YPARSE   yLOG_snote   ("hcomma");
      if      (a_val < -99999999999998LL)  ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 999999999999998LL)  ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else {
         ystrl4comma (a_val, s, 0, 'c', '-', LEN_LABEL);
         sprintf (t, "%19.19s", s);
      }
      break;
   case  'k'  :
      DEBUG_YPARSE   yLOG_snote   ("ykine");
      if      (a_val < -999.9)        ystrlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 9999.9)        ystrlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%6.1lf"   , a_val);
      break;
   case  'f'  :
      DEBUG_YPARSE   yLOG_snote   ("float");
      if      (a_val < -9999.99)      ystrlcpy (t, "¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 99999.99)      ystrlcpy (t, "¬¬¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%8.2lf"   , a_val);
      break;
   case  'd'  :
      DEBUG_YPARSE   yLOG_snote   ("double");
      if      (a_val < -99999.999)    ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 999999.999)    ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%10.3lf"  , a_val);
      break;
   case  't'  :
      DEBUG_YPARSE   yLOG_snote   ("technical");
      if      (a_val < -9999999999.999990)   ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 99999999999.999990)   ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else                                   sprintf (t, "%18.6lf"  , a_val);
      break;
   case  'e'  :
      DEBUG_YPARSE   yLOG_snote   ("small exponent");
      sprintf (t, "%+2.3e"      , a_val);
      break;
   case  'm'  :
      DEBUG_YPARSE   yLOG_snote   ("medium exponent");
      sprintf (t, "%+2.7e"      , a_val);
      break;
   case  'b'  :
      DEBUG_YPARSE   yLOG_snote   ("big exponent");
      sprintf (t, "%+2.12e"    , a_val);
      break;
   default    :
      DEBUG_YPARSE   yLOG_snote   ("unknown");
      s_qout.q_good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(enqueue)------------------------*/
   rc = yparse_queue_enqueue (&s_qout, t);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char yPARSE_pushchar    (uchar   a_val) { return yparse__push_numeric ((double) a_val); }
char yPARSE_pushint     (llong  a_val)  { return yparse__push_numeric ((double) a_val); }
char yPARSE_pushfloat   (double a_val)  { return yparse__push_numeric (a_val); }



/*====================------------------------------------====================*/
/*===----                    field aggregation                         ----===*/
/*====================------------------------------------====================*/
static void      o___AGGREGRATE______________o (void) {;};

char
yparse__popout           (char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_item != NULL)  ystrlcpy (a_item, "", LEN_LABEL);
   /*---(defense)------------------------*/
   rc = yparse_out__defense ('-');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
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
   rc = yparse_queue_dequeue (&s_qout, a_item);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yparse_aggregate        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   char        t           [LEN_RECD];
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out__defense ('-');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0)  {
      s_qout.q_good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_value   ("iverb"     , s_qout.q_iverb);
   --rce;  if (s_qout.q_iverb < 0)  {
      s_qout.q_good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   n = yparse_spec_len (&s_qout);
   DEBUG_YPARSE  yLOG_value   ("cols"      , n);
   DEBUG_YPARSE  yLOG_value   ("count"     , s_qout.q_count);
   --rce;  if (s_qout.q_count != n)  {
      s_qout.q_good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-thru)----------------------*/
   while (yparse__popout (t) == 0) {
      ystrlcat (s_qout.q_recd, t    , LEN_RECD);
      ystrlcat (s_qout.q_recd, " § ", LEN_RECD);
   }
   s_qout.q_len  = strlen (s_qout.q_recd);
   s_qout.q_good = 'C';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     writing output                           ----===*/
/*====================------------------------------------====================*/
static void      o___OUTPUT__________________o (void) {;};

char
yPARSE_write            (int *n, int *c)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out__defense ('-');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(aggregate)----------------------*/
   rc = yparse_aggregate ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   --rce;  if (s_qout.q_file == NULL)  {
      DEBUG_YPARSE   yLOG_note    ("file/stdout not open");
      DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(write)--------------------------*/
   ystrlcpy  (myPARSE.y_recd, s_qout.q_recd, LEN_RECD);
   ystrlcpy  (t, s_qout.q_recd, LEN_RECD);
   ystrldchg (t, G_CHAR_FIELD, G_KEY_FIELD, LEN_RECD);
   if (s_qout.q_file != NULL)   fprintf  (s_qout.q_file, "%s\n", t);
   if (s_qout.q_file != NULL)   fflush   (s_qout.q_file);
   s_qout.q_good = 'W';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   variadic interface                         ----===*/
/*====================------------------------------------====================*/
static void      o___STATISTICS______________o (void) {;};

char yparse_out__count        (void) { return s_qout.q_count; }

char
yPARSE_qout_info         (char r_label [LEN_SHORT], char r_loc [LEN_PATH], void **r_file, int *r_nwrote)
{
   if (r_label  != NULL)  ystrlcpy (r_label, s_qout.q_label, LEN_SHORT);
   if (r_loc    != NULL)  ystrlcpy (r_loc  , s_qout.q_loc  , LEN_PATH);
   if (r_file   != NULL)  *r_file   =  s_qout.q_file;
   if (r_nwrote != NULL)  *r_nwrote =  s_qout.q_nfull;
   return 0;
}

char    yPARSE_outclear         (void) { yPARSE_out_purge   (); return 0; }
char*   yPARSE_outrecd          (void) { ystrltrim (s_qout.q_recd, ySTR_BOTH, LEN_RECD); return s_qout.q_recd; }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_out        (char *a_question, int a_num)
{
   /*> return yparse__unit_queue (&s_qout, a_question, a_num);                        <*/
}

