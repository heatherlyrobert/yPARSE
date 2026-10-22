/*============================[[    beg-code    ]]============================*/
/*········´ ´·············headers·´ ´·········································*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*====================------------------------------------====================*/
/*===----                     unit test endcaps                        ----===*/
/*====================------------------------------------====================*/
static void      o___ENDCAPS_________________o (void) {;}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yparse__unit_quiet      (void)
{
   yparse_config_clear ();
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
   yparse_config_clear ();
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_end        (void)
{
   yLOGS_end     ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     unit test support                        ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char*
yparse_config_status    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_ready     [LEN_TERSE] = "FROZEN·";
   char        x_verbs     [LEN_TERSE] = "manual·";
   char        x_reuse     [LEN_TERSE] = "onetime";
   char        x_in        [LEN_PATH]  = "";
   char        x_out       [LEN_PATH]  = "";
   char        x_del       [LEN_LABEL] = "´·········";
   char        x_ver       [LEN_TERSE] = "···";
   char        x_fill      [LEN_TERSE] = "´·····";
   yPARSE_qin_info   (NULL, x_in , NULL, NULL);
   yPARSE_qout_info  (NULL, x_out, NULL, NULL);
   if      (myPARSE.y_ready   == 'y')            strcpy (x_ready , "ready··");
   if      (myPARSE.y_verbs   == YPARSE_AUTO  )  strcpy (x_verbs , "auto···");
   else if (myPARSE.y_verbs   == YPARSE_SIMPLE)  strcpy (x_verbs , "simple·");
   if      (myPARSE.y_reusing == YPARSE_REUSING) strcpy (x_reuse , "reusing");
   if      (strcmp (myPARSE.y_dellist, YPARSE_FIELDS)     == 0)  strcpy (x_del, "field·····");
   else if (strcmp (myPARSE.y_dellist, YPARSE_FUNCTIONS)  == 0)  strcpy (x_del, "function··");
   else if (strcmp (myPARSE.y_dellist, YPARSE_TRADITIONS) == 0)  strcpy (x_del, "tradition·");
   else if (strcmp (myPARSE.y_dellist, "")                != 0)  strcpy (x_del, "custom····");
   if      (myPARSE.y_verber != NULL)  strcpy (x_ver , "SET");
   if      (myPARSE.y_fill   == YPARSE_FILL)   strcpy (x_fill, "fill··");
   else if (myPARSE.y_fill   == YPARSE_PACK)   strcpy (x_fill, "pack··");
   if (strcmp (x_in , "") == 0)   strcpy (x_in  , "····················");
   if (strcmp (x_out, "") == 0)   strcpy (x_out , "····················");
   sprintf (yparse_print, "%c/%-7.7s  %c/%-7.7s  verber %-3.3s  %c/%-7.7s  ·inå%-20.20sæ  outå%-20.20sæ  %c/%-10.10s %c/%-6.6s  Ï",
         myPARSE.y_ready, x_ready, myPARSE.y_verbs, x_verbs, x_ver, myPARSE.y_reusing, x_reuse,
         x_in, x_out, myPARSE.y_deltype, x_del, myPARSE.y_fill, x_fill);
   return yparse_print;
}

char
yparse_queue_rando      (tQUEUE *a_queue)
{
   /*---(master data)--------------------*/
   a_queue->q_dir      =  '*';
   strcpy (a_queue->q_label, "abc");
   a_queue->q_handler  = 0x01;
   a_queue->q_iverb    =    2;
   a_queue->q_good     =  'g';
   a_queue->q_hidden   =  'h';
   /*---(file)---------------------------*/
   strcpy (a_queue->q_loc, "test file");
   a_queue->q_file     = 0x03;
   a_queue->q_tline    =    6;
   a_queue->q_nline    =    7;
   a_queue->q_cline    =    8;
   /*---(record)-------------------------*/
   strcpy (a_queue->q_recd , "lots of fields");
   a_queue->q_len      =    9;
   /*---(fields)-------------------------*/
   a_queue->q_head     = NULL;
   a_queue->q_tail     = NULL;
   a_queue->q_count    =    8;
   a_queue->q_first    =    5;
   a_queue->q_last     =   12;
   a_queue->q_curr     =   11;
   /*---(complete)-----------------------*/
   return 0;
}

char*
yparse_queue_status     (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    1;
   char        x_label     [LEN_TERSE] = "´····";
   char        x_handler   [LEN_SHORT] = "···";
   char        x_loc       [LEN_DESC]  = "´·······································";
   char        x_file      [LEN_SHORT] = "···";
   char        x_recd      [LEN_DESC]  = "´·······································";
   char        x_head      [LEN_LABEL] = "´·········";
   char        x_tail      [LEN_LABEL] = "´·········";
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   if (a_queue == 'T') {
      DEBUG_YPARSE  yLOG_note    ("requested titiles");
      strcpy (yparse_print, "D label vrb had  G H  ---location--------- ptr tot acp cur  len ---record-------------------------------  ---head--- ---tail--- cnt fst lst cur  Ï");
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return yparse_print;
   }
   DEBUG_YPARSE  yLOG_note    ("requested actual queue");
   /*---(defense)------------------------*/
   rc = yparse_queue__defense   (a_queue, '´');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      strcpy (yparse_print, "(run yPARSE_config and yparse_queue_init first)");
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return yparse_print;
   }
   /*---(defaults)-----------------------*/
   strcpy (yparse_print, "- ´···· ··- ···  - -  ´··················· ··· ··- ··- ··-  ··- ´·······································  ´········· ´········· ··- ··- ··- ··-  Ï");
   /*---(prepare)------------------------*/
   if (a_queue->q_label    != NULL)  snprintf (x_label, LEN_TERSE, "%s·····", a_queue->q_label);
   if (a_queue->q_handler  != NULL)  strcpy   (x_handler, "SET");
   if (a_queue->q_loc  [0] != '\0')  snprintf (x_loc  , 21       , "%s········································", a_queue->q_loc);
   if (a_queue->q_file     != NULL)  strcpy   (x_file   , "SET");
   if (a_queue->q_recd [0] != '\0')  snprintf (x_recd , 41       , "%s········································", a_queue->q_recd);
   if (a_queue->q_head     != NULL) {
      snprintf (x_head , 11, "%s··········", a_queue->q_head->n_item);
      if (x_head [ 9] != '·')  x_head [ 9] = '>';
   }
   if (a_queue->q_tail     != NULL) {
      snprintf (x_tail , 11, "%s··········", a_queue->q_tail->n_item);
      if (x_tail [ 9] != '·')  x_tail [ 9] = '>';
   }
   sprintf (yparse_print, "%c %-5.5s %3d %-3.3s  %c %c  %-20.20s %-3.3s %3d %3d %3d  %3d %-40.40s  %-10.10s %-10.10s %3d %3d %3d %3d  Ï",
         a_queue->q_dir, x_label, a_queue->q_iverb, x_handler,
         a_queue->q_good, a_queue->q_hidden,
         x_loc, x_file, a_queue->q_tline, a_queue->q_nline, a_queue->q_cline,
         a_queue->q_len, x_recd,
         x_head, x_tail, a_queue->q_count, a_queue->q_first, a_queue->q_last, a_queue->q_curr);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return yparse_print;
}

