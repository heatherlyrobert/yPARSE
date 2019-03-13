/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



static      tQUEUE      s_qout;


#define     MAX_TYPES   50
typedef   struct cTYPES  tTYPES;
struct cTYPES {
   cchar       abbr;                        /* unique one char id             */
   cchar       name        [LEN_LABEL];     /* short name                     */
   cint        cat;                         /* category -- string, numeric    */
   cint        size;                        /* width                          */
   cchar       desc        [LEN_DESC];      /* long description               */
};
static tTYPES  s_types [MAX_TYPES] = {
   { 'c', "char"               , 'n',    1, "single char     (c)"              },
   { 's', "short"              , 'n',    3, "short integer   (3d)"             },
   { 'i', "integer"            , 'n',    5, "normal integer  (5d)"             },
   { 'l', "long"               , 'n',   10, "long integer    (10d)"            },
   { 'k', "ykine"              , 'n',    6, "short float     (6.1f)"           },
   { 'f', "float"              , 'n',    8, "normal float    (8.2f)"           },
   { 'd', "double"             , 'n',   10, "normal float    (10.3lf)"         },
   { 'r', "real"               , 'n',   12, "tech float      (lf)"             },
   { 'e', "exponent"           , 'n',   20, "exponent        (e)"              },

   { 'C', "char"               , 's',    1, "single char     (-1.1s)"          },
   { 'S', "short"              , 's',    5, "short string    (-5.5s)"          },
   { 'T', "terse"              , 's',   10, "terse string    (-10.10s)"        },
   { 'L', "label"              , 's',   12, "label string    (-12.12s)"        },
   { 'N', "name"               , 's',   20, "name string     (-20.20s)"        },
   { 'F', "forty"              , 's',   40, "forty string    (-40.40s)"        },
   { 'D', "desc"               , 's',   60, "desc string     (-60.60s)"        },
   { 'U', "unit"               , 's',   70, "unit string     (-70.70s)"        },
   { 'H', "hundred"            , 's',  100, "hundred string  (-100.100s)"      },
   { 'O', "open"               , 's',   60, "open string     (s)"              },

   {  0 , "end-of-types"       , '-',    0, ""                                 },
};
static int   s_ntype       =    0;
static char  s_strings     [LEN_LABEL]  = "";
static char  s_numbers     [LEN_LABEL]  = "";



/*====================------------------------------------====================*/
/*===----                      shared functions                        ----===*/
/*====================------------------------------------====================*/
static void      o___SHARED__________________o (void) {;};

char
yparse_init_types       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_ntype = 0;
   strlcpy (s_strings, "", LEN_LABEL);
   strlcpy (s_numbers, "", LEN_LABEL);
   /*---(walk)---------------------------*/
   for (i = 0; i < MAX_TYPES; ++i) {
      DEBUG_YPARSE  yLOG_sint    (i);
      DEBUG_YPARSE  yLOG_snote   (s_types [i].name);
      if (s_types [i].abbr ==  0 )  break;
      sprintf (t, "%c", s_types [i].abbr);
      if (s_types [i].cat  == 's')   strlcat (s_strings, t, LEN_LABEL);
      if (s_types [i].cat  == 'n')   strlcat (s_numbers, t, LEN_LABEL);
      ++s_ntype;
   }
   DEBUG_YPARSE  yLOG_snote   (s_strings);
   DEBUG_YPARSE  yLOG_snote   (s_numbers);
   DEBUG_YPARSE  yLOG_sint    (s_ntype);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

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

