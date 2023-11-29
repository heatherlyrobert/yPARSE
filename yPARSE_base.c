/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
tACCESSOR   myPARSE = { 0, '-', '-', '-', "|§", NULL, 'y', "", "", "", '-', 0, 0, '-' };
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
 *>    DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);                              <* 
 *>    myPARSE.verbs   = a_auto;                                                                <* 
 *>    myPARSE.verber  = a_verber;                                                              <* 
 *>    myPARSE.ready   = 'y';                                                                   <* 
 *>    myPARSE.reusing = a_reusing;                                                             <* 
 *>    DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);                              <* 
 *>    yparse_init_types ();                                                                    <* 
 *>    yparse_verb_init  ();                                                                    <* 
 *>    yparse_init_in    ();                                                                    <* 
 *>    yparse_init_out   ();                                                                    <* 
 *>    yparse_initline   ();                                                                    <* 
 *>    /+> yPARSE_delimiters (YPARSE_FIELD);                                              <+/   <* 
 *>    DEBUG_YPARSE  yLOG_char    ("reusing"   , myPARSE.reusing);                              <* 
 *>    DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);                                               <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/
char
yparse__clear           (void)
{
   myPARSE.verbs   = YPARSE_MANUAL;
   myPARSE.verber  = NULL;
   myPARSE.reusing = YPARSE_ONETIME;
   strcpy (myPARSE.delimiters, "");
   myPARSE.fill    = '-';
   myPARSE.ready   = '-';
   return 0;
}

char
yparse__config           (char a_1st, char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill)
{
   char        rce         =  -10;
   char        rc          =    0;
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(reset all)----------------------*/
   yparse__clear ();
   /*---(auto)---------------------------*/
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
   /*---(reusing)------------------------*/
   DEBUG_YPARSE  yLOG_char    ("a_delim"   , a_delim);
   DEBUG_YPARSE  yLOG_info    ("valid"     , YPARSE_REUSES);
   --rce;  if (a_delim == '\0' || strchr (YPARSE_DELIMS, a_delim) == NULL) {
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   switch (a_delim) {
   case YPARSE_FUNCTION  :
      ystrlcpy (myPARSE.delimiters, "§(,)", LEN_LABEL);
      break;
   case YPARSE_FIELD     :
   default :
      ystrlcpy (myPARSE.delimiters, "§" , LEN_LABEL);
      break;
   }
   /*---(make settings)------------------*/
   myPARSE.verbs   = a_auto;
   myPARSE.verber  = a_verber;
   myPARSE.reusing = a_reusing;
   myPARSE.ready   = 'y';
   /*---(initialize all areas)-----------*/
   if (a_1st == 'y') {
      yparse_init_types ();
      yparse_verb_init  ();
      yparse_init_in    ();
      yparse_init_out   ();
      yparse_initline   ();
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_reconfig         (char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill)
{
   return yparse__config ('-', a_auto, a_verber, a_reusing, a_delim, a_fill);
}

char
yPARSE_config           (char a_auto, void *a_verber, char a_reusing, char a_delim, char a_fill)
{
   return yparse__config ('y', a_auto, a_verber, a_reusing, a_delim, a_fill);
}

char
yPARSE_delimiters       (uchar a_type)
{
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   switch (a_type) {
   case YPARSE_FUNCTION  :
      ystrlcpy (myPARSE.delimiters, "§(,)", LEN_LABEL);
      break;
   case YPARSE_FIELD     :
   default :
      ystrlcpy (myPARSE.delimiters, "§" , LEN_LABEL);
      break;
   }
   DEBUG_YPARSE  yLOG_info    ("delimit"   , myPARSE.delimiters);
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_wrap             (void)
{
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*> yPARSE_close_in  ();                                                           <*/
   /*> yPARSE_close_out ();                                                           <*/
   yparse_line_purge ();
   yparse__clear ();
   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_force            (void)
{
   myPARSE.good = 'y';
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
   sprintf (t, " %s ", myPARSE.verb);
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
   strcpy (g_mocks [g_nmock++].recd, myPARSE.recd);
   yPARSE_vprintf   (-1, "macro"        , 'z',    12, "testing"       , 14.46 , "hey back"     );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.recd);
   yPARSE_vprintf   (-1, "macro"        , 'f', -4922, "another string", 186.0 , "hey one last" );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.recd);
   return 0;
}

char
yparse_mock__reader     (void)
{
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("g_nmock"   , g_nmock);
   yPARSE_vscanf    ("macro", &(g_mocks[g_nmock].x_ch), &(g_mocks[g_nmock].x_int), &(g_mocks[g_nmock].x_str), &(g_mocks[g_nmock].x_float), &(g_mocks[g_nmock].x_str2));
   DEBUG_YPARSE  yLOG_info    ("recd"      , myPARSE.recd);
   strcpy (g_mocks [g_nmock++].recd, myPARSE.recd);
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

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yparse__unit_quiet      (void)
{
   yPARSE_config (YPARSE_MANUAL, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);  /* defaults */
   myPARSE.ready = '-';
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [ 1]  = {"yPARSE_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("yparse", 'y');
   yURG_by_name  ("ystr"  , 'y');
   yPARSE_config (YPARSE_MANUAL, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);  /* defaults */
   myPARSE.ready = '-';
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_end        (void)
{
   yLOGS_end     ();
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
   ystrlcpy  (yPARSE__unit_answer, "BASE unit        : question not understood", LEN_STR);
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "ready"    ) == 0) {
      yPARSE_qin_info   (NULL, x_in , NULL, NULL);
      yPARSE_qout_info  (NULL, x_out, NULL, NULL);
      if      (strcmp (myPARSE.delimiters, "§")    == 0)  strcpy (x_del, "field");
      else if (strcmp (myPARSE.delimiters, "§(,)") == 0)  strcpy (x_del, "function");
      else if (strcmp (myPARSE.delimiters, "")       == 0)  strcpy (x_del, "·····");
      else                                                  strcpy (x_del, "custom");
      if      (myPARSE.verber != NULL)  strcpy (x_ver, "SET");
      else                              strcpy (x_ver, "···");
      sprintf (yPARSE__unit_answer, "BASE ready     : %c  %c  %-3.3s  %c   å%-20.20sæ  å%-20.20sæ  %s", myPARSE.ready, myPARSE.verbs, x_ver, myPARSE.reusing, x_in, x_out, x_del);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}