/*> char*                                                                                                                                                <* 
 *> yparse_queue_by_cursor  (tQUEUE *a_queue, char a_dir)                                                                                                <* 
 *> {                                                                                                                                                    <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                          <* 
 *>    char        rce         =  -10;                                                                                                                   <* 
 *>    char        rc          =    1;                                                                                                                   <* 
 *>    char        n           =    0;                                                                                                                   <* 
 *>    char        c           =    0;                                                                                                                   <* 
 *>    char        x_prev      [LEN_DESC]  = "´·····························";                                                                           <* 
 *>    char        x_curr      [LEN_DESC]  = "´·····························";                                                                           <* 
 *>    char        x_next      [LEN_DESC]  = "´·····························";                                                                           <* 
 *>    tNODE      *x_node      = NULL;                                                                                                                   <* 
 *>    /+---(header)-------------------------+/                                                                                                          <* 
 *>    DEBUG_YDLST  yLOG_senter  (__FUNCTION__);                                                                                                         <* 
 *>    /+---(quick-out)----------------------+/                                                                                                          <* 
 *>    if (a_dir == 'T') {                                                                                                                               <* 
 *>       strcpy (yparse_print, "seq  ref  ---curr-----------------------  ---prev-----------------------  ---next-----------------------  Ï");   <* 
 *>       DEBUG_YDLST   yLOG_sexit   (__FUNCTION__);                                                                                                     <* 
 *>       return yparse_print;                                                                                                                    <* 
 *>    }                                                                                                                                                 <* 
 *>    strcpy (yparse_print, "··-  ··-  ´·····························  ´·····························  ´·····························  Ï");      <* 
 *>    /+---(defense)------------------------+/                                                                                                          <* 
 *>    DEBUG_YDLST  yLOG_spoint  (a_queue);                                                                                                              <* 
 *>    --rce;  if (a_queue == NULL) {                                                                                                                    <* 
 *>       strcpy (yparse_print, "(not a legal queue)");                                                                                           <* 
 *>       DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);                                                                                                 <* 
 *>       return yparse_print;                                                                                                                    <* 
 *>    }                                                                                                                                                 <* 
 *>    /+---(quick-out)----------------------+/                                                                                                          <* 
 *>    --rce;  if (a_queue->q_count == 0) {                                                                                                              <* 
 *>       strcpy (yparse_print, "(empty)");                                                                                                       <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                                                                                                <* 
 *>       return yparse_print;                                                                                                                    <* 
 *>    }                                                                                                                                                 <* 
 *>    /+---(preparse)-----------------------+/                                                                                                          <* 
 *>    n = a_queue->q_curr;                                                                                                                              <* 
 *>    DEBUG_YDLST  yLOG_sint    (n);                                                                                                                    <* 
 *>    /+---(switch)-------------------------+/                                                                                                          <* 
 *>    DEBUG_YDLST  yLOG_schar   (a_dir);                                                                                                                <* 
 *>    --rce;  switch (a_dir) {                                                                                                                          <* 
 *>    case YDLST_HEAD : case YDLST_DHEAD :                                                                                                              <* 
 *>       n = 0;                                                                                                                                         <* 
 *>       break;                                                                                                                                         <* 
 *>    case YDLST_PREV : case YDLST_DPREV :                                                                                                              <* 
 *>       --n;                                                                                                                                           <* 
 *>       break;                                                                                                                                         <* 
 *>    case YDLST_CURR : case YDLST_DCURR :                                                                                                              <* 
 *>       n = n;                                                                                                                                         <* 
 *>       break;                                                                                                                                         <* 
 *>    case YDLST_NEXT : case YDLST_DNEXT :                                                                                                              <* 
 *>       ++n;                                                                                                                                           <* 
 *>       break;                                                                                                                                         <* 
 *>    case YDLST_TAIL : case YDLST_DTAIL :                                                                                                              <* 
 *>       n = a_queue->q_count - 1;                                                                                                                      <* 
 *>       break;                                                                                                                                         <* 
 *>    default         :                                                                                                                                 <* 
 *>       DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);                                                                                                 <* 
 *>       return yparse_print;                                                                                                                    <* 
 *>    }                                                                                                                                                 <* 
 *>    DEBUG_YDLST  yLOG_sint    (n);                                                                                                                    <* 
 *>    /+---(check end)----------------------+/                                                                                                          <* 
 *>    /+> printf ("\nnew find\n");                                                       <+/                                                            <* 
 *>    --rce;  if (n < 0) {                                                                                                                              <* 
 *>       strcpy (yparse_print, "(under)");                                                                                                       <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                                                                                                <* 
 *>       return yparse_print;                                                                                                                    <* 
 *>    }                                                                                                                                                 <* 
 *>    --rce;  if (n >= MAX_NODE) {                                                                                                                      <* 
 *>       strcpy (yparse_print, "(over)");                                                                                                        <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                                                                                                <* 
 *>       return yparse_print;                                                                                                                    <* 
 *>    }                                                                                                                                                 <* 
 *>    /+---(find)---------------------------+/                                                                                                          <* 
 *>    x_node = a_queue->q_head;                                                                                                                         <* 
 *>    while (x_node != NULL) {                                                                                                                          <* 
 *>       /+> printf ("%2d %2d %2d %-20.20s", a_queue->q_count, n, c, x_node->n_item);    <+/                                                            <* 
 *>       DEBUG_YDLST  yLOG_snote   (x_node->n_item);                                                                                                    <* 
 *>       if (c == n) {                                                                                                                                  <* 
 *>          /+> printf ("  FOUND\n");                                                    <+/                                                            <* 
 *>          DEBUG_YDLST  yLOG_snote   ("found it");                                                                                                     <* 
 *>          break;                                                                                                                                      <* 
 *>       }                                                                                                                                              <* 
 *>       ++c;                                                                                                                                           <* 
 *>       /+> printf ("  nope\n");                                                        <+/                                                            <* 
 *>       x_node = x_node->n_next;                                                                                                                       <* 
 *>    }                                                                                                                                                 <* 
 *>    if (x_node == NULL) {                                                                                                                             <* 
 *>       strcpy (yparse_print, "(n/a)");                                                                                                         <* 
 *>       DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);                                                                                                 <* 
 *>       return yparse_print;                                                                                                                    <* 
 *>    }                                                                                                                                                 <* 
 *>    /+---(output)-------------------------+/                                                                                                          <* 
 *>    if (x_node->n_prev != NULL) {                                                                                                                     <* 
 *>       if (x_node->n_prev->n_item != NULL) snprintf (x_prev, 31, "%s······························", x_node->n_prev->n_item);                         <* 
 *>       else                                strcpy   (x_prev, "(null)························");                                                       <* 
 *>    }                                                                                                                                                 <* 
 *>    if (x_node->n_item != NULL) snprintf (x_curr, 31, "%s······························", x_node->n_item);                                            <* 
 *>    if (x_node->n_next != NULL) {                                                                                                                     <* 
 *>       if (x_node->n_next->n_item != NULL) snprintf (x_next, 31, "%s······························", x_node->n_next->n_item);                         <* 
 *>       else                                strcpy   (x_next, "(null)························");                                                       <* 
 *>    }                                                                                                                                                 <* 
 *>    sprintf (yparse_print, "%3d  %3d  %-30.30s  %-30.30s  %-30.30s  Ï", n, x_node->n_ref, x_curr, x_prev, x_next);                             <* 
 *>    /+---(save-back)----------------------+/                                                                                                          <* 
 *>    a_queue->q_curr = n;                                                                                                                              <* 
 *>    /+---(complete)-----------------------+/                                                                                                          <* 
 *>    DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);                                                                                                         <* 
 *>    return yparse_print;                                                                                                                       <* 
 *> }                                                                                                                                                    <*/



