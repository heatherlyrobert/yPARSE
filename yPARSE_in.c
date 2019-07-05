/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
static      tQUEUE      s_qin;



/*--------- ----------- ----------- ----------- ------------------------------*/
typedef     struct      cLINE       tLINE;
struct      cLINE {
   int         line;
   char       *recd;
   int         uses;
   tLINE      *next;
   tLINE      *prev;
};
/*--------- ----------- ----------- ----------- ------------------------------*/
static      tLINE      *s_head      = NULL;
static      tLINE      *s_tail      = NULL;
static      int         s_count     =    0;




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
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("must call yPARSE_init () first");
      return rce;
   }
   --rce;  if (s_qin.good != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("record processing was not successful");
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse__popable         (void)
{
   if (s_qin.head == NULL)  return 0;
   return 1;
}

char yparse_init_in          (void) { return yparse_init  (&s_qin, "IN"); }
char yPARSE_purge_in         (void) { return yparse_purge (&s_qin);       }
char yparse_good_in          (void) { s_qin.good = 'y'; return 0; }

char
yPARSE_ready            (int *a_count)
{
   if (a_count != NULL)  *a_count = s_qin.count;
   return s_qin.good;
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
   rc = yparse_dequeue (&s_qin, NULL);
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
   if (a_item != NULL)  strlcpy (a_item, "", LEN_LABEL);
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
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
   rc = yparse_dequeue (&s_qin, a_item);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yparse_peek_in          (const int a_ref, char *a_item)
{
   return yparse_peek   (&s_qin, a_ref, a_item);
}

char
yparse_peek_verb        (int *a_index, char *a_verb)
{
   if (a_index != NULL)  *a_index = s_qin.iverb;
   if (a_verb  != NULL)  strlcpy (a_verb, yPARSE_verb (s_qin.iverb), LEN_LABEL);
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
   strlcpy (x_entry, a_item, LEN_LABEL);
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
   /*---(check zero markers)-------------*/
   if (x_len == 4 && strcmp (x_entry, "-.--") == 0) {
      DEBUG_YPARSE  yLOG_snote   ("zero marker");
      *a_new = 0.0;
   }
   if (x_len == 3 && strcmp (x_entry, "-.-") == 0) {
      DEBUG_YPARSE  yLOG_snote   ("zero marker");
      *a_new = 0.0;
   }
   else if (x_len == 1 && x_entry[0] == '-') {
      DEBUG_YPARSE  yLOG_snote   ("zero marker");
      *a_new = 0.0;
   }
   /*---(check min/one marker)-----------*/
   else if (x_len == 1 && x_entry[0] == '.') {
      DEBUG_YPARSE  yLOG_snote   ("min/one marker");
      *a_new = 1.0;
   }
   /*---(check unchanged marker)---------*/
   else if (x_len == 1 && x_entry[0] == '=') {
      DEBUG_YPARSE  yLOG_snote   ("unchanged marker");
      *a_new   = a_old;
   }
   /*---(check normal value)-------------*/
   else {
      if (x_len > 1 && x_entry[x_len - 1] == 'r') {
         DEBUG_YPARSE  yLOG_snote   ("relative");
         x_rel   = 'y';
         x_entry[--x_len] = 0;
      } else {
         DEBUG_YPARSE  yLOG_snote   ("normal");
      }
      *a_new = atof (x_entry);
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
   char        x_item      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE  yLOG_sdouble (a_old);
   /*---(prepare)------------------------*/
   if (a_new != NULL)  *a_new = 0.0;
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(check)--------------------------*/
   rc = yparse_dequeue (&s_qin, x_item);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YPARSE  yLOG_snote   (x_item);
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   /*---(run)----------------------------*/
   rc = yPARSE_adjval (a_old, x_item, a_new);
   if (rc < 0) {
      return rc;
   }
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
   char        t         [LEN_RECD];
   rc = yPARSE_popstr (t);
   if (a_new != NULL)  *a_new = (char) t [0];
   return rc;
}

char
yPARSE_popint           (int *a_new)
{
   char        rc        =     0;
   double      a         =   0.0;
   rc = yPARSE_popval (0.0, &a);
   if (a_new != NULL)  *a_new = (int) a;
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



/*====================------------------------------------====================*/
/*===----                         full records                         ----===*/
/*====================------------------------------------====================*/
static void      o___RECORDS_________________o (void) {;};

char         /*--> parse incomming record ----------------[ ------ [ ------ ]-*/
yparse_recd             (char *a_recd)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;               /* generic return code       */
   int         x_len       =    0;
   int         c           =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YPARSE yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("a_recd"    , a_recd);
   x_len = strllen   (a_recd, LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
   x_len = strllen   (myPARSE.delimiters, LEN_RECD);
   for (i = c = 0; i < x_len; ++i)   c += strldcnt (a_recd, myPARSE.delimiters [i], LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("fields"    , c);
   myPARSE.nfield = c;
   /*---(get first)----------------------*/
   p     = strtok_r (a_recd, myPARSE.delimiters, &r);
   DEBUG_YPARSE yLOG_point   ("p"         , p);
   c     = 0;
   /*---(read fields)--------------------*/
   while (p != NULL) {
      /*---(clean it up)-----------------*/
      strltrim (p, ySTR_BOTH, LEN_RECD);
      x_len = strllen (p, LEN_RECD);
      strlunstore (p, x_len);
      DEBUG_YPARSE yLOG_info    ("field"     , p);
      DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
      /*---(enqueue it)------------------*/
      rc = yparse_enqueue (&s_qin, p);
      DEBUG_YPARSE yLOG_value   ("enqueue"   , rc);
      ++c;
      /*---(get next)--------------------*/
      p = strtok_r (NULL  , myPARSE.delimiters, &r);
      DEBUG_YPARSE yLOG_point   ("p"         , p);
      /*---(done)------------------------*/
   }
   /*---(check tail)---------------------*/
   rc = yparse_queue_tail (&s_qin);
   DEBUG_YPARSE yLOG_value   ("fields"    , c);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_reusable         (const char a_masked)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD];
   char        x_recd      [LEN_RECD];
   tNODE      *x_curr      = NULL;
   int         c           =    1;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("masked"    , a_masked);
   /*---(short-cut)----------------------*/
   DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);
   if (myPARSE.reusing != YPARSE_REUSE) {
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YPARSE  yLOG_char    ("hidden"    , s_qin.hidden);
   --rce;  if (s_qin.hidden  == 'y') {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(start)--------------------------*/
   sprintf (x_recd, "%s (", yPARSE_verb (s_qin.iverb));
   DEBUG_YPARSE  yLOG_info    ("reusable"  , x_recd);
   /*---(clear)--------------------------*/
   x_curr = s_qin.head;
   while (x_curr != NULL) {
      if (a_masked == c)   strlcat (x_recd, "¢¢"        , LEN_RECD);
      else                 strlcat (x_recd, x_curr->item, LEN_RECD);
      strlcat (x_recd, ","         , LEN_RECD);
      DEBUG_YPARSE  yLOG_info    ("reusable"  , x_recd);
      x_curr = x_curr->next;
      ++c;
   }
   /*---(fix end)------------------------*/
   if (x_recd [strlen (x_recd) - 1] == '(')  strlcat (x_recd, ")", LEN_RECD);
   else                                      x_recd [strlen (x_recd) - 1] = ')';
   DEBUG_YPARSE  yLOG_info    ("reusable"  , x_recd);
   /*---(save)---------------------------*/
   yparse_addline (s_qin.nline, x_recd);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       getting lines                          ----===*/
/*====================------------------------------------====================*/
static void      o___PARSING_________________o (void) {;};

char         /*--> pull script record from stdin ---------[ ------ [ ------ ]-*/
yparse__infile          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_stdin     =  '-';
   char        x_bad       =  '-';
   static int  x_tries     =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (s_qin.loc != NULL && strcmp ("stdin", s_qin.loc) == 0) {
      x_stdin = 'y';
      DEBUG_YPARSE  yLOG_snote    ("stdin");
   }
   /*> printf ("loc    = %p\n", s_qin.loc);                                           <*/
   /*> if (s_qin.loc  != NULL)   printf ("loc  = %s\n", s_qin.loc);                   <*/
   /*> printf ("file = %p\n", s_qin.file);                                            <*/
   /*---(get record)---------------------*/
   x_tries = 0;
   while (1) {
      ++x_tries;
      x_bad  = '-';
      rc   = 0;
      fgets (s_qin.recd, LEN_RECD, s_qin.file);
      if (feof (s_qin.file))  {
         DEBUG_YPARSE   yLOG_snote   ("end-of-file");
         DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, 1);
         return 1;
      }
      ++s_qin.tline;
      /*---(clean)-----------------------*/
      s_qin.len = strlen (s_qin.recd);
      if (s_qin.len > 0)  s_qin.recd [--s_qin.len] = 0;
      /*> printf ("yparse__infile  %3d %3d %3d \n", x_tries, s_qin.len, s_qin.recd [0]);   <*/
      /*> printf ("yparse__infile  %3d %3d %3d %s\n", x_tries, s_qin.len, s_qin.recd [0], s_qin.recd);   <*/
      if (x_tries > 50)  break;
      DEBUG_YPARSE   yLOG_sint    (s_qin.len);
      /*---(filter)----------------------*/
      if (s_qin.recd [0] == '#') {
         DEBUG_YPARSE  yLOG_snote    ("#");
         x_bad = 'y';
         rc    = rce - 1;
      }
      else if (s_qin.len      <   5 ) {
         DEBUG_YPARSE  yLOG_snote    ("¨");
         x_bad = 'y';
         rc    = rce - 3;
      }
      /*---(break)-----------------------*/
      if (x_stdin == 'y') {
         DEBUG_YPARSE  yLOG_snote    ("stdin, breakout");
         return rc;
      } else if (x_bad == '-') {
         DEBUG_YPARSE  yLOG_snote    ("success");
         break;
      }
      /*---(next)------------------------*/
      ++s_qin.nline;
      s_qin.cline  = s_qin.nline;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*--> pull script record from history -------[ ------ [ ------ ]-*/
yparse__existing        (int a_line, char *a_label)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char       *p           = NULL;
   char        x_recd      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(retrieve)-----------------------*/
   rc = yparse_getline (a_line, x_recd);
   DEBUG_YPARSE   yLOG_value   ("getline"   , rc);
   if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YPARSE   yLOG_point   ("x_recd"    , x_recd);
   x_len = strlen (x_recd);
   DEBUG_YPARSE   yLOG_value   ("x_len"     , x_len);
   /*---(update)-------------------------*/
   p = strchr (x_recd, '¢');
   DEBUG_YPARSE   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      strlcpy (s_qin.recd, x_recd , LEN_RECD);
   } else {
      DEBUG_YPARSE   yLOG_point   ("a_label"   , a_label);
      if (a_label == NULL) {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YPARSE   yLOG_info    ("a_label"   , a_label);
      *p       = 0;
      *(p + 1) = 0;
      DEBUG_YPARSE   yLOG_point   ("x_recd"    , x_recd);
      x_len = strlen (x_recd);
      DEBUG_YPARSE   yLOG_value   ("x_len"     , x_len);
      strlcpy (s_qin.recd, x_recd , LEN_RECD);
      strlcat (s_qin.recd, a_label, LEN_RECD);
      DEBUG_YPARSE   yLOG_point   ("p + 2"     , p + 2);
      x_len = strlen (p + 2);
      DEBUG_YPARSE   yLOG_value   ("x_len"     , x_len);
      strlcat (s_qin.recd, p + 2  , LEN_RECD);
   }
   s_qin.len = strlen (s_qin.recd);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char  /*--> parse a full record -------------------[ ------ [ ------ ]-*/
yparse__main            (int *n, int *c, int a_line, char *a_recd, char *a_label)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;                /* return code for errors    */
   char        rc          =    0;
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_char    ("ready"     , myPARSE.ready);
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_note    ("must call yPARSE_init () first");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   yPARSE_purge_in ();
   /*---(defense)------------------------*/
   /*> --rce;  if (a_line < 0) {                                                      <* 
    *>    if (s_qin.label == NULL || strcmp (s_qin  s_qin.file == NULL) {             <* 
    *>    DEBUG_YPARSE   yLOG_note    ("file is not open");                           <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);                            <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(line number)--------------------*/
   DEBUG_YPARSE   yLOG_value   ("a_line"    , a_line);
   if (a_line < 0) {
      ++s_qin.nline;
      s_qin.cline  = s_qin.nline;
      DEBUG_YPARSE   yLOG_value   ("new line"  , s_qin.cline);
      s_qin.hidden = '-';
   } else if (a_line > 0) {
      s_qin.cline  = a_line;
      DEBUG_YPARSE   yLOG_value   ("old line"  , s_qin.cline);
      s_qin.hidden = '-';
   } else {
      s_qin.cline  = -1;
      DEBUG_YPARSE   yLOG_value   ("hidden"    , s_qin.cline);
      s_qin.hidden = 'y';
   }
   if (n != NULL)  *n = s_qin.nline;
   if (c != NULL)  *c = s_qin.cline;
   /*---(read)---------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      if (a_line < 0) {
         rc = yparse__infile ();
         DEBUG_YPARSE  yLOG_value   ("read"      , rc);
         if (rc == 1) {
            DEBUG_YPARSE  yLOG_note    ("end-of-file");
            yPARSE_purge_in ();
            s_qin.good = 'n';
            DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
            return 0;
         }
      } else {
         rc = yparse__existing (a_line, a_label);
         DEBUG_YPARSE  yLOG_value   ("existing"  , rc);
      }
      if (rc < 0) {
         yPARSE_purge_in ();
         s_qin.good = 'n';
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
   } else {
      strlcpy (s_qin.recd, a_recd, LEN_RECD);
      s_qin.len = strlen (s_qin.recd);
   }
   /*---(load the queue)-----------------*/
   strcpy (myPARSE.recd, s_qin.recd);
   strldchg (myPARSE.recd, G_KEY_FIELD, G_CHAR_FIELD, LEN_RECD);
   rc = yparse_recd  (s_qin.recd);
   DEBUG_YPARSE  yLOG_value   ("queue"     , rc);
   --rce;  if (rc < 0) {
      yPARSE_purge_in ();
      s_qin.good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(set as good)-----------------*/
   s_qin.good = 'y';
   DEBUG_YPARSE  yLOG_char    ("s_qin.good", s_qin.good);
   /*---(pop verb)--------------------*/
   DEBUG_YPARSE  yLOG_point   ("verber"    , myPARSE.verber);
   --rce;  if (myPARSE.verbs == YPARSE_AUTO || myPARSE.verber != NULL) {
      rc = yparse_peek_in   (0, myPARSE.verb);
      DEBUG_YPARSE  yLOG_value   ("peek"      , rc);
      if (rc < 0) {
         yPARSE_purge_in ();
         s_qin.good = 'n';
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
         return rce;
      }
      DEBUG_YPARSE  yLOG_info    ("verb"      , myPARSE.verb);
      DEBUG_YPARSE  yLOG_char    ("verbs"     , myPARSE.verbs);
      --rce;  if (myPARSE.verbs == YPARSE_AUTO) {
         rc = yparse_verb_find (&s_qin, myPARSE.verb);
         DEBUG_YPARSE  yLOG_value   ("find"      , rc);
         if (rc < 0) {
            yPARSE_purge_in ();
            s_qin.good = 'n';
            DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
            return rce;
         }
      }
      if (myPARSE.verber != NULL) {
         rc = myPARSE.verber ();
         DEBUG_YPARSE  yLOG_value   ("verber"    , rc);
         if (rc < 0) {
            yPARSE_purge_in ();
            s_qin.good = 'n';
            DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
            return rce;
         }
      }
   }
   /*---(pop verb)--------------------*/
   --rce;  if (a_line < 0 && s_qin.hidden != 'y') {
      rc = yparse_reusable (rc);
      if (rc < 0) {
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 1;
}

char yPARSE_read        (int *n, int *c)                            { return yparse__main (n, c, -1, NULL, NULL); }
char yPARSE_load        (int *n, int *c, char *a_recd)              { return yparse__main (n, c, -1, a_recd, NULL); }
char yPARSE_reload      (int *n, int *c, int a_line, char *a_label) { return yparse__main (n, c, a_line, NULL, a_label); }
char yPARSE_hidden      (int *n, int *c, char *a_recd)              { return yparse__main (n, c,  0, a_recd, NULL); }
int  yPARSE_recdno      (void)  { return s_qin.tline; }



/*====================------------------------------------====================*/
/*===----                           file control                       ----===*/
/*====================------------------------------------====================*/
static void      o___FILES___________________o (void) {;};

char yPARSE_stdin      (void)          { return yparse_open  (&s_qin, "stdin"); }
char yPARSE_open_in    (char *a_name)  { return yparse_open  (&s_qin, a_name);  }
char yPARSE_close_in   (void)          { return yparse_close (&s_qin);          }



/*====================------------------------------------====================*/
/*===----                      incomming lines                         ----===*/
/*====================------------------------------------====================*/
static void      o___LINES___________________o (void) {;};

char
yparse_line_purge       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   tLINE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(walk-thru)----------------------*/
   DEBUG_YPARSE   yLOG_sint    (s_count);
   DEBUG_YPARSE   yLOG_snote   ("walk");
   x_curr = s_head;
   while (x_curr != NULL) {
      DEBUG_YPARSE   yLOG_sint    (x_curr->line);
      /*---(list integrity)--------------*/
      if (x_curr->next == NULL) {
         s_head             = NULL;
         s_tail             = NULL;
         s_count            = 0;
      } else {
         s_head             = x_curr->next;
         x_curr->next->prev = NULL;
         --s_count;
      }
      /*---(free line)-------------------*/
      if (x_curr->recd != NULL)  free (x_curr->recd);
      free (x_curr);
      x_curr = s_head;
      /*---(done)------------------------*/
   }
   DEBUG_YPARSE   yLOG_snote   ("done");
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yparse_initline         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(purge)--------------------------*/
   yparse_line_purge ();
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yparse_getline          (const int a_line, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   tLINE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE   yLOG_sint    (a_line);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YPARSE   yLOG_snote   ("prepare");
   strlcpy (a_recd, "", LEN_RECD);
   x_curr = s_tail;
   /*---(find)---------------------------*/
   while (x_curr != NULL) {
      if (a_line == x_curr->line) {
         ++(x_curr->uses);
         strlcpy (a_recd, x_curr->recd, LEN_RECD);
         DEBUG_YPARSE   yLOG_snote   ("found");
         DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      x_curr = x_curr->prev;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_snote   ("not found");
   DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
   return -1;
}

char
yparse_addline          (const int a_line, const char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   tLINE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE   yLOG_sint    (a_line);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   x_curr = (tLINE *) malloc (sizeof (tLINE));
   DEBUG_YPARSE   yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defaults)-----------------------*/
   DEBUG_YPARSE   yLOG_snote   ("defaults");
   x_curr->line = a_line;
   x_curr->recd = strdup (a_recd);
   x_curr->next = NULL;
   x_curr->prev = NULL;
   x_curr->uses =    0;
   /*---(attatch)------------------------*/
   if (s_head == NULL) {
      DEBUG_YPARSE   yLOG_snote   ("first");
      s_head  = x_curr;
      s_tail  = x_curr;
      s_count = 1;
   } else  {
      DEBUG_YPARSE   yLOG_snote   ("append");
      s_tail->next = x_curr;
      x_curr->prev = s_tail;
      s_tail       = x_curr;
      ++s_count;
   }
   DEBUG_YPARSE   yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   variadic interface                         ----===*/
/*====================------------------------------------====================*/
static void      o___VARIADIC________________o (void) {;};

char
yPARSE_fullread         (char *a_verb, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =  -10;
   char        n           =    0;
   char        i           =    0;
   char        x_type      =  '-';
   va_list     x_vlist;
   char       *x_char      = NULL;
   int        *x_int       = NULL;
   float      *x_float     = NULL;
   double     *x_double    = NULL;
   char       *x_str       = NULL;
   char        t           [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(column count)-------------------*/
   n = yparse_col_count (&s_qin);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   /*---(cycle columns)------------------*/
   va_start (x_vlist, a_verb);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   --rce;  for (i = 1; i < n; ++i) {
      s_qin.first = i;
      x_type = yparse_col_by_first (&s_qin);
      DEBUG_YPARSE   yLOG_char    ("x_type"    , x_type);
      DEBUG_YPARSE   yLOG_value   ("first"     , s_qin.first);
      yparse_peek_in (i, &t);
      DEBUG_YPARSE   yLOG_info    ("peek"      , t);
      switch (x_type) {
      case 'c' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "char*");
         x_char    = (char *) va_arg (x_vlist, int*);
         DEBUG_YPARSE   yLOG_point   ("x_char"    , x_char);
         DEBUG_YPARSE   yLOG_value   ("*x_char"   , *x_char);
         rc = yPARSE_popchar   (x_char);
         DEBUG_YPARSE   yLOG_point   ("x_char"    , x_char);
         DEBUG_YPARSE   yLOG_value   ("*x_char"   , *x_char);
         break;
      case 's' : case 'i' : case 'l' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "int*");
         x_int     = va_arg (x_vlist, int*);
         DEBUG_YPARSE   yLOG_point   ("x_int"      , x_int);
         DEBUG_YPARSE   yLOG_value   ("*x_int"     , *x_int);
         rc = yPARSE_popint    (x_int);
         DEBUG_YPARSE   yLOG_point   ("x_int"      , x_int);
         DEBUG_YPARSE   yLOG_value   ("*x_int"     , *x_int);
         break;
      case 'k' : case 'f' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "float*");
         x_float   = (float *) va_arg (x_vlist, double*);
         DEBUG_YPARSE   yLOG_point   ("x_float"   , x_float);
         DEBUG_YPARSE   yLOG_double  ("*x_float"  , *x_float);
         rc = yPARSE_popfloat  (x_float);
         DEBUG_YPARSE   yLOG_point   ("x_float"   , x_float);
         DEBUG_YPARSE   yLOG_double  ("*x_float"  , *x_float);
         break;
      case 'd' : case 'r' : case 't' : case 'e' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "double*");
         x_double  = va_arg (x_vlist, double*);
         DEBUG_YPARSE   yLOG_double  ("*x_double" , *x_double);
         rc = yPARSE_popdouble (x_double);
         break;
      case 'C' : case 'S' : case 'T' : case 'A' :
      case 'L' : case 'D' : case 'U' : case 'F' : case 'O' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "string");
         x_str     = (char *) va_arg (x_vlist, int*);
         DEBUG_YPARSE   yLOG_point   ("x_str"     , x_str);
         DEBUG_YPARSE   yLOG_info    ("x_str"    , x_str);
         rc = yPARSE_popstr    (x_str);
         DEBUG_YPARSE   yLOG_point   ("x_str"     , x_str);
         DEBUG_YPARSE   yLOG_info    ("x_str"    , x_str);
         break;
      default  :
         DEBUG_YPARSE   yLOG_bullet  (i           , "unknown type");
         va_end (x_vlist);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
      DEBUG_YPARSE   yLOG_value   ("pop"       , rc);
      if (rc < 0)  {
         va_end (x_vlist);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
   }
   va_end (x_vlist);
   s_qin.good = 'R';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_in         (char *a_question, int a_num)
{
   return yparse__unit_queue (&s_qin, a_question, a_num);
}

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_line       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(preprare)-----------------------*/
   strlcpy  (yPARSE__unit_answer, "LINE unit        : question not understood", LEN_STR);
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "stats"    ) == 0) {
      sprintf (yPARSE__unit_answer, "LINE stats     : nline %2d, cline %2d, total %2d", s_qin.nline, s_qin.cline, s_count);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      if (s_count < 1 || a_num > s_qin.nline) {
         sprintf (yPARSE__unit_answer, "LINE entry  %2d : null", a_num);
      } else {
         rc = yparse_getline (a_num, t);
         if (rc < 0) {
            sprintf (yPARSE__unit_answer, "LINE entry  %2d : not reusable", a_num);
         } else {
            sprintf (yPARSE__unit_answer, "LINE entry  %2d : %2d[%s]", a_num, strlen (t), t);
         }
      }
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}


char         /*-> add item to end of queue -----------[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_enqueue_in       (char *a_item)
{
   return yparse_enqueue (&s_qin, a_item);
}

