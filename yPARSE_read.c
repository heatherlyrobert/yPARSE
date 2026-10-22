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



char
yparse_read_skip        (char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_pre       [LEN_LABEL] = "";
   char        x_eof       =  '-';
   int         l           =    0;
   char        x_skip      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("null record found");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (x_pre, a_recd, LEN_LABEL);
   DEBUG_YPARSE  yLOG_snote   (x_pre);
   l = strlen (x_pre);
   DEBUG_YPARSE  yLOG_sint    (l);
   /*---(check for bottom)---------------*/
   if      (strncmp (a_recd, "# END-OF-FILE"   , 12) == 0)   x_eof  = 'y';
   else if (strncmp (a_recd, "## END-OF-FILE"  , 12) == 0)   x_eof  = 'y';
   else if (strncmp (a_recd, "# end-of-file"   , 12) == 0)   x_eof  = 'y';
   else if (strncmp (a_recd, "## end-of-file"  , 12) == 0)   x_eof  = 'y';
   else if (strncmp (a_recd, "# done, finito"  , 12) == 0)   x_eof  = 'y';
   else if (strncmp (a_recd, "## done, finito" , 12) == 0)   x_eof  = 'y';
   if (x_eof == 'y') {
      DEBUG_YPARSE  yLOG_snote   ("end of content found");
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 1;
   }
   /*---(trouble)------------------------*/
   if (a_recd [0] == '#')  {
      switch (a_recd [1]) {
      case '>' :
         DEBUG_YPARSE  yLOG_snote   ("savec macro, skip");
         x_skip = 'y';
         break;
      case '@' :
         DEBUG_YPARSE  yLOG_snote   ("file control, retain");
         break;
      case '#' :
         DEBUG_YPARSE  yLOG_snote   ("double comment, skip ");
         x_skip = 'y';
         break;
      default  :
         DEBUG_YPARSE  yLOG_snote   ("normal comment, skip");
         x_skip = 'y';
         break;
      }
   }
   if (a_recd [0] == '\0') {
      DEBUG_YPARSE  yLOG_snote   ("empty record found");
      x_skip = 'y';
   }
   if (l < 5) {
      DEBUG_YPARSE  yLOG_snote   ("line too short (<5 char)");
      x_skip = 'y';
   }
   if (x_skip == 'y') {
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 2;
   }
   /*---(default)------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("realistic line found");
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

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


