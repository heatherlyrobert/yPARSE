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
/*--------- ----------- ----------- ----------- ------------------------------*/
static      tLINE      *S_head      = NULL;
static      tLINE      *S_tail      = NULL;
static      int         S_count     =    0;
static      tLINE      *S_curr      = NULL;



/*====================------------------------------------====================*/
/*===----                     program support                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;};

char
yparse_line_purge       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLINE      *x_old       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(walk-thru)----------------------*/
   DEBUG_YPARSE   yLOG_value   ("S_count"   , S_count);
   x_old = S_head;
   DEBUG_YPARSE   yLOG_point   ("x_old"     , x_old);
   while (x_old != NULL) {
      DEBUG_YPARSE   yLOG_value   ("l_line"    , x_old->l_line);
      /*---(list integrity)--------------*/
      if (x_old->l_next == NULL) {
         S_head  = NULL;
         S_tail  = NULL;
      } else {
         S_head                = x_old->l_next;
         x_old->l_next->l_prev = NULL;
      }
      /*---(free line)-------------------*/
      rc = yENV_free ("line", &x_old, &S_count);
      /*---(go to next)------------------*/
      x_old = S_head;
      DEBUG_YPARSE   yLOG_point   ("x_old"     , x_old);
      /*---(done)------------------------*/
   }
   DEBUG_YPARSE   yLOG_value   ("S_count"   , S_count);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yparse_line_init        (void)
{
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(purge)--------------------------*/
   yparse_line_purge ();
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    creation and use                          ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;};

char
yparse_line__wipe       (tLINE *a_line)
{
   a_line->l_line =    0;
   strcpy (a_line->l_recd, "");
   a_line->l_next = NULL;
   a_line->l_prev = NULL;
   a_line->l_uses =    0;
   return 0;
}

char
yparse_line_add         (int a_line, char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLINE      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_value   ("a_line"    , a_line);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL || a_recd [0] == '\0') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("a_recd"    , a_recd);
   /*---(create)-------------------------*/
   rc = yENV_new ("line", sizeof (tLINE), &x_new, &S_count, '-', yparse_line__wipe);
   DEBUG_YPARSE   yLOG_value   ("new"       , rc);
   DEBUG_YPARSE   yLOG_point   ("x_new"     , x_new);
   --rce;  if (rc < 0 || x_new == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_YPARSE   yLOG_note    ("populate fields");
   x_new->l_line = a_line;
   strlcpy (x_new->l_recd, a_recd, LEN_RECD);
   /*---(attatch)------------------------*/
   if (S_head == NULL) {
      DEBUG_YPARSE   yLOG_note    ("add as first");
      S_head  = x_new;
      S_tail  = x_new;
   } else  {
      DEBUG_YPARSE   yLOG_note    ("append to end");
      S_tail->l_next = x_new;
      x_new->l_prev  = S_tail;
      S_tail         = x_new;
   }
   DEBUG_YPARSE   yLOG_value   ("S_count"   , S_count);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                      searching for lines                     ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;};

int yparse_line_count  (void)  { return S_count; }

