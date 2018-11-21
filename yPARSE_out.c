/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



static      tQUEUE      s_qout;



/*
 * char
 *     c   = char            ( 1 char)    1.0
 *
 * int
 *     s   = short           ( 3 char)    3.0
 *     i   = moderate int    ( 5 char)    5.0
 *     l   = longer          (10 char)   10.0
 *
 * float
 *     k   = kine            ( 6 char)    6.1_
 *     f   = float           ( 6 char)    8.2
 *
 * double
 *     d   = double          (10 char)   10.3
 *     e   = exponent        (10 char)   any
 *     t   = technical       (20 char)   any
 *     r   = real            (12 char)   any
 *
 * string
 *     C   = char            (  1 char)
 *     S   = short           (  5 char)
 *     T   = terse           ( 10 char)
 *     A   = address         ( 12 char)
 *     L   = label/name      ( 20 char)
 *     D   = description     ( 60 char)
 *     U   = unit test       ( 70 char)
 *     F   = full            (100 char)
 *     O   = open            (no trunc)
 *
 *
 */



/*====================------------------------------------====================*/
/*===----                      shared functions                        ----===*/
/*====================------------------------------------====================*/
static void      o___SHARED__________________o (void) {;};

char
yparse_out_defense      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("must call yPARSE_init () first");
      return rce;
   }
   --rce;  if (strchr ("-y", s_qout.good) == NULL)  {
      DEBUG_YPARSE   yLOG_snote   ("output record has failed");
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char yparse_init_out         (void) { return yparse_init  (&s_qout, "OUT"); }
char yPARSE_purge_out        (void) { return yparse_purge (&s_qout);        }



/*====================------------------------------------====================*/
/*===----                       formatting functions                   ----===*/
/*====================------------------------------------====================*/
static void      o___FORMAT__________________o (void) {;};

char
yparse__push_string     (char *a_str)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   char        t           [LEN_RECD];
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_str);
   --rce;  if (a_str == NULL) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_str);
   /*---(prepare)------------------------*/
   x_type = yparse_col_by_count (&s_qout);
   /*---(format)-------------------------*/
   --rce;  switch (x_type) {
   case  'c' :
      DEBUG_OUTP   yLOG_note    ("char");
      sprintf (t, "%c"       , a_str [0]);
      break;
   case  'S' :
      DEBUG_OUTP   yLOG_note    ("short string");
      sprintf (t, "%-5.5s"    , a_str);
      break;
   case  'T' :
      DEBUG_OUTP   yLOG_note    ("terse string");
      sprintf (t, "%-10.10s"  , a_str);
      break;
   case  'A' :
      DEBUG_OUTP   yLOG_note    ("address string");
      sprintf (t, "%-12.12s"  , a_str);
      break;
   case  'L' :
      DEBUG_OUTP   yLOG_note    ("label/name string");
      sprintf (t, "%-20.20s"  , a_str);
      break;
   case  'D' :
      DEBUG_OUTP   yLOG_note    ("description string");
      sprintf (t, "%-70.70s"  , a_str);
      break;
   case  'H' :
      DEBUG_OUTP   yLOG_note    ("hundred string");
      sprintf (t, "%-100.100s", a_str);
      break;
   case  'O' :
      DEBUG_OUTP   yLOG_note    ("open string");
      sprintf (t, "%s"        , a_str);
      break;
   default    :
      DEBUG_OUTP   yLOG_note    ("unknown");
      s_qout.good = 'n';
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(encode)-------------------------*/
   rc = strlstore (t, x_len);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(enqueue)------------------------*/
   rc = yparse_enqueue (&s_qout, t);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse__push_numeric    (double a_val)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(prepare)------------------------*/
   x_type = yparse_col_by_count (&s_qout);
   /*---(format)-------------------------*/
   --rce;  switch (x_type) {
   case  'c' :
      DEBUG_OUTP   yLOG_note    ("char");
      sprintf (t, "%c"       , (char) a_val);
      break;
   case  's'  :
      DEBUG_OUTP   yLOG_note    ("short");
      sprintf (t, "%3d"      , (int)  a_val);
      break;
   case  'i'  :
      DEBUG_OUTP   yLOG_note    ("integer");
      sprintf (t, "%6d"      , (int)  a_val);
      break;
   case  'l'  :
      DEBUG_OUTP   yLOG_note    ("long");
      sprintf (t, "%10d"     , (int)  a_val);
      break;
   case  'k'  :
      DEBUG_OUTP   yLOG_note    ("ykine");
      sprintf (t, "%6.1lf "  , a_val);
      break;
   case  'f'  :
      DEBUG_OUTP   yLOG_note    ("float");
      sprintf (t, "%8.2lf"   , a_val);
      break;
   case  'd'  :
      DEBUG_OUTP   yLOG_note    ("double");
      sprintf (t, "%10.3lf"  , a_val);
      break;
   case  't'  :
      DEBUG_OUTP   yLOG_note    ("technical");
      sprintf (t, "%18.6lf"  , a_val);
      break;
   default    :
      DEBUG_OUTP   yLOG_note    ("unknown");
      s_qout.good = 'n';
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(enqueue)------------------------*/
   rc = yparse_enqueue (&s_qout, t);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yPARSE_pushverb         (char *a_verb)
{
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_verb);
   --rce;  if (a_verb == NULL || a_verb [0] == '\0') {
      s_qout.good = 'n';
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find it)------------------------*/
   n = yparse_verb_find (&s_qout, a_verb);
   if (n < 0) {
      s_qout.good = 'n';
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   sprintf (t, "%-12.12s"  , a_verb);
   /*---(enqueue)------------------------*/
   rc = yparse_enqueue (&s_qout, t);
   if (rc < 0) {
      s_qout.good = 'n';
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   s_qout.good = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    simplifying functions                     ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLIFIERS_____________o (void) {;};

char yPARSE_pushempty   (void)         { return yparse__push_string  ("");    }
char yPARSE_pushstr     (char  *a_str) { return yparse__push_string  (a_str); }

char yPARSE_pushchar    (char   a_val) { return yparse__push_numeric ((double) a_val); }
char yPARSE_pushint     (int    a_val) { return yparse__push_numeric ((double) a_val); }
char yPARSE_pushfloat   (float  a_val) { return yparse__push_numeric ((double) a_val); }
char yPARSE_pushdouble  (double a_val) { return yparse__push_numeric ((double) a_val); }



/*====================------------------------------------====================*/
/*===----                    simplifying functions                     ----===*/
/*====================------------------------------------====================*/
static void      o___RECORDS_________________o (void) {;};

char
yparse_popout           (char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_item != NULL)  strlcpy (a_item, "", LEN_LABEL);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
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
   rc = yparse_dequeue (&s_qout, a_item);
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
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   if (rc < 0)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   --rce;  if (s_qout.iverb < 0)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   n = yparse_col_count (&s_qout);
   --rce;  if (s_qout.count != n)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-thru)----------------------*/
   while (yparse_popout (t) == 0) {
      strlcat (s_qout.recd, t    , LEN_RECD);
      strlcat (s_qout.recd, " § ", LEN_RECD);
   }
   s_qout.len  = strlen (s_qout.recd);
   s_qout.good = 'C';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_write            (int *n, int *c)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(aggregate)----------------------*/
   rc = yparse_aggregate ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   --rce;  if (s_qout.file == NULL)  {
      DEBUG_YPARSE   yLOG_snote   ("file/stdout not open");
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(write)--------------------------*/
   strlcpy  (t, s_qout.recd, LEN_RECD);
   strldchg (t, G_CHAR_FIELD, G_KEY_FIELD, LEN_RECD);
   fprintf  (s_qout.file, "%s\n", t);
   fflush   (s_qout.file);
   s_qout.good = 'W';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   variadic interface                         ----===*/
/*====================------------------------------------====================*/
static void      o___VARIADIC________________o (void) {;};

char
yPARSE_fullwrite        (char *a_verb, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   int         i           =    0;
   char        x_type      =  '-';
   va_list     x_vlist;
   char        x_char      =    0;
   int         x_int       =    0;
   double      x_double    =  0.0;
   char       *x_str       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(verb)---------------------------*/
   rc = yPARSE_pushverb (a_verb);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(column count)-------------------*/
   n = yparse_col_count (&s_qout);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   /*---(cycle columns)------------------*/
   va_start (x_vlist, a_verb);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   --rce;  for (i = 1; i < n; ++i) {
      x_type = yparse_col_by_count  (&s_qout);
      DEBUG_YPARSE   yLOG_char    ("x_type"    , x_type);
      switch (x_type) {
      case 'c' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "char");
         x_char    = va_arg (x_vlist, int);
         DEBUG_YPARSE   yLOG_value   ("x_char"    , x_char);
         rc = yPARSE_pushchar   (x_char);
         break;
      case 's' : case 'i' : case 'l' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "int");
         x_int     = va_arg (x_vlist, int);
         DEBUG_YPARSE   yLOG_value   ("x_int"     , x_int);
         rc = yPARSE_pushint    (x_int);
         break;
      case 'k' : case 'f' :
      case 'd' : case 'r' : case 't' : case 'e' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "double");
         x_double  = va_arg (x_vlist, double);
         DEBUG_YPARSE   yLOG_double  ("x_double"  , x_double);
         rc = yPARSE_pushdouble (x_double);
         break;
      case 'C' : case 'S' : case 'T' : case 'A' :
      case 'L' : case 'D' : case 'U' : case 'F' : case 'O' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "string");
         x_str     = va_arg (x_vlist, char*);
         DEBUG_YPARSE   yLOG_info    ("x_str"     , x_str);
         rc = yPARSE_pushstr    (x_str);
         break;
      default  :
         DEBUG_YPARSE   yLOG_bullet  (i           , "unknown type");
         va_end (x_vlist);
         return rce;
         break;
      }
      DEBUG_YPARSE   yLOG_value   ("push"      , rc);
      if (rc < 0)  {
         va_end (x_vlist);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
   }
   va_end (x_vlist);
   /*---(write)--------------------------*/
   rc = yPARSE_write (NULL, NULL);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           file control                       ----===*/
/*====================------------------------------------====================*/
static void      o___FILES___________________o (void) {;};

char yPARSE_stdout     (void)          { return yparse_open  (&s_qout, "stdout"); }
char yPARSE_open_out   (char *a_name)  { return yparse_open  (&s_qout, a_name); }
char yPARSE_close_out  (void)          { return yparse_close (&s_qout);         }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_out        (char *a_question, int a_num)
{
   return yparse__unit_queue (&s_qout, a_question, a_num);
}

