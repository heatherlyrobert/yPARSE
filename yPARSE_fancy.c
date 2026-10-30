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



static char s_sect  [LEN_RECD]  = "";
static char s_div   [LEN_RECD]  = "";
static char s_foot  [LEN_RECD]  = "";



/*====================------------------------------------====================*/
/*===----                     underlying support                       ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;};

char
yparse_fancy__write     (char a_line [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE yLOG_spoint  (s_qout.q_file);
   --rce;  if (s_qout.q_file == NULL) {
      DEBUG_YPARSE yLOG_snote   ("file not open");
      DEBUG_YPARSE yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YPARSE yLOG_snote   ("no line to print");
      DEBUG_YPARSE yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(print)--------------------------*/
   fprintf (s_qout.q_file, "%s\n", a_line);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE yLOG_sexit   (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                     fancy output writing                     ----===*/
/*====================------------------------------------====================*/
static void      o___FANCY___________________o (void) {;};

char
yPARSE_section          (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_fill      =    0;
   char        t           [LEN_DESC] = "";
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prepare title)------------------*/
   if (a_title != NULL)  ystrlcpy (t, a_title, LEN_DESC);
   ystrlupper (t, LEN_DESC);
   DEBUG_YPARSE   yLOG_info    ("title"     , t);
   x_len       = strlen (t);
   DEBUG_YPARSE   yLOG_value   ("x_len"     , x_len);
   /*---(prepare filler)-----------------*/
   x_fill      = 80 - 12 - x_len;
   DEBUG_YPARSE   yLOG_value   ("x_fill"    , x_fill);
   /*---(print title)--------------------*/
   yPARSE_spacer  (3);
   sprintf (s_sect, "#===[[ %s ]]%*.*s=#", t, x_fill, x_fill, YSTR_EQUAL);
   rc = yparse_fancy__write (s_sect);
   DEBUG_YPARSE  yLOG_value   ("write"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yparse_fancy__columns    (uchar *a_specs, uchar *a_labels)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_labels    [LEN_RECD]  = "";
   char        t           [LEN_RECD]  = "";
   char        u           [LEN_TERSE] = "";
   int         i           =    0;
   int         l           =    0;
   char       *p           = NULL;
   char       *n           = NULL;
   char       *p2          = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   uchar       x_spec      =  '-';
   int         x_avail     =    0;
   int         x_len       =    0;
   int         x_pre       =    0;
   int         x_mid       =    0;
   int         x_suf       =    0;
   char       *x_dashes    = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ystrlcpy (s_div, "#---verb---- § ", LEN_RECD);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_specs"   , a_specs);
   if (a_specs == NULL) {
      DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_YPARSE   yLOG_info    ("a_specs"   , a_specs);
   /*---(prepare)------------------------*/
   if (a_labels != NULL)  ystrlcpy (x_labels, a_labels, LEN_RECD);
   l = strlen (x_labels);
   p = x_labels;
   if (p != NULL)  n = strchr (x_labels, ',');
   if (n != NULL)  n [0] = '\0';
   DEBUG_YPARSE   yLOG_complex ("next"      , "%p, %d, %p, %d, %p, %d, [%s]", x_labels, l, p, p - x_labels, n, n - x_labels, p);
   /*---(walk labels)--------------------*/
   for (i = 0; i < MAX_COLS; ++i) {
      DEBUG_YPARSE   yLOG_value   ("loop"      , i);
      /*---(filter)----------------------*/
      x_spec = a_specs [i];
      DEBUG_YPARSE   yLOG_char    ("x_spec"    , x_spec);
      if (x_spec == '-')  break;
      if (x_spec ==  0 )  break;
      /*---(get width)-------------------*/
      x_avail = yparse_spec_size (x_spec);
      DEBUG_YPARSE   yLOG_value   ("x_avail"   , x_avail);
      DEBUG_YPARSE   yLOG_point   ("p"         , p);
      /*---(handle empties)--------------*/
      if (p == NULL || strlen (p) <= 0) {
         if (x_spec == 'c' || x_spec == 'C')   sprintf (u, "%c", x_spec);
         else                                  sprintf (u, "(%c)", x_spec);
         p2 = u;
      } else {
         p2 = p;
      }
      /*---(handle labels)---------------*/
      DEBUG_YPARSE   yLOG_info    ("p2"        , p2);
      x_len   = strlen (p2);
      x_pre   = x_avail - x_len;
      if (x_pre < 0)  x_pre = 0;
      if (x_pre > 3)  x_pre = 3;
      x_suf   = x_avail - x_pre - x_len;
      if (x_suf < 0)  x_suf = 0;
      x_mid   = x_avail - x_pre - x_suf;
      sprintf (t, "%*.*s%-*.*s%*.*s", x_pre, x_pre, "---", x_mid, x_mid, p2, x_suf, x_suf, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
      DEBUG_YPARSE   yLOG_info    ("t"         , t);
      /*---(concat)----------------------*/
      ystrlcat (s_div, t, LEN_RECD);
      ystrlcat (s_div, " § ", LEN_RECD);
      DEBUG_YPARSE   yLOG_info    ("s_div"     , s_div);
      /*---(next)------------------------*/
      if (n == NULL)  p = NULL;
      else {
         p = n + 1;
         if (p - x_labels + 1 >= l)  p = NULL;
         n = NULL;
      }
      if (p != NULL)  n = strchr (p, ',');
      if (n != NULL)  n [0] = '\0';
      DEBUG_YPARSE   yLOG_complex ("next"      , "%p, %d, %p, %d, %p, %d, [%s]", x_labels, l, p, p - x_labels, n, n - x_labels, p);
      /*---(done)------------------------*/
   }
   /*---(decode)-------------------------*/
   ystrldecode (s_div, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_columns          (int c, char *a_specs, char *a_labels)
{
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   if (c % 5 == 0) {
      yparse_fancy__columns (a_specs, a_labels);
      yparse_fancy__write (s_div);
   }
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_spacer           (char a_lines)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (s_qout.q_file);
   --rce;  if (s_qout.q_file == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   ("open");
   /*---(print)--------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("print");
   if (a_lines < 1)  a_lines = 1;
   if (a_lines > 5)  a_lines = 5;
   for (i = 0; i < a_lines; ++i)   fprintf  (s_qout.q_file, "\n");
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yparse_fancy__begin     (uchar *a_verb, uchar *a_specs, uchar *a_labels, uchar *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_DESC ];
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   ystrlcpy (s_div,  "", LEN_RECD);
   ystrlcpy (s_sect, "", LEN_RECD);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("a_verb"    , a_verb);
   /*---(call section header)------------*/
   if (a_desc != NULL && strcmp (a_desc, "") != 0)  ystrlcpy   (t, a_desc, LEN_DESC );
   else                                             ystrlcpy   (t, a_verb, LEN_DESC );
   ystrlupper (t, LEN_DESC );
   DEBUG_YPARSE   yLOG_info    ("t"         , t);
   yPARSE_section (t);
   /*---(create divider)-----------------*/
   yparse_fancy__columns (a_specs, a_labels);
   /*> yparse_fancy_break    (0);                                                     <*/
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_fancy_begin       (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   ystrlcpy (s_div,  "", LEN_RECD);
   ystrlcpy (s_sect, "", LEN_RECD);
   /*---(defense)------------------------*/
   --rce;  if (n < 0 || n >= G_nverb) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   rc = yparse_fancy__begin (G_verbs [n].v_verb, G_verbs [n].v_specs, G_verbs [n].v_labels, G_verbs [n].v_desc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_fancy_break      (int c)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(print)--------------------------*/
   DEBUG_YPARSE  yLOG_sint    (c);
   if (c % 5 != 0) {
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(print)--------------------------*/
   rc = yparse_fancy__write (s_div);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yparse_fancy_end        (int c)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_DESC];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   ystrlcpy (s_foot, "", LEN_RECD);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_sint    (c);
   --rce;  if (c < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(footer)-------------------------*/
   if      (c == 0)  sprintf (s_foot, "# no records required");
   else if (c == 1)  sprintf (s_foot, "# wrote a single record");
   else              sprintf (s_foot, "# wrote %d records", c);
   yparse_fancy__write (s_foot);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_footer           (int c)
{
   return yparse_fancy_end (c);
}


/*====================------------------------------------====================*/
/*===----                     public simplifiers                       ----===*/
/*====================------------------------------------====================*/
static void      o___PUBLIC__________________o (void) {;};

char
yPARSE_sect_begin       (uchar *a_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =   -1;
   int         i           =    0;
   for (i = 0; i < G_nverb; ++i) {
      if (G_verbs [i].v_verb [0] != a_verb [0])      continue;
      if (strcmp (G_verbs [i].v_verb, a_verb) != 0)  continue;
      n = i;
      break;
   }
   yparse_fancy_begin (n);
   return 0;
}

char yPARSE_sect_break       (int c) { return yparse_fancy_break (c); }
char yPARSE_sect_end         (int c) { return yparse_fancy_end   (c); }