/*====================------------------------------------====================*/
/*===----                      mock test helpers                       ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_SUPPORT____________o (void) {;}

static char    *i_verb        [LEN_LABEL];
static char    *i_label       [LEN_LABEL];
static char    *i_terse       [LEN_TERSE];
static int      i_int         = 0;
static llong    i_long        = 0;
static float    i_float       = 0.0;
static double   i_double      = 0.0;
static char     i_char        = 0;
static double   i_exp         = 0.0;
static char    *i_desc        [LEN_DESC];
static char    *i_string      [LEN_RECD];

static char    *s_verb           = NULL;
static char    *s_label          = NULL;
static char    *s_terse          = NULL;
static int     *s_int            = NULL;
static llong   *s_long           = NULL;
static float   *s_float          = NULL;
static double  *s_double         = NULL;
static char    *s_char           = NULL;
static double  *s_exp            = NULL;
static char    *s_desc           = NULL;
static char    *s_string         = NULL;

/*> char                                                                              <* 
 *> yparse_mock__clear      (void)                                                    <* 
 *> {                                                                                 <* 
 *>    int         i           =    0;                                                <* 
 *>    for (i = 0; i < 10; ++i) {                                                     <* 
 *>       strcpy (g_mocks [i].recd, "");                                              <* 
 *>       g_mocks [i].x_ch    = '·';                                                  <* 
 *>       g_mocks [i].x_int   = -1;                                                   <* 
 *>       strcpy (g_mocks [i].x_str , "-");                                           <* 
 *>       g_mocks [i].x_float = -1.1;                                                 <* 
 *>       strcpy (g_mocks [i].x_str2, "-");                                           <* 
 *>    }                                                                              <* 
 *>    g_nmock = 0;                                                                   <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/


#define    MAX_MOCK   50
static struct {
   /*---(input)-------------*/
   char       *d_recd      [LEN_RECD];
   char       *d_verb      [LEN_LABEL];
   /*---(fields)------------*/
   char       *d_label     [LEN_LABEL];
   char        d_terse     [LEN_TERSE];
   int         d_int;
   llong       d_long;
   float       d_float;
   double      d_double;
   char        d_char;
   double      d_exp;
   char       *d_desc      [LEN_DESC];
   char       *d_string    [LEN_RECD];
   /*---(done)--------------*/
} s_mocks [MAX_MOCK];
static char   s_nmock   = 0;


