/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*---1----- -----2----- -----3----- -----4----- ----------comments------------*/
typedef     struct      cQUEUE      tQUEUE;
struct      cQUEUE {
   int         ref;
   char       *item;
   tQUEUE     *next;
   tQUEUE     *prev;
};
static      tQUEUE     *s_head      = NULL;
static      tQUEUE     *s_tail      = NULL;
static      int         s_first     =    0;
static      int         s_count     =    0;



/*====================------------------------------------====================*/
/*===----                     very basic actions                       ----===*/
/*====================------------------------------------====================*/
static void      o___PRIMATIVE_______________o (void) {;};

char
yparse__enqueue         (char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tQUEUE     *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   /*---(defense)------------------------*/
   --rce;  if (a_item   == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("nothing to save");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_item);
   /*---(create)-------------------------*/
   x_new = (tQUEUE *) malloc (sizeof (tQUEUE));
   DEBUG_YPARSE  yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("malloc failed");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(saving)-------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("saving");
   x_new->ref  = s_count;
   x_new->item = strdup (a_item);
   x_new->next = NULL;
   x_new->prev = NULL;
   /*---(attatch)------------------------*/
   if (s_head == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("first");
      s_head       = x_new;
      s_tail       = x_new;
   } else  {
      DEBUG_YPARSE  yLOG_snote   ("append");
      s_tail->next = x_new;
      x_new->prev  = s_tail;
      s_tail       = x_new;
   }
   ++s_count;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (s_first);
   DEBUG_YPARSE  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char yPARSE_push  (char *a_item) { return yparse__enqueue (a_item); }

char
yparse__dequeue         (char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tQUEUE     *x_save      = NULL;
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   if (a_item != NULL)  strlcpy (a_item, "", LEN_RECD);
   /*---(no entries)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (s_head);
   --rce;  if (s_head == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(copy and clear)-----------------*/
   if (a_item != NULL)  strlcpy (a_item, s_head->item, LEN_RECD);
   if (s_head->item != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("free item");
      free (s_head->item);
   }
   /*---(single entry)-------------------*/
   if (s_tail == s_head) {
      DEBUG_YPARSE  yLOG_snote   ("single item");
      free (s_head);
      s_tail  = s_head = NULL;
   }
   /*---(multi entry)--------------------*/
   else {
      DEBUG_YPARSE  yLOG_snote   ("multiple items");
      x_save  = s_head->next;
      x_save->prev = NULL;
      free (s_head);
      s_head  = x_save;
   }
   ++s_first;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (s_first);
   DEBUG_YPARSE  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   return 0;
}

char
yPARSE_purge            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tQUEUE     *x_curr      = NULL;
   /*---(header)-------------------------*/
   /*---(clear)--------------------------*/
   x_curr = s_head;
   while (x_curr != NULL) {
      DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
      yparse__dequeue (NULL);
      x_curr = s_head;
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   }
   s_first = 0;
   s_count = 0;
   strlcpy (myPARSE.verb, "", LEN_RECD);
   /*> strlcpy (myPARSE.orig, "", LEN_RECD);                                          <*/
   /*> strlcpy (myPARSE.recd, "", LEN_RECD);                                          <*/
   /*> myPARSE.len    = 0;                                                            <*/
   /*> myPARSE.good   = '-';                                                          <*/
   /*> myPARSE.hidden = '-';                                                          <*/
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       pushing actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___PUSHING_________________o (void) {;};

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
   yPARSE_purge ();
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
      rc = yparse__enqueue (p);
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
   tQUEUE     *x_curr      = NULL;
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
   x_curr = s_head;
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
/*===----                       popping actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___STRINGS_________________o (void) {;};

char
yPARSE_toss             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
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
   /*---(check)--------------------------*/
   rc = yparse__dequeue (NULL);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_popstr           (char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   if (a_item != NULL)  strlcpy (a_item, "", LEN_LABEL);
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
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   --rce;  if (a_item == NULL) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(dequeue)------------------------*/
   rc = yparse__dequeue (a_item);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yparse__popable         (void)
{
   if (s_head == NULL)  return 0;
   return 1;
}

char
yparse_peek             (const int a_ref, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tQUEUE     *x_curr      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_item == NULL)  return rce;
   /*---(defense)------------------------*/
   strlcpy (a_item, "", LEN_LABEL);
   /*---(search)-------------------------*/
   x_curr = s_head;
   while (x_curr != NULL) {
      if (x_curr->ref == a_ref) {
         strlcpy (a_item, x_curr->item, LEN_RECD);
         return 0;
      }
      x_curr = x_curr->next;
   }
   /*---(complete)-----------------------*/
   return -1;
}



/*====================------------------------------------====================*/
/*===----                       popping actions                        ----===*/
/*====================------------------------------------====================*/
static void      o___NUMBERS_________________o (void) {;};

char
yPARSE_adjval           (float a_old, const char *a_item, float *a_new)
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
yPARSE_adjfrom          (float a_old, const char *a_item, float *a_new)
{
   char        rc          =    0;
   float       a_temp      =  0.0;
   rc = yPARSE_adjval (0.0, a_item, &a_temp);
   if (rc < 0)  return rc;
   *a_new = a_old + a_temp;
   return 0;
}

char
yPARSE_popval           (float a_old, float *a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_rel       =  '-';
   char        x_item      [LEN_RECD];
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
   /*---(check)--------------------------*/
   rc = yparse__dequeue (x_item);
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
yPARSE_popfrom          (float a_old, float *a_new)
{
   char        rc          =    0;
   float       a_temp      =  0.0;
   rc = yPARSE_popval (0.0, &a_temp);
   if (rc < 0)  return rc;
   *a_new = a_old + a_temp;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char yPARSE__unit_answer [ LEN_STR  ];

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_queue      (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(preprare)-----------------------*/
   strlcpy  (yPARSE__unit_answer, "QUEUE unit       : question not understood", LEN_STR);
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "stats"    ) == 0) {
      sprintf (yPARSE__unit_answer, "QUEUE stats    : total %2d, curr %2d", s_count, s_first);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      if (s_count < 1 || a_num < s_first || a_num >= s_count) {
         sprintf (yPARSE__unit_answer, "QUEUE entry  %d : null", a_num);
      } else {
         rc = yparse_peek (a_num, t);
         if (rc < 0) {
            sprintf (yPARSE__unit_answer, "QUEUE entry  %d : trouble finding", a_num);
         } else {
            sprintf (yPARSE__unit_answer, "QUEUE entry  %d : %2d[%s]", a_num, strlen (t), t);
         }
      }
   }
   else if (strcmp (a_question, "verb"     ) == 0) {
      sprintf (yPARSE__unit_answer, "QUEUE verb     : %2d[%s]", strlen (myPARSE.verb), myPARSE.verb);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}
