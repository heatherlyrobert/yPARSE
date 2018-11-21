/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"




#define     MAX_VERBS     50
struct {
   /*---(master)------------*/
   char       mode;                     
   char       verb         [LEN_LABEL];
   char       specs        [LEN_LABEL];
   char       flags        [LEN_LABEL];
   /*---(handlers)----------*/
   char        (*writer)   (void);
   char        (*reader)   (void);
   /*---(runtime)-----------*/
   int         uses;
   int         fails;
   /*---(descriptive)-------*/
   char       labels       [LEN_RECD];
   char       desc         [LEN_DESC ];
   /*---(done)--------------*/
}  static   s_verbs   [MAX_VERBS];
static int  s_nverb   = 0;

static char *s_nada = "";


/*--------------- master data -------------------- */
/* -   ----mode----- ---label----- ---specs-------    writer   reader   ---1st----    ---2nd----    ---3rd----    ---4th----    ---5th----    ---6th----    ---7th----    ---8th----    ---9th----     try  bad   ---name------------  */
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

/*> yPARSE_handler (UMOD_MARK    , "loc_mark"  , "ciii--------", MARK_reader   , MARK_writer   , "a,xpos,ypos,zpos"          , "map mode location marks"   );   <*/
/*> yPARSE_handler (UMOD_VISUAL  , "visu_mark" , "ciiiii------", VISU_reader   , VISU_writer   , "a,xbeg,ybeg,xend,yend,zpos", "map mode visual selections"),   <*/
/*> yPARSE_handler (SMOD_MACRO   , "macro"     , "ciiO--------", MACRO_reader  , MACRO_writer  , "a,count,rc,keys"           , "keyboard macros"           ),   <*/
/*> yPARSE_handler (MODE_COMMAND , "command"   , "ciiO--------", CMDS_reader   , CMDS_writer   , "a,count,rc,command"        , "command history"           ),   <*/
/*> yPARSE_handler (MODE_SEARCH  , "search"    , "ciiO--------", SRCH_reader   , SRCH_writer   , "a,count,found,search"      , "search history"            ),   <*/
/*> yPARSE_handler (SMOD_SRC_REG , "text_reg"  , "cO----------", SRC_REG_reader, SRC_REG_writer, "a,text"                    , "text editing registers"    ),   <*/


char
yparse_verb_init        (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_VERBS; ++i) {
      s_verbs [i].mode    =  '�';
      strlcpy (s_verbs [i].verb   , ""            , LEN_LABEL);
      strlcpy (s_verbs [i].specs  , "------------", LEN_LABEL);
      strlcpy (s_verbs [i].flags  , "------------", LEN_LABEL);
      s_verbs [i].writer  = NULL;
      s_verbs [i].reader  = NULL;
      s_verbs [i].uses    =    0;
      s_verbs [i].fails   =    0;
      strlcpy (s_verbs [i].labels , ""            , LEN_RECD);
      strlcpy (s_verbs [i].desc   , ""            , LEN_DESC);
   }
   s_nverb = 0;
   return 0;
}

char
yparse_verb_find        (tQUEUE *a_queue, char *a_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   static char x_last      [LEN_LABEL] = "-";
   static char n           =   -1;
   int         i           =    0;
   /*---(short-cut)----------------------*/
   if (a_verb == NULL)                return -10;
   if (a_verb [0] == '\0')            return -11;
   if (n >= 0 && strcmp (a_verb, x_last) == 0) {
      if (a_queue != NULL)  a_queue->iverb = n;
      return n;
   }
   /*---(find entry)---------------------*/
   n = -1;
   for (i = 0; i < s_nverb; ++i) {
      if (s_verbs [i].verb [0] != a_verb [0])      continue;
      if (strcmp (s_verbs [i].verb, a_verb) != 0)  continue;
      n = i;
      break;
   }
   /*---(save)---------------------------*/
   strlcpy (x_last, a_verb, LEN_LABEL);
   if (a_queue != NULL)  a_queue->iverb = n;
   /*---(complete)-----------------------*/
   return n;
}

