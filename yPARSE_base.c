/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
tACCESSOR   myPARSE;
static      char        yPARSE_ver  [200] = "";


#define     MAX_SECTION   50
struct {
   /*---(master)------------*/
   cchar       abbr;                     
   cchar       label       [LEN_LABEL];
   cchar       specs       [LEN_LABEL];
   /*---(handlers)----------*/
   char        (*writer)   (void);
   char        (*reader)   (void);
   /*---(runtime)-----------*/
   int         try;
   int         bad;
   /*---(descriptive)-------*/
   cchar       column      [LEN_RECD];
   cchar       desc        [LEN_DESC ];
   /*---(done)--------------*/
}  static s_sections [MAX_SECTION];
   /*--------------- master data -------------------- */
   /* -   ----abbr----- ---label----- ---specs-------    writer   reader   ---1st----    ---2nd----    ---3rd----    ---4th----    ---5th----    ---6th----    ---7th----    ---8th----    ---9th----     try  bad   ---name------------  */
   /*> { 'i', UMOD_MARK    , "loc_mark"  , "ciii--------",  , NULL  , NULL      "-a"        , "--x"       , "--y"       , "--z"       , ""          , ""          , ""          , ""          , ""          ,   0,   0 , "location marks"     },   <* 
    *> { 'i', UMOD_VISUAL  , "visu_mark" , "ciiiii------",  , NULL  , NULL      "-a"        , "xbeg"      , "ybeg"      , "xend"      , "yend"      , "zall"      , ""          , ""          , ""          ,   0,   0 , "visual marks"       },   <* 
    *> { 'i', SMOD_MACRO   , "macro"     , "ciiO--------",  , NULL  , NULL      "-a"        , "count"     , "rc"        , "command"   , ""          , ""          , ""          , ""          , ""          ,   0,   0 , "saved macros"       },   <* 
    *> { 'i', MODE_SEARCH  , "search"    , "ciiO--------",  , NULL  , NULL      "-a"        , "count"     , "found"     , "search"    , ""          , ""          , ""          , ""          , ""          ,   0,   0 , "search history"     },   <* 
    *> { 'i', MODE_COMMAND , "command"   , "ciiO--------",  , NULL  , NULL      "-a"        , "count"     , "rc"        , "command"   , ""          , ""          , ""          , ""          , ""          ,   0,   0 , "command history"    },   <* 
    *> { 'i', SMOD_SRC_REG , "text_reg"  , "cO----------",  , NULL  , NULL      "-a"        , "data"      , ""          , ""          , ""          , ""          , ""          , ""          , ""          ,   0,   0 , "text registers"     },   <* 
    *> { 'e', FILE_DEPCEL  , "cell_dep"  , "TiaTO-------",  , NULL  , NULL      "lvl/reg"   , "seq"       , "label"     , "t-f-d-a-m" , "contents"  , ""          , ""          , ""          , ""          ,   0,   0 , "dependent cells"    },   <* 
    *> { 'e', FILE_FREECEL , "cell_free" , "TiaTO-------",  , NULL  , NULL      "lvl/reg"   , "seq"       , "label"     , "t-f-d-a-m" , "contents"  , ""          , ""          , ""          , ""          ,   0,   0 , "independent cells"  },   <* 
    *> { 'e', FILE_TABS    , "tab"       , "Naaiiic-----",  , NULL  , NULL      "name"      , "min"       , "max"       , "x_size"    , "y_size"    , "z_size"    , "type"      , ""          , ""          ,   0,   0 , "tab (v-axis)"       },   <* 
    *> { 'e', FILE_COLS    , "width"     , "aii---------",  , NULL  , NULL      "label"     , "size"      , "count"     , ""          , ""          , ""          , ""          , ""          , ""          ,   0,   0 , "columns (x-axis)"   },   <* 
    *> { 'e', FILE_ROWS    , "height"    , "aii---------",  , NULL  , NULL      "label"     , "size"      , "count"     , ""          , ""          , ""          , ""          , ""          , ""          ,   0,   0 , "rows (y-axis)"      },   <* 
    *> {  0 , 0            , ""          , "------------",  , NULL  , NULL      ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          ,   0,   0 , ""                   },   <*/
static int  s_nsection   = 0;

/*> yPARSE_handler (UMOD_MARK    , "loc_mark"  , "ciii--------", MARK_reader   , MARK_writer   , "a,xpos,ypos,zpos"          , "map mode location marks"   );   <*/
/*> yPARSE_handler (UMOD_VISUAL  , "visu_mark" , "ciiiii------", VISU_reader   , VISU_writer   , "a,xbeg,ybeg,xend,yend,zpos", "map mode visual selections"),   <*/
/*> yPARSE_handler (SMOD_MACRO   , "macro"     , "ciiO--------", MACRO_reader  , MACRO_writer  , "a,count,rc,keys"           , "keyboard macros"           ),   <*/
/*> yPARSE_handler (MODE_COMMAND , "command"   , "ciiO--------", CMDS_reader   , CMDS_writer   , "a,count,rc,command"        , "command history"           ),   <*/
/*> yPARSE_handler (MODE_SEARCH  , "search"    , "ciiO--------", SRCH_reader   , SRCH_writer   , "a,count,found,search"      , "search history"            ),   <*/
/*> yPARSE_handler (SMOD_SRC_REG , "text_reg"  , "cO----------", SRC_REG_reader, SRC_REG_writer, "a,text"                    , "text editing registers"    ),   <*/


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
yPARSE_handler          (char a_abbr, char *a_label, char *a_spec, void *a_reader, void *a_writer, char *a_desc)
{
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
