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

/*
 * purpose is to handle saved lines 
 *
 *
 *
 *
 */



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
yparse_line_init        (void)
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
yparse_line_add         (int a_line, char a_recd [LEN_RECD])
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

char
yparse_line_get         (int a_line, char r_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   tLINE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE   yLOG_sint    (a_line);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_spoint  (r_recd);
   --rce;  if (r_recd == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YPARSE   yLOG_snote   ("prepare");
   ystrlcpy (r_recd, "", LEN_RECD);
   x_curr = s_tail;
   /*---(find)---------------------------*/
   while (x_curr != NULL) {
      if (a_line == x_curr->line) {
         ++(x_curr->uses);
         ystrlcpy (r_recd, x_curr->recd, LEN_RECD);
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



