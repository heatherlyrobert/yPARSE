/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



static      tQUEUE      s_qin;



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
   --rce;  if (myPARSE.good != 'y')  {
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
   /*---(defense)------------------------*/
   if (a_new != NULL)  *a_new = 0.0;
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("must call yPARSE_init () first");
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myPARSE.good != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("record processing was not successful");
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
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
   yPARSE_purge_in ();
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
   char        t           [LEN_RECD];
   char        x_recd      [LEN_RECD];
   tNODE      *x_curr      = NULL;
   int         c           =    1;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_value   ("masked"    , a_masked);
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_note    ("must call yPARSE_init () first");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);
   --rce;  if (myPARSE.reusing != 'y') {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_char    ("good"      , myPARSE.good);
   --rce;  if (myPARSE.good    != 'y') {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_char    ("hidden"    , myPARSE.hidden);
   --rce;  if (myPARSE.hidden  == 'y') {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(start)--------------------------*/
   sprintf (x_recd, "%s (", myPARSE.verb);
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
   yparse_addline (myPARSE.nline, x_recd);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
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


char         /*-> add item to end of queue -----------[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_enqueue_in       (char *a_item)
{
   return yparse_enqueue (&s_qin, a_item);
}

