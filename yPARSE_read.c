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
/*===----                     detailed parsing                         ----===*/
/*====================------------------------------------====================*/
static void      o___PARSE___________________o (void) {;};

char
yparse_read__nfield     (char b_recd [LEN_RECD], char a_dellist [LEN_TERSE], char *r_field)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         l           =    0;
   int         i           =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_field != NULL)  *r_field = 0;
   /*---(defense)------------------------*/
   DEBUG_YPARSE yLOG_point   ("b_recd"    , b_recd);
   --rce;  if (b_recd == NULL) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("b_recd"    , b_recd);
   DEBUG_YPARSE yLOG_point   ("a_dellist" , a_dellist);
   --rce;  if (a_dellist == NULL) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("a_dellist" , a_dellist);
   /*---(clean record)-------------------*/
   ystrltrim (b_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_YPARSE yLOG_info    ("b_recd"    , b_recd);
   x_len = ystrllen   (b_recd, LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
   if (x_len == 0) {
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(fix ending)---------------------*/
   if (strchr (a_dellist, b_recd [x_len - 1]) != NULL) {
      DEBUG_YPARSE yLOG_note    ("found trailing delimiter");
      b_recd [x_len - 1] = '\0';
      ystrltrim (b_recd, ySTR_BOTH, LEN_RECD);
      DEBUG_YPARSE yLOG_info    ("b_recd"    , b_recd);
      x_len = ystrllen   (b_recd, LEN_RECD);
      DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
   }
   /*---(prepare)------------------------*/
   l     = ystrllen   (a_dellist, LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("l"         , l);
   /*---(count delimeters)---------------*/
   for (i = c = 0; i < l; ++i) {
      c += ystrldcnt (b_recd, a_dellist [i], LEN_RECD);
   }
   DEBUG_YPARSE yLOG_value   ("delimiters", c);
   /*---(add for trailing field)---------*/
   ++c;
   DEBUG_YPARSE yLOG_value   ("fields"    , c);
   /*---(save-back)----------------------*/
   if (r_field != NULL)  *r_field = c;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yparse_read__parse      (tQUEUE *a_queue, char a_recd [LEN_RECD], char a_dellist [LEN_TERSE], char a_fill)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char        c           =    0;
   char        n           =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   int         i           =    0;
   char       *s           =  "·";
   char       *x_nada      =   "";
   char       *x_place     =  "¤";
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(queue check)--------------------*/
   DEBUG_YPARSE yLOG_point   ("a_queue"   , a_queue);
   --rce;  if (a_queue == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("->q_label" , a_queue->q_label);
   /*---(parepare for parse)-------------*/
   ystrlcpy  (x_recd, a_recd   , LEN_RECD);
   rc = yparse_read__nfield (x_recd, a_dellist, &c);
   DEBUG_YPARSE yLOG_point   ("nfield"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get first)----------------------*/
   p     = strtok_r (x_recd, a_dellist, &r);
   DEBUG_YPARSE yLOG_point   ("p"         , p);
   /*---(read fields)--------------------*/
   --rce;  while (p != NULL) {
      /*---(clean it up)-----------------*/
      ystrltrim (p, ySTR_BOTH, LEN_RECD);
      l = ystrllen (p, LEN_RECD);
      if (l == 0) {
         if (a_fill == YPARSE_FILL)  p = x_place;
         else                        p = x_nada;
      }
      else if (l == 1 && strchr ("·´Ï-", p [0]) != NULL) {
         if (a_fill == YPARSE_PACK)  p = x_nada;
         else                        p = x_place;
      }
      else                           ystrlunstore (p, l);
      l = ystrllen (p, LEN_RECD);
      DEBUG_YPARSE yLOG_info    ("field"     , p);
      DEBUG_YPARSE yLOG_value   ("l"         , l);
      /*---(enqueue it)------------------*/
      rc = yparse_queue_enqueue (a_queue, p);
      DEBUG_YPARSE yLOG_value   ("enqueue"   , rc);
      if (rc < 0) {
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++n;
      /*---(get next)--------------------*/
      p = strtok_r (NULL  , a_dellist, &r);
      DEBUG_YPARSE yLOG_point   ("p"         , p);
      /*---(done)------------------------*/
   }
   DEBUG_YPARSE yLOG_value   ("fields"    , n);
   /*---(trouble)------------------------*/
   --rce;  if (n != c) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   a_queue->q_nfield = n;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return n;
}



/*====================------------------------------------====================*/
/*===----                    detailed reading                          ----===*/
/*====================------------------------------------====================*/
static void      o___READING_________________o (void) {;};

char
yparse_read__lineno     (int a_line, int *b_nline, int *b_cline, char *r_hidden)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;                /* return code for errors    */
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(args)---------------------------*/
   DEBUG_YPARSE   yLOG_value   ("a_line"    , a_line);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("b_nline"   , b_nline);
   --rce;  if (b_nline == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_value   ("*b_nline"  , *b_nline);
   DEBUG_YPARSE   yLOG_point   ("b_cline"   , b_cline);
   --rce;  if (b_cline == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_value   ("*b_cline"  , *b_cline);
   DEBUG_YPARSE   yLOG_point   ("r_hidden"  , r_hidden);
   --rce;  if (r_hidden == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_point   ("*r_hidden" , *r_hidden);
   /*---(new line)-----------------------*/
   if (a_line < 0) {
      DEBUG_YPARSE   yLOG_note    ("handle new line");
      ++(*b_nline);
      *b_cline  = *b_nline;
      *r_hidden = '-';
   }
   /*---(old line)-----------------------*/
   else if (a_line > 0) {
      DEBUG_YPARSE   yLOG_note    ("handle old line");
      *b_cline  = a_line;
      *r_hidden = '-';
   }
   /*---(hidden line)--------------------*/
   else {
      DEBUG_YPARSE   yLOG_note    ("handle hidden line");
      *b_cline  = -1;
      *r_hidden = 'y';
   }
   /*---(save-back)----------------------*/
   DEBUG_YPARSE   yLOG_value   ("*b_nline"  , *b_nline);
   DEBUG_YPARSE   yLOG_value   ("*b_cline"  , *b_cline);
   DEBUG_YPARSE   yLOG_point   ("*r_hidden" , *r_hidden);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yparse_read__rollback   (tQUEUE *a_queue, int a_line)
{
   yPARSE_in_purge ();
   a_queue->q_good = 'n';
   if (a_line < 0) {
      --a_queue->q_nused;
      a_queue->q_ncurr  = a_queue->q_nused;
   }
   return 0;
}

char
yparse_read__source     (FILE *a_file, int a_line, char a_recd [LEN_RECD], char a_label [LEN_HUND], int *b_tline, char r_recd [LEN_RECD], int *r_len)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_recd   != NULL)  strcpy (r_recd, "");
   if (r_len    != NULL)  *r_len    = 0;
   /*---(defense)------------------------*/
   DEBUG_YPARSE yLOG_point   ("b_tline"   , b_tline);
   --rce;  if (b_tline == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_value   ("b_tline"   , b_tline);
   DEBUG_YPARSE yLOG_point   ("r_recd"    , r_recd);
   --rce;  if (r_recd  == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_point   ("r_len"     , r_len);
   --rce;  if (r_len   == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(passed record)------------------*/
   if (a_recd != NULL) {
      DEBUG_YPARSE yLOG_note    ("request to use record provided as argument");
      ystrlcpy (r_recd, a_recd, LEN_RECD);
      *r_len    = strlen (r_recd);
   }
   /*---(read record)--------------------*/
   else if (a_line < 0) {
      DEBUG_YPARSE yLOG_note    ("request to read input for record");
      rc = yENV_read (a_file, '-', '-', 'y', '-', b_tline, NULL, r_recd, NULL, r_len);
      DEBUG_YPARSE yLOG_value   ("read"      , rc);
   }
   /*---(using eisting record)-----------*/
   else {
      DEBUG_YPARSE yLOG_note    ("request to use an existing record");
      rc = yparse_reuse_existing (a_line, a_label, NULL, NULL);
      DEBUG_YPARSE yLOG_value   ("existing"  , rc);
   }
   /*---(handle trouble)-----------------*/
   if (rc < 0) {
      DEBUG_YPARSE yLOG_note    ("trouble, must roll-back");
      rc = RC_ROLLBACK;
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(clean record in queue)----------*/
   ystrldchg (r_recd, G_KEY_FIELD, G_CHAR_FIELD, LEN_RECD);
   DEBUG_YPARSE yLOG_info    ("r_recd"    , r_recd);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yparse_read__finish     (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_verb      [LEN_LABEL] = "";
   char        n           =    0;
   char        x_exist     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(peek at verb)----------------*/
   rc = yparse_peek_in   (0, x_verb);
   DEBUG_YPARSE  yLOG_value   ("peek"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("x_verb"    , x_verb);
   /*---(remove verb from queue)------*/
   yPARSE_toss ();  /* verb */
   /*---(quick-out for non-auto)------*/
   DEBUG_YPARSE  yLOG_char    ("y_verbs"   , myPARSE.y_verbs);
   if (myPARSE.y_verbs != YPARSE_AUTO) {
      DEBUG_YPARSE yLOG_note    ("auto-processing, not set, return");
      DEBUG_YPARSE yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
   }
   /*---(auto process verb)-----------*/
   n = yparse_verb_find (a_queue, x_verb);
   DEBUG_YPARSE  yLOG_value   ("find"      , n);
   if (n < 0) {
      if (myPARSE.y_verber == NULL) {
         DEBUG_YPARSE  yLOG_note    ("verb unrecognized and verber not active");
         rc = RC_ROLLBACK;
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      DEBUG_YPARSE  yLOG_note    ("verb unrecognized, verber will need to sort out");
   }
   /*---(contact callback)------------*/
   DEBUG_YPARSE  yLOG_point   ("verber"    , myPARSE.y_verber);
   --rce;  if (myPARSE.y_verber != NULL) {
      if (n >= 0)  x_exist = 'y';
      rc = myPARSE.y_verber (a_queue->q_nfull, x_verb, x_exist, a_queue->q_handler);
      DEBUG_YPARSE  yLOG_value   ("verber"    , rc);
      if (rc < 0) {
         rc = RC_ROLLBACK;
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yparse_read             (char a_func [LEN_TITLE], tQUEUE *a_queue, int a_line, char a_recd [LEN_RECD], char a_label [LEN_HUND], int *r_nread, int *r_nused, int *r_ncurr, char r_verb [LEN_LABEL], char r_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   char        x_index     =   -1;
   char        x_mask      =   -1;
   char        x_exist     =  '-';
   char        x_recd      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (a_func);
   /*---(default)------------------------*/
   if (r_nread != NULL)  *r_nread = 0;
   if (r_nused != NULL)  *r_nused = 0;
   if (r_ncurr != NULL)  *r_ncurr = 0;
   if (r_verb  != NULL)  strcpy (r_verb, "");
   if (r_recd  != NULL)  strcpy (r_recd, "");
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_char    ("ready"     , myPARSE.y_ready);
   --rce;  if (myPARSE.y_ready != 'y')  {
      DEBUG_YPARSE   yLOG_note    ("must call yPARSE_config () first");
      DEBUG_YPARSE   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(queue check)--------------------*/
   DEBUG_YPARSE yLOG_point   ("a_queue"   , a_queue);
   --rce;  if (a_queue == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("->q_label" , a_queue->q_label);
   /*---(purge existing data)------------*/
   rc = yparse_queue_purge (a_queue);
   DEBUG_YPARSE yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(temporary verbs)----------------*/
   if (myPARSE.y_verbs  == YPARSE_MANUAL) {
      DEBUG_YPARSE  yLOG_note    ("single use verb/handlers, purge before each");
      rc = yparse_verb_init ();
   }
   /*---(line number)--------------------*/
   rc = yparse_read__lineno (a_line, &(a_queue->q_nused), &(a_queue->q_ncurr), &(a_queue->q_hidden));
   DEBUG_YPARSE   yLOG_point   ("lineno"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(read)---------------------------*/
   rc = yparse_read__source (a_queue->q_file, a_line, a_recd, a_label, &(a_queue->q_nfull), a_queue->q_recd, &(a_queue->q_len));
   DEBUG_YPARSE   yLOG_point   ("source"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_note    ("drastic problem with reading source");
      DEBUG_YPARSE   yLOG_exitr   (a_func, rce);
      return rce;
   }
   --rce;  if (rc == RC_ROLLBACK) {
      DEBUG_YPARSE   yLOG_note    ("trouble with last read, roll-back");
      yparse_read__rollback  (a_queue, a_line);
      DEBUG_YPARSE   yLOG_exitr   (a_func, rce);
      return rce;
   }
   if (rc == RC_DONE) {
      DEBUG_YPARSE   yLOG_note    ("read the end-of-file");
      DEBUG_YPARSE   yLOG_exit    (a_func);
      return RC_DONE;
   }
   /*---(clean record in queue)----------*/
   ystrldchg (a_queue->q_recd, G_KEY_FIELD, G_CHAR_FIELD, LEN_RECD);
   /*---(working copy for parsing)-------*/
   ystrlcpy  (x_recd, a_queue->q_recd, LEN_RECD);
   /*---(parse)--------------------------*/
   rc = yparse_read__parse (a_queue, x_recd, myPARSE.y_dellist, myPARSE.y_fill);
   DEBUG_YPARSE  yLOG_value   ("queue"     , rc);
   --rce;  if (rc < 0) {
      yparse_read__rollback  (a_queue, a_line);
      DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(set as good)-----------------*/
   a_queue->q_good = 'y';
   DEBUG_YPARSE  yLOG_char    ("q_good"    , a_queue->q_good);
   /*---(peek at verb)----------------*/
   rc = yparse_read__finish (a_queue);
   DEBUG_YPARSE  yLOG_value   ("finish"    , rc);
   --rce;  if (rc < 0) {
      yparse_read__rollback  (a_queue, a_line);
      DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*> rc = yparse_peek_in   (0, a_queue->q_verb);                                                  <* 
    *> yPARSE_toss ();  /+ verb +/                                                                  <* 
    *> DEBUG_YPARSE  yLOG_value   ("peek"      , rc);                                               <* 
    *> if (rc < 0) {                                                                                <* 
    *>    yparse_read__rollback  (a_queue, a_line);                                                 <* 
    *>    DEBUG_YPARSE  yLOG_exitr   (a_func, rc);                                                  <* 
    *>    return rce;                                                                               <* 
    *> }                                                                                            <* 
    *> DEBUG_YPARSE  yLOG_info    ("verb"      , a_queue->q_verb);                                  <* 
    *> /+---(auto process verb)-----------+/                                                        <* 
    *> DEBUG_YPARSE  yLOG_char    ("verbs"     , myPARSE.y_verbs);                                  <* 
    *> --rce;  if (myPARSE.y_verbs == YPARSE_AUTO) {                                                <* 
    *>    x_index = yparse_verb_find (a_queue, a_queue->q_verb);                                    <* 
    *>    DEBUG_YPARSE  yLOG_value   ("find"      , x_index);                                       <* 
    *>    if (x_index < 0) {                                                                        <* 
    *>       if (myPARSE.y_verber == NULL) {                                                        <* 
    *>          DEBUG_YPARSE  yLOG_note    ("verb unrecognized and verber not active");             <* 
    *>          yparse_read__rollback  (a_queue, a_line);                                           <* 
    *>          DEBUG_YPARSE  yLOG_exitr   (a_func, rce);                                           <* 
    *>          return rce;                                                                         <* 
    *>       }                                                                                      <* 
    *>       DEBUG_YPARSE  yLOG_note    ("verb unrecognized, verber will need to sort out");        <* 
    *>    }                                                                                         <* 
    *> }                                                                                            <* 
    *> /+---(contact callback)------------+/                                                        <* 
    *> DEBUG_YPARSE  yLOG_point   ("verber"    , myPARSE.y_verber);                                 <* 
    *> --rce;  if (myPARSE.y_verber != NULL) {                                                      <* 
    *>    if (x_index >= 0)  x_exist = 'y';                                                         <* 
    *>    rc = myPARSE.y_verber (a_queue->q_nfull, a_queue->q_verb, x_exist, a_queue->q_handler);   <* 
    *>    DEBUG_YPARSE  yLOG_value   ("verber"    , rc);                                            <* 
    *>    if (rc < 0) {                                                                             <* 
    *>       yparse_read__rollback  (a_queue, a_line);                                              <* 
    *>       DEBUG_YPARSE  yLOG_exitr   (a_func, rce);                                              <* 
    *>       return rce;                                                                            <* 
    *>    }                                                                                         <* 
    *> }                                                                                            <*/
   /*---(check resuse)----------------*/
   DEBUG_YPARSE  yLOG_complex ("reusing"   , "%c, %d, %c", myPARSE.y_reusing, a_line, a_queue->q_hidden);
   --rce;  if (myPARSE.y_reusing == 'y' && a_line < 0 && a_queue->q_hidden != 'y') {
      DEBUG_YPARSE  yLOG_note    ("preparing/saving for reuse");
      if (x_index < 0)  x_index = yparse_verb_find (a_queue, a_queue->q_verb);
      x_mask = yparse_verb_mask (x_index);
      rc = yparse_reusable (x_mask);
      if (rc < 0) {
         DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
         return rce;
      }
   }
   /*---(result)-------------------------*/
   DEBUG_YPARSE   yLOG_value   ("count"     , a_queue->q_count);
   /*---(save-back)----------------------*/
   if (r_nread != NULL)  *r_nread = a_queue->q_nfull;
   if (r_nused != NULL)  *r_nused = a_queue->q_nused;
   if (r_ncurr != NULL)  *r_ncurr = a_queue->q_ncurr;
   if (r_verb  != NULL)  ystrlcpy (r_verb, a_queue->q_verb, LEN_LABEL);
   if (r_recd  != NULL)  ystrlcpy (r_recd, x_recd, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (a_func);
   return a_queue->q_count;
}



/*====================------------------------------------====================*/
/*===----                        simplifiers                           ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPILIERS______________o (void) {;};

char yPARSE_read        (int *r_nfull, int *r_nused, int *r_ncurr, char r_verb [LEN_LABEL]) { return yparse_read (__FUNCTION__, &s_qin,  -1    , NULL  , NULL   , r_nfull, r_nused, r_ncurr, r_verb, NULL); }
char yPARSE_read_one    (int *r_nused, char r_verb [LEN_LABEL])                             { return yparse_read (__FUNCTION__, &s_qin,  -1    , NULL  , NULL   , NULL   , r_nused, NULL   , r_verb, NULL); }
char yPARSE_load        (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD])                { return yparse_read (__FUNCTION__, &s_qin,  -1    , a_recd, NULL   , NULL   , r_nused, r_ncurr, NULL  , NULL); }
char yPARSE_reload      (int *r_nused, int *r_ncurr, int a_line, char a_label [LEN_HUND])   { return yparse_read (__FUNCTION__, &s_qin,  a_line, NULL  , a_label, NULL   , r_nused, r_ncurr, NULL  , NULL); }
char yPARSE_hidden      (int *r_nused, int *r_ncurr, char a_recd [LEN_RECD])                { return yparse_read (__FUNCTION__, &s_qin,  -1    , a_recd, NULL   , NULL   , r_nused, r_ncurr, NULL  , NULL); }

char yPARSE_inrecd      (char r_recd [LEN_RECD]) { ystrlcpy (r_recd, s_qin.q_recd, LEN_RECD); }


