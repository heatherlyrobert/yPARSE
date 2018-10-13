/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



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
/*===----                       getting lines                          ----===*/
/*====================------------------------------------====================*/
static void      o___PARSING_________________o (void) {;};

char         /*--> pull script record from stdin ---------[ ------ [ ------ ]-*/
yparse__stdin           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(get record)---------------------*/
   fgets (myPARSE.recd, LEN_RECD, stdin);
   --rce;  if (feof (stdin))  {
      DEBUG_YPARSE   yLOG_snote   ("end of file reached");
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clean)--------------------------*/
   myPARSE.len = strlen (myPARSE.recd);
   if (myPARSE.len > 0)  myPARSE.recd [--myPARSE.len] = 0;
   DEBUG_YPARSE   yLOG_sint    (myPARSE.len);
   DEBUG_YPARSE   yLOG_snote   (myPARSE.recd);
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
      strlcpy (myPARSE.recd, x_recd , LEN_RECD);
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
      strlcpy (myPARSE.recd, x_recd , LEN_RECD);
      strlcat (myPARSE.recd, a_label, LEN_RECD);
      DEBUG_YPARSE   yLOG_point   ("p + 2"     , p + 2);
      x_len = strlen (p + 2);
      DEBUG_YPARSE   yLOG_value   ("x_len"     , x_len);
      strlcat (myPARSE.recd, p + 2  , LEN_RECD);
   }
   myPARSE.len = strlen (myPARSE.recd);
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
   myPARSE.good = '-';
   /*---(line number)--------------------*/
   DEBUG_YPARSE   yLOG_value   ("a_line"    , a_line);
   if (a_line < 0) {
      ++myPARSE.nline;
      myPARSE.cline  = myPARSE.nline;
      DEBUG_YPARSE   yLOG_value   ("new line"  , myPARSE.cline);
      myPARSE.hidden = '-';
   } else if (a_line > 0) {
      myPARSE.cline  = a_line;
      DEBUG_YPARSE   yLOG_value   ("old line"  , myPARSE.cline);
      myPARSE.hidden = '-';
   } else {
      myPARSE.cline  = -1;
      DEBUG_YPARSE   yLOG_value   ("hidden"    , myPARSE.cline);
      myPARSE.hidden = 'y';
   }
   if (n != NULL)  *n = myPARSE.nline;
   if (c != NULL)  *c = myPARSE.cline;
   /*---(read)---------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_recd"    , a_recd);
   if (a_recd == NULL) {
      if (a_line < 0) {
         rc = yparse__stdin ();
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
      strlcpy (myPARSE.recd, a_recd, LEN_RECD);
      myPARSE.len = strlen (myPARSE.recd);
   }
   /*---(filter)-------------------------*/
   --rce;  if (myPARSE.len      <  5) {
      DEBUG_YPARSE   yLOG_note    ("line too short");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myPARSE.recd [0] == '#') {
      DEBUG_YPARSE   yLOG_note    ("comment line");
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(load the queue)-----------------*/
   rc = yparse_recd  (myPARSE.recd);
   DEBUG_YPARSE  yLOG_value   ("queue"     , rc);
   if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(set as good)-----------------*/
   myPARSE.good = 'y';
   /*---(pop verb)--------------------*/
   rc = yparse_peek   (0, myPARSE.verb);
   rc = myPARSE.verber ();
   if (rc < 0) {
      myPARSE.good = '-';
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   /*---(pop verb)--------------------*/
   if (a_line < 0 && myPARSE.hidden != 'y') {
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

char yPARSE_stdin       (int *n, int *c)                            { return yparse__main (n, c, -1, NULL, NULL); }
char yPARSE_load        (int *n, int *c, char *a_recd)              { return yparse__main (n, c, -1, a_recd, NULL); }
char yPARSE_reload      (int *n, int *c, int a_line, char *a_label) { return yparse__main (n, c, a_line, NULL, a_label); }
char yPARSE_hidden      (int *n, int *c, char *a_recd)              { return yparse__main (n, c,  0, a_recd, NULL); }




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

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
      sprintf (yPARSE__unit_answer, "LINE stats     : nline %2d, cline %2d, total %2d", myPARSE.nline, myPARSE.cline, s_count);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      if (s_count < 1 || a_num > myPARSE.nline) {
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