char
yparse_mock_clear       (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      /*---(input)-----------------------*/
      ystrlcpy (s_mocks [i].d_recd      , "", LEN_RECD);
      ystrlcpy (s_mocks [i].d_verb      , "", LEN_LABEL);
      /*---(fields)----------------------*/
      ystrlcpy (s_mocks [i].d_label     , "", LEN_LABEL);
      ystrlcpy (s_mocks [i].d_terse     , "", LEN_LABEL);
      s_mocks [i].d_int       = 0;
      s_mocks [i].d_long      = 0;
      s_mocks [i].d_float     = 0.0;
      s_mocks [i].d_double    = 0.0;
      s_mocks [i].d_char      = 0;
      s_mocks [i].d_exp       = 0.0;
      ystrlcpy (s_mocks [i].d_desc      , "", LEN_DESC);
      ystrlcpy (s_mocks [i].d_string    , "", LEN_RECD);
      /*---(done)------------------------*/
   }
   s_nmock = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      mock test shared                        ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_SHARED_____________o (void) {;}

char
yparse_mock_internal    (void)
{
   s_verb    = i_verb;
   s_label   = i_label;
   s_terse   = i_terse;
   s_int     = &i_int;
   s_long    = &i_long;
   s_float   = &i_float;
   s_double  = &i_double;
   s_char    = &i_char;
   s_exp     = &i_exp;
   s_desc    = i_desc;
   s_string  = i_string;
   return 0;
}

