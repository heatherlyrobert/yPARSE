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


/*--------- ----------- ----------- ----------- ------------------------------*/
tACCESSOR   myPARSE = {
   0, '-',
   YPARSE_MANUAL, NULL, YPARSE_ONETIME,
   '-', YPARSE_FIELDS, YPARSE_NOFILL,
   "", "", '-', 0
};

static      char        yPARSE_ver  [200] = "";



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*      /* ---- : return library versioning information -------------------*/
yPARSE_version          (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yPARSE_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yPARSE_ver;
}



/*====================------------------------------------====================*/
/*===----                         program level                        ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

/*> char                                                                                        <* 
 *> yPARSE_init             (char a_auto, void *a_verber, char a_reusing)                       <* 
 *> {                                                                                           <* 
 *>    DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);                                               <* 
 *>    DEBUG_YPARSE  yLOG_char    ("a_reusing" , a_reusing);                                    <* 
 *>    DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.y_reusing);                              <* 
 *>    myPARSE.y_verbs   = a_auto;                                                                <* 
 *>    myPARSE.y_verber  = a_verber;                                                              <* 
 *>    myPARSE.y_ready   = 'y';                                                                   <* 
 *>    myPARSE.y_reusing = a_reusing;                                                             <* 
 *>    DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.y_reusing);                              <* 
 *>    yparse_init_types ();                                                                    <* 
 *>    yparse_verb_init  ();                                                                    <* 
 *>    yparse_init_in    ();                                                                    <* 
 *>    yparse_init_out   ();                                                                    <* 
 *>    yparse_line_init  ();                                                                    <* 
 *>    /+> yPARSE_delimiters (YPARSE_FIELD);                                              <+/   <* 
 *>    DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.y_reusing);                              <* 
 *>    DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);                                               <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/

char
yPARSE_verber_stub      (int n, uchar *a_verb, char a_exist, void *a_handler)
{
   return 0;
}

char
yPARSE_wrap             (void)
{
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*> yPARSE_close_in  ();                                                           <*/
   /*> yPARSE_close_out ();                                                           <*/
   yparse_line_purge ();
   yparse_config_clear ();
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_force            (void)
{
   myPARSE.y_good = 'y';
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

tMOCK       g_mocks     [10];
int         g_nmock     = 0;

char
yparse__unit_verber     (void)
{
   char       *x_masking   = " ik_pure ik_from fk_pure fk_from ";
   char        t           [LEN_LABEL];
   yPARSE_toss ();
   sprintf (t, " %s ", myPARSE.y_verb);
   /*> if (strstr (x_masking, t) != NULL)  return 1;                                  <*/
   return 0;
}

char
yparse_mock__clear      (void)
{
   int         i           =    0;
   for (i = 0; i < 10; ++i) {
      strcpy (g_mocks [i].recd, "");
      g_mocks [i].x_ch    = '·';
      g_mocks [i].x_int   = -1;
      strcpy (g_mocks [i].x_str , "-");
      g_mocks [i].x_float = -1.1;
      strcpy (g_mocks [i].x_str2, "-");
   }
   g_nmock = 0;
   return 0;
}

char
yparse_mock__writer     (void)
{
   yPARSE_vprintf   (-1, "macro"        , 'A', 32726, "jub jub"       , 3.1416, "hey"          );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.y_recd);
   yPARSE_vprintf   (-1, "macro"        , 'z',    12, "testing"       , 14.46 , "hey back"     );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.y_recd);
   yPARSE_vprintf   (-1, "macro"        , 'f', -4922, "another string", 186.0 , "hey one last" );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.y_recd);
   return 0;
}

char
yparse_mock__reader     (void)
{
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("g_nmock"   , g_nmock);
   yPARSE_vscanf    ("macro", &(g_mocks[g_nmock].x_ch), &(g_mocks[g_nmock].x_int), &(g_mocks[g_nmock].x_str), &(g_mocks[g_nmock].x_float), &(g_mocks[g_nmock].x_str2));
   DEBUG_YPARSE  yLOG_info    ("recd"      , myPARSE.y_recd);
   strcpy (g_mocks [g_nmock++].recd, myPARSE.y_recd);
   DEBUG_YPARSE  yLOG_value   ("g_nmock"   , g_nmock);
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 1;
}

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse_mock__unit       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(preprare)-----------------------*/
   ystrlcpy  (yPARSE__unit_answer, "MOCK unit        : question not understood", LEN_STR);
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "count"    ) == 0) {
      sprintf (yPARSE__unit_answer, "MOCK count     : %2d", g_nmock);
   }
   else if (strcmp (a_question, "recd"     ) == 0) {
      sprintf (yPARSE__unit_answer, "MOCK recd   %2d : %2d[%s]", a_num, strlen (g_mocks [a_num].recd), g_mocks [a_num].recd);
   }
   else if (strcmp (a_question, "detail"   ) == 0) {
      sprintf (yPARSE__unit_answer, "MOCK detail %2d : %c %5d %-20.20s %11.5f %s", a_num, g_mocks [a_num].x_ch, g_mocks [a_num].x_int, g_mocks [a_num].x_str, g_mocks [a_num].x_float, g_mocks [a_num].x_str2);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse_base__unit       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_in        [LEN_HUND];
   char        x_out       [LEN_HUND];
   char        x_del       [LEN_TERSE];
   char        x_ver       [LEN_TERSE];
   /*---(preprare)-----------------------*/
   ystrlcpy  (yPARSE__unit_answer, "BASE unit        : question not understood", LEN_STR);
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "ready"    ) == 0) {
      yPARSE_qin_info   (NULL, x_in , NULL, NULL);
      yPARSE_qout_info  (NULL, x_out, NULL, NULL);
      if      (strcmp (myPARSE.y_dellist, "§")    == 0)  strcpy (x_del, "field");
      else if (strcmp (myPARSE.y_dellist, "§(,)") == 0)  strcpy (x_del, "function");
      else if (strcmp (myPARSE.y_dellist, ""    ) == 0)  strcpy (x_del, "tradition");
      else if (strcmp (myPARSE.y_dellist, "")       == 0)  strcpy (x_del, "·····");
      else                                                  strcpy (x_del, "custom");
      if      (myPARSE.y_verber != NULL)  strcpy (x_ver, "SET");
      else                                strcpy (x_ver, "···");
      sprintf (yPARSE__unit_answer, "BASE ready     : %c  %c  %-3.3s  %c   å%-20.20sæ  å%-20.20sæ  %s", myPARSE.y_ready, myPARSE.y_verbs, x_ver, myPARSE.y_reusing, x_in, x_out, x_del);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}


