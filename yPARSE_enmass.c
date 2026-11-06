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
/*===----                      configuration                           ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

/* auto     means it immediately reads all records and uses a_verber to handle each of them */
char yPARSE_autoread  (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH], void *a_verber) { return yparse_opener (YPARSE_MANUAL, a_ifile, a_ofile, a_verber, YPARSE_READALL, YPARSE_ONETIME); }

/* manual   means when you call uread, it immediately uses a_verber to handle the current record */
char yPARSE_justread  (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH], void *a_verber) { return yparse_opener (YPARSE_MANUAL, a_ifile, a_ofile, a_verber, YPARSE_NOREAD , YPARSE_ONETIME); }

/* planned  means it configures the system, you define all the verbs, then call yPARSE_read_all which does all the work */
char yPARSE_planned   (char a_ifile [LEN_PATH], char a_ofile [LEN_PATH], void *a_verber) { return yparse_opener (YPARSE_AUTO  , a_ifile, a_ofile, a_verber, YPARSE_NOREAD , YPARSE_ONETIME); }



/*====================------------------------------------====================*/
/*===----                        reading                               ----===*/
/*====================------------------------------------====================*/
static void      o___IN______________________o (void) {;}

char
yPARSE_read_all         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =   -1;
   int         c           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   char        x_verb      [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   while (1) {
      rc = yPARSE_read_one (NULL, NULL);
      DEBUG_YPARSE  yLOG_value   ("read"      , n);
      if (rc == 0)  {
         DEBUG_YPARSE   yLOG_note    ("end-of-file");
         break;
      }
      if (rc <  0)  {
         DEBUG_YPARSE   yLOG_note    ("trouble reading record");
         continue;
      }
      yparse_peek_verb (&n, x_verb);
      DEBUG_YPARSE  yLOG_value   ("n"         , n);
      if (n < 0)  {
         DEBUG_YPARSE   yLOG_note    ("verb not recognized");
         continue;
      }
      DEBUG_YPARSE  yLOG_info    ("verb"      , x_verb);
      DEBUG_YPARSE  yLOG_point   ("reader"    , G_verbs [n].v_reader);
      if (G_verbs [n].v_reader == NULL) {
         DEBUG_YPARSE   yLOG_note    ("reader not assigned");
         continue;
      }
      rc = G_verbs [n].v_reader (s_qin.q_nfull, x_verb);
      if (rc < 0)  {
         DEBUG_YPARSE   yLOG_note    ("handler not successful");
         continue;
      }
      ++c;
   }
   /*---(limits)-------------------------*/
   DEBUG_YPARSE  yLOG_value   ("c"         , c);
   if (c > 99)  c = 99;
   DEBUG_YPARSE  yLOG_value   ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                     outgoing                                 ----===*/
/*====================------------------------------------====================*/
static void      o___OUT_____________________o (void) {;}

char
yPARSE_write_all        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("G_nverb"   , G_nverb);
   /*---(prepare)------------------------*/
   for (i = 0; i < G_nverb; ++i)  G_verbs [i].v_done = '-';
   /*---(call writers)-------------------*/
   while (1) {
      /*---(find next)-------------------*/
      x_lowest = 999999.0;
      x_next   = -1;
      for (i = 0; i < G_nverb; ++i) {
         if (G_verbs [i].v_done == 'y'    )   continue;
         if (G_verbs [i].v_seq >=  x_lowest)  continue;
         x_lowest = G_verbs [i].v_seq;
         x_next   = i;
      }
      if (x_lowest > 999.0)  break;
      if (x_next   < 0    )  break;
      G_verbs [x_next].v_done = 'y';
      /*---(filter)----------------------*/
      DEBUG_INPT  yLOG_info    ("verb"      , G_verbs [x_next].v_verb);
      DEBUG_INPT  yLOG_point   ("reader"    , G_verbs [x_next].v_writer);
      if (G_verbs [x_next].v_writer == NULL)  continue;
      /*---(handle)----------------------*/
      rc = G_verbs [x_next].v_writer (s_qout.q_nfull, G_verbs [x_next].v_verb);
      if (rc >= 0)  c += rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}


