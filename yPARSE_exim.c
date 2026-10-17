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



/*====================------------------------------------====================*/
/*===----                   interpreting parser spec                   ----===*/
/*====================------------------------------------====================*/
static void      o___INTERPRET_______________o (void) {;}

char
yparse__exim_prepare    (char *a_parser, char r_feedback [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_ch        =  '-';
   int         l           =    0;
   char        x_curr      [LEN_TERSE] = "";
   char        x_error     [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("r_feedback", r_feedback);
   --rce;  if (r_feedback == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_point   ("a_parser"  , a_parser);
   --rce;  if (a_parser == NULL) {
      if (r_feedback != NULL)  strlcat (r_feedback, BOLD_ERR "(null)" BOLD_OFF, LEN_RECD);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("a_parser"  , a_parser);
   l = strlen (a_parser);
   DEBUG_YPARSE   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      if (r_feedback != NULL)  strlcat (r_feedback, BOLD_ERR "(empty)" BOLD_OFF, LEN_RECD);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_parser, "#ù "            ,  3) != NULL) {
      sprintf (x_error, BOLD_ERR "%s-3.3s" BOLD_OFF "%s", a_parser, a_parser + 3);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_parser, "#ù parsing··´··", 15) != NULL) {
      sprintf (x_error, BOLD_GRN "#ù" BOLD_OFF BOLD_ERR "12.12s" BOLD_OFF "%s", a_parser + 3, a_parser + 15);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strncmp (a_parser, "#ù parsing··´··å", 16) != 0) {
      sprintf (x_error, BOLD_GRN "#ù parsing··´··" BOLD_OFF BOLD_ERR "%c" BOLD_OFF "%s", a_parser [15], a_parser + 16);
      if (r_feedback != NULL)  strlcat (r_feedback, x_error, LEN_RECD);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (l == 17 && strcmp (a_parser, "#ù parsing··´··åæ") == 0) {
      if (r_feedback != NULL)  strlcpy (r_feedback, BOLD_ERR "#ù parsing··´··åæ (no fields)" BOLD_OFF, LEN_RECD);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare feedback)---------------*/
   if (r_feedback != NULL) {
      strcpy  (r_feedback, BOLD_GRN);
      strlcat (r_feedback, "#ù parsing··´··å", LEN_RECD);
   }
   /*---(complete)-----------------------*/
   return 1;
}

char
yparse__exim_clear      (char *r_width, char *r_gap, char *r_dots, char *r_suffix, char r_field [LEN_RECD], char *r_delm, char *r_algn, char *r_form, char *r_decs, char *r_unit, char r_check [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (r_width  == NULL)  return rce;
   --rce;  if (r_gap    == NULL)  return rce;
   --rce;  if (r_dots   == NULL)  return rce;
   --rce;  if (r_suffix == NULL)  return rce;
   --rce;  if (r_field  == NULL)  return rce;
   --rce;  if (r_delm   == NULL)  return rce;
   --rce;  if (r_algn   == NULL)  return rce;
   --rce;  if (r_form   == NULL)  return rce;
   --rce;  if (r_decs   == NULL)  return rce;
   --rce;  if (r_unit   == NULL)  return rce;
   /*---(initialize)---------------------*/
   *r_width   = 0;
   *r_gap     = 0;
   *r_dots    = '-';
   *r_suffix  = 0;
   strcpy (r_field, "");
   *r_delm    = '·';
   *r_algn    = '·';
   *r_form    = '·';
   *r_decs    = '·';
   *r_unit    = '·';
   /*---(unit-testing)-------------------*/
   if (r_check   != NULL)  sprintf (r_check, "····· w=%2d, g=%2d, d=%c, s=%d, %c %c %c %c %c , å%sæ", *r_width, *r_gap, *r_dots, *r_suffix, *r_delm, *r_algn, *r_form, *r_decs, *r_unit, r_field);
   /*---(complete)-----------------------*/
   return 1;
}

char
yparse__exim_title      (char a_ch, char a_curr [LEN_TERSE], char *b_width, char *b_gap, char *b_dots, char *b_suffix, char b_field [LEN_RECD], char r_check [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_names     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_0123456789/èéêëìíîïðñòóôõö÷øùúûüýþÿ·´±Ú§<|> ";
   char       *x_dotss     = "·´±Ú§<|> ";
   /*---(defense)------------------------*/
   --rce;  if (a_curr   == NULL)  return rce;
   --rce;  if (b_width  == NULL)  return rce;
   --rce;  if (b_gap    == NULL)  return rce;
   --rce;  if (b_dots   == NULL)  return rce;
   --rce;  if (b_suffix == NULL)  return rce;
   --rce;  if (b_field  == NULL)  return rce;
   /*---(quick-out)----------------------*/
   if (*b_suffix >  0)    return 0;
   --rce;  if (a_ch == 0)         return rce;
   /*---(check character)----------------*/
   --rce; if (strchr (x_names , a_ch) == NULL) {
      DEBUG_YPARSE   yLOG_note    ("title can only use use åa-z0-9è-ÿ/_-æ, move on with å·´±Ú§<|>æ, or next field with space ( )");
      return rce;
   }
   --rce;  if (a_ch == '·' && *b_width <= 0) {
      DEBUG_YPARSE   yLOG_note    ("can not start using dots (·) with no title");
      return rce;
   }
   --rce;  if (*b_dots == 'y' && strchr (x_dotss, a_ch) == NULL) {
      DEBUG_YPARSE   yLOG_note    ("once using dots, can only use use å·æ, move on with å´±Ú§<|>æ, or next field with space ( )");
      return rce;
   }
   /*---(handle)-------------------------*/
   switch (a_ch) {
   case ' '  :
      DEBUG_YPARSE   yLOG_note    ("title hit space ( ), field complete");
      ++(*b_gap);
      break;
   case '·'  :
      DEBUG_YPARSE   yLOG_note    ("title hit dot (·), done with title");
      *b_dots = 'y';
      ++(*b_width);
      break;
   case '´'  :  case '±'  :  case 'Ú'  :  case '§'  :
      DEBUG_YPARSE   yLOG_note    ("title hit delimiter marker å´±Ú§æ, done with title");
      *b_suffix = 1;
      break;
   case '<'  :  case '|'  :  case '>'  :
      DEBUG_YPARSE   yLOG_note    ("title hit alignment marker å<|>æ, done with title");
      *b_suffix = 2;
      break;
   default   :
      DEBUG_YPARSE   yLOG_note    ("title adds a new character");
      ++(*b_width);
      strlcat (b_field, a_curr, LEN_RECD);
      break;
   }
   /*---(unit-testing)-------------------*/
   if (r_check != NULL)  sprintf (r_check, "%c/%-3d w=%2d, g=%2d, d=%c, s=%d, · · · · · , å%sæ", ychrvisible (a_ch), (uchar) a_ch, *b_width, *b_gap, *b_dots, *b_suffix, b_field);
   /*---(complete)-----------------------*/
   return 1;
}

char
yparse__exim_suffix     (char a_ch, char a_width, char *b_suffix, char *r_delm, char *r_algn, char *r_form, char *r_decs, char *r_unit, char r_check [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_delms     = "´±Ú§";
   char       *x_algns     = "<|>";
   char       *x_forms     = "iIfF,cCaAsS$#pPeErRbBoOxXzZ-tTdDyY";
   char       *x_decss     = "01253456789";
   char       *x_units     = "YZEPTGMKHD-.dcmunpfazy";
   /*---(defense)------------------------*/
   --rce;  if (b_suffix == NULL)  return rce;
   --rce;  if (r_delm   == NULL)  return rce;
   --rce;  if (r_algn   == NULL)  return rce;
   --rce;  if (r_form   == NULL)  return rce;
   --rce;  if (r_decs   == NULL)  return rce;
   --rce;  if (r_unit   == NULL)  return rce;
   /*---(quick-out)----------------------*/
   if (*b_suffix <= 0)            return 0;
   --rce;  if (*b_suffix > 5)     return rce;
   --rce;  if (a_ch == 0)         return rce;
   /*---(defense)------------------------*/
   --rce;  if (a_width <= 0) {
      DEBUG_YPARSE   yLOG_note    ("can not start suffix with no title");
      return rce;
   }
   /*---(handle)-------------------------*/
   switch (*b_suffix) {
   case  1  :
      DEBUG_YPARSE   yLOG_note    ("checking either delimiter or alignment");
      if      (strchr (x_delms, a_ch) != NULL)  {  *r_delm = a_ch;  *b_suffix = 2; }
      else if (strchr (x_algns, a_ch) != NULL)  {  *r_algn = a_ch;  *b_suffix = 3; }
      else                                         return rce - 1;
      break;
   case  2  :
      DEBUG_YPARSE   yLOG_note    ("checking alignment");
      if (strchr (x_algns, a_ch) != NULL)       {  *r_algn = a_ch;  *b_suffix = 3; }
      else                                         return rce - 2;
      break;
   case  3  :
      DEBUG_YPARSE   yLOG_note    ("checking formatting");
      if (strchr (x_forms, a_ch) != NULL)       {  *r_form = a_ch;  *b_suffix = 4; }
      else                                         return rce - 3;
      break;
   case  4  :
      DEBUG_YPARSE   yLOG_note    ("checking decimal places");
      if (strchr (x_decss, a_ch) != NULL)       {  *r_decs = a_ch;  *b_suffix = 5; }
      else                                         return rce - 4;
      break;
   case  5  :
      DEBUG_YPARSE   yLOG_note    ("checking unit-of-measure");
      if (strchr (x_units, a_ch) != NULL)       {  *r_unit = a_ch;  *b_suffix = 6; }
      else                                         return rce - 5;
      break;
   }
   /*---(unit-testing)-------------------*/
   if (r_check != NULL)  sprintf (r_check, "%c/%-3d w=%2d, ····, ···, s=%d, %c %c %c %c %c , Ï", ychrvisible (a_ch), (uchar) a_ch, a_width, *b_suffix, *r_delm, *r_algn, *r_form, *r_decs, *r_unit);
   /*---(complete)-----------------------*/
   return 1;
}

char
yparse__exim_field      (char *b_count, char a_ch, char a_width, char a_gap, char a_field [LEN_FULL], char a_delm, char a_algn, char a_form, char a_decs, char a_unit, char b_header [LEN_RECD], char b_break [LEN_RECD], char b_control [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_algn      =  '·';
   char        t           [LEN_FULL]  = "";
   char        x_val       [LEN_TERSE] = "";
   /*---(defense)------------------------*/
   --rce;  if (b_count   == NULL)    return rce;
   --rce;  if (a_field   == NULL)    return rce;
   --rce;  if (a_delm    == NULL)    return rce;
   --rce;  if (a_algn    == NULL)    return rce;
   --rce;  if (a_form    == NULL)    return rce;
   --rce;  if (a_decs    == NULL)    return rce;
   --rce;  if (a_unit    == NULL)    return rce;
   --rce;  if (b_header  == NULL)    return rce;
   --rce;  if (b_break   == NULL)    return rce;
   --rce;  if (b_control == NULL)    return rce;
   /*---(quick-out)----------------------*/
   --rce;  if (a_width   <= 0)       return rce;
   --rce;  if (a_gap     <  0)       return rce;
   if (a_ch != 0 && strchr (" æ", a_ch) == NULL)  return 0;
   /*---(prepare)------------------------*/
   if (*b_count == 0) {
      strcpy (b_header , "");
      strcpy (b_break  , "");
      strcpy (b_control, "");
   }
   ++(*b_count);
   if (a_delm == '·')  a_delm = '´';
   if (a_algn == '·')  x_algn = '<';
   else                x_algn = a_algn;
   /*---(add gap)------------------*/
   if (a_gap > 0) {
      ystrlpad (""      , t, '²', '<'    , a_gap);
      strlcat  (b_header, t, LEN_RECD);
      strlcat  (b_break , t, LEN_RECD);
   }
   /*---(add header)---------------*/
   ystrlpad (a_field, t, '·', x_algn, a_width);
   DEBUG_YPARSE   yLOG_info    ("t"         , t);
   strlcat  (b_header, t, LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("b_header"  , b_header);
   /*---(add break)----------------*/
   ystrlpad ("-"    , t, '·', x_algn, a_width);
   DEBUG_YPARSE   yLOG_info    ("t"         , t);
   strlcat  (b_break , t, LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("b_break"   , b_break);
   /*---(add control)--------------*/
   ystrlpadn (a_width, x_val, '·', '>'    , 3);
   sprintf (t, "%c%s%c%c%c%c  ", a_delm, x_val, a_algn, a_form, a_decs, a_unit);
   DEBUG_YPARSE   yLOG_info    ("t"         , t);
   strlcat  (b_control, t, LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("b_control" , b_control);
   /*---(complete)-----------------------*/
   return 1;
}

char
yPARSE_interpret        (char *a_parser, char *r_header, char *r_break, int a_max, char r_control [LEN_RECD], char r_feedback [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        c           =    0;
   char        x_ch        =  '-';
   char        x_curr      [LEN_TERSE] = "";
   char        x_error     [LEN_RECD]  = "";
   int         l           =    0;
   int         i           =    0;
   /*---(parsring)-----------------------*/
   char        x_field     [LEN_FULL]  = "";
   char        x_width     =    0;
   char        x_gap       =    0;
   char        x_dots      =  '-';
   char        x_suffix    =    0;
   char        x_algnt     =  '·';
   /*---(gyges present)------------------*/
   char        x_delm      =  '·';
   char        x_algn      =  '·';
   char        x_form      =  '·';
   char        x_decs      =  '·';
   char        x_unit      =  '·';
   /*---(valid strings)------------------*/
   char       *x_valid     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_0123456789/èéêëìíîïðñòóôõö÷øùúûüýþÿ·´±Ú§<|>,.$# ";
   /*---(outputs)------------------------*/
   char        x_header    [LEN_RECD]  = "";
   char        x_break     [LEN_RECD]  = "";
   char        x_control   [LEN_RECD]  = "";
   char        x_feedback  [LEN_RECD]  = "";
   /*---(trouble marker)-----------------*/
   char        x_boom      =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_header   != NULL)  strcpy (r_header  , "");
   if (r_break    != NULL)  strcpy (r_break   , "");
   if (r_control  != NULL)  strcpy (r_control , "");
   if (r_feedback != NULL)  strcpy (r_feedback, "");
   /*---(defense)------------------------*/
   rc = yparse__exim_prepare (a_parser, x_feedback);
   DEBUG_YPARSE   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      if (r_feedback != NULL)  strlcpy (r_feedback, x_feedback, LEN_RECD);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yparse__exim_clear (&x_width, &x_gap, &x_dots, &x_suffix, x_field, &x_delm, &x_algn, &x_form, &x_decs, &x_unit, NULL);
   l = strlen (a_parser);
   /*---(walk characters)----------------*/
   --rce;  for (i = 16; i <= l; ++i) {
      /*---(prepare loop)----------------*/
      DEBUG_YPARSE   yLOG_complex ("LOOP"      , "%3d, g=%2d w=%2d,%s, d=%c, s=%d, %c %c %c %c %c", i, x_gap, x_width, x_field, x_dots, x_suffix, x_delm, x_algn, x_form, x_decs, x_unit);
      x_ch = a_parser [i];
      DEBUG_YPARSE   yLOG_char    ("x_ch"      , x_ch);
      sprintf (x_curr , "%c", x_ch);
      if (x_ch != ' ')  sprintf (x_error, BOLD_OFF BOLD_ERR "%c" BOLD_OFF "%s", x_ch, a_parser + i + 1);
      else              sprintf (x_error, BOLD_OFF BOLD_ERR "%c" BOLD_OFF "%s", '²' , a_parser + i + 1);
      DEBUG_YPARSE   yLOG_info    ("x_curr"    , x_curr);
      /*---(handle complete field)-------*/
      rc = 0;
      rc = yparse__exim_field (&c, x_ch, x_width, x_gap, x_field, x_delm, x_algn, x_form, x_decs, x_unit, x_header, x_break, x_control);
      DEBUG_YPARSE   yLOG_value   ("field"     , rc);
      if (rc == 1) {
         yparse__exim_clear (&x_width, &x_gap, &x_dots, &x_suffix, x_field, &x_delm, &x_algn, &x_form, &x_decs, &x_unit, NULL);
         DEBUG_YPARSE   yLOG_value   ("clear"     , rc);
      }
      /*---(filters for end)-------------*/
      if (x_ch == '\0')  break;
      if (x_ch == 'æ')   break;
      /*---(defenses)--------------------*/
      if (strchr (x_valid   , x_ch) == NULL) {
         DEBUG_YPARSE   yLOG_note    ("used illegal character");
         x_boom = rce - 1;
         break;
      }
      /*---(titles)----------------------*/
      x_boom = yparse__exim_title  (x_ch, x_curr, &x_width, &x_gap, &x_dots, &x_suffix, x_field, NULL);
      if (x_boom < 0) break;
      /*---(suffix)----------------------*/
      if (x_boom >= 0)  x_boom = yparse__exim_suffix (x_ch, x_width, &x_suffix, &x_delm, &x_algn, &x_form, &x_decs, &x_unit, NULL);
      if (x_boom < 0) break;
      /*---(concatinate)-----------------*/
      if (x_feedback != NULL)  strlcat (x_feedback, x_curr, LEN_RECD);
      /*---(done)------------------------*/
   }
   /*---(check end)----------------------*/
   DEBUG_YPARSE   yLOG_value   ("x_boom"    , x_boom);
   rce -= 20;
   if (x_boom >= 0 && x_ch != 'æ') {
      DEBUG_YPARSE   yLOG_note    ("did not have æ at end");
      x_boom = rce;
      sprintf (x_error, BOLD_OFF BOLD_ERR "¢" BOLD_OFF);
   }
   /*---(check trouble)------------------*/
   DEBUG_YPARSE   yLOG_value   ("x_boom"    , x_boom);
   if (x_boom < 0) {
      if (x_feedback != NULL)  strlcat (x_feedback, x_error   , LEN_RECD);
      if (r_feedback != NULL)  strlcpy (r_feedback, x_feedback, LEN_RECD);
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, x_boom);
      return x_boom;
   }
   /*---(finish feedback)----------------*/
   strlcat (x_feedback, x_curr, LEN_RECD);
   strlcat (x_feedback, BOLD_OFF, LEN_RECD);
   if (x_header [0] != '\0')  x_header [0] = '#';
   if (x_header [1] != '\0' && x_header [1] != ' ')  x_header [1] = '#';
   if (x_break  [0] != '\0')  x_break  [0] = '#';
   if (x_break  [1] != '\0' && x_break  [1] != ' ')  x_break  [1] = '#';
   /*---(save-back)----------------------*/
   if (r_header   != NULL)  strlcpy (r_header  , x_header  , a_max);
   if (r_break    != NULL)  strlcpy (r_break   , x_break   , a_max);
   if (r_control  != NULL)  strlcpy (r_control , x_control , LEN_RECD);
   if (r_feedback != NULL)  strlcpy (r_feedback, x_feedback, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                     exporting records                        ----===*/
/*====================------------------------------------====================*/
static void      o___EXPORT__________________o (void) {;}

static FILE *s_output   = NULL;
static char  s_parser   [LEN_RECD]  = "";
static char  s_header   [LEN_RECD]  = "";
static char  s_break    [LEN_RECD]  = "";
static char  s_control  [LEN_RECD]  = "";
static char  s_feedback [LEN_RECD]  = "";
static int   s_count    =   0;
static int   s_len      =   0;
static char  s_exim     =  '-';
static char  s_titles   =  '-';
static char  s_group    =  '-';

char*
yparse__exim_timestamp  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   long        x_now       =    0;
   tTIME      *x_broke     = NULL;
   static char t           [LEN_TITLE] = "";
   /*---(handle)-------------------------*/
   x_now  = time (NULL);
   x_broke   = localtime (&x_now);
   strftime (t, LEN_TITLE, "%y.%m.%d.%H.%M.%S.%u.%W.%j", x_broke);
   /*---(complete------------------------*/
   return t;
}

char
yparse__export_clear    (void)
{
   s_count  = 0;
   s_len    = 0;
   s_exim   = '-';
   s_titles = '-';
   s_group  = '-';
   strcpy (s_parser   , "");
   strcpy (s_header   , "");
   strcpy (s_break    , "");
   strcpy (s_control  , "");
   strcpy (s_feedback , "");
   return 1;
}

char
yPARSE_export_header    (char a_file [LEN_PATH], char a_fullname [LEN_HUND], char a_cmdline [LEN_HUND], char a_oneline [LEN_HUND], char a_vernum [LEN_TERSE], char a_vertxt [LEN_HUND], char a_report [LEN_HUND], char a_parser [LEN_RECD], char c_exim, char c_titles)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_host      [LEN_HUND]  = "";
   /*---(defense)------------------------*/
   --rce;  if (a_fullname  == NULL)  return rce;
   --rce;  if (a_cmdline   == NULL)  return rce;
   --rce;  if (a_oneline   == NULL)  return rce;
   --rce;  if (a_vernum    == NULL)  return rce;
   --rce;  if (a_vertxt    == NULL)  return rce;
   --rce;  if (a_report    == NULL)  return rce;
   --rce;  if (a_parser    == NULL)  return rce;
   /*---(default)------------------------*/
   yparse__export_clear ();
   /*---(handle parser)------------------*/
   rc = yPARSE_interpret (a_parser, s_header, s_break, LEN_FULL, s_control, s_feedback);
   --rce;  if (rc < 0)    return rce;
   strlcpy (s_parser, a_parser, LEN_RECD);
   /*---(open output)--------------------*/
   rc = yENV_open (a_file, "", 'w', &s_output);
   --rce;  if (rc < 0)    return rce;
   /*---(display header)-----------------*/
   if (c_exim == 'y') {
      gethostname (x_host, LEN_HUND);
      fprintf (s_output, "#!%s%s\n", a_fullname, a_cmdline);
      fprintf (s_output, "\n");
      fprintf (s_output, "#ö origin···´··å%sæ\n", a_oneline);
      fprintf (s_output, "#ý version··´··å%s: %sæ\n", a_vernum, a_vertxt);
      fprintf (s_output, "#î time·····´··å%sæ\n", yparse__exim_timestamp());
      fprintf (s_output, "#ó machine··´··å%sæ\n", x_host);
      fprintf (s_output, "#÷ process··´··å%dæ\n", getpid ());
      fprintf (s_output, "\n");
      fprintf (s_output, "#ú title····´··å%sæ\n", a_report);
      fprintf (s_output, "%s\n", a_parser);
   } else {
      fprintf (s_output, "## %s\n", a_report);
   }
   /*---(update count)-------------------*/
   s_count  = 0;
   s_len    = strlen (s_header);
   s_exim   = c_exim;
   s_titles = c_titles;
   /*---(complete)-----------------------*/
   return 1;
}

char
yPARSE_export_group     (char a_content [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        l           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_content   == NULL)  return rce;
   /*---(handle line)--------------------*/
   l = s_len - strlen (a_content) - 7;
   fprintf (s_output, "\n\n##=== %s %*.*s\n", a_content, l, l, YSTR_EQUAL);
   /*---(handle titles)------------------*/
   if (s_titles == 'y') fprintf (s_output, "%s\n\n", s_header);
   /*---(update count)-------------------*/
   s_count = 0;
   s_group = 'y';
   /*---(complete)-----------------------*/
   return 1;
}

char
yPARSE_export_line      (char a_content [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_content   == NULL)  return rce;
   /*---(handle titles)------------------*/
   if (s_titles == 'y' && s_group == '-') {
      if      (s_count % 25 == 0) fprintf (s_output, "\n%s\n\n", s_header);
      else if (s_count %  5 == 0) fprintf (s_output, "\n%s\n\n", s_break);
   }
   /*---(handle line)--------------------*/
   fprintf (s_output, "%s\n", a_content);
   /*---(update count)-------------------*/
   ++s_count;
   s_group = '-';
   /*---(complete)-----------------------*/
   return 1;
}

char
yPARSE_export_footer    (char a_total [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(handle footer)------------------*/
   if (s_titles == 'y' && s_count %  5 >= 3) fprintf (s_output, "\n%s\n", s_break);
   if (s_exim   == 'y') {
      if (s_titles == 'y') fprintf (s_output, "\n");
      if (a_total != NULL && a_total [0] != '\0') fprintf (s_output, "%s\n\n", a_total);
      fprintf (s_output, "#ÿ end-of-data.  fatto, completare, finito, morto, sepolta, y la signora grassa sta cantando ;)\n");
   }
   /*---(close output)-------------------*/
   if (s_output == stdout) rc = yENV_close_full ("(stdout)", &s_output, '-');
   else                    rc = yENV_close      (&s_output);
   --rce;  if (rc < 0)    return rce;
   /*---(default)------------------------*/
   yparse__export_clear ();
   /*---(complete)-----------------------*/
   return 1;
}

char
yPARSE_export_OLD       (FILE *a_output, char a_shebang [LEN_HUND], char a_oneline [LEN_HUND], char a_vernum [LEN_TERSE], char a_vertxt [LEN_HUND], char a_report [LEN_HUND], int c, char c_exim, char c_titles)
{
   /*> char        rce         =  -10;                                                                                                                                                                   <* 
    *> char        rc          =    0;                                                                                                                                                                   <* 
    *> char       *x_group     = "#ù parsing··´··åID  GID··>  LN> name········<  q  a  CNT>  LN> unames············································<  LN> uids····································<æ";   <* 
    *> char       *x_gspace    = "´·  ´····  ´· ´···········  ´  ´  ´··  ´· ´·················································  ´· ´·······································  Ï";                         <* 
    *> char       *x_gheader   = "##  --gid  ln name--------  q  a  cnt  ln unames--------------------------------------------  ln uids------------------------------------  Ï";                         <* 
    *> char       *x_gbreak    = "·-  -····  ·- -···········  -  -  ··-  ·- -·················································  ·- -·······································  Ï";                         <* 
    *> char       *r, *t, *s, *h, *b;                                                                                                                                                                    <* 
    *> static char x_header    [LEN_RECD]  = "";                                                                                                                                                         <* 
    *> static char x_break     [LEN_RECD]  = "";                                                                                                                                                         <* 
    *> static char x_control   [LEN_RECD]  = "";                                                                                                                                                         <* 
    *> static char x_feedback  [LEN_RECD]  = "";                                                                                                                                                         <* 
    *> static char x_host      [LEN_HUND]  = "";                                                                                                                                                         <* 
    *> /+---(handle openning)----------------+/                                                                                                                                                          <* 
    *> if (c == 0) {                                                                                                                                                                                     <* 
    *>    rc = SHOW_parser_interpret (x_group, x_header, x_break, LEN_FULL, x_control, x_feedback);                                                                                                      <* 
    *>    /+> fprintf (my.m_output, "parsing %d\n", rc);                                  <*                                                                                                             <* 
    *>     *> fprintf (my.m_output, "## header···´··å%sæ\n", x_header);                   <*                                                                                                             <* 
    *>     *> fprintf (my.m_output, "## break····´··å%sæ\n", x_break);                    <*                                                                                                             <* 
    *>     *> fprintf (my.m_output, "## control··´··å%sæ\n", x_control);                  <*                                                                                                             <* 
    *>     *> fprintf (my.m_output, "## feedback·´··å%sæ\n", x_feedback);                 <+/                                                                                                            <* 
    *>    if ( c_exim == 'y') {                                                                                                                                                                          <* 
    *>       gethostname (x_host, LEN_HUND);                                                                                                                                                             <* 
    *>       fprintf (my.m_output, "#!/usr/local/bin/argus%s\n", my.m_cmdline);                                                                                                                          <* 
    *>       fprintf (my.m_output, "\n");                                                                                                                                                                <* 
    *>       fprintf (my.m_output, "#ö orgin····´··å%sæ\n", P_ONELINE);                                                                                                                                  <* 
    *>       fprintf (my.m_output, "#ý version··´··å%s: %sæ\n", P_VERNUM, P_VERTXT);                                                                                                                     <* 
    *>       fprintf (my.m_output, "#î time·····´··å%sæ\n", SHOW__timestamp());                                                                                                                          <* 
    *>       fprintf (my.m_output, "#ó machine··´··å%sæ\n", x_host);                                                                                                                                     <* 
    *>       fprintf (my.m_output, "#÷ process··´··å%dæ\n", getpid ());                                                                                                                                  <* 
    *>       fprintf (my.m_output, "\n");                                                                                                                                                                <* 
    *>       fprintf (my.m_output, "#ú title····´··å%sæ\n", "linux group inventory (local system)");                                                                                                     <* 
    *>       fprintf (my.m_output, "%s\n", x_group);                                                                                                                                                     <* 
    *>    } else if (c_titles == 'y') {                                                                                                                                                                  <* 
    *>       fprintf (my.m_output, "## %s\n", "group inventory");                                                                                                                                        <* 
    *>    }                                                                                                                                                                                              <* 
    *> }                                                                                                                                                                                                 <* 
    *> /+---(handle titles)------------------+/                                                                                                                                                          <* 
    *> if (c_titles == 'y') {                                                                                                                                                                            <* 
    *>    if      (c % 25 == 0) fprintf (my.m_output, "\n%s\n\n", x_header);                                                                                                                             <* 
    *>    else if (c %  5 == 0) fprintf (my.m_output, "\n%s\n\n", x_break);                                                                                                                              <* 
    *> }                                                                                                                                                                                                 <* 
    *> /+---(handle closing)-----------------+/                                                                                                                                                          <* 
    *> if (c == -1) {                                                                                                                                                                                    <* 
    *>    if (c_titles == 'y' && c %  5 >= 3) fprintf (my.m_output, "\n%s\n", x_break);                                                                                                                  <* 
    *>    if (c_exim   == 'y') {                                                                                                                                                                         <* 
    *>       if (c_titles == 'y') fprintf (my.m_output, "\n");                                                                                                                                           <* 
    *>       fprintf (my.m_output, "#ÿ end-of-data.  fatto, completare, finito, morto, sepolta, y la signora grassa sta cantando.");                                                                     <* 
    *>    }                                                                                                                                                                                              <* 
    *> }                                                                                                                                                                                                 <* 
    *> /+---(complete)-----------------------+/                                                                                                                                                          <* 
    *> return 0;                                                                                                                                                                                         <*/
}


