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
   double      a         =   0.0;
   rc = yPARSE_popval (0.0, &a);
   if (a_new != NULL)  *a_new = (char) a;
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
   char       *q           = "(,)";
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
   x_len = strllen   (q, LEN_RECD);
   for (i = c = 0; i < x_len; ++i)   c += strldcnt (a_recd, q [i], LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("fields"    , c);
   myPARSE.nfield = c;
   /*---(get first)----------------------*/
   p     = strtok_r (a_recd, q, &r);
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
      p = strtok_r (NULL  , q, &r);
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
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);
   --rce;  if (myPARSE.reusing != 'y') {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
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
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(get record)---------------------*/
   fgets (s_qin.recd, LEN_RECD, s_qin.file);
   --rce;  if (feof (s_qin.file))  {
      DEBUG_YPARSE   yLOG_snote   ("end of file reached");
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clean)--------------------------*/
   s_qin.len = strlen (s_qin.recd);
   if (s_qin.len > 0)  s_qin.recd [--s_qin.len] = 0;
   DEBUG_YPARSE   yLOG_sint    (s_qin.len);
   DEBUG_YPARSE   yLOG_snote   (s_qin.recd);
   /*---(complete)--------------------*/
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
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_note    ("must call yPARSE_init () first");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   yPARSE_purge_in ();
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
   if (a_recd == NULL) {
      if (a_line < 0) {
         rc = yparse__infile ();
         DEBUG_YPARSE  yLOG_value   ("read"      , rc);
      } else {
         rc = yparse__existing (a_line, a_label);
         DEBUG_YPARSE  yLOG_value   ("existing"  , rc);
      }
      if (rc < 0) {
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
   } else {
      strlcpy (s_qin.recd, a_recd, LEN_RECD);
      s_qin.len = strlen (s_qin.recd);
   }
   /*---(filter)-------------------------*/
   --rce;  if (s_qin.len      <  5) {
      DEBUG_YPARSE   yLOG_note    ("line too short");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (s_qin.recd [0] == '#') {
      DEBUG_YPARSE   yLOG_note    ("comment line");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(load the queue)-----------------*/
   rc = yparse_recd  (s_qin.recd);
   DEBUG_YPARSE  yLOG_value   ("queue"     , rc);
   if (rc < 0) {
      yPARSE_purge_in ();
      s_qin.good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(set as good)-----------------*/
   s_qin.good = 'y';
   /*---(pop verb)--------------------*/
   rc = yparse_peek_in   (0, myPARSE.verb);
   rc = yparse_verb_find (&s_qin, myPARSE.verb);
   if (rc < 0) {
      yPARSE_purge_in ();
      s_qin.good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   rc = myPARSE.verber ();
   if (rc < 0) {
      yPARSE_purge_in ();
      s_qin.good = 'n';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   /*---(pop verb)--------------------*/
   if (a_line < 0 && s_qin.hidden != 'y') {
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

