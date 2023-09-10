/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"

/*
 *  readers and writers must accept two arguments...
 *  1) n       reference number (out is a sequence, in is file line number)
 *  2) a_verb  the string verb name to verify and prepare
 *  these two provide excellent, targeted debugging information
 *
 *
 *
 */


#define     MAX_COLS      29
#define     MAX_VERBS     50
struct {
   /*---(master)------------*/
   uchar       mode;                        /* one char yvikeys mode id       */
   char        verb        [LEN_LABEL];     /* verb name as used in files     */
   uchar       specs       [LEN_TITLE];     /* field specifications           */
   char        mask;                        /* field for reload/change        */
   /*---(handlers)----------*/
   int         (*reader)   (int n, char *a_verb);
   int         (*writer)   (int n, char *a_verb);
   float       seq;                         /* writing sequence               */
   char        done;                        /* written (y/n)                  */
   /*---(descriptive)-------*/
   char        flags       [LEN_TITLE];     /* flags for use by program       */
   uchar       labels      [LEN_RECD];      /* field labels for headers       */
   uchar       desc        [LEN_DESC ];     /* long verb description          */
   /*---(done)--------------*/
}  static   s_verbs   [MAX_VERBS];
static int  s_nverb   = 0;

static char *s_nada = "";



static char s_sect  [LEN_RECD]  = "";
static char s_div   [LEN_RECD]  = "";
static char s_foot  [LEN_RECD]  = "";




char
yparse_verb__wipe       (char n)
{
   s_verbs [n].mode    =  '·';
   ystrlcpy (s_verbs [n].verb   , ""            , LEN_LABEL);
   ystrlcpy (s_verbs [n].specs  , "------------", LEN_TITLE);
   s_verbs [n].mask    = -1;
   s_verbs [n].reader  = NULL;
   s_verbs [n].writer  = NULL;
   ystrlcpy (s_verbs [n].flags  , "------------", LEN_TITLE);
   ystrlcpy (s_verbs [n].labels , ""            , LEN_RECD);
   ystrlcpy (s_verbs [n].desc   , ""            , LEN_DESC);
   return 0;
}

char
yPARSE_verb_purge       (void)
{
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < MAX_VERBS; ++i) {
      yparse_verb__wipe (i);
   }
   s_nverb = 0;
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_verb_init        (void)
{
   yPARSE_verb_purge ();
   return 0;
}

