/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



tQUEUE      s_qout;


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
   { 'i', "integer"            , 'n',    6, "normal integer  (6d)"             },
   { 'l', "long"               , 'n',   10, "long integer    (10d)"            },
   { 'h', "huge"               , 'n',   16, "long integer    (16ld)"           },
   { ',', "comma"              , 'n',   10, "comma           (10d)"            },
   { ';', "hcomma"             , 'n',   19, "long comma      (19ld)"           },
   { 'k', "ykine"              , 'n',    6, "short float     (6.1f)"           },
   { 'f', "float"              , 'n',    8, "normal float    (8.2f)"           },
   { 'd', "double"             , 'n',   10, "double float    (10.3lf)"         },
   { 't', "technical"          , 'n',   18, "technical       (18.6lf)"         },
   { 'e', "sml-exp"            , 'n',   10, "tech float      (2.3e)"           },
   { 'm', "med-exp"            , 'n',   14, "tech float      (2.7e)"           },
   { 'b', "big-exp"            , 'n',   19, "exponent        (2.12e)"          },

   { 'C', "char"               , 's',    1, "single char     (-1.1s)"          },
   { 'S', "short"              , 's',    5, "short string    (-5.5s)"          },
   { 'T', "terse"              , 's',   10, "terse string    (-10.10s)"        },
   { 'U', "user"               , 's',   12, "user string     (-12.12s)"        },
   { 'L', "label"              , 's',   20, "label string    (-20.20s)"        },
   { '3', "thirty"             , 's',   30, "thirty string   (-30.30s)"        },
   { '4', "forty"              , 's',   40, "forty string    (-40.40s)"        },
   { 'D', "desc"               , 's',   50, "desc string     (-50.50s)"        },
   { '6', "sixty"              , 's',   60, "sixty string    (-40.40s)"        },
   { '7', "seventy"            , 's',   70, "seventy string  (-70.70s)"        },
   { '8', "eighty"             , 's',   80, "eighty string   (-80.80s)"        },
   { 'H', "hundred"            , 's',  100, "hundred string  (-100.100s)"      },
   { 'F', "full"               , 's',  200, "two-hundred     (-200.200s)"      },
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
   --rce;  if (myPARSE.verbs != YPARSE_SIMPLE && strchr ("-y", s_qout.good) == NULL)  {
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

char
yPARSE_qout_info         (char *a_label, char *a_loc, void **a_file, int *t)
{
   if (a_label != NULL)  strlcpy (a_label, s_qout.label   , LEN_LABEL);
   if (a_loc   != NULL) {
      if (s_qout.loc != NULL) strlcpy (a_loc  , s_qout.loc     , LEN_HUND);
      else                    strlcpy (a_loc  , "-"            , LEN_HUND);
   }
   if (a_file  != NULL)  *a_file =  s_qout.file;
   if (t       != NULL)  *t      =  s_qout.tline;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       formatting functions                   ----===*/
/*====================------------------------------------====================*/
static void      o___FORMAT__________________o (void) {;};

char
yparse__push_string     (uchar *a_str)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   uchar       s           [LEN_RECD];
   uchar       t           [LEN_RECD];
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (s_qout.file);
   DEBUG_YPARSE  yLOG_sint    (s_qout.iverb);
   DEBUG_YPARSE  yLOG_sint    (s_qout.count);
   --rce;  if (s_qout.file == NULL || s_qout.iverb < 0 || s_qout.count < 1)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_str);
   --rce;  if (a_str == NULL) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_str);
   strlcpy  (s, a_str, LEN_RECD);
   strlmark (s, ySTR_PRINT, LEN_RECD);
   /*---(prepare)------------------------*/
   x_type = yparse_specs_next_write ();
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
      DEBUG_YPARSE   yLOG_snote   ("char");
      if (s [0] == 0)        strlcpy (t, "¬"   , 2);
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
   case  'O' :
      DEBUG_YPARSE   yLOG_snote   ("open string");
      sprintf (t, "%s"        , s);
      break;
   default    :
      DEBUG_YPARSE   yLOG_snote   ("unknown");
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
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
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
   char        s           [LEN_RECD];
   llong       v           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE  yLOG_sdouble (a_val);
   /*---(defense)------------------------*/
   rc = yparse_out_defense ();
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (s_qout.file);
   DEBUG_YPARSE  yLOG_sint    (s_qout.iverb);
   DEBUG_YPARSE  yLOG_sint    (s_qout.count);
   --rce;  if (s_qout.file == NULL || s_qout.iverb < 0 || s_qout.count < 1)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_type = yparse_specs_next_write ();
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
      DEBUG_YPARSE   yLOG_snote   ("char");
      if      (a_val < 31)            strlcpy (t, "¬", LEN_RECD);
      else if (a_val > 255)           strlcpy (t, "¬", LEN_RECD);
      else                            sprintf (t, "%c"       , (uchar) a_val);
      break;
   case  's'  :
      DEBUG_YPARSE   yLOG_snote   ("short");
      if      (a_val < -99)           strlcpy (t, "¬¬¬", LEN_RECD);
      else if (a_val > 999)           strlcpy (t, "¬¬¬", LEN_RECD);
      else                            sprintf (t, "%3d"      , (int) a_val);
      break;
   case  'i'  :
      DEBUG_YPARSE   yLOG_snote   ("integer");
      if      (a_val < -99999)        strlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 999999)        strlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%6d"      , (int) a_val);
      break;
   case  'l'  :
      DEBUG_YPARSE   yLOG_snote   ("long");
      if      (a_val < -999999999LL)  strlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 9999999999LL)  strlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%10ld"    , (llong) a_val);
      break;
   case  'h'  :
      DEBUG_YPARSE   yLOG_snote   ("huge");
      if      (a_val < -999999999999998LL)  strlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 9999999999999998LL)  strlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else                                  sprintf (t, "%16ld"    , (llong) a_val);
      break;
   case  ','  :
      DEBUG_YPARSE   yLOG_snote   ("comma");
      if      (a_val < -9999999)      strlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 99999999)      strlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else  {
         strl4comma (a_val, s, 0, 'c', '-', LEN_LABEL);
         sprintf (t, "%10.10s", s);
      }
      break;
   case  ';'  :
      DEBUG_YPARSE   yLOG_snote   ("hcomma");
      if      (a_val < -99999999999998LL)  strlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 999999999999998LL)  strlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else {
         strl4comma (a_val, s, 0, 'c', '-', LEN_LABEL);
         sprintf (t, "%19.19s", s);
      }
      break;
   case  'k'  :
      DEBUG_YPARSE   yLOG_snote   ("ykine");
      if      (a_val < -999.9)        strlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 9999.9)        strlcpy (t, "¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%6.1lf"   , a_val);
      break;
   case  'f'  :
      DEBUG_YPARSE   yLOG_snote   ("float");
      if      (a_val < -9999.99)      strlcpy (t, "¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 99999.99)      strlcpy (t, "¬¬¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%8.2lf"   , a_val);
      break;
   case  'd'  :
      DEBUG_YPARSE   yLOG_snote   ("double");
      if      (a_val < -99999.999)    strlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 999999.999)    strlcpy (t, "¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else                            sprintf (t, "%10.3lf"  , a_val);
      break;
   case  't'  :
      DEBUG_YPARSE   yLOG_snote   ("technical");
      if      (a_val < -9999999999.999990)   strlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
      else if (a_val > 99999999999.999990)   strlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_RECD);
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
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
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
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("defense");
   rc = yparse_out_defense ();
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (s_qout.file);
   --rce;  if (s_qout.file == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
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

char yPARSE_pushempty   (void)          { return yparse__push_string  ("");    }
char yPARSE_pushstr     (uchar  *a_str) { return yparse__push_string  (a_str); }

char yPARSE_pushchar    (uchar   a_val) { return yparse__push_numeric ((double) a_val); }
char yPARSE_pushint     (llong  a_val)  { return yparse__push_numeric ((double) a_val); }
char yPARSE_pushfloat   (double a_val)  { return yparse__push_numeric (a_val); }



/*====================------------------------------------====================*/
/*===----                    simplifying functions                     ----===*/
/*====================------------------------------------====================*/
static void      o___RECORDS_________________o (void) {;};

char
yparse__popout           (char *a_item)
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
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_value   ("iverb"     , s_qout.iverb);
   --rce;  if (s_qout.iverb < 0)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   n = yparse_specs_len (&s_qout);
   DEBUG_YPARSE  yLOG_value   ("cols"      , n);
   DEBUG_YPARSE  yLOG_value   ("count"     , s_qout.count);
   --rce;  if (s_qout.count != n)  {
      s_qout.good = 'X';
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-thru)----------------------*/
   while (yparse__popout (t) == 0) {
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

char yparse_out__count        (void) { return s_qout.count; }



/*====================------------------------------------====================*/
/*===----                   variadic interface                         ----===*/
/*====================------------------------------------====================*/
static void      o___VARIADIC________________o (void) {;};

char
yparse_out_variadic    (va_list a_vlist, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        x_type      =  '-';
   char        x_char      =    0;
   int         x_int       =    0;
   llong       x_long      =    0;
   float       x_float     =  0.0;
   double      x_double    =  0.0;
   uchar      *x_str       = NULL;
   int         c           =    0;
   double      x_val       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(walk fields)--------------------*/
   --rce;  for (i = 1; i < n; ++i) {
      x_type = yparse_specs_next_write ();
      switch (x_type) {
      case 'c' :
         x_char    = va_arg (a_vlist, int);
         rc = yPARSE_pushchar   (x_char);
         DEBUG_YPARSE   yLOG_complex ("char"      , "%d, %c, %3d, %c", i, x_type, rc, x_char);
         break;
      case 's' : case 'i' : case ',' :
         x_int     = va_arg (a_vlist, int);
         rc = yPARSE_pushint    (x_int);
         DEBUG_YPARSE   yLOG_complex ("int"       , "%d, %c, %3d, %ld", i, x_type, rc, x_int);
         break;
      case 'l' : case 'h' : case ';' :
         x_long    = va_arg (a_vlist, llong);
         rc = yPARSE_pushint    (x_long);
         DEBUG_YPARSE   yLOG_complex ("long"      , "%d, %c, %3d, %ld", i, x_type, rc, x_long);
         break;
      case 'k' : case 'f' : case 'd' : case 'r' : case 't' : case 'e' :
         x_double  = va_arg (a_vlist, double);
         rc = yPARSE_pushfloat  (x_double);
         DEBUG_YPARSE   yLOG_complex ("double"    , "%d, %c, %3d, %lf", i, x_type, rc, x_double);
         break;
      case 'C' : case 'S' : case 'T' : case 'U' : case 'L' :
      case '3' : case '4' : case 'D' : case '5' : case '6' :
      case '7' : case '8' : case 'H' : case 'F' : case 'O' :
         x_str     = va_arg (a_vlist, char*);
         rc = yPARSE_pushstr    (x_str);
         DEBUG_YPARSE   yLOG_complex ("string"    , "%d, %c, %3d, %s", i, x_type, rc, x_str);
         break;
      default  :
         DEBUG_YPARSE   yLOG_complex ("unknown"   , "%d, %c, ---, -", i, x_type);
         rc = -1;
         break;
      }
      if (rc < 0)  {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
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
   /*> if (a_prog != NULL)  fprintf  (s_qout.file, "#!%s\n", a_prog);                   <* 
    *> if (a_desc != NULL)  fprintf  (s_qout.file, "#   generated by %s\n", a_desc);    <* 
    *> if (a_prog != NULL)  fprintf  (s_qout.file, "#   using the yPARSE library\n");   <*/
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
   yPARSE_spacer  (3);
   if (s_qout.file != NULL)   fprintf (s_qout.file, "# end-of-file.  done, finito, completare.\n");
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

