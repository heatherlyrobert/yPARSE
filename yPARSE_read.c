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



/*> char                                                                              <* 
 *> yparse_read_skip        (char a_recd [LEN_RECD])                                  <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        x_pre       [LEN_LABEL] = "";                                      <* 
 *>    char        x_eof       =  '-';                                                <* 
 *>    int         l           =    0;                                                <* 
 *>    char        x_skip      =  '-';                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);                                     <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_YPARSE  yLOG_spoint  (a_recd);                                           <* 
 *>    --rce;  if (a_recd == NULL) {                                                  <* 
 *>       DEBUG_YPARSE  yLOG_snote   ("null record found");                           <* 
 *>       DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(prepare)------------------------+/                                       <* 
 *>    ystrlcpy (x_pre, a_recd, LEN_LABEL);                                           <* 
 *>    DEBUG_YPARSE  yLOG_snote   (x_pre);                                            <* 
 *>    l = strlen (x_pre);                                                            <* 
 *>    DEBUG_YPARSE  yLOG_sint    (l);                                                <* 
 *>    /+---(check for bottom)---------------+/                                       <* 
 *>    if      (strncmp (a_recd, "# END-OF-FILE"   , 12) == 0)   x_eof  = 'y';        <* 
 *>    else if (strncmp (a_recd, "## END-OF-FILE"  , 12) == 0)   x_eof  = 'y';        <* 
 *>    else if (strncmp (a_recd, "# end-of-file"   , 12) == 0)   x_eof  = 'y';        <* 
 *>    else if (strncmp (a_recd, "## end-of-file"  , 12) == 0)   x_eof  = 'y';        <* 
 *>    else if (strncmp (a_recd, "# done, finito"  , 12) == 0)   x_eof  = 'y';        <* 
 *>    else if (strncmp (a_recd, "## done, finito" , 12) == 0)   x_eof  = 'y';        <* 
 *>    if (x_eof == 'y') {                                                            <* 
 *>       DEBUG_YPARSE  yLOG_snote   ("end of content found");                        <* 
 *>       DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                  <* 
 *>       return 1;                                                                   <* 
 *>    }                                                                              <* 
 *>    /+---(trouble)------------------------+/                                       <* 
 *>    if (a_recd [0] == '#')  {                                                      <* 
 *>       switch (a_recd [1]) {                                                       <* 
 *>       case '>' :                                                                  <* 
 *>          DEBUG_YPARSE  yLOG_snote   ("savec macro, skip");                        <* 
 *>          x_skip = 'y';                                                            <* 
 *>          break;                                                                   <* 
 *>       case '@' :                                                                  <* 
 *>          DEBUG_YPARSE  yLOG_snote   ("file control, retain");                     <* 
 *>          break;                                                                   <* 
 *>       case '#' :                                                                  <* 
 *>          DEBUG_YPARSE  yLOG_snote   ("double comment, skip ");                    <* 
 *>          x_skip = 'y';                                                            <* 
 *>          break;                                                                   <* 
 *>       default  :                                                                  <* 
 *>          DEBUG_YPARSE  yLOG_snote   ("normal comment, skip");                     <* 
 *>          x_skip = 'y';                                                            <* 
 *>          break;                                                                   <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    if (a_recd [0] == '\0') {                                                      <* 
 *>       DEBUG_YPARSE  yLOG_snote   ("empty record found");                          <* 
 *>       x_skip = 'y';                                                               <* 
 *>    }                                                                              <* 
 *>    if (l < 5) {                                                                   <* 
 *>       DEBUG_YPARSE  yLOG_snote   ("line too short (<5 char)");                    <* 
 *>       x_skip = 'y';                                                               <* 
 *>    }                                                                              <* 
 *>    if (x_skip == 'y') {                                                           <* 
 *>       DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                  <* 
 *>       return 2;                                                                   <* 
 *>    }                                                                              <* 
 *>    /+---(default)------------------------+/                                       <* 
 *>    DEBUG_YPARSE  yLOG_snote   ("realistic line found");                           <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                     <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char         /+--> pull script record from stdin ---------[ ------ [ ------ ]-+/           <* 
 *> yparse_read_next        (FILE *a_file, int *b_tline, char r_recd [LEN_RECD], int *r_len)   <* 
 *> {                                                                                          <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                <* 
 *>    char        rce         =  -10;                                                         <* 
 *>    char        rc          =    0;                                                         <* 
 *>    char        x_stdin     =  '-';                                                         <* 
 *>    int         x_tries     =    0;                                                         <* 
 *>    /+---(header)-------------------------+/                                                <* 
 *>    DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);                                              <* 
 *>    /+---(default)------------------------+/                                                <* 
 *>    if (r_recd  != NULL)  strcpy (r_recd, "");                                              <* 
 *>    if (r_len   != NULL)  *r_len = 0;                                                       <* 
 *>    /+---(defense)------------------------+/                                                <* 
 *>    DEBUG_YPARSE  yLOG_point    ("a_file"    , a_file);                                     <* 
 *>    --rce;  if (a_file == NULL) {                                                           <* 
 *>       DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);                                      <* 
 *>       return rce;                                                                          <* 
 *>    }                                                                                       <* 
 *>    DEBUG_YPARSE  yLOG_point    ("b_tline"   , b_tline);                                    <* 
 *>    --rce;  if (b_tline == NULL) {                                                          <* 
 *>       DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);                                      <* 
 *>       return rce;                                                                          <* 
 *>    }                                                                                       <* 
 *>    DEBUG_YPARSE  yLOG_value    ("*b_tline"  , *b_tline);                                   <* 
 *>    DEBUG_YPARSE  yLOG_point    ("r_recd"    , r_recd);                                     <* 
 *>    --rce;  if (r_recd == NULL) {                                                           <* 
 *>       DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);                                      <* 
 *>       return rce;                                                                          <* 
 *>    }                                                                                       <* 
 *>    /+---(prepare)------------------------+/                                                <* 
 *>    if (a_file == stdin)  x_stdin = 'y';                                                    <* 
 *>    DEBUG_YPARSE  yLOG_char     ("x_stdin"   , x_stdin);                                    <* 
 *>    /+---(get record)---------------------+/                                                <* 
 *>    --rce;  while (1) {                                                                     <* 
 *>       /+---(prepare)---------------------+/                                                <* 
 *>       ++x_tries;                                                                           <* 
 *>       DEBUG_YPARSE  yLOG_value    ("x_tries"   , x_tries);                                 <* 
 *>       if (x_tries > 50)  {                                                                 <* 
 *>          DEBUG_YPARSE  yLOG_note     ("too many tries (>50)");                             <* 
 *>          break;                                                                            <* 
 *>       }                                                                                    <* 
 *>       rc     = 0;                                                                          <* 
 *>       /+---(read)------------------------+/                                                <* 
 *>       fgets (r_recd, LEN_RECD, a_file);                                                    <* 
 *>       if (feof (a_file))  {                                                                <* 
 *>          DEBUG_YPARSE   yLOG_note    ("actual end-of-file");                               <* 
 *>          DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, 1);                                    <* 
 *>          return 1;                                                                         <* 
 *>       }                                                                                    <* 
 *>       ++(*b_tline);                                                                        <* 
 *>       DEBUG_YPARSE  yLOG_value    ("*b_tline"  , *b_tline);                                <* 
 *>       /+---(clean)-----------------------+/                                                <* 
 *>       *r_len = strlen (r_recd);                                                            <* 
 *>       if (*r_len > 0 && r_recd [*r_len - 1] == '\n')  r_recd [--(*r_len)] = '\0';          <* 
 *>       DEBUG_YPARSE  yLOG_value    ("*r_len"    , *r_len);                                  <* 
 *>       DEBUG_YPARSE  yLOG_info     ("r_recd"    , r_recd);                                  <* 
 *>       /+---(filter)----------------------+/                                                <* 
 *>       rc = yparse_read_skip (r_recd);                                                      <* 
 *>       DEBUG_YPARSE  yLOG_value    ("skip"      , rc);                                      <* 
 *>       if (rc == 1) {                                                                       <* 
 *>          DEBUG_YPARSE   yLOG_note    ("logical end-of-file");                              <* 
 *>          DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, 1);                                    <* 
 *>          return 1;                                                                         <* 
 *>       }                                                                                    <* 
 *>       if (rc == 0) {                                                                       <* 
 *>          DEBUG_YPARSE  yLOG_note     ("found a good record");                              <* 
 *>          break;                                                                            <* 
 *>       }                                                                                    <* 
 *>       /+---(stdin exception)-------------+/                                                <* 
 *>       if (x_stdin == 'y') {                                                                <* 
 *>          DEBUG_YPARSE  yLOG_note     ("stdin, breakout after each");                       <* 
 *>          break;                                                                            <* 
 *>       }                                                                                    <* 
 *>       /+---(done)------------------------+/                                                <* 
 *>    }                                                                                       <* 
 *>    /+---(complete)-----------------------+/                                                <* 
 *>    DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);                                             <* 
 *>    return 0;                                                                               <* 
 *> }                                                                                          <*/

