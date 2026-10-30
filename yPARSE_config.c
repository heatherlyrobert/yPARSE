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
/*===----                       configuration                          ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

char
yparse_config_clear     (void)
{
   myPARSE.y_verbs   = YPARSE_MANUAL;
   myPARSE.y_verber  = NULL;
   myPARSE.y_reusing = YPARSE_ONETIME;
   strcpy (myPARSE.y_dellist, "");
   myPARSE.y_deltype = '-';
   myPARSE.y_fill    = '-';
   myPARSE.y_ready   = '-';
   return 0;
}

char
yparse_config__delimit  (char a_delim, char a_fill)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_char    ("a_delim"   , a_delim);
   DEBUG_YPARSE  yLOG_info    ("valid"     , YPARSE_DELIMS);
   --rce;  if (a_delim == '\0' || strchr (YPARSE_DELIMS, a_delim) == NULL) {
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_YPARSE  yLOG_char    ("a_fill"    , a_fill);
   DEBUG_YPARSE  yLOG_info    ("valid"     , YPARSE_FILLS);
   --rce;  if (a_fill == '\0' || strchr (YPARSE_FILLS, a_fill) == NULL) {
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(set delimiters)-----------------*/
   switch (a_delim) {
   case YPARSE_FUNCTION  :
      ystrlcpy (myPARSE.y_dellist, YPARSE_FUNCTIONS , LEN_LABEL);
      break;
   case YPARSE_TRADITION :
      ystrlcpy (myPARSE.y_dellist, YPARSE_TRADITIONS, LEN_LABEL);
      break;
   case YPARSE_FIELD     : default :
      ystrlcpy (myPARSE.y_dellist, YPARSE_FIELDS    , LEN_LABEL);
      a_delim = YPARSE_FIELD;
      break;
   }
   DEBUG_YPARSE  yLOG_info    ("delimit"   , myPARSE.y_dellist);
   /*---(set global)---------------------*/
   myPARSE.y_deltype = a_delim;
   myPARSE.y_fill    = a_fill;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yparse_config__verber   (char a_auto, void *a_verber, char a_reusing)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_char    ("a_auto"    , a_auto);
   DEBUG_YPARSE  yLOG_info    ("valid"     , YPARSE_VERBS);
   --rce;  if (a_auto == '\0' || strchr (YPARSE_VERBS, a_auto) == NULL) {
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(reusing)------------------------*/
   DEBUG_YPARSE  yLOG_char    ("a_reusing" , a_reusing);
   DEBUG_YPARSE  yLOG_info    ("valid"     , YPARSE_REUSES);
   --rce;  if (a_reusing == '\0' || strchr (YPARSE_REUSES, a_reusing) == NULL) {
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(set global)---------------------*/
   myPARSE.y_verbs   = a_auto;
   myPARSE.y_verber  = a_verber;
   myPARSE.y_reusing = a_reusing;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yparse_config            (char a_1st, char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(reset all)----------------------*/
   rc = yparse_config_clear ();
   DEBUG_YPARSE  yLOG_value   ("clear"     , rc);
   /*---(verber)-------------------------*/
   rc = yparse_config__verber  (a_auto, a_verber, a_reusing);
   DEBUG_YPARSE  yLOG_value   ("verber"    , rc);
   --rce;  if (rc < 0) {
      yparse_config_clear ();
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(reusing)------------------------*/
   rc = yparse_config__delimit (a_delim, a_fill);
   DEBUG_YPARSE  yLOG_value   ("delims"    , rc);
   --rce;  if (rc < 0) {
      yparse_config_clear ();
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(initialize all areas)-----------*/
   if (a_1st == 'y') {
      DEBUG_YPARSE  yLOG_note    ("first time run, intialize data structures");
      rc = yparse_spec_init  ();
      DEBUG_YPARSE  yLOG_value   ("init_types", rc);
      rc = yparse_verb_init  ();
      DEBUG_YPARSE  yLOG_value   ("verb_init" , rc);
      rc = yparse_init_in    ();
      DEBUG_YPARSE  yLOG_value   ("init_in"   , rc);
      rc = yparse_init_out   ();
      DEBUG_YPARSE  yLOG_value   ("init_out"  , rc);
      rc = yparse_reuse_init ();
      DEBUG_YPARSE  yLOG_value   ("initline"  , rc);
   } else {
      DEBUG_YPARSE  yLOG_note    ("reconfig run, do not intialize data structures");
   }
   /*---(set ready)----------------------*/
   myPARSE.y_ready   = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                    external simplifiers                      ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLIFIERS_____________o (void) {;}

char yPARSE_delimiters  (char a_delim, char a_fill) { return yparse_config__delimit (a_delim, a_fill); }

char yPARSE_verber      (char a_auto, void *a_verber, char a_reusing) { return yparse_config__verber (a_auto, a_verber, a_reusing); }

char yPARSE_config      (char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill) { return yparse_config ('y', a_auto, a_verber, a_reusing, a_delim, a_fill); }

char yPARSE_reconfig    (char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill) { return yparse_config ('-', a_auto, a_verber, a_reusing, a_delim, a_fill); }