char
yparse_mock_external    (char *a_verb, char *a_label, char *a_terse, int *a_int, llong *a_long, float *a_float, double *a_double, char *a_char, double *a_exp, char *a_desc, char *a_str)
{
   s_verb    = a_verb;
   s_label   = a_label;
   s_terse   = a_terse;
   s_int     = a_int;
   s_long    = a_long;
   s_float   = a_float;
   s_double  = a_double;
   s_char    = a_char;
   s_exp     = a_exp;
   s_desc    = a_desc;
   s_string  = a_str;
   return 0;
}

char
yparse_mock_handler     (int n, uchar *a_verb, char a_exist, void *a_handler)
{
   char rc = 0;
   ystrlcpy (s_verb, a_verb, LEN_USER);
   if      (strcmp (a_verb, "tiny"    ) == 0) {
      rc = yPARSE_scanf  (a_verb, "i"         , s_int);
      yPARSE_printf ("tiny"     , "i"         , *s_int);
   }
   else if (strcmp (a_verb, "small"   ) == 0) {
      rc = yPARSE_scanf  (a_verb, "TL"        , s_terse, s_label);
      yPARSE_printf ("small"    , "TL"        , s_terse, s_label);
   }
   else if (strcmp (a_verb, "medium"  ) == 0) {
      rc = yPARSE_scanf  (a_verb, "TidcO"     , s_terse, s_int, s_double, s_char, s_string);
      yPARSE_printf ("medium"   , "TidcO"     , s_terse, *s_int, *s_double, *s_char, s_string);
   }
   else if (strcmp (a_verb, "large"   ) == 0) {
      rc = yPARSE_scanf  (a_verb, "LTfdcileLO", s_label, s_terse, s_float, s_double, s_char, s_int, s_long, s_exp, s_desc, s_string);
      yPARSE_printf ("large"    , "LTfdcileLO", s_label, s_terse, *s_float, *s_double, *s_char, *s_int, *s_long, *s_exp, s_desc, s_string);
   }
   else if (strcmp (a_verb, "sample"  ) == 0) {
      rc = yPARSE_scanf  (a_verb, "LifcO"     , s_label, s_int, s_float, s_char, s_desc);
      yPARSE_printf ("sample"   , "LifcO"     , s_label, *s_int, *s_float, *s_char, s_desc);
   }
   else {
      rc = -100;
   }
   return rc;
}

