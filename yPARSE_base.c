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

char yparse_print [LEN_RECD];



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
   ystrlcpy  (yparse_print, "BASE unit        : question not understood", LEN_STR);
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
      sprintf (yparse_print, "BASE ready     : %c  %c  %-3.3s  %c   å%-20.20sæ  å%-20.20sæ  %s", myPARSE.y_ready, myPARSE.y_verbs, x_ver, myPARSE.y_reusing, x_in, x_out, x_del);
   }
   /*---(complete)----------------------------------------*/
   return yparse_print;
}


