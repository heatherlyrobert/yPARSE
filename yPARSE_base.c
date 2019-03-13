/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
tACCESSOR   myPARSE;
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

char
yPARSE_init             (char a_verbs, void *a_verber, char a_reusing)
{
   myPARSE.verbs   = a_verbs;
   myPARSE.verber  = a_verber;
   myPARSE.ready   = 'y';
   myPARSE.reusing = a_reusing;
   yparse_init_types ();
   yparse_verb_init  ();
   yparse_init_in    ();
   yparse_init_out   ();
   yparse_initline   ();
   strlcpy (myPARSE.delimiters, "(,)", LEN_LABEL);
   return 0;
}

char
yPARSE_delimiters       (char *a_list)
{
   if (a_list == NULL) {
      strlcpy (myPARSE.delimiters, "(,)", LEN_LABEL);
   } else  {
      strlcpy (myPARSE.delimiters, a_list , LEN_LABEL);
   }
   return 0;
}

char
yPARSE_wrap             (void)
{
   /*> yPARSE_close_in  ();                                                           <*/
   /*> yPARSE_close_out ();                                                           <*/
   myPARSE.verber  = NULL;
   myPARSE.ready   = '-';
   myPARSE.reusing = NULL;
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
   if (strstr (x_masking, t) != NULL)  return 1;
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
   yPARSE_fullwrite   ("macro"        , 'A', 32726, "jub jub"       , 3.1416, "hey"          );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.recd);
   yPARSE_fullwrite   ("macro"        , 'z',    12, "testing"       , 14.46 , "hey back"     );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.recd);
   yPARSE_fullwrite   ("macro"        , 'f', -4922, "another string", 186.0 , "hey one last" );
   strcpy (g_mocks [g_nmock++].recd, myPARSE.recd);
   return 0;
}

char
yparse_mock__reader     (void)
{
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("g_nmock"   , g_nmock);
   yPARSE_fullread    ("macro", &(g_mocks[g_nmock].x_ch), &(g_mocks[g_nmock].x_int), &(g_mocks[g_nmock].x_str), &(g_mocks[g_nmock].x_float), &(g_mocks[g_nmock].x_str2));
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
   strlcpy  (yPARSE__unit_answer, "MOCK unit        : question not understood", LEN_STR);
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
   int         x_narg       = 1;
   char       *x_args [20]  = {"yPARSE_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yPARSE_init ('y', yparse__unit_verber, 'y');
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yPARSE_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name     ("yparse", 'y');
   yPARSE_init ('y', yparse__unit_verber, 'y');
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_end        (void)
{
   yLOGS_end     ();
   return 0;
}
