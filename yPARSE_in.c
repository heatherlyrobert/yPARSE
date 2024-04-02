/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
tQUEUE      s_qin;



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
      DEBUG_YPARSE   yLOG_snote   ("must call yPARSE_config () first");
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
yparse_in_fakeready     (void)
{
   myPARSE.ready = 'y';
   s_qin.good    = 'y';
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
char yPARSE_reset_in         (void) { return yparse_reset (&s_qin);       }
char yparse_good_in          (void) { s_qin.good = 'y'; return 0; }

char
yPARSE_ready            (int *a_count)
{
   if (a_count != NULL)  *a_count = s_qin.count;
   return s_qin.good;
}

char
yPARSE_qin_info          (char *a_label, char *a_loc, void **a_file, int *t)
{
   if (a_label != NULL)  ystrlcpy (a_label, s_qin.label   , LEN_LABEL);
   if (a_loc   != NULL) {
      if (s_qin.loc != NULL)  ystrlcpy (a_loc  , s_qin.loc      , LEN_HUND);
      else                    ystrlcpy (a_loc  , "-"            , LEN_HUND);
   }
   if (a_file  != NULL)  *a_file =  s_qin.file;
   if (t       != NULL)  *t      =  s_qin.tline;
   return 0;
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
   if (a_item != NULL)  ystrlcpy (a_item, "", LEN_LABEL);
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   DEBUG_YPARSE  yLOG_sint       (rc);
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
   DEBUG_YPARSE  yLOG_sint    (rc);
   DEBUG_YPARSE  yLOG_snote   (a_item);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_top              (char *a_item)
{
   return yparse_topqueue (&s_qin, a_item);
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
   if (a_verb  != NULL)  ystrlcpy (a_verb, yPARSE_verb (s_qin.iverb), LEN_LABEL);
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
   char        x_suffix    =  ' ';
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
   ystrlcpy (x_entry, a_item, LEN_LABEL);
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
   /*---(zero degree markers)------------*/
   --rce;  if (strncmp (x_entry, "-.--", 4) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("zero degree");
      x_suffix = x_entry [4];
      if (x_suffix == ' ')  x_suffix = x_entry [5];
      switch (x_suffix) {
      case '\0' :
         DEBUG_YPARSE  yLOG_snote   ("implicit relative");
         *a_new  = a_old;
         break;
      case 'r'  :
         DEBUG_YPARSE  yLOG_snote   ("explicit relative");
         *a_new  = a_old;
         break;
      case 'a'  : case '='  :
         DEBUG_YPARSE  yLOG_snote   ("center absolute");
         *a_new  = 0.0;
         break;
      case 'g'  :
         DEBUG_YPARSE  yLOG_snote   ("ground absolute");
         *a_new  = 0.0;
         break;  /* absolute ground     */
      default   :
         DEBUG_YPARSE  yLOG_snote   ("unknown marker");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
         return rce;
      }
   }
   /*---(zero distance markers)----------*/
   else if (strncmp (x_entry, "-.-", 3) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("zero distance");
      x_suffix = x_entry [3];
      if (x_suffix == ' ')  x_suffix = x_entry [4];
      switch (x_suffix) {
      case '\0' :
         DEBUG_YPARSE  yLOG_snote   ("implicit relative");
         *a_new  = a_old;
         break;
      case 'r'  :
         DEBUG_YPARSE  yLOG_snote   ("explicit relative");
         *a_new  = a_old;
         break;
      case 'a'  : case '='  :
         DEBUG_YPARSE  yLOG_snote   ("center absolute");
         *a_new  = 0.0;
         break;
      case 'g'  :
         DEBUG_YPARSE  yLOG_snote   ("ground absolute");
         *a_new  = 0.0;
         break;
      default   :
         DEBUG_YPARSE  yLOG_snote   ("unknown marker");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
         return rce;
      }
   }
   /*---(no-change markers)--------------*/
   else if (x_len == 1 && strchr ("+-=&~.\"", x_entry [0]) != 0) {
      DEBUG_YPARSE  yLOG_snote   ("universal no-change");
      *a_new  = a_old;
   }
   /*---(filling marker)-----------------*/
   else if (x_len == 1 && x_entry [0] == '*') {
      DEBUG_YPARSE  yLOG_snote   ("universal fill passage/section");
      *a_new  = 10001;
   }
   /*---(check normal value)-------------*/
   else {
      DEBUG_YPARSE  yLOG_snote   ("normal entry");
      if (x_len > 1) {
         switch (x_entry [x_len - 1]) {
         case 'r' :
            DEBUG_YPARSE  yLOG_snote   ("explicit relative");
            x_entry [--x_len] = 0;
            x_rel = 'y';
            break;
         case 'a' : case '=' :
            DEBUG_YPARSE  yLOG_snote   ("center absolute");
            x_entry [--x_len] = 0;
            x_rel = '-';
            break;
         case 'g'  :
            DEBUG_YPARSE  yLOG_snote   ("ground absolute");
            x_entry [--x_len] = 0;
            x_rel = '-';
            break;
         default  :
            DEBUG_YPARSE  yLOG_snote   ("implicit absolute");
            x_rel = '-';
            break;
         }
      } else {
         DEBUG_YPARSE  yLOG_snote   ("implicit absolute");
         x_rel = '-';
      }
      *a_new = atof (x_entry);
      DEBUG_YPARSE  yLOG_sint    (*a_new);
      DEBUG_YPARSE  yLOG_sdouble (a_old);
      DEBUG_YPARSE  yLOG_schar   (x_rel);
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
   uchar       x_item      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE  yLOG_sdouble (a_old);
   /*---(prepare)------------------------*/
   if (a_new != NULL)  *a_new = 0.0;
   /*---(defense)------------------------*/
   rc = yparse_in_defense ();
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   rc = yparse_dequeue (&s_qin, x_item);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (x_item);
   /*---(cdefense)-----------------------*/
   --rce;  if (x_item [0] == (uchar) '¬') {
      if (a_new != NULL)  *a_new = -666.0;
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   /*---(run)----------------------------*/
   rc = yPARSE_adjval (a_old, x_item, a_new);
   if (rc < 0) return rc;
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
   uchar       t         [LEN_RECD];
   rc = yPARSE_popstr (t);
   DEBUG_YPARSE yLOG_info    ("t"         , t);
   DEBUG_YPARSE yLOG_point   ("a_new"     , a_new);
   if (a_new != NULL) {
      *a_new = t [0];
      DEBUG_YPARSE yLOG_char    ("*a_new"    , *a_new);
   }
   return rc;
}

char
yPARSE_popint           (int *a_new)
{
   char        rc        =     0;
   double      a         =   0.0;
   rc = yPARSE_popval (0.0, &a);
   DEBUG_YPARSE yLOG_value   ("a"         , a);
   if (a_new != NULL)  *a_new = (int) a;
   return rc;
}

char
yPARSE_poplong          (llong *a_new)
{
   char        rc        =     0;
   double      a         =   0.0;
   rc = yPARSE_popval (0.0, &a);
   if (a_new != NULL)  *a_new = (llong) a;
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

char
yPARSE_popexp           (double *a_new)
{
   char        rc        =     0;
   uchar       t         [LEN_RECD];
   double      a         =   0.0;
   rc = yPARSE_popstr (t);
   DEBUG_YPARSE yLOG_info    ("t"         , t);
   if (a_new != NULL) 
      if (t [0] == (uchar) '¬')  a = -666.0;
      else                       ystrl2real (t, &a, LEN_RECD);
   DEBUG_YPARSE yLOG_double  ("a"         , a);
   if (a_new != NULL)  *a_new = a;
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         full records                         ----===*/
/*====================------------------------------------====================*/
static void      o___RECORDS_________________o (void) {;};

char         /*--> parse incomming record ----------------[ ------ [ ------ ]-*/
yparse_recd             (uchar *a_recd)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;               /* generic return code       */
   int         x_len       =    0;
   int         c           =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   int         i           =    0;
   char       *s           =  "·";
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YPARSE yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("a_recd"    , a_recd);
   x_len = ystrllen   (a_recd, LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
   DEBUG_YPARSE yLOG_info    ("delimit"   , myPARSE.delimiters);
   x_len = ystrllen   (myPARSE.delimiters, LEN_RECD);
   for (i = c = 0; i < x_len; ++i)   c += ystrldcnt (a_recd, myPARSE.delimiters [i], LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("fields"    , c);
   myPARSE.nfield = c;
   /*---(get first)----------------------*/
   p     = strtok_r (a_recd, myPARSE.delimiters, &r);
   DEBUG_YPARSE yLOG_point   ("p"         , p);
   c     = 0;
   /*---(read fields)--------------------*/
   while (p != NULL) {
      /*---(clean it up)-----------------*/
      ystrltrim (p, ySTR_BOTH, LEN_RECD);
      x_len = ystrllen (p, LEN_RECD);
      if (x_len == 0 && myPARSE.fill == YPARSE_FILL)  p = s;
      else                                            ystrlunstore (p, x_len);
      DEBUG_YPARSE yLOG_info    ("field"     , p);
      DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
      /*---(enqueue it)------------------*/
      rc = yparse_enqueue_full (&s_qin, p);
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
yPARSE_set_reuse        (void)
{
   myPARSE.reusing = 'y';
   DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);
   return 0;
}

char
yparse_reusable         (char a_masked)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD] = "";
   tNODE      *x_curr      = NULL;
   int         c           =    1;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("masked"    , a_masked);
   /*---(short-cut)----------------------*/
   DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);
   if (myPARSE.reusing != YPARSE_REUSING) {
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
   --rce;  if (a_masked >= s_qin.count) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_masked < 1)  a_masked = -1;
   /*> --rce;  if (s_qin.count <= 1) {                                                <* 
    *>    DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   DEBUG_YPARSE  yLOG_info    ("verb"      , myPARSE.verb);
   DEBUG_YPARSE  yLOG_value   ("iverb"     , s_qin.iverb);
   --rce;  if (s_qin.iverb < 0 || strcmp (myPARSE.verb, "") == 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(start)--------------------------*/
   /*> sprintf (x_recd, "%s (", yPARSE_verb (s_qin.iverb));                           <*/
   sprintf (x_recd, "%s (", myPARSE.verb);
   /*> DEBUG_YPARSE  yLOG_info    ("reusable"  , x_recd);                             <*/
   /*---(clear)--------------------------*/
   x_curr = s_qin.head;
   while (x_curr != NULL) {
      if (a_masked == c)   ystrlcat (x_recd, "¢¢"        , LEN_RECD);
      else                 ystrlcat (x_recd, x_curr->item, LEN_RECD);
      ystrlcat (x_recd, ","         , LEN_RECD);
      DEBUG_YPARSE  yLOG_complex ("reusable"  , "%2d, %20.20s, %s", c, x_curr->item, x_recd);
      x_curr = x_curr->next;
      ++c;
   }
   /*---(fix end)------------------------*/
   if (x_recd [strlen (x_recd) - 1] == '(')  ystrlcat (x_recd, ")", LEN_RECD);
   else                                      x_recd [strlen (x_recd) - 1] = ')';
   DEBUG_YPARSE  yLOG_info    ("reusable"  , x_recd);
   /*---(save)---------------------------*/
   /*> yparse_addline (s_qin.nline, x_recd);                                          <*/
   yparse_addline (s_qin.tline, x_recd);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       getting lines                          ----===*/
/*====================------------------------------------====================*/
static void      o___PARSING_________________o (void) {;};

char
yparse__comments        (char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_eof       =  '-';
   /*---(defense)------------------------*/
   if (a_recd == NULL) return 0;
   /*---(filtering)----------------------*/
   if      (strncmp (a_recd, "# END-OF-FILE" , 12) == 0)         x_eof = 'y';
   else if (strncmp (a_recd, "# end-of-file" , 12) == 0)         x_eof = 'y';
   else if (strncmp (a_recd, "# done, finito", 12) == 0)         x_eof = 'y';
   /*---(trouble)------------------------*/
   if (x_eof == 'y') {
      DEBUG_YPARSE   yLOG_snote   ("end-of-file");
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   /*---(complete)-----------------------*/
   return 0;
}

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
   DEBUG_YPARSE   yLOG_snote   (s_qin.loc);
   if (s_qin.loc != NULL && strcmp ("stdin", s_qin.loc) == 0)  x_stdin = 'y';
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
      DEBUG_YPARSE  yLOG_sint     (s_qin.tline);
      /*---(clean)-----------------------*/
      s_qin.len = strlen (s_qin.recd);
      if (s_qin.len > 0)  s_qin.recd [--s_qin.len] = 0;
      /*> DEBUG_YPARSE   yLOG_snote   (s_qin.recd);                                   <*/
      /*> printf ("yparse__infile  %3d %3d %3d \n", x_tries, s_qin.len, s_qin.recd [0]);   <*/
      /*> printf ("yparse__infile  %3d %3d %3d %s\n", x_tries, s_qin.len, s_qin.recd [0], s_qin.recd);   <*/
      if (x_tries > 50)  {
         DEBUG_YPARSE  yLOG_snote    ("too many tries (>50)");
         break;
      }
      DEBUG_YPARSE   yLOG_sint    (s_qin.len);
      /*---(filter)----------------------*/
      if (s_qin.recd [0] == '#') {
         DEBUG_YPARSE  yLOG_snote    ("# comment");
         rc = yparse__comments (s_qin.recd);
         x_bad = 'y';
      }
      else if (s_qin.recd [0] == '\0') {
         DEBUG_YPARSE  yLOG_snote    ("£ null/empty");
         x_bad = 'y';
      }
      else if (s_qin.len      <   5 ) {
         DEBUG_YPARSE  yLOG_snote    ("too short (<5c)");
         x_bad = 'y';
      }
      /*---(break)-----------------------*/
      /*> if (x_stdin == 'y') {                                                                 <* 
       *>    DEBUG_YPARSE  yLOG_snote    ("stdin, breakout");                                   <* 
       *>    DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rc);                                    <* 
       *>    /+> return rc;                                                               <+/   <* 
       *> }                                                                                     <*/
      if (rc >= 1) {
         DEBUG_YPARSE  yLOG_snote    ("end of file");
         DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
         return 1;
      }
      if (x_bad == '-') {
         DEBUG_YPARSE  yLOG_snote    ("success");
         break;
      }
      /*---(next)------------------------*/
      DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
      DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
      /*> ++s_qin.nline;                                                              <* 
       *> s_qin.cline  = s_qin.nline;                                                 <*/
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
      ystrlcpy (s_qin.recd, x_recd , LEN_RECD);
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
      ystrlcpy (s_qin.recd, x_recd , LEN_RECD);
      ystrlcat (s_qin.recd, a_label, LEN_RECD);
      DEBUG_YPARSE   yLOG_point   ("p + 2"     , p + 2);
      x_len = strlen (p + 2);
      DEBUG_YPARSE   yLOG_value   ("x_len"     , x_len);
      ystrlcat (s_qin.recd, p + 2  , LEN_RECD);
   }
   s_qin.len = strlen (s_qin.recd);
   DEBUG_YPARSE   yLOG_info    ("recd"      , s_qin.recd);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse__main_rollback   (int a_line)
{
   yPARSE_purge_in ();
   s_qin.good = 'n';
   if (a_line < 0) {
      --s_qin.nline;
      s_qin.cline  = s_qin.nline;
   }
   return 0;
}

char  /*--> parse a full record -------------------[ ------ [ ------ ]-*/
yparse__main            (char *a_func, int *t, int *n, int *c, int a_line, char *a_recd, char *a_label, char *a_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;                /* return code for errors    */
   char        rc          =    0;
   char        x_type      =  '-';
   char        x_index     =   -1;
   char        x_mask      =   -1;
   char        x_exist     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (a_func);
   /*---(default)------------------------*/
   if (t != NULL)  *t = 0;
   if (n != NULL)  *n = 0;
   if (c != NULL)  *c = 0;
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_char    ("ready"     , myPARSE.ready);
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_note    ("must call yPARSE_config () first");
      DEBUG_YPARSE   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   yPARSE_purge_in ();
   /*---(temporary verbs)----------------*/
   if (myPARSE.verbs  == YPARSE_MANUAL) {
      DEBUG_YPARSE  yLOG_note    ("single use verb/handlers, purge before each");
      yPARSE_verb_purge ();
   }
   /*---(defense)------------------------*/
   /*> --rce;  if (a_line < 0) {                                                      <* 
    *>    if (s_qin.label == NULL || strcmp (s_qin  s_qin.file == NULL) {             <* 
    *>    DEBUG_YPARSE   yLOG_note    ("file is not open");                           <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (a_func, rce);                            <* 
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
            yparse__main_rollback (a_line);
            DEBUG_YPARSE  yLOG_exit    (a_func);
            return 0;
         }
      } else {
         rc = yparse__existing (a_line, a_label);
         DEBUG_YPARSE  yLOG_value   ("existing"  , rc);
      }
      if (rc < 0) {
         yparse__main_rollback (a_line);
         DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
         return rc;
      }
   } else {
      ystrlcpy (s_qin.recd, a_recd, LEN_RECD);
      s_qin.len = strlen (s_qin.recd);
   }
   if (t != NULL)  *t = s_qin.tline;
   /*---(load the queue)-----------------*/
   strcpy (myPARSE.recd, s_qin.recd);
   ystrldchg (myPARSE.recd, G_KEY_FIELD, G_CHAR_FIELD, LEN_RECD);
   rc = yparse_recd  (s_qin.recd);
   DEBUG_YPARSE  yLOG_value   ("queue"     , rc);
   --rce;  if (rc < 0) {
      yparse__main_rollback (a_line);
      DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
      return rc;
   }
   /*---(set as good)-----------------*/
   s_qin.good = 'y';
   DEBUG_YPARSE  yLOG_char    ("s_qin.good", s_qin.good);
   /*---(peek at verb)----------------*/
   rc = yparse_peek_in   (0, myPARSE.verb);
   yPARSE_toss ();  /* verb */
   DEBUG_YPARSE  yLOG_value   ("peek"      , rc);
   if (rc < 0) {
      yparse__main_rollback (a_line);
      DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("verb"      , myPARSE.verb);
   /*---(auto process verb)-----------*/
   DEBUG_YPARSE  yLOG_char    ("verbs"     , myPARSE.verbs);
   --rce;  if (myPARSE.verbs == YPARSE_AUTO) {
      x_index = yparse_verb_find (&s_qin, myPARSE.verb);
      DEBUG_YPARSE  yLOG_value   ("find"      , x_index);
      if (x_index < 0) {
         if (myPARSE.verber == NULL) {
            DEBUG_YPARSE  yLOG_note    ("verb unrecognized and verber not active");
            yparse__main_rollback (a_line);
            DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
            return rce;
         }
         DEBUG_YPARSE  yLOG_note    ("verb unrecognized, verber will need to sort out");
      }
   }
   /*---(contact callback)------------*/
   DEBUG_YPARSE  yLOG_point   ("verber"    , myPARSE.verber);
   --rce;  if (myPARSE.verber != NULL) {
      if (x_index >= 0)  x_exist = 'y';
      rc = myPARSE.verber (s_qin.tline, myPARSE.verb, x_exist, s_qin.handler);
      DEBUG_YPARSE  yLOG_value   ("verber"    , rc);
      if (rc < 0) {
         yparse__main_rollback (a_line);
         DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
         return rce;
      }
   }
   /*---(check resuse)----------------*/
   DEBUG_YPARSE  yLOG_complex ("reusing"   , "%c, %d, %c", myPARSE.reusing, a_line, s_qin.hidden);
   --rce;  if (myPARSE.reusing == 'y' && a_line < 0 && s_qin.hidden != 'y') {
      DEBUG_YPARSE  yLOG_note    ("preparing/saving for reuse");
      if (x_index < 0)  x_index = yparse_verb_find (&s_qin, myPARSE.verb);
      x_mask = yparse_verb_mask (x_index);
      rc = yparse_reusable (x_mask);
      if (rc < 0) {
         DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
         return rce;
      }
   }
   /*---(result)-------------------------*/
   DEBUG_YPARSE   yLOG_value   ("count"     , s_qin.count);
   if (a_verb != NULL)  ystrlcpy (a_verb, myPARSE.verb, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (a_func);
   return s_qin.count;
}

char yPARSE_read        (int *t, int *n, int *c, uchar *a_verb)     { return yparse__main (__FUNCTION__, t, n, c, -1, NULL, NULL, a_verb); }
char yPARSE_read_one    (int *n, uchar *a_verb)                     { return yparse__main (__FUNCTION__, NULL, n, NULL, -1, NULL, NULL, a_verb); }
char yPARSE_load        (int *n, int *c, char *a_recd)              { return yparse__main (__FUNCTION__, NULL, n, c, -1, a_recd, NULL, NULL); }
char yPARSE_reload      (int *n, int *c, int a_line, char *a_label) { return yparse__main (__FUNCTION__, NULL, n, c, a_line, NULL, a_label, NULL); }
char yPARSE_hidden      (int *n, int *c, char *a_recd)              { return yparse__main (__FUNCTION__, NULL, n, c,  0, a_recd, NULL, NULL); }
int  yPARSE_recdno      (void)  { return s_qin.tline; }

char yPARSE_inrecd      (char a_recd [LEN_RECD]) { ystrlcpy (a_recd, myPARSE.recd, LEN_RECD); }


/*====================------------------------------------====================*/
/*===----                           file control                       ----===*/
/*====================------------------------------------====================*/
static void      o___FILES___________________o (void) {;};

char yPARSE_stdin      (void)          { return yparse_open  (&s_qin, "stdin"); }
char yPARSE_tmpin      (void)          { return yparse_open  (&s_qin, "/tmp/yparse.txt"); };
char yPARSE_open_in    (char *a_name)  { return yparse_open  (&s_qin, a_name);  }
char yPARSE_close_in   (void)          { return yparse_close (&s_qin);          }

char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
yPARSE_stdin_peek       (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;
   int         x_flags     =    0;
   int         x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(set stdin to non-blocking)------*/
   DEBUG_INPT   yLOG_note    ("make stdin non-blocking");
   x_flags = fcntl (STDIN_FILENO, F_GETFL, 0);
   rc = fcntl (STDIN_FILENO,  F_SETFL, x_flags | O_NONBLOCK);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_value   ("errno"     , errno);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, non-blocking");
   }
   /*---(test stdin for input)-----------*/
   DEBUG_INPT   yLOG_note    ("test for input on stdin");
   x_ch = getc (stdin);
   ungetc (x_ch, stdin);
   /*---(put stdin back to normal)-------*/
   DEBUG_INPT   yLOG_note    ("put stdin back to blocking");
   rc = fcntl  (STDIN_FILENO, F_SETFL, x_flags);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_value   ("errno"     , errno);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, back to blocking");
   }
   /*---(test stdin for input)-----------*/
   DEBUG_INPT   yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch == -1) {
      DEBUG_INPT   yLOG_note    ("no input available");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, input found");
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



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
   ystrlcpy (a_recd, "", LEN_RECD);
   x_curr = s_tail;
   /*---(find)---------------------------*/
   while (x_curr != NULL) {
      if (a_line == x_curr->line) {
         ++(x_curr->uses);
         ystrlcpy (a_recd, x_curr->recd, LEN_RECD);
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
yparse_in_variadic      (va_list a_vlist, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   uchar       x_type      =  '-';
   uchar      *x_char      = NULL;
   int        *x_short     = NULL;
   int        *x_int       = NULL;
   llong      *x_long      = NULL;
   float      *x_float     = NULL;
   double     *x_double    = NULL;
   uchar      *x_str       = NULL;
   uchar       x_work      [LEN_RECD] = "";
   int         a           =    0;
   int         c           =    0;
   uchar       t           [LEN_RECD] = "";
   double      x_val       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("n"         , n);
   DEBUG_YPARSE  yLOG_value   ("first"     , s_qin.first);
   /*---(check position)-----------------*/
   if (s_qin.first == 0)   yPARSE_toss ();
   /*---(walk fields)--------------------*/
   --rce;  for (i = 1; i < n; ++i) {
      x_type = yparse_specs_next_read ();
      yparse_peek_in (i, &t);
      DEBUG_YPARSE   yLOG_complex ("FIELD"     , "%2d, %c, %2d, %s", i, x_type, s_qin.first, t);
      switch (x_type) {
      case 'c' :
         x_char    = (char *) va_arg (a_vlist, int*);
         if (x_char == NULL) {
            DEBUG_YPARSE   yLOG_note    ("char type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popchar   (x_char);
         DEBUG_YPARSE   yLOG_complex ("char"      , "%d, %c, %3d, %p, %d", i, x_type, rc, x_char, *x_char);
         break;
      case 's' :
         x_short   = (short *) va_arg (a_vlist, int*);
         if (x_short == NULL) {
            DEBUG_YPARSE   yLOG_note    ("short type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popint    (&a);
         *x_short = a;
         DEBUG_YPARSE   yLOG_complex ("short"     , "%d, %c, %3d, %p, %d", i, x_type, rc, x_short, *x_short);
         break;
      case 'i' :
         x_int     = va_arg (a_vlist, int*);
         if (x_int == NULL) {
            DEBUG_YPARSE   yLOG_note    ("int type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popint    (x_int);
         DEBUG_YPARSE   yLOG_complex ("int"       , "%d, %c, %3d, %p, %d", i, x_type, rc, x_int, *x_int);
         break;
      case ',' :
         x_int     = va_arg (a_vlist, int*);
         if (x_int == NULL) {
            DEBUG_YPARSE   yLOG_note    ("comma type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popstr    (x_work);
         if (x_work [0] == (uchar) '¬')  x_val = -666.0;
         else  ystrl2comma (x_work, &x_val, LEN_LABEL);
         *x_int = (int) x_val;
         DEBUG_YPARSE   yLOG_complex ("comma"     , "%d, %c, %3d, %s, %lf, %p, %d", i, x_type, rc, x_work, x_val, x_int, *x_int);
         break;
      case 'l' : case 'h' :
         x_long    = va_arg (a_vlist, llong*);
         if (x_long == NULL) {
            DEBUG_YPARSE   yLOG_note    ("long type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_poplong   (x_long);
         DEBUG_YPARSE   yLOG_complex ("long"      , "%d, %c, %3d, %p, %ld", i, x_type, rc, x_long, *x_long);
         break;
      case ';' :
         x_long    = va_arg (a_vlist, llong*);
         if (x_long == NULL) {
            DEBUG_YPARSE   yLOG_note    ("hcomma type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popstr    (x_work);
         if (x_work [0] == (uchar) '¬')  x_val = -666.0;
         else  ystrl2comma (x_work, &x_val, LEN_LABEL);
         *x_long = (llong) x_val;
         DEBUG_YPARSE   yLOG_complex ("hcomma"    , "%d, %c, %3d, %s, %lf, %p, %ld", i, x_type, rc, x_work, x_val, x_long, *x_long);
         break;
      case 'k' : case 'f' :
         x_float   = (float *) va_arg (a_vlist, float*);
         if (x_float == NULL) {
            DEBUG_YPARSE   yLOG_note    ("float type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popfloat  (x_float);
         DEBUG_YPARSE   yLOG_complex ("float"     , "%d, %c, %3d, %p, %f", i, x_type, rc, x_float, (x_float == NULL) ? -666.0 : *x_float);
         break;
      case 'd' : case 't' : 
         x_double  = va_arg (a_vlist, double*);
         if (x_double == NULL) {
            DEBUG_YPARSE   yLOG_note    ("double type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popdouble (x_double);
         DEBUG_YPARSE   yLOG_complex ("double"    , "%d, %c, %3d, %p, %lf", i, x_type, rc, x_double, *x_double);
         break;
      case 'e' : case 'm' : case 'b' :
         x_double  = va_arg (a_vlist, double*);
         if (x_double == NULL) {
            DEBUG_YPARSE   yLOG_note    ("exp type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popexp    (x_double);
         DEBUG_YPARSE   yLOG_complex ("exp"       , "%d, %c, %3d, %p, %lf", i, x_type, rc, x_double, *x_double);
         break;
      case 'C' : case 'S' : case 'T' : case 'U' : case 'L' :
      case '3' : case '4' : case 'D' : case '5' : case '6' :
      case '7' : case '8' : case 'H' : case 'F' : case 'R' : case 'O' :
         DEBUG_YPARSE  yLOG_note    ("string");
         x_str     = (char *) va_arg (a_vlist, int*);
         if (x_str == NULL) {
            DEBUG_YPARSE   yLOG_note    ("string type, return null");
            yPARSE_toss ();
            break;
         }
         rc = yPARSE_popstr    (x_work);
         DEBUG_YPARSE  yLOG_value   ("popstr"    , rc);
         DEBUG_YPARSE  yLOG_info    ("x_work"    , x_work);
         if (x_str != NULL) {
            switch (x_type) {
            case 'C'  : *x_str = x_work [0];                  break;
            case 'S'  : ystrlcpy (x_str, x_work, LEN_SHORT);   break;
            case 'T'  : ystrlcpy (x_str, x_work, LEN_TERSE);   break;
            case 'U'  : ystrlcpy (x_str, x_work, LEN_USER );   break;
            case 'L'  : ystrlcpy (x_str, x_work, LEN_LABEL);   break;
            case '3'  : ystrlcpy (x_str, x_work, LEN_TITLE);   break;
            case '4'  : ystrlcpy (x_str, x_work, 40       );   break;
            case 'D'  : ystrlcpy (x_str, x_work, LEN_DESC );   break;
            case '6'  : ystrlcpy (x_str, x_work, 60       );   break;
            case '7'  : ystrlcpy (x_str, x_work, 70       );   break;
            case '8'  : ystrlcpy (x_str, x_work, 80       );   break;
            case 'H'  : ystrlcpy (x_str, x_work, LEN_HUND );   break;
            case 'F'  : ystrlcpy (x_str, x_work, LEN_FULL );   break;
            case 'R'  : ystrlcpy (x_str, x_work, LEN_RECD );   break;
            case 'O'  : strcpy  (x_str, x_work);              break;
            default   : ystrlcpy  (x_str, x_work, LEN_SHORT);  break;
            }
         }
         DEBUG_YPARSE   yLOG_complex ("string"    , "%d, %c, %3d, %s, %p, %s", i, x_type, rc, x_work, x_str, x_str);
         break;
      case '-' :
         DEBUG_YPARSE   yLOG_bullet  (i           , "skipping field");
         rc = yPARSE_toss   ();
         break;
      default  :
         DEBUG_YPARSE   yLOG_bullet  (i           , "unknown type");
         va_end (a_vlist);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
      if (rc < 0)  {
         va_end (a_vlist);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
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
   ystrlcpy  (yPARSE__unit_answer, "LINE unit        : question not understood", LEN_STR);
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "stats"    ) == 0) {
      sprintf (yPARSE__unit_answer, "LINE stats     : nline %2d, cline %2d, total %2d", s_qin.nline, s_qin.cline, s_count);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      if (s_count < 1 || a_num >  s_qin.nline) {
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

