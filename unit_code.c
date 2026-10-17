/*============================[[    beg-code    ]]============================*/
/*········´ ´·············headers·´ ´·········································*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yparse__unit_quiet      (void)
{
   yparse__clear ();
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
   yparse__clear ();
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_end        (void)
{
   yLOGS_end     ();
   return 0;
}

char*
yparse_config_status    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_in        [LEN_HUND];
   char        x_out       [LEN_HUND];
   char        x_del       [LEN_LABEL]; 
   char        x_ver       [LEN_TERSE];
   yPARSE_qin_info   (NULL, x_in , NULL, NULL);
   yPARSE_qout_info  (NULL, x_out, NULL, NULL);
   if      (strcmp (myPARSE.delimiters, YPARSE_FIELDS)     == 0)  strcpy (x_del, "field·····");
   else if (strcmp (myPARSE.delimiters, YPARSE_FUNCTIONS)  == 0)  strcpy (x_del, "function··");
   else if (strcmp (myPARSE.delimiters, YPARSE_TRADITIONS) == 0)  strcpy (x_del, "tradition·");
   else if (strcmp (myPARSE.delimiters, "")                == 0)  strcpy (x_del, "··········");
   else                                                           strcpy (x_del, "custom····");
   if      (myPARSE.verber != NULL)  strcpy (x_ver, "SET");
   else                              strcpy (x_ver, "···");
   sprintf (yPARSE__unit_answer, "ready %c, verbs  %c, verber %-3.3s, reuse %c   å%-20.20sæ  å%-20.20sæ  %-10.10s  Ï", myPARSE.ready, myPARSE.verbs, x_ver, myPARSE.reusing, x_in, x_out, x_del);
   return yPARSE__unit_answer;
}