int
yparse_field_len        (char a_type)
{
   int         i           =    0;
   for (i = 0; i < s_ntype; ++i) {
      if (s_types [i].abbr != a_type)  continue;
      return s_types [i].size;
   }
   return 0;
}



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
   DEBUG_YPARSE   yLOG_schar   (x_type);
   DEBUG_YPARSE   yLOG_snote   (s_strings);
   --rce;  if (strchr (s_strings, x_type) == NULL) {
      s_qout.good = 'n';
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(format)-------------------------*/
   --rce;  switch (x_type) {
   case  'C' :
      DEBUG_YPARSE   yLOG_note    ("char");
      sprintf (t, "%c"       , a_str [0]);
      break;
   case  'S' :
      DEBUG_YPARSE   yLOG_note    ("short string");
      sprintf (t, "%-5.5s"    , a_str);
      break;
   case  'T' :
      DEBUG_YPARSE   yLOG_note    ("terse string");
      sprintf (t, "%-10.10s"  , a_str);
      break;
   case  'L' :
      DEBUG_YPARSE   yLOG_note    ("label/address string");
      sprintf (t, "%-12.12s"  , a_str);
      break;
   case  'N' :
      DEBUG_YPARSE   yLOG_note    ("name string");
      sprintf (t, "%-20.20s"  , a_str);
      break;
   case  'F' :
      DEBUG_YPARSE   yLOG_note    ("forty-five string");
      sprintf (t, "%-40.40s"  , a_str);
      break;
   case  'D' :
      DEBUG_YPARSE   yLOG_note    ("description string");
      sprintf (t, "%-60.60s"  , a_str);
      break;
   case  'U' :
      DEBUG_YPARSE   yLOG_note    ("unit test string");
      sprintf (t, "%-70.70s"  , a_str);
      break;
   case  'H' :
      DEBUG_YPARSE   yLOG_note    ("hundred string");
      sprintf (t, "%-100.100s", a_str);
      break;
   case  'O' :
      DEBUG_YPARSE   yLOG_note    ("open string");
      sprintf (t, "%s"        , a_str);
      break;
   default    :
      DEBUG_YPARSE   yLOG_note    ("unknown");
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
   DEBUG_YPARSE   yLOG_schar   (x_type);
   DEBUG_YPARSE   yLOG_snote   (s_numbers);
   --rce;  if (strchr (s_numbers, x_type) == NULL) {
      s_qout.good = 'n';
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(format)-------------------------*/
   --rce;  switch (x_type) {
   case  'c' :
      DEBUG_YPARSE   yLOG_note    ("char");
      sprintf (t, "%c"       , (char) a_val);
      break;
   case  's'  :
      DEBUG_YPARSE   yLOG_note    ("short");
      sprintf (t, "%3d"      , (int)  a_val);
      break;
   case  'i'  :
      DEBUG_YPARSE   yLOG_note    ("integer");
      sprintf (t, "%6d"      , (int)  a_val);
      break;
   case  'l'  :
      DEBUG_YPARSE   yLOG_note    ("long");
      sprintf (t, "%10d"     , (int)  a_val);
      break;
   case  'k'  :
      DEBUG_YPARSE   yLOG_note    ("ykine");
      sprintf (t, "%6.1lf "  , a_val);
      break;
   case  'f'  :
      DEBUG_YPARSE   yLOG_note    ("float");
      sprintf (t, "%8.2lf"   , a_val);
      break;
   case  'd'  :
      DEBUG_YPARSE   yLOG_note    ("double");
      sprintf (t, "%10.3lf"  , a_val);
      break;
   case  't'  :
      DEBUG_YPARSE   yLOG_note    ("technical");
      sprintf (t, "%18.6lf"  , a_val);
      break;
   case  'e'  :
      DEBUG_YPARSE   yLOG_note    ("exponent");
      sprintf (t, "%e"       , a_val);
      break;
   default    :
      DEBUG_YPARSE   yLOG_note    ("unknown");
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
   /*---(prepare)------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("purge");
   rc = yPARSE_purge_out   ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("defense");
   rc = yparse_out_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("check");
   DEBUG_YPARSE  yLOG_spoint  (a_verb);
   --rce;  if (a_verb == NULL || a_verb [0] == '\0') {
      s_qout.good = 'n';
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find it)------------------------*/
   DEBUG_YPARSE  yLOG_snote   (a_verb);
   DEBUG_YPARSE  yLOG_snote   ("find");
   n = yparse_verb_find (&s_qout, a_verb);
   if (n < 0) {
      s_qout.good = 'n';
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   sprintf (t, "%-12.12s"  , a_verb);
   /*---(enqueue)------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("enqueue");
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
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   if (rc < 0)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(defense)------------------------*/
   --rce;  if (s_qout.iverb < 0)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   n = yparse_col_count (&s_qout);
   --rce;  if (s_qout.count != n)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
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
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
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
   --rce;  if (s_qout.file == NULL)  {
      DEBUG_YPARSE   yLOG_note    ("file/stdout not open");
      DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(write)--------------------------*/
   strlcpy  (myPARSE.recd, s_qout.recd, LEN_RECD);
   strlcpy  (t, s_qout.recd, LEN_RECD);
   strldchg (t, G_CHAR_FIELD, G_KEY_FIELD, LEN_RECD);
   if (s_qout.file != NULL)   fprintf  (s_qout.file, "%s\n", t);
   if (s_qout.file != NULL)   fflush   (s_qout.file);
   s_qout.good = 'W';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      special output lines                    ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIAL_________________o (void) {;};

char
yparse__spacer          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (s_qout.file);
   --rce;  if (s_qout.file == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   ("open");
   /*---(print)--------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("print");
   fprintf  (s_qout.file, "\n\n\n");
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_section          (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_fill      =    0;
   char        t           [LEN_DESC] = "";
   char        x_filler    [LEN_DESC] = "===========================================================================================================";
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prep)---------------------------*/
   yPARSE_purge_out ();
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (s_qout.file == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare title)------------------*/
   if (a_title != NULL)  strlcpy (t, a_title, LEN_DESC);
   DEBUG_YPARSE   yLOG_info    ("title"     , t);
   x_len       = strlen (t);
   if (x_len > 50) {
      x_len     = 50;
      t [x_len] = '\0';
   }
   /*---(prepare filler)-----------------*/
   x_fill      = 80 - 14 - x_len;
   x_filler [x_fill] = '\0';
   /*---(print title)--------------------*/
   yparse__spacer ();
   fprintf (s_qout.file, "##===[[ %s ]]%s=##\n", t, x_filler);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_out_line         (char *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (s_qout.file);
   --rce;  if (s_qout.file == NULL) {
      DEBUG_YPARSE   yLOG_snote   ("file not open");
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YPARSE   yLOG_snote   ("no line to print");
      return rce;
   }
   /*---(print)--------------------------*/
   fprintf (s_qout.file, "%s\n", a_line);
   /*---(complete)-----------------------*/
   return 0;
}

int 
yPARSE_write_verb        (char *a_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   int         n           =   -1;
   char        x_upper     [LEN_LABEL];
   void       *x_field     [9];
   char        t           [LEN_RECD ];
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_point   ("a_verb"    , a_verb);
   /*---(find it)------------------------*/
   n = yparse_verb_find (&s_qout, a_verb);
   DEBUG_YPARSE  yLOG_value   ("n"         , n);
   if (n < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, n);
      return n;
   }
   DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);



   /*> /+---(defense)------------------------+/                                                                                                            <* 
    *> DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);                                                                                                 <* 
    *> --rce;  if (a_verb == NULL) {                                                                                                                       <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                 <* 
    *>    return rce;                                                                                                                                      <* 
    *> }                                                                                                                                                   <* 
    *> DEBUG_YPARSE   yLOG_info    ("a_verb"    , a_verb);                                                                                                 <* 
    *> /+---(find entry)---------------------+/                                                                                                            <* 
    *> n = FILE__by_name (a_verb);                                                                                                                         <* 
    *> DEBUG_YPARSE   yLOG_value   ("n"         , n);                                                                                                      <* 
    *> if (n < 0) {                                                                                                                                        <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                 <* 
    *>    return rce;                                                                                                                                      <* 
    *> }                                                                                                                                                   <* 
    *> /+---(write header)-------------------+/                                                                                                            <* 
    *> DEBUG_YPARSE   yLOG_info    ("name"      , s_sections [n].name);                                                                                    <* 
    *> strlcpy (x_upper, s_sections [n].name, LEN_LABEL);                                                                                                  <* 
    *> for (i = 0; i < strllen (x_upper, LEN_LABEL); ++i)  x_upper [i] = toupper (x_upper [i]);                                                            <* 
    *> DEBUG_YPARSE   yLOG_info    ("upper"     , x_upper);                                                                                                <* 
    *> if (s_file != NULL) {                                                                                                                               <* 
    *>    DEBUG_YPARSE   yLOG_note    ("write the header");                                                                                                <* 
    *>    fprintf (s_file, "\n\n\n#===[[ %-20.20s ]]===============================================================================================#\n",   <* 
    *>          x_upper);                                                                                                                                  <* 
    *>    OUTP__sec_columns (n);                                                                                                                           <* 
    *> }                                                                                                                                                   <* 
    *> /+---(write entries)------------------+/                                                                                                            <* 
    *> s_lines = 0;                                                                                                                                        <* 
    *> rc = s_sections [n].writer ();                                                                                                                      <* 
    *> DEBUG_YPARSE   yLOG_value   ("rc"        , rc);                                                                                                     <* 
    *> DEBUG_YPARSE   yLOG_value   ("s_lines"   , s_lines);                                                                                                <* 
    *> /+---(write footer)-------------------+/                                                                                                            <* 
    *> if (s_file != NULL) {                                                                                                                               <* 
    *>    DEBUG_YPARSE   yLOG_note    ("write the footer");                                                                                                <* 
    *>    if (s_lines == 0)  fprintf (s_file, "# no %s\n", s_sections [n].name);                                                                           <* 
    *>    else               fprintf (s_file, "# complete with %d line(s)\n", s_lines);                                                                    <* 
    *>    fflush  (s_file);                                                                                                                                <* 
    *> }                                                                                                                                                   <*/
   /*> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);                                    <* 
    *> return s_lines;                                                                <*/
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
      case 'C' : case 'S' : case 'T' : case 'L' :
      case 'N' : case 'D' : case 'U' : case 'H' : case 'O' :
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
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           file control                       ----===*/
/*====================------------------------------------====================*/
static void      o___FILES___________________o (void) {;};

char
yPARSE_stdout           (void)
{
   return yparse_open  (&s_qout, "stdout");
}

char
yPARSE_open_out         (char *a_name, char *a_prog, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_spacer    =  '-';
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = yparse_open  (&s_qout, a_name);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(shebang)------------------------*/
   if (a_prog != NULL)  fprintf  (s_qout.file, "#!%s\n", a_prog);
   if (a_desc != NULL)  fprintf  (s_qout.file, "#   generated by %s\n", a_desc);
   fflush   (s_qout.file);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_close_out  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(footer)-------------------------*/
   yparse__spacer ();
   if (s_qout.file != NULL)   fprintf (s_qout.file, "## done, finito, complete\n");
   /*---(close)--------------------------*/
   rc = yparse_close (&s_qout);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}

char    yPARSE_outclear         (void) { yPARSE_purge_out   (); return 0; }
char*   yPARSE_outrecd          (void) { strltrim (s_qout.recd, ySTR_BOTH, LEN_RECD); return s_qout.recd; }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_out        (char *a_question, int a_num)
{
   return yparse__unit_queue (&s_qout, a_question, a_num);
}

