/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"




#define     MAX_VERBS     50
struct {
   /*---(master)------------*/
   char        mode;                        /* one char yvikeys mode id       */
   char        verb        [LEN_LABEL];     /* verb name as used in files     */
   char        specs       [LEN_LABEL];     /* field specifications           */
   /*---(handlers)----------*/
   char        (*reader)   (void);          /* function to read one record    */
   char        (*writer)   (void);          /* function to write all of type  */
   float       seq;                         /* writing sequence               */
   char        done;                        /* written (y/n)                  */
   /*---(descriptive)-------*/
   char        flags       [LEN_LABEL];     /* flags for use by program       */
   char        labels      [LEN_RECD];      /* field labels for headers       */
   char        desc        [LEN_DESC ];     /* long verb description          */
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

/*> yPARSE_handler (UMOD_MARK    , "loc_mark"  , 7.1, "ciii--------", MARK_reader   , MARK_writer   , "a,xpos,ypos,zpos"          , "map mode location marks"   );   <*/
/*> yPARSE_handler (UMOD_VISUAL  , "visu_mark" , 7.2, "ciiiii------", VISU_reader   , VISU_writer   , "a,xbeg,ybeg,xend,yend,zpos", "map mode visual selections"),   <*/
/*> yPARSE_handler (SMOD_MACRO   , "macro"     , 7.3, "ciiO--------", MACRO_reader  , MACRO_writer  , "a,count,rc,keys"           , "keyboard macros"           ),   <*/
/*> yPARSE_handler (MODE_COMMAND , "command"   , 7.4, "ciiO--------", CMDS_reader   , CMDS_writer   , "a,count,rc,command"        , "command history"           ),   <*/
/*> yPARSE_handler (MODE_SEARCH  , "search"    , 7.5, "ciiO--------", SRCH_reader   , SRCH_writer   , "a,count,found,search"      , "search history"            ),   <*/
/*> yPARSE_handler (SMOD_SRC_REG , "text_reg"  , 7.6, "cO----------", SRC_REG_reader, SRC_REG_writer, "a,text"                    , "text editing registers"    ),   <*/


char
yparse_verb_init        (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_VERBS; ++i) {
      s_verbs [i].mode    =  '·';
      strlcpy (s_verbs [i].verb   , ""            , LEN_LABEL);
      strlcpy (s_verbs [i].specs  , "------------", LEN_LABEL);
      s_verbs [i].reader  = NULL;
      s_verbs [i].writer  = NULL;
      strlcpy (s_verbs [i].flags  , "------------", LEN_LABEL);
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
   char        rce         =  -10;
   static char x_last      [LEN_LABEL] = "-";
   static char n           =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(short-cut)----------------------*/
   DEBUG_YPARSE   yLOG_spoint  (a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_snote   (a_verb);
   --rce;  if (a_verb [0] == '\0') {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(short-cut)----------------------*/
   DEBUG_YPARSE   yLOG_sint    (n);
   DEBUG_YPARSE   yLOG_snote   (x_last);
   if (n >= 0 && strcmp (a_verb, x_last) == 0) {
      if (a_queue != NULL)  a_queue->iverb = n;
      DEBUG_YPARSE   yLOG_snote   ("short-cut");
      DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
      return n;
   }
   /*---(find entry)---------------------*/
   DEBUG_YPARSE   yLOG_sint    (s_nverb);
   --rce;  if (s_nverb <= 0) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   n = -1;
   for (i = 0; i < s_nverb; ++i) {
      if (s_verbs [i].verb [0] != a_verb [0])      continue;
      if (strcmp (s_verbs [i].verb, a_verb) != 0)  continue;
      DEBUG_YPARSE   yLOG_snote   ("FOUND");
      n = i;
      break;
   }
   /*---(save)---------------------------*/
   strlcpy (x_last, a_verb, LEN_LABEL);
   if (a_queue != NULL)  a_queue->iverb = n;
   DEBUG_YPARSE   yLOG_sint    (n);
   DEBUG_YPARSE   yLOG_snote   (x_last);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
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
yPARSE_handler          (char a_mode, char *a_verb, float a_seq, char *a_specs, void *a_reader, void *a_writer, char *a_flags, char *a_labels, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   /*---(defense)------------------------*/
   if (a_verb == NULL)     return -1;
   /*---(check existing)-----------------*/
   n = yparse_verb_find (NULL, a_verb);
   if (n < 0)  n = s_nverb;
   /*---(copy values)--------------------*/
   if (a_mode   != 0   )  s_verbs [n].mode    = a_mode;
   if (a_verb   != NULL)  strlcpy (s_verbs [n].verb  , a_verb  , LEN_LABEL);
   if (a_seq    >  0.0 )  s_verbs [n].seq     = a_seq;
   if (a_specs  != NULL)  strlcpy (s_verbs [n].specs , a_specs , LEN_LABEL);
   if (a_reader != NULL)  s_verbs [n].reader  = a_reader;
   if (a_writer != NULL)  s_verbs [n].writer  = a_writer;
   if (a_flags  != NULL)  strlcpy (s_verbs [n].flags , a_flags , LEN_LABEL);
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
/*===----                         output writing                       ----===*/
/*====================------------------------------------====================*/
static void      o___VERB_WRITING____________o (void) {;};

static int  s_n     = -1;
static char s_div   [LEN_RECD]  = "";

char
yparse__verb_divider     (int a_iverb)
{
   /*---(locals)-----------+-----+-----+-*/
   char        s           [LEN_RECD ];
   char        t           [LEN_RECD ];
   int         i           =    0;
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   char       x_spec       =  '-';
   int        x_avail      =    0;
   int        x_len        =    0;
   int        x_pre        =    0;
   int        x_mid        =    0;
   int        x_suf        =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(prepare)----------+-----+-----+-*/
   strlcpy (s_div, "#---verb---- § ", LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("verb col"  , s_div);
   /*---(build)------------+-----+-----+-*/
   strlcpy (s, s_verbs [a_iverb].labels, LEN_RECD );
   p     = strtok_r (s, q, &r);
   for (i = 0; i < 12; ++i) {
      DEBUG_YPARSE   yLOG_value   ("loop"      , i);
      /*---(filter)----------------------*/
      x_spec = s_verbs [a_iverb].specs [i];
      DEBUG_YPARSE   yLOG_char    ("x_spec"    , x_spec);
      if (x_spec == '-')  break;
      /*---(get width)-------------------*/
      x_avail = yparse_field_len (s_verbs [a_iverb].specs [i]);
      DEBUG_YPARSE   yLOG_value   ("x_avail"   , x_avail);
      DEBUG_YPARSE   yLOG_point   ("p"         , p);
      /*---(handle empties)--------------*/
      if (p == NULL)  {
         sprintf (t, "%-*.*s", x_avail, x_avail, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
      }
      /*---(handle labels)---------------*/
      else {
         DEBUG_YPARSE   yLOG_info    ("p"         , p);
         x_len   = strlen (p);
         x_pre   = x_avail - x_len;
         if (x_pre < 0)  x_pre = 0;
         if (x_pre > 3)  x_pre = 3;
         x_suf   = x_avail - x_pre - x_len;
         if (x_suf < 0)  x_suf = 0;
         x_mid   = x_avail - x_pre - x_suf;
         sprintf (t, "%*.*s%-*.*s%*.*s", x_pre, x_pre, "---", x_mid, x_mid, p, x_suf, x_suf, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
      }
      DEBUG_YPARSE   yLOG_info    ("t"         , t);
      /*---(concat)----------------------*/
      strlcat (s_div, t, LEN_RECD);
      strlcat (s_div, " § ", LEN_RECD);
      DEBUG_YPARSE   yLOG_info    ("s_div"     , s_div);
      /*---(next)------------------------*/
      p     = strtok_r (NULL, q, &r);
      /*---(done)------------------------*/
   }
   /*---(decode)-------------------------*/
   strldecode (s_div, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_verb_begin        (char *a_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_DESC ];
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   s_n = -1;
   strlcpy (s_div, "", LEN_RECD);
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("a_verb"    , a_verb);
   /*---(check existing)-----------------*/
   s_n = yparse_verb_find (NULL, a_verb);
   DEBUG_YPARSE   yLOG_value   ("find"      , s_n);
   --rce;  if (s_n < 0) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call section header)------------*/
   strlcpy   (t, s_verbs [s_n].desc, LEN_DESC );
   strlupper (t, LEN_DESC );
   DEBUG_YPARSE   yLOG_info    ("t"         , t);
   yPARSE_section (t);
   /*---(create divider)-----------------*/
   yparse__verb_divider (s_n);
   yPARSE_verb_break    (0);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_verb_break        (int   a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(print)--------------------------*/
   DEBUG_YPARSE  yLOG_sint    (s_n);
   if (s_n == -1       ) {
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_YPARSE  yLOG_sint    (a_count);
   if (a_count % 5 != 0) {
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(print)--------------------------*/
   rc = yparse_out_line (s_div);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_verb_end          (int   a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_DESC];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(print)--------------------------*/
   DEBUG_YPARSE  yLOG_sint    (s_n);
   if (s_n == -1       ) {
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_YPARSE  yLOG_sint    (a_count);
   --rce;  if (a_count % 5 != 0) {
      rc = yparse_out_line (s_div);
      if (rc < 0) {
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(footer)-------------------------*/
   sprintf (t, "# wrote %d records", a_count);
   if (a_count == 0)  yparse_out_line ("# no records required");
   else               yparse_out_line (t);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yPARSE_write_all        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("s_nverb"   , s_nverb);
   /*---(prepare)------------------------*/
   for (i = 0; i < s_nverb; ++i)  s_verbs [i].done = '-';
   /*---(call writers)-------------------*/
   while (1) {
      /*---(find next)-------------------*/
      x_lowest = 999999.0;
      x_next   = -1;
      for (i = 0; i < s_nverb; ++i) {
         if (s_verbs [i].done == 'y'    )   continue;
         if (s_verbs [i].seq >=  x_lowest)  continue;
         x_lowest = s_verbs [i].seq;
         x_next   = i;
      }
      if (x_lowest > 999.0)  break;
      if (x_next   < 0    )  break;
      s_verbs [x_next].done = 'y';
      /*---(filter)----------------------*/
      DEBUG_INPT  yLOG_info    ("verb"      , s_verbs [i].verb);
      DEBUG_INPT  yLOG_point   ("reader"    , s_verbs [i].writer);
      if (s_verbs [x_next].writer == NULL)  continue;
      /*---(handle)----------------------*/
      rc = s_verbs [x_next].writer ();
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         input reading                        ----===*/
/*====================------------------------------------====================*/
static void      o___VERB_READING____________o (void) {;};

char
yPARSE_read_all         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =   -1;
   char        c           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   char        x_verb      [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   while (1) {
      rc = yPARSE_read (NULL, NULL);
      if (rc <= 0)  {
         DEBUG_YPARSE   yLOG_note    ("end-of-file");
         break;
      }
      /*> printf ("%s\n", myPARSE.recd);                                              <*/
      if (rc <  0)  {
         DEBUG_YPARSE   yLOG_note    ("trouble reading records");
         break;
      }
      yparse_peek_verb (&n, x_verb);
      DEBUG_YPARSE  yLOG_value   ("index"     , n);
      if (n < 0)  {
         DEBUG_YPARSE   yLOG_note    ("verb not recognized");
         continue;
      }
      DEBUG_YPARSE  yLOG_info    ("verb"      , x_verb);
      DEBUG_YPARSE  yLOG_point   ("reader"    , s_verbs [n].reader);
      if (s_verbs [n].reader == NULL) {
         DEBUG_YPARSE   yLOG_note    ("reader not assigned");
         continue;
      }
      rc = s_verbs [n].reader ();
      if (rc < 0)  {
         DEBUG_YPARSE   yLOG_note    ("handler not successful");
         continue;
      }
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}

/*> char         /+-> file reading driver ----------------[ leaf   [ge.C71.072.GA]+/ /+-[02.0000.102.!]-+/ /+-[--.---.---.--]-+/                                                            <* 
 *> INPT_edit          (void)                                                                                                                                                               <* 
 *> {                                                                                                                                                                                       <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                                                                             <* 
 *>    char        rce         =  -10;                                                                                                                                                      <* 
 *>    int         rc          =    0;                                                                                                                                                      <* 
 *>    int         i           =    0;                                                                                                                                                      <* 
 *>    int         n           =   -1;                                                                                                                                                      <* 
 *>    int         x_celltry   = 0;                                                                                                                                                         <* 
 *>    int         x_cellbad   = 0;                                                                                                                                                         <* 
 *>    /+---(header)-------------------------+/                                                                                                                                             <* 
 *>    DEBUG_INPT  yLOG_enter   (__FUNCTION__);                                                                                                                                             <* 
 *>    /+---(defense)------------------------+/                                                                                                                                             <* 
 *>    --rce;  if (!STATUS_operational (FMOD_FILE)) {                                                                                                                                       <* 
 *>       DEBUG_INPT   yLOG_note    ("can not execute until operational");                                                                                                                  <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                    <* 
 *>       return rce;                                                                                                                                                                       <* 
 *>    }                                                                                                                                                                                    <* 
 *>    /+---(open file)----------------------+/                                                                                                                                             <* 
 *>    rc = yvikeys__file_open ("r");                                                                                                                                                       <* 
 *>    --rce;  if (rc < 0) {                                                                                                                                                                <* 
 *>       DEBUG_INPT  yLOG_exit    (__FUNCTION__);                                                                                                                                          <* 
 *>       return rce;                                                                                                                                                                       <* 
 *>    }                                                                                                                                                                                    <* 
 *>    /+---(read lines)---------------------+/                                                                                                                                             <* 
 *>    DEBUG_INPT  yLOG_note    ("read lines");                                                                                                                                             <* 
 *>    while (s_file != NULL) {                                                                                                                                                             <* 
 *>       /+---(read and clean)--------------+/                                                                                                                                             <* 
 *>       rc = INPT__read ();                                                                                                                                                               <* 
 *>       if (rc < 0)  break;                                                                                                                                                               <* 
 *>       rc = INPT__parse ();                                                                                                                                                              <* 
 *>       if (rc < 0)  break;                                                                                                                                                               <* 
 *>       /+---(find type)-------------------+/                                                                                                                                             <* 
 *>       DEBUG_INPT  yLOG_info    ("f_type"    , myVIKEYS.f_type);                                                                                                                         <* 
 *>       n = yvikeys__file_by_label (myVIKEYS.f_type);                                                                                                                                     <* 
 *>       DEBUG_INPT  yLOG_value   ("n"         , n);                                                                                                                                       <* 
 *>       if (n < 0)  continue;                                                                                                                                                             <* 
 *>       /+---(handle)----------------------+/                                                                                                                                             <* 
 *>       ++s_sections [n].try;                                                                                                                                                             <* 
 *>       rc = -1;                                                                                                                                                                          <* 
 *>       DEBUG_INPT  yLOG_point   ("reader"    , s_sections [n].reader);                                                                                                                   <* 
 *>       if (s_sections [n].reader != NULL) {                                                                                                                                              <* 
 *>          rc = s_sections [n].reader (myVIKEYS.f_vers, s_fields [2], s_fields [3], s_fields [4], s_fields [5], s_fields [6], s_fields [7], s_fields [8], s_fields [9], s_fields [10]);   <* 
 *>       }                                                                                                                                                                                 <* 
 *>       if (rc < 0)  ++s_sections [n].bad;                                                                                                                                                <* 
 *>       /+---(done)------------------------+/                                                                                                                                             <* 
 *>    }                                                                                                                                                                                    <* 
 *>    /+---(close file)---------------------+/                                                                                                                                             <* 
 *>    yvikeys__file_close ();                                                                                                                                                              <* 
 *>    /+---(complete)-----------------------+/                                                                                                                                             <* 
 *>    DEBUG_INPT yLOG_exit    (__FUNCTION__);                                                                                                                                              <* 
 *>    return 0;                                                                                                                                                                            <* 
 *> }                                                                                                                                                                                       <*/



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
   if      (strcmp (a_question, "entry"    ) == 0) {
      sprintf (yPARSE__unit_answer, "VERB entry     : %c, %-12.12s, %-12.12s", s_verbs [n].mode, s_verbs [n].verb, s_verbs [n].specs);
   }
   else if (strcmp (a_question, "divider"  ) == 0) {
      sprintf (yPARSE__unit_answer, "VERB divider   : %-45s", s_div);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}