char
yparse_read_parse       (char a_recd [LEN_RECD], char a_dellist [LEN_TERSE], char a_fill, char *r_nfield)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;               /* generic return code       */
   char        x_recd      [LEN_RECD]  = "";
   int         x_len       =    0;
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
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_nfield != NULL)  *r_nfield = 0;
   /*---(defense)------------------------*/
   DEBUG_YPARSE yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("a_recd"    , a_recd);
   DEBUG_YPARSE yLOG_point   ("a_dellist" , a_dellist);
   --rce;  if (a_dellist == NULL) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("a_dellist" , a_dellist);
   /*---(prepare recd)-------------------*/
   ystrlcpy (x_recd, a_recd, LEN_RECD);
   x_len = ystrllen   (x_recd, LEN_RECD);
   DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
   /*---(prepare field count)------------*/
   l     = ystrllen   (a_dellist, LEN_RECD);
   for (i = c = 0; i < l; ++i) {
      c += ystrldcnt (x_recd, a_dellist [i], LEN_RECD);
   }
   DEBUG_YPARSE yLOG_value   ("delimiters", c);
   ++c;
   DEBUG_YPARSE yLOG_char    ("x_len - 1" , a_recd [x_len - 1]);
   if (strchr (a_dellist, a_recd [x_len - 1]) != NULL) --c;
   DEBUG_YPARSE yLOG_value   ("fields"    , c);
   /*---(get first)----------------------*/
   p     = strtok_r (x_recd, a_dellist, &r);
   DEBUG_YPARSE yLOG_point   ("p"         , p);
   /*---(read fields)--------------------*/
   --rce;  while (p != NULL) {
      /*---(clean it up)-----------------*/
      ystrltrim (p, ySTR_BOTH, LEN_RECD);
      x_len = ystrllen (p, LEN_RECD);
      if (x_len == 0) {
         if (a_fill == YPARSE_FILL)  p = x_place;
         else                        p = x_nada;
      }
      else if (x_len == 1 && strchr ("·´Ï-", p [0]) != NULL) {
         if (a_fill == YPARSE_PACK)  p = x_nada;
         else                        p = x_place;
      }
      else                           ystrlunstore (p, x_len);
      x_len = ystrllen (p, LEN_RECD);
      DEBUG_YPARSE yLOG_info    ("field"     , p);
      DEBUG_YPARSE yLOG_value   ("x_len"     , x_len);
      /*---(enqueue it)------------------*/
      rc = yparse_queue_enqueue (&s_qin, p);
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
   if (r_nfield != NULL)  *r_nfield = n;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yparse_read_lineno      (int a_line, int *b_nline, int *b_cline, char *r_hidden)
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
   return 1;
}

