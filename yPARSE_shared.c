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
   snprintf (yPARSE_ver, 100, "%s   %s : %s", t, YPARSE_VER_NUM, YPARSE_VER_TXT);
   return yPARSE_ver;
}

char
yPARSE_init             (void *a_verber, char a_reusing)
{
   myPARSE.verber  = a_verber;
   myPARSE.nline   = 0;
   myPARSE.ready   = 'y';
   myPARSE.reusing = a_reusing;
   return 0;
}

char
yPARSE_force            (void)
{
   myPARSE.good = 'y';
   return 0;
}

char
yparse__unit_verb       (void)
{
   char       *x_masking   = " ik_pure ik_from fk_pure fk_from ";
   char        t           [LEN_LABEL];
   yPARSE_toss ();
   sprintf (t, " %s ", myPARSE.verb);
   if (strstr (x_masking, t) != NULL)  return 1;
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yparse__unit_quiet      (void)
{
   myPARSE.logger = yLOG_begin ("yPARSE", yLOG_SYSTEM, yLOG_QUIET);
   yPARSE_init (yparse__unit_verb, 'y');
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_loud       (void)
{
   myPARSE.logger = yLOG_begin ("yPARSE", yLOG_SYSTEM, yLOG_NOISE);
   yURG_name ("yparse", 'y');
   yPARSE_init (yparse__unit_verb, 'y');
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_end        (void)
{
   yLOG_end     ();
   return 0;
}