char 
yparse_line_by_cursor   (char a_action, char a_dir, char a_line, tLINE **r_line, char r_recd [LEN_RECD], int *r_uses, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    1;
   char        n           =   -1;
   char        x_exact     =   -1;
   char        c           =    0;
   char        x_prev      [LEN_DESC]  = "´·····························";
   char        x_curr      [LEN_DESC]  = "´·····························";
   char        x_next      [LEN_DESC]  = "´·····························";
   tLINE      *x_line      = NULL;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_line  != NULL)  *r_line  = NULL;
   if (r_recd  != NULL)  strcpy (r_recd , "");
   if (r_uses  != NULL)  *r_uses  = 0;
   if (d_entry != NULL)  strcpy (d_entry, "");
   /*---(quick-out)----------------------*/
   if (a_dir == 'T') {
      if (d_entry != NULL)  strcpy (d_entry, "seq  ---curr-----------------------  use  ---prev-----------------------  ---next-----------------------  Ï");
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (d_entry != NULL)  strcpy (d_entry, "··-  ´·····························  ··-  ´·····························  ´·····························  Ï");
   /*---(quick-out)----------------------*/
   DEBUG_YPARSE  yLOG_value   ("S_count"   , S_count);
   if (S_count == 0) {
      if (d_entry != NULL)  strcpy (d_entry, "(empty)");
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle cursor)------------------*/
   DEBUG_YPARSE yLOG_char    ("a_dir"     , a_dir);
   DEBUG_YPARSE yLOG_value   ("a_line"    , a_line);
   --rce;  if (a_dir >  0) {
      DEBUG_YPARSE yLOG_note    ("requested cursoring");
      /*---(prepare)---------------------*/
      n = S_curr;
      DEBUG_YPARSE yLOG_value   ("n"         , n);
      /*---(update)----------------------*/
      --rce;  switch (a_dir) {
      case YDLST_HEAD : case YDLST_DHEAD :
         n = 0;
         break;
      case YDLST_PREV : case YDLST_DPREV :
         --n;
         break;
      case YDLST_CURR : case YDLST_DCURR :
         n = n;
         break;
      case YDLST_NEXT : case YDLST_DNEXT :
         ++n;
         break;
      case YDLST_TAIL : case YDLST_DTAIL :
         n = S_count - 1;
         break;
      default         :
         DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YPARSE yLOG_value   ("n"         , n);
   }
   /*---(handle index)-------------------*/
   else if (a_line >= 0) {
      DEBUG_YPARSE yLOG_note    ("requesed indexing");
      x_exact = a_line;
   }
   /*---(handle trouble)-----------------*/
   else {
      DEBUG_YPARSE  yLOG_note    ("neither cursor or line number");
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle endpoints)---------------*/
   DEBUG_YPARSE yLOG_value   ("n"         , n);
   --rce;  if (a_dir > 0 && n < 0) {
      if (d_entry != NULL)  strcpy (d_entry, "(under)");
      S_curr = 0;
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_dir > 0 && n >= S_count) {
      if (d_entry != NULL)  strcpy (d_entry, "(over)");
      S_curr = S_count - 1;
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   x_line = S_head;
   DEBUG_YPARSE yLOG_point   ("S_head"    , S_head);
   while (x_line != NULL) {
      DEBUG_YPARSE yLOG_complex ("loop"      , "%3dn, %3dc, %3de, %3d#", n, c, x_exact, x_line->l_line);
      if (n >= 0 && c == n) {
         DEBUG_YPARSE yLOG_note    ("found it by cursor");
         break;
      }
      if (x_exact >= 0 && x_line->l_line == x_exact) {
         DEBUG_YPARSE yLOG_note    ("found it by line number");
         break;
      }
      ++c;
      x_line = x_line->l_next;
      DEBUG_YPARSE yLOG_point   ("x_line"    , x_line);
   }
   /*---(not found)----------------------*/
   if (x_line == NULL) {
      if (d_entry != NULL)  strcpy (d_entry, "(n/a)");
      DEBUG_YPARSE yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(save-back)----------------------*/
   S_curr = c;
   if (r_line  != NULL)  *r_line  = x_line;
   if (r_recd  != NULL)  ystrlcpy (r_recd , x_line->l_recd, LEN_RECD);
   if (r_uses  != NULL)  *r_uses  = x_line->l_uses;
   /*---(output)-------------------------*/
   if (d_entry != NULL) {
      DEBUG_YPARSE yLOG_note    ("requested d_entry");
      if (x_line->l_prev != NULL)  ystrldisplay (x_line->l_prev->l_recd, LEN_TITLE, x_prev);
      ystrldisplay (x_line->l_recd, LEN_TITLE, x_curr);
      if (x_line->l_next != NULL)  ystrldisplay (x_line->l_next->l_recd, LEN_TITLE, x_next);
      sprintf (d_entry, "%3d  %-30.30s  %3d  %-30.30s  %-30.30s  Ï", n, x_curr, x_line->l_uses, x_prev, x_next);
   }
   /*---(update uses)--------------------*/
   if (a_action == 'g')  ++(x_line->l_uses);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char   yparse_line_get    (int a_line, char r_recd [LEN_RECD]) { return yparse_line_by_cursor ('g', -1, a_line, NULL, r_recd, NULL, NULL); }
char*  yparse_line_entry  (char a_dir) { yparse_line_by_cursor ('e', a_dir, -1, NULL, NULL, NULL, yparse_print);  return yparse_print; }