char
yparse_read_rollback    (int a_line)
{
   yPARSE_purge_in ();
   s_qin.q_good = 'n';
   if (a_line < 0) {
      --s_qin.q_nused;
      s_qin.q_ncurr  = s_qin.q_nused;
   }
   return 0;
}

char
yparse_read_source      (FILE *a_file, int a_line, char a_recd [LEN_RECD], char a_label [LEN_HUND], int *b_tline, char r_recd [LEN_RECD], int *r_len)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_recd  != NULL)  strcpy (r_recd, "");
   if (r_len   != NULL)  *r_len = 0;
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
   --rce;  if (a_recd != NULL) {
      DEBUG_YPARSE yLOG_note    ("using record provided as argument");
      ystrlcpy (r_recd, a_recd, LEN_RECD);
      *r_len = strlen (r_recd);
   }
   /*---(read record)--------------------*/
   else if (a_line < 0) {
      DEBUG_YPARSE yLOG_note    ("request to read input for record");
      /*> rc = yparse_read_next (a_file, b_tline, r_recd, r_len);                     <*/
      rc = yENV_read (a_file, '-', '-', 'y', '-', b_tline, NULL, r_recd, NULL, r_len);
      DEBUG_YPARSE yLOG_value   ("read"      , rc);
      if (rc == RC_DONE)      rc = 1;
      if (rc == RC_POSITIVE)  rc = 0;
   }
   /*---(using eisting record)-----------*/
   else {
      rc = yparse_reuse_existing (a_line, a_label, NULL, NULL);
      DEBUG_YPARSE yLOG_value   ("existing"  , rc);
   }
   /*---(handle trouble)-----------------*/
   if (rc != 0) {
      if (rc == 1)  DEBUG_YPARSE yLOG_note    ("end-of-file");
      yparse_read_rollback  (a_line);
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}