char
yparse_mock_verber      (void)
{
   char       *x_masking   = " ik_pure ik_from fk_pure fk_from ";
   char        t           [LEN_LABEL];
   yPARSE_toss ();
   sprintf (t, " %s ", myPARSE.y_verb);
   /*> if (strstr (x_masking, t) != NULL)  return 1;                                  <*/
   return 0;
}

char
yparse_mock_header      (void)
{
   yPARSE_printf  ("s_control", "cSO" , 'y', "0.6w", "testing integration");
   yPARSE_printf  ("s_format" , "O"  , "mimecat");
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    mock test tiny model                     ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_TINY_______________o (void) {;}

char
yparse_mock_rtiny       (int n, uchar *a_verb)
{
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   if (a_verb != NULL) DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
   yPARSE_vscanf (a_verb, s_int);
   ystrlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   s_mocks [s_nmock].d_int     = *s_int;
   ++s_nmock;
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_mock__wtiny       (char a_fancy, int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   if (a_verb != NULL) DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
   for (i = 0; i < MAX_MOCK; ++i) {
      DEBUG_YPARSE   yLOG_info    ("check"     , s_mocks [i].d_verb);
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
      if (a_fancy == 'f')  yPARSE_vprintf (c , a_verb, s_mocks [i].d_int);
      else                 yPARSE_vprintf (-1, a_verb, s_mocks [i].d_int);
      ++c;
   }
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return c;
}

char yparse_mock_wtiny    (int n, uchar *a_verb) { return yparse_mock__wtiny ('-', n, a_verb); }
char yparse_mock_ftiny    (int n, uchar *a_verb) { return yparse_mock__wtiny ('f', n, a_verb); }



/*====================------------------------------------====================*/
/*===----                    mock test small model                     ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_SMALL______________o (void) {;}

char
yparse_mock_rsmall      (int n, uchar *a_verb)
{
   yPARSE_vscanf (a_verb, s_terse, s_label);
   ystrlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   ystrlcpy (s_mocks [s_nmock].d_terse     , s_terse   , LEN_TERSE);
   ystrlcpy (s_mocks [s_nmock].d_label     , s_label   , LEN_LABEL);
   ++s_nmock;
   return 0;
}

char
yparse_mock__wsmall      (char a_fancy, int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      if (a_fancy == 'f')  yPARSE_vprintf (c , a_verb, s_mocks [i].d_terse, s_mocks [i].d_label);
      else                 yPARSE_vprintf (-1, a_verb, s_mocks [i].d_terse, s_mocks [i].d_label);
      ++c;
   }
   return c;
}

char yparse_mock_wsmall   (int n, uchar *a_verb) { return yparse_mock__wsmall ('-', n, a_verb); }
char yparse_mock_fsmall   (int n, uchar *a_verb) { return yparse_mock__wsmall ('f', n, a_verb); }



/*====================------------------------------------====================*/
/*===----                   mock test medium model                     ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_MEDIUM_____________o (void) {;}

char
yparse_mock_rmedium     (int n, uchar *a_verb)
{
   yPARSE_vscanf (a_verb, s_terse, s_int, s_double, s_char, s_string);
   ystrlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   ystrlcpy (s_mocks [s_nmock].d_terse     , s_terse   , LEN_TERSE);
   s_mocks [s_nmock].d_int     = *s_int;
   s_mocks [s_nmock].d_double  = *s_double;
   s_mocks [s_nmock].d_char    = *s_char;
   ystrlcpy (s_mocks [s_nmock].d_string    , s_string  , LEN_RECD);
   ++s_nmock;
   return 0;
}

char
yparse_mock__wmedium     (char a_fancy, int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      if (a_fancy == 'f')  yPARSE_vprintf (c , a_verb, s_mocks [i].d_terse, s_mocks [i].d_int, s_mocks [i].d_double, s_mocks [i].d_char, s_mocks [i].d_string);
      else                 yPARSE_vprintf (-1, a_verb, s_mocks [i].d_terse, s_mocks [i].d_int, s_mocks [i].d_double, s_mocks [i].d_char, s_mocks [i].d_string);
      ++c;
   }
   return c;
}

char yparse_mock_wmedium (int n, uchar *a_verb) { return yparse_mock__wmedium ('-', n, a_verb); }
char yparse_mock_fmedium (int n, uchar *a_verb) { return yparse_mock__wmedium ('f', n, a_verb); }



/*====================------------------------------------====================*/
/*===----                   mock test large model                     ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_LARGE______________o (void) {;}

char
yparse_mock_rlarge      (int n, uchar *a_verb)
{
   yPARSE_vscanf (a_verb, s_terse, s_int, s_double, s_char, s_string);
   ystrlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   ystrlcpy (s_mocks [s_nmock].d_terse     , s_terse   , LEN_TERSE);
   ystrlcpy (s_mocks [s_nmock].d_label     , s_label   , LEN_LABEL);
   s_mocks [s_nmock].d_float   = *s_float;
   s_mocks [s_nmock].d_double  = *s_double;
   s_mocks [s_nmock].d_char    = *s_char;
   s_mocks [s_nmock].d_int     = *s_int;
   s_mocks [s_nmock].d_long    = *s_long;
   s_mocks [s_nmock].d_exp     = *s_exp;
   ystrlcpy (s_mocks [s_nmock].d_desc      , s_desc    , LEN_DESC);
   ystrlcpy (s_mocks [s_nmock].d_string    , s_string  , LEN_RECD);
   ++s_nmock;
   return 0;
}

char
yparse_mock__wlarge      (char a_fancy, int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      if (a_fancy == 'f')  yPARSE_vprintf (c , a_verb, s_mocks [i].d_terse, s_mocks [i].d_label, s_mocks [i].d_float, s_mocks [i].d_double, s_mocks [i].d_char, s_mocks [i].d_int, s_mocks [i].d_long, s_mocks [i].d_exp, s_mocks [i].d_desc, s_mocks [i].d_string);
      else                 yPARSE_vprintf (-1, a_verb, s_mocks [i].d_terse, s_mocks [i].d_label, s_mocks [i].d_float, s_mocks [i].d_double, s_mocks [i].d_char, s_mocks [i].d_int, s_mocks [i].d_long, s_mocks [i].d_exp, s_mocks [i].d_desc, s_mocks [i].d_string);
      ++c;
   }
   return c;
}

char yparse_mock_wlarge  (int n, uchar *a_verb) { return yparse_mock__wlarge ('-', n, a_verb); }
char yparse_mock_flarge  (int n, uchar *a_verb) { return yparse_mock__wlarge ('f', n, a_verb); }



/*====================------------------------------------====================*/
/*===----                      mock test exim                          ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_EXIM_______________o (void) {;}

char
yparse_mock_writer      (void)
{
   yPARSE_vprintf   (-1, "macro"        , 'A', 32726, "jub jub"       , 3.1416, "hey"          );
   ystrlcpy (s_mocks [s_nmock++].d_recd, myPARSE.y_recd, LEN_RECD);
   yPARSE_vprintf   (-1, "macro"        , 'z',    12, "testing"       , 14.46 , "hey back"     );
   ystrlcpy (s_mocks [s_nmock++].d_recd, myPARSE.y_recd, LEN_RECD);
   yPARSE_vprintf   (-1, "macro"        , 'f', -4922, "another string", 186.0 , "hey one last" );
   ystrlcpy (s_mocks [s_nmock++].d_recd, myPARSE.y_recd, LEN_RECD);
   return 0;
}

char
yparse_mock_reader      (void)
{
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("s_nmock"   , s_nmock);
   yPARSE_vscanf    ("macro", &(s_mocks[s_nmock].d_char), &(s_mocks[s_nmock].d_int), &(s_mocks[s_nmock].d_label), &(s_mocks[s_nmock].d_float), &(s_mocks[s_nmock].d_desc));
   DEBUG_YPARSE  yLOG_info    ("recd"      , myPARSE.y_recd);
   ystrlcpy (s_mocks [s_nmock++].d_recd, myPARSE.y_recd, LEN_RECD);
   DEBUG_YPARSE  yLOG_value   ("s_nmock"   , s_nmock);
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        mock testing                          ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK____________________o (void) {;}

/*> tMOCK       g_mocks     [10];                                                     <*/
/*> int         g_nmock     = 0;                                                      <*/

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse_mock__unit       (char *a_question, int a_num)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                       <* 
    *> char        rc          =    0;                                                                                                                                                                                <* 
    *> char        t           [LEN_RECD];                                                                                                                                                                            <* 
    *> /+---(preprare)-----------------------+/                                                                                                                                                                       <* 
    *> ystrlcpy  (yparse_print, "MOCK unit        : question not understood", LEN_STR);                                                                                                                        <* 
    *> /+---(answer)------------------------------------------+/                                                                                                                                                      <* 
    *> if      (strcmp (a_question, "count"    ) == 0) {                                                                                                                                                              <* 
    *>    sprintf (yparse_print, "MOCK count     : %2d", g_nmock);                                                                                                                                             <* 
    *> }                                                                                                                                                                                                              <* 
    *> else if (strcmp (a_question, "recd"     ) == 0) {                                                                                                                                                              <* 
    *>    sprintf (yparse_print, "MOCK recd   %2d : %2d[%s]", a_num, strlen (g_mocks [a_num].recd), g_mocks [a_num].recd);                                                                                     <* 
    *> }                                                                                                                                                                                                              <* 
    *> else if (strcmp (a_question, "detail"   ) == 0) {                                                                                                                                                              <* 
    *>    sprintf (yparse_print, "MOCK detail %2d : %c %5d %-20.20s %11.5f %s", a_num, g_mocks [a_num].x_ch, g_mocks [a_num].x_int, g_mocks [a_num].x_str, g_mocks [a_num].x_float, g_mocks [a_num].x_str2);   <* 
    *> }                                                                                                                                                                                                              <* 
    *> /+---(complete)----------------------------------------+/                                                                                                                                                      <* 
    *> return yparse_print;                                                                                                                                                                                    <*/
}