char
yparse_col_by_count     (tQUEUE *a_queue)
{
   if (a_queue        == NULL)  return -1;
   if (a_queue->iverb <  0   )  return -2;
   if (a_queue->count <  0   )  return -3;
   if (a_queue->count >= 12  )  return -4;
   DEBUG_YPARSE   yLOG_info    ("spec"      , s_verbs [a_queue->iverb].specs);
   return s_verbs [a_queue->iverb].specs [a_queue->count - 1];
}

char
yparse_col_by_first     (tQUEUE *a_queue)
{
   if (a_queue        == NULL)  return -1;
   if (a_queue->iverb <  0   )  return -2;
   if (a_queue->first <  0   )  return -3;
   if (a_queue->first >= 12  )  return -4;
   DEBUG_YPARSE   yLOG_info    ("spec"      , s_verbs [a_queue->iverb].specs);
   return s_verbs [a_queue->iverb].specs [a_queue->first - 1];
}

char
yparse_col_count        (tQUEUE *a_queue)
{
   int         i           =    0;
   int         n           =    1;   /* start with one for verb  */
   if (a_queue        == NULL)  return -1;
   if (a_queue->iverb <  0   )  return -2;
   DEBUG_YPARSE   yLOG_info    ("spec"      , s_verbs [a_queue->iverb].specs);
   for (i = 0; i < 12; ++i) {
      if (s_verbs [a_queue->iverb].specs [i] == '-')   break;
      ++n;
   }
   return n;
}

char
yPARSE_handler          (char a_mode, char *a_verb, char *a_specs, void *a_reader, void *a_writer, char *a_flags, char *a_labels, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   /*---(defense)------------------------*/
   if (s_verbs [n].verb == NULL)     return -1;
   /*---(check existing)-----------------*/
   n = yparse_verb_find (NULL, a_verb);
   if (n < 0)  n = s_nverb;
   /*---(copy values)--------------------*/
   if (a_mode   != 0   )  s_verbs [n].mode    = a_mode;
   if (a_verb   != NULL)  strlcpy (s_verbs [n].verb  , a_verb  , LEN_LABEL);
   if (a_specs  != NULL)  strlcpy (s_verbs [n].specs , a_specs , LEN_LABEL);
   if (a_flags  != NULL)  strlcpy (s_verbs [n].flags , a_flags , LEN_LABEL);
   if (a_reader != NULL)  s_verbs [n].reader  = a_reader;
   if (a_writer != NULL)  s_verbs [n].writer  = a_writer;
   if (a_labels != NULL)  strlcpy (s_verbs [n].labels, a_labels, LEN_RECD);
   if (a_desc   != NULL)  strlcpy (s_verbs [n].desc  , a_desc  , LEN_DESC);
   /*---(update)-------------------------*/
   ++s_nverb;
   /*---(complete)-----------------------*/
   return 0;
}

char*
yPARSE_verb             (int a_num)
{
   if (a_num <  0      )   return s_nada;
   if (a_num >= s_nverb)   return s_nada;
   return s_verbs [a_num].verb;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_verb       (char *a_question, char *a_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   /*---(preprare)-----------------------*/
   strlcpy  (yPARSE__unit_answer, "VERB unit        : question not understood", LEN_STR);
   /*---(check existing)-----------------*/
   if (a_verb == NULL || a_verb [0] == '\0') {
      sprintf (yPARSE__unit_answer, "VERB entry     : verb not given");
      return yPARSE__unit_answer;
   }
   n = yparse_verb_find (NULL, a_verb);
   if (n < 0) {
      sprintf (yPARSE__unit_answer, "VERB entry     : %-12.12s is unknown", a_verb);
      return yPARSE__unit_answer;
   }
   /*---(answer)------------------------------------------*/
   if     (strcmp (a_question, "entry"    ) == 0) {
      sprintf (yPARSE__unit_answer, "VERB entry     : %c, %-12.12s, %-12.12s", s_verbs [n].mode, s_verbs [n].verb, s_verbs [n].specs);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}