char
yparse_read             (char a_func [LEN_TITLE], int a_line, char a_recd [LEN_RECD], char a_label [LEN_HUND], int *r_nread, int *r_nused, int *r_ncurr, char r_verb [LEN_LABEL], char r_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;                /* return code for errors    */
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
   /*---(prepare)------------------------*/
   yPARSE_purge_in ();
   /*---(temporary verbs)----------------*/
   if (myPARSE.y_verbs  == YPARSE_MANUAL) {
      DEBUG_YPARSE  yLOG_note    ("single use verb/handlers, purge before each");
      yparse_verb_init ();
   }
   /*---(defense)------------------------*/
   /*> --rce;  if (a_line < 0) {                                                      <* 
    *>    if (s_qin.q_label == NULL || strcmp (s_qin  s_qin.q_file == NULL) {             <* 
    *>    DEBUG_YPARSE   yLOG_note    ("file is not open");                           <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (a_func, rce);                            <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(line number)--------------------*/
   rc = yparse_read_lineno (a_line, &(s_qin.q_nused), &(s_qin.q_ncurr), &(s_qin.q_hidden));
   DEBUG_YPARSE   yLOG_point   ("lineno"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*> DEBUG_YPARSE   yLOG_value   ("a_line"    , a_line);                            <*/
   /*> if (a_line < 0) {                                                              <* 
    *>    ++s_qin.q_nused;                                                            <* 
    *>    s_qin.q_ncurr  = s_qin.q_nused;                                             <* 
    *>    DEBUG_YPARSE   yLOG_value   ("new line"  , s_qin.q_ncurr);                  <* 
    *>    s_qin.q_hidden = '-';                                                       <* 
    *> } else if (a_line > 0) {                                                       <* 
    *>    s_qin.q_ncurr  = a_line;                                                    <* 
    *>    DEBUG_YPARSE   yLOG_value   ("old line"  , s_qin.q_ncurr);                  <* 
    *>    s_qin.q_hidden = '-';                                                       <* 
    *> } else {                                                                       <* 
    *>    s_qin.q_ncurr  = -1;                                                        <* 
    *>    DEBUG_YPARSE   yLOG_value   ("hidden"    , s_qin.q_ncurr);                  <* 
    *>    s_qin.q_hidden = 'y';                                                       <* 
    *> }                                                                              <*/
   if (r_nused != NULL)  *r_nused = s_qin.q_nused;
   if (r_ncurr != NULL)  *r_ncurr = s_qin.q_ncurr;
   /*---(read)---------------------------*/
   rc = yparse_read_source (s_qin.q_file, a_line, a_recd, a_label, &(s_qin.q_nfull), s_qin.q_recd, &(s_qin.q_len));
   DEBUG_YPARSE   yLOG_point   ("source"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (a_func, rce);
      return rce;
   }
   if (rc == 1) {
      DEBUG_YPARSE   yLOG_exit    (a_func);
      return 1;
   }
   /*> DEBUG_YPARSE   yLOG_point   ("a_recd"    , a_recd);                            <*/
   /*> --rce;  if (a_recd == NULL) {                                                                 <* 
    *>    if (a_line < 0) {                                                                          <* 
    *>       rc = yparse_read_next (s_qin.q_file, &(s_qin.q_nfull), s_qin.q_recd, &(s_qin.q_len));   <* 
    *>       DEBUG_YPARSE  yLOG_value   ("read"      , rc);                                          <* 
    *>       if (rc == 1) {                                                                          <* 
    *>          DEBUG_YPARSE  yLOG_note    ("end-of-file");                                          <* 
    *>          yparse_read_rollback  (a_line);                                                      <* 
    *>          DEBUG_YPARSE  yLOG_exit    (a_func);                                                 <* 
    *>          return 0;                                                                            <* 
    *>       }                                                                                       <* 
    *>    } else {                                                                                   <* 
    *>       rc = yparse_read_existing (a_line, a_label);                                            <* 
    *>       DEBUG_YPARSE  yLOG_value   ("existing"  , rc);                                          <* 
    *>    }                                                                                          <* 
    *>    if (rc < 0) {                                                                              <* 
    *>       yparse_read_rollback  (a_line);                                                         <* 
    *>       DEBUG_YPARSE  yLOG_exitr   (a_func, rc);                                                <* 
    *>       return rc;                                                                              <* 
    *>    }                                                                                          <* 
    *> } else {                                                                                      <* 
    *>    ystrlcpy (s_qin.q_recd, a_recd, LEN_RECD);                                                 <* 
    *>    s_qin.q_len = strlen (s_qin.q_recd);                                                       <* 
    *> }                                                                                             <*/
   if (r_nread != NULL)  *r_nread = s_qin.q_nfull;
   /*---(load the queue)-----------------*/
   strcpy (myPARSE.y_recd, s_qin.q_recd);
   ystrldchg (myPARSE.y_recd, G_KEY_FIELD, G_CHAR_FIELD, LEN_RECD);
   rc = yparse_read_parse (myPARSE.y_recd, myPARSE.y_dellist, myPARSE.y_fill, &(myPARSE.y_nfield));
   DEBUG_YPARSE  yLOG_value   ("queue"     , rc);
   --rce;  if (rc < 0) {
      yparse_read_rollback  (a_line);
      DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
      return rc;
   }
   /*---(set as good)-----------------*/
   s_qin.q_good = 'y';
   DEBUG_YPARSE  yLOG_char    ("q_good"    , s_qin.q_good);
   /*---(peek at verb)----------------*/
   rc = yparse_peek_in   (0, myPARSE.y_verb);
   yPARSE_toss ();  /* verb */
   DEBUG_YPARSE  yLOG_value   ("peek"      , rc);
   if (rc < 0) {
      yparse_read_rollback  (a_line);
      DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("verb"      , myPARSE.y_verb);
   /*---(auto process verb)-----------*/
   DEBUG_YPARSE  yLOG_char    ("verbs"     , myPARSE.y_verbs);
   --rce;  if (myPARSE.y_verbs == YPARSE_AUTO) {
      x_index = yparse_verb_find (&s_qin, myPARSE.y_verb);
      DEBUG_YPARSE  yLOG_value   ("find"      , x_index);
      if (x_index < 0) {
         if (myPARSE.y_verber == NULL) {
            DEBUG_YPARSE  yLOG_note    ("verb unrecognized and verber not active");
            yparse_read_rollback  (a_line);
            DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
            return rce;
         }
         DEBUG_YPARSE  yLOG_note    ("verb unrecognized, verber will need to sort out");
      }
   }
   /*---(contact callback)------------*/
   DEBUG_YPARSE  yLOG_point   ("verber"    , myPARSE.y_verber);
   --rce;  if (myPARSE.y_verber != NULL) {
      if (x_index >= 0)  x_exist = 'y';
      rc = myPARSE.y_verber (s_qin.q_nfull, myPARSE.y_verb, x_exist, s_qin.q_handler);
      DEBUG_YPARSE  yLOG_value   ("verber"    , rc);
      if (rc < 0) {
         yparse_read_rollback  (a_line);
         DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
         return rce;
      }
   }
   /*---(check resuse)----------------*/
   DEBUG_YPARSE  yLOG_complex ("reusing"   , "%c, %d, %c", myPARSE.y_reusing, a_line, s_qin.q_hidden);
   --rce;  if (myPARSE.y_reusing == 'y' && a_line < 0 && s_qin.q_hidden != 'y') {
      DEBUG_YPARSE  yLOG_note    ("preparing/saving for reuse");
      if (x_index < 0)  x_index = yparse_verb_find (&s_qin, myPARSE.y_verb);
      x_mask = yparse_verb_mask (x_index);
      rc = yparse_reusable (x_mask);
      if (rc < 0) {
         DEBUG_YPARSE  yLOG_exitr   (a_func, rc);
         return rce;
      }
   }
   /*---(result)-------------------------*/
   DEBUG_YPARSE   yLOG_value   ("count"     , s_qin.q_count);
   if (r_verb  != NULL)  ystrlcpy (r_verb, myPARSE.y_verb, LEN_LABEL);
   if (r_recd  != NULL)  ystrlcpy (r_verb, myPARSE.y_recd, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (a_func);
   return s_qin.q_count;
}