char
yparse_verb_find        (tQUEUE *a_queue, char *a_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   static char x_last      [LEN_LABEL] = "-";
   static char n           =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(short-cut)----------------------*/
   DEBUG_YPARSE   yLOG_spoint  (a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_snote   (a_verb);
   --rce;  if (a_verb [0] == '\0') {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(short-cut)----------------------*/
   /*> DEBUG_YPARSE   yLOG_sint    (n);                                               <*/
   /*> DEBUG_YPARSE   yLOG_snote   (x_last);                                          <*/
   /*> if (n >= 0 && strcmp (a_verb, x_last) == 0) {                                  <* 
    *>    if (a_queue != NULL)  a_queue->iverb = n;                                   <* 
    *>    DEBUG_YPARSE   yLOG_snote   ("short-cut");                                  <* 
    *>    DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);                                 <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <*/
   /*---(find entry)---------------------*/
   DEBUG_YPARSE   yLOG_sint    (s_nverb);
   --rce;  if (s_nverb <= 0) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   n = -1;
   for (i = 0; i < s_nverb; ++i) {
      if (s_verbs [i].verb [0] != a_verb [0])      continue;
      if (strcmp (s_verbs [i].verb, a_verb) != 0)  continue;
      DEBUG_YPARSE   yLOG_snote   ("FOUND");
      n = i;
      break;
   }
   /*---(save)---------------------------*/
   ystrlcpy (x_last, a_verb, LEN_LABEL);
   if (a_queue != NULL) {
      a_queue->iverb   = n;
      if (n >= 0) {
         if (a_queue == &s_qin)  a_queue->handler = s_verbs [n].reader;
         else                    a_queue->handler = s_verbs [n].writer;
      } else {
         a_queue->handler = NULL;
      }
   }
   DEBUG_YPARSE   yLOG_sint    (n);
   DEBUG_YPARSE   yLOG_snote   (x_last);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
   return n;
}

char yparse_verb_mask        (int n) { return s_verbs [n].mask; }

char
yparse_specs_next_write  (void)
{
   if (s_qout.iverb <  0       )  return -2;
   if (s_qout.count <  0       )  return -3;
   if (s_qout.count >= MAX_COLS)  return -4;
   return s_verbs [s_qout.iverb].specs [s_qout.count - 1];
}

char
yparse_specs_next_read  (void)
{
   if (s_qin.iverb <  0       )  return -2;
   if (s_qin.first <  0       )  return -3;
   if (s_qin.first >= MAX_COLS)  return -4;
   return s_verbs [s_qin.iverb].specs [s_qin.first - 1];
}

char
yparse_specs_len        (tQUEUE *a_queue)
{
   int         i           =    0;
   int         n           =    1;   /* start with one for verb  */
   if (a_queue        == NULL)  return -1;
   if (a_queue->iverb <  0   )  return -2;
   /*> DEBUG_YPARSE   yLOG_info    ("spec"      , s_verbs [a_queue->iverb].specs);    <*/
   for (i = 0; i < MAX_COLS; ++i) {
      if (s_verbs [a_queue->iverb].specs [i] == '\0')   break;
      if (s_verbs [a_queue->iverb].specs [i] == '-')    break;
      ++n;
   }
   return n;
}

char
yPARSE_handler_max      (char a_mode, char *a_verb, float a_seq, uchar *a_specs, char a_mask, void *a_reader, void *a_writer, uchar *a_flags, uchar *a_labels, uchar *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_found     =    0;
   int         n           =    0;
   char        x_specs     [LEN_TITLE] = "";
   int         l           =    0;
   /*---(defense)------------------------*/
   if (myPARSE.ready != 'y')  return -1;
   if (a_verb == NULL)        return -2;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(note)---------------------------*/
   if (a_desc != NULL) {
      DEBUG_YPARSE   yLOG_info    ("a_desc"    , a_desc);
   }
   /*---(check verb)---------------------*/
   if (myPARSE.verbs  != YPARSE_MANUAL) {
      rc = ystrlgood (a_verb, ySTR_ALNUM, LEN_USER);
      --rce;  if (rc < 0) {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check existing)-----------------*/
   n = x_found = yparse_verb_find (NULL, a_verb);
   DEBUG_YPARSE   yLOG_value   ("s_nverb"   , s_nverb);
   DEBUG_YPARSE   yLOG_value   ("find"      , n);
   if (n < 0)  n = s_nverb;
   DEBUG_YPARSE   yLOG_value   ("n"         , n);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_specs"   , a_specs);
   if (a_specs != NULL && strlen (a_specs) >  0) {
      ystrlcpy (x_specs, a_specs, LEN_TITLE);
   }
   ystrltrim (x_specs, ySTR_BOTH, LEN_TITLE);
   ystrlddel (x_specs, '-', LEN_TITLE);
   DEBUG_YPARSE   yLOG_info    ("x_specs"   , x_specs);
   --rce;  for (i = 0; i < strlen (x_specs); ++i) {
      l = yparse_field_len (x_specs [i]);
      DEBUG_YPARSE   yLOG_complex ("entry"     , "%2d, %c, %d", i, x_specs [i], l);
      if (l > 0)  continue;
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_point   ("a_reader"  , a_reader);
   DEBUG_YPARSE   yLOG_point   ("a_writer"  , a_writer);
   /*> --rce;  if (a_reader == NULL && a_writer == NULL) {                            <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);                            <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(copy values)--------------------*/
   if (a_mode   != 0   )  s_verbs [n].mode    = a_mode;
   ystrlcpy (s_verbs [n].verb  , a_verb  , LEN_LABEL);
   if (a_seq    >  0.0 )  s_verbs [n].seq     = a_seq;
   ystrlcpy (s_verbs [n].specs , x_specs , LEN_TITLE);
   s_verbs [n].mask    = a_mask;
   if (a_reader != NULL)  s_verbs [n].reader  = a_reader;
   if (a_writer != NULL)  s_verbs [n].writer  = a_writer;
   if (a_flags  != NULL)  ystrlcpy (s_verbs [n].flags , a_flags , LEN_TITLE);
   if (a_labels != NULL)  ystrlcpy (s_verbs [n].labels, a_labels, LEN_RECD);
   if (a_desc   != NULL)  ystrlcpy (s_verbs [n].desc  , a_desc  , LEN_DESC);
   /*---(update)-------------------------*/
   if (x_found < 0)  ++s_nverb;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_handler_remove   (char *a_verb)
{
   int         i           =    0;
   int         n           =   -1;
   for (i = 0; i < s_nverb; ++i) {
      if (s_verbs [i].verb [0] != a_verb [0])      continue;
      if (strcmp (s_verbs [i].verb, a_verb) != 0)  continue;
      DEBUG_YPARSE   yLOG_snote   ("FOUND");
      n = i;
      break;
   }
   if (n >= 0)  yparse_verb__wipe (n);
   return 0;
}

char*
yPARSE_verb             (int a_num)
{
   if (a_num <  0      )   return s_nada;
   if (a_num >= s_nverb)   return s_nada;
   return s_verbs [a_num].verb;
}



/*====================------------------------------------====================*/
/*===----                     fancy output writing                     ----===*/
/*====================------------------------------------====================*/
static void      o___FANCY___________________o (void) {;};

char
yparse_fancy__write     (uchar *a_line)
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

char
yPARSE_section          (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_fill      =    0;
   char        t           [LEN_RECD] = "";
   char        x_filler    [LEN_RECD] = "===========================================================================================================";
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prepare title)------------------*/
   if (a_title != NULL)  ystrlcpy (t, a_title, LEN_DESC);
   ystrlupper (t, LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("title"     , t);
   x_len       = strlen (t);
   if (x_len > 50) {
      x_len     = 50;
      t [x_len] = '\0';
   }
   /*---(prepare filler)-----------------*/
   x_fill      = 80 - 12 - x_len;
   /*---(print title)--------------------*/
   yPARSE_spacer  (3);
   sprintf (s_sect, "#===[[ %s ]]%*.*s=#", t, x_fill, x_fill, x_filler);
   yparse_fancy__write (s_sect);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
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
      x_avail = yparse_field_len (x_spec);
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
yPARSE_spacer           (char a_lines)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
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
   if (a_lines < 1)  a_lines = 1;
   if (a_lines > 5)  a_lines = 5;
   for (i = 0; i < a_lines; ++i)   fprintf  (s_qout.file, "\n");
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
   --rce;  if (n < 0 || n >= s_nverb) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   rc = yparse_fancy__begin (s_verbs [n].verb, s_verbs [n].specs, s_verbs [n].labels, s_verbs [n].desc);
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
   for (i = 0; i < s_nverb; ++i) {
      if (s_verbs [i].verb [0] != a_verb [0])      continue;
      if (strcmp (s_verbs [i].verb, a_verb) != 0)  continue;
      n = i;
      break;
   }
   yparse_fancy_begin (n);
   return 0;
}

char yPARSE_sect_break       (int c) { return yparse_fancy_break (c); }
char yPARSE_sect_end         (int c) { return yparse_fancy_end   (c); }



/*====================------------------------------------====================*/
/*===----                        major drivers                         ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVERS_________________o (void) {;};

char
yPARSE_write_all        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("s_nverb"   , s_nverb);
   /*---(prepare)------------------------*/
   for (i = 0; i < s_nverb; ++i)  s_verbs [i].done = '-';
   /*---(call writers)-------------------*/
   while (1) {
      /*---(find next)-------------------*/
      x_lowest = 999999.0;
      x_next   = -1;
      for (i = 0; i < s_nverb; ++i) {
         if (s_verbs [i].done == 'y'    )   continue;
         if (s_verbs [i].seq >=  x_lowest)  continue;
         x_lowest = s_verbs [i].seq;
         x_next   = i;
      }
      if (x_lowest > 999.0)  break;
      if (x_next   < 0    )  break;
      s_verbs [x_next].done = 'y';
      /*---(filter)----------------------*/
      DEBUG_INPT  yLOG_info    ("verb"      , s_verbs [x_next].verb);
      DEBUG_INPT  yLOG_point   ("reader"    , s_verbs [x_next].writer);
      if (s_verbs [x_next].writer == NULL)  continue;
      /*---(handle)----------------------*/
      rc = s_verbs [x_next].writer (s_qout.tline, s_verbs [x_next].verb);
      if (rc >= 0)  c += rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yPARSE_read_all         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =   -1;
   int         c           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   char        x_verb      [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   while (1) {
      rc = yPARSE_read_one (NULL, NULL);
      if (rc == 0)  {
         DEBUG_YPARSE   yLOG_note    ("end-of-file");
         break;
      }
      /*> printf ("%s\n", myPARSE.recd);                                              <*/
      if (rc <  0)  {
         DEBUG_YPARSE   yLOG_note    ("trouble reading record");
         continue;
      }
      yparse_peek_verb (&n, x_verb);
      DEBUG_YPARSE  yLOG_value   ("index"     , n);
      if (n < 0)  {
         DEBUG_YPARSE   yLOG_note    ("verb not recognized");
         continue;
      }
      DEBUG_YPARSE  yLOG_info    ("verb"      , x_verb);
      DEBUG_YPARSE  yLOG_point   ("reader"    , s_verbs [n].reader);
      if (s_verbs [n].reader == NULL) {
         DEBUG_YPARSE   yLOG_note    ("reader not assigned");
         continue;
      }
      rc = s_verbs [n].reader (s_qin.tline, x_verb);
      if (rc < 0)  {
         DEBUG_YPARSE   yLOG_note    ("handler not successful");
         continue;
      }
      ++c;
   }
   /*---(limits)-------------------------*/
   DEBUG_YPARSE  yLOG_value   ("c"         , c);
   if (c > 99)  c = 99;
   DEBUG_YPARSE  yLOG_value   ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_verb       (char *a_question, char *a_verb, int a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(preprare)-----------------------*/
   ystrlcpy  (yPARSE__unit_answer, "VERB unit        : question not understood", LEN_STR);
   /*---(check existing)-----------------*/
   if      (strcmp (a_question, "count"    ) == 0) {
      sprintf (yPARSE__unit_answer, "VERB count       : %d", s_nverb);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      n = a_seq;
      if (n < 0 || n >= MAX_VERBS)       sprintf (yPARSE__unit_answer, "VERB entry  (--) : out of range");
      else if (s_verbs [n].verb [0] == '\0') sprintf (yPARSE__unit_answer, "VERB entry  (%2d) : verb slot not used", n);
      else sprintf (yPARSE__unit_answer, "VERB entry  (%2d) : %c, %-12.12s [%-12.12s] %cr %cw %3.1fs %2dm [%-20.20s] [%-10.10s]", n, s_verbs [n].mode, s_verbs [n].verb, s_verbs [n].specs, (s_verbs [n].reader != NULL) ? 'y' : '-', (s_verbs [n].writer != NULL) ? 'y' : '-', s_verbs [n].seq, s_verbs [n].mask, s_verbs [n].labels, s_verbs [n].desc);
   }
   /*---(answer)------------------------------------------*/
   else if (strcmp (a_question, "by_name"  ) == 0) {
      if (a_verb == NULL || a_verb [0] == '\0') {
         sprintf (yPARSE__unit_answer, "VERB name   (--) : verb not given");
      } else {
         n = yparse_verb_find (NULL, a_verb);
         if (n < 0) sprintf (yPARSE__unit_answer, "VERB name   (--) : %s is unknown", a_verb);
         else       sprintf (yPARSE__unit_answer, "VERB name   (%2d) : %c, %-12.12s [%-12.12s] %cr %cw %3.1fs %2dm [%-20.20s] [%-10.10s]", n, s_verbs [n].mode, s_verbs [n].verb, s_verbs [n].specs, (s_verbs [n].reader != NULL) ? 'y' : '-', (s_verbs [n].writer != NULL) ? 'y' : '-', s_verbs [n].seq, s_verbs [n].mask, s_verbs [n].labels, s_verbs [n].desc);
      }
   }
   else if (strcmp (a_question, "section"  ) == 0) {
      ystrlcpy    (t, s_sect, LEN_RECD);
      ystrlencode (t, ySTR_NORM, LEN_RECD);
      sprintf (yPARSE__unit_answer, "VERB section     : %2d[%s]", strlen (t), t);
   }
   else if (strcmp (a_question, "divider"  ) == 0) {
      ystrlcpy    (t, s_div, LEN_RECD);
      ystrlencode (t, ySTR_NORM, LEN_RECD);
      sprintf (yPARSE__unit_answer, "VERB divider     : %2d[%s]", strlen (t), t);
   }
   else if (strcmp (a_question, "footer"   ) == 0) {
      ystrlcpy    (t, s_foot, LEN_RECD);
      ystrlencode (t, ySTR_NORM, LEN_RECD);
      sprintf (yPARSE__unit_answer, "VERB footer      : %2d[%s]", strlen (t), t);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}



