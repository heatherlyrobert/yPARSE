/*============================[[    beg-code    ]]============================*/
/*········´ ´·····················´ ´·········································*/
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



#define     MAX_TYPES   50
typedef   struct cTYPES  tTYPES;
struct cTYPES {
   /*---(base)--------------*/
   char        t_spec;                      /* unique one char id             */
   char        t_name      [LEN_LABEL];     /* short name                     */
   int         t_cat;                       /* category -- string, numeric    */
   char        t_desc      [LEN_LABEL];     /* description                    */
   /*---(usage)-------------*/
   char        t_varg;                      /* use with vargs                 */
   char        t_save;                      /* save-to type                   */
   int         t_size;                      /* width                          */
   char        t_format    [LEN_LABEL];     /* actual format string           */
   /*---(ranges)------------*/
   char        t_ranged;                    /* forced range check             */
   llong       t_lmin;                      /* minimum allowed (int/long)     */
   llong       t_lmax;                      /* maximum allowed (int/long)     */
   double      t_dmin;                      /* minimum allowed (float/double) */
   double      t_dmax;                      /* maximum allowed (float/double) */
   /*---(done)--------------*/
};
static const tTYPES  S_specs [MAX_TYPES] = {
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
   { '-' , "nothing"     , 'n' , "spacer"          , '-' , '-' ,     1 , ""                , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
   { 'c' , "char"        , 'n' , "single char"     , 'i' , 'c' ,     1 , "%c"              , 'u' ,               31   ,              255   ,                0.0 ,                0.0 },
   { 's' , "short"       , 'n' , "short integer"   , 'i' , 's' ,     3 , "%3d"             , 'i' ,              -99   ,              999   ,                0.0 ,                0.0 },
   { 'i' , "integer"     , 'n' , "normal integer"  , 'i' , 'i' ,     6 , "%6d"             , 'i' ,           -99999   ,           999999   ,                0.0 ,                0.0 },
   { 'l' , "long"        , 'n' , "long integer"    , 'L' , 'L' ,    10 , "%10d"            , 'L' ,       -999999999LL ,       9999999999LL ,                0.0 ,                0.0 },
   { 'h' , "huge"        , 'n' , "long integer"    , 'L' , 'L' ,    16 , "%16ld"           , 'L' , -999999999999998LL , 9999999999999998LL ,                0.0 ,                0.0 },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
   { ',' , "comma"       , 'n' , "comma"           , 'i' , 'i' ,    10 , "%10d"            , 'i' ,          -999999   ,           999999   ,                0.0 ,                0.0 },
   { ';' , "hcomma"      , 'n' , "long comma"      , 'L' , 'L' ,    19 , "%19ld"           , 'L' , -999999999999998LL , 9999999999999998LL ,                0.0 ,                0.0 },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
   { 'u' , "micro"       , 'n' , "micro float"     , 'f' , 'f' ,     6 , "%6.3f"           , 'f' ,                0   ,                0   ,             -9.999 ,             99.999 },
   { 'n' , "nano"        , 'n' , "nano float"      , 'f' , 'f' ,     9 , "%9.6f"           , 'f' ,                0   ,                0   ,          -9.999999 ,          99.999999 },
   { 'k' , "ykine"       , 'n' , "short float"     , 'f' , 'f' ,     6 , "%6.1f"           , 'f' ,                0   ,                0   ,             -999.9 ,             9999.9 },
   { 'f' , "float"       , 'n' , "normal float"    , 'f' , 'f' ,     8 , "%8.2f"           , 'f' ,                0   ,                0   ,           -9999.99 ,           99999.99 },
   { 'd' , "double"      , 'n' , "double float"    , 'd' , 'd' ,    10 , "%10.3lf"         , 'f' ,                0   ,                0   ,         -99999.999 ,         999999.999 },
   { 't' , "technical"   , 'n' , "technical"       , 'd' , 'd' ,    18 , "%18.6lf"         , 'D' ,                0   ,                0   , -9999999999.999990 , 99999999999.999990 },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
   { 'e' , "sml-exp"     , 'n' , "tech float"      , 'd' , 'd' ,    10 , "%2.3e"           , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'm' , "med-exp"     , 'n' , "tech float"      , 'd' , 'd' ,    14 , "%2.7e"           , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'b' , "big-exp"     , 'n' , "exponent"        , 'd' , 'd' ,    19 , "%2.12e"          , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
   { 'C' , "one-char"    , 's' , "1 char string"   , 's' , 's' ,     1 , "%-1.1s"          , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'S' , "short"       , 's' , "short string"    , 's' , 's' ,     5 , "%-5.5s"          , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'T' , "terse"       , 's' , "terse string"    , 's' , 's' ,    10 , "%-10.10s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'U' , "user"        , 's' , "user string"     , 's' , 's' ,    12 , "%-12.12s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'L' , "label"       , 's' , "label string"    , 's' , 's' ,    20 , "%-20.20s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { '3' , "thirty"      , 's' , "thirty string"   , 's' , 's' ,    30 , "%-30.30s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { '4' , "forty"       , 's' , "forty string"    , 's' , 's' ,    40 , "%-40.40s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'D' , "desc"        , 's' , "desc string"     , 's' , 's' ,    50 , "%-50.50s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { '6' , "sixty"       , 's' , "sixty string"    , 's' , 's' ,    60 , "%-40.40s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { '7' , "seventy"     , 's' , "seventy string"  , 's' , 's' ,    70 , "%-70.70s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { '8' , "eighty"      , 's' , "eighty string"   , 's' , 's' ,    80 , "%-80.80s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'H' , "hundred"     , 's' , "hundred string"  , 's' , 's' ,   100 , "%-100.100s"      , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'F' , "full"        , 's' , "two-hundred"     , 's' , 's' ,   200 , "%-200.200s"      , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'R' , "recd"        , 's' , "two-thousand"    , 's' , 's' ,  2000 , "%-2000.2000s"    , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   { 'O' , "open"        , 's' , "open string"     , 's' , 's' ,    60 , "%s"              , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
   {  0  , "end-of-types", '-' , ""                , '-' , '-' ,     0 , ""                , '-' ,                0   ,                0   ,                0.0 ,                0.0 },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float--- */
};
static char  S_strings     [LEN_LABEL]  = "";
static char  S_numbers     [LEN_LABEL]  = "";
static int   S_nspec       =    0;
static int   S_cspec       =    0;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;};

char
yparse_spec_init        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   S_nspec = 0;
   ystrlcpy (S_strings, "", LEN_LABEL);
   ystrlcpy (S_numbers, "", LEN_LABEL);
   /*---(walk)---------------------------*/
   for (i = 0; i < MAX_TYPES; ++i) {
      DEBUG_YPARSE  yLOG_sint    (i);
      DEBUG_YPARSE  yLOG_snote   (S_specs [i].t_name);
      if (S_specs [i].t_spec ==  0 )  break;
      sprintf (t, "%c", S_specs [i].t_spec);
      if (S_specs [i].t_cat  == 's')   ystrlcat (S_strings, t, LEN_LABEL);
      if (S_specs [i].t_cat  == 'n')   ystrlcat (S_numbers, t, LEN_LABEL);
      ++S_nspec;
   }
   DEBUG_YPARSE  yLOG_snote   (S_strings);
   DEBUG_YPARSE  yLOG_snote   (S_numbers);
   DEBUG_YPARSE  yLOG_sint    (S_nspec);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     searching specs                          ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;};

char
yparse_spec__search     (char a_func [LEN_TITLE], char a_spec, char a_dir, char a_index, char *r_spec, char r_name [LEN_LABEL], char *r_cat, char r_desc [LEN_LABEL], char *r_varg, char *r_save, char *r_size, char r_format [LEN_LABEL], char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        n           =    0;
   char        x_found     =  '-';
   char        x_name      [LEN_LABEL] = "´········";
   char        x_desc      [LEN_LABEL] = "´··············";
   char        x_format    [LEN_LABEL] = "´··············";
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (a_func);
   /*---(default)------------------------*/
   if (r_spec   != NULL)  *r_spec   =  '-';
   if (r_name   != NULL)  strcpy (r_name   , "");
   if (r_cat    != NULL)  *r_cat    =  '-';
   if (r_desc   != NULL)  strcpy (r_desc   , "");
   if (r_varg   != NULL)  *r_varg   =  '-';
   if (r_save   != NULL)  *r_save   =  '-';
   if (r_size   != NULL)  *r_size   =    0;
   if (r_format != NULL)  strcpy (r_format , "");
   if (d_entry  != NULL)  strcpy (d_entry  , "");
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      if (d_entry  != NULL)  strcpy (d_entry, "(null func)");
      DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(title)--------------------------*/
   if (a_dir == 'T') {
      if (d_entry  != NULL)  strcpy (d_entry, "##  A  ---name---  C  ---desc--------  V  S  sz  ---format------  R  ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  Ï");
      DEBUG_YPARSE  yLOG_exit    (a_func);
      return RC_ACK;
   }
   /*---(quick-out)----------------------*/
   DEBUG_YPARSE  yLOG_value   ("S_nspec"   , S_nspec);
   --rce;  if (S_nspec == 0) {
      if (d_entry  != NULL)  strcpy (d_entry, "(empty)");
      DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YPARSE yLOG_char    ("a_spec"    , a_spec);
   DEBUG_YPARSE yLOG_char    ("a_dir"     , a_dir);
   DEBUG_YPARSE yLOG_value   ("a_index"   , a_index);
   /*---(handlen verb)-------------------*/
   --rce;  if (a_spec >= 32) {
      DEBUG_YPARSE yLOG_note    ("requested abbr search");
      for (i = 0; i < S_nspec; ++i) {
         if (S_specs [i].t_spec != a_spec)      continue;
         DEBUG_YPARSE   yLOG_note    ("FOUND");
         n = i;
         x_found = 'y';
         break;
      }
   }
   /*---(handle cursor)------------------*/
   else if (a_dir >  0) {
      DEBUG_YPARSE yLOG_note    ("requested cursoring");
      /*---(prepare)---------------------*/
      n = S_cspec;
      DEBUG_YPARSE yLOG_value   ("n"         , n);
      /*---(update)----------------------*/
      --rce;  switch (a_dir) {
      case YDLST_HEAD : case YDLST_DHEAD :
         n = 0;
         break;
      case YDLST_PREV : case YDLST_DPREV :
         --n;
         break;
      case YDLST_CURR : case YDLST_DCURR :
         n = n;
         break;
      case YDLST_NEXT : case YDLST_DNEXT :
         ++n;
         break;
      case YDLST_TAIL : case YDLST_DTAIL :
         n = S_nspec - 1;
         break;
      default         :
         DEBUG_YPARSE yLOG_exitr   (a_func, rce);
         return rce;
      }
      DEBUG_YPARSE yLOG_value   ("n"         , n);
   }
   /*---(handle index)-------------------*/
   else if (a_index >= 0) {
      DEBUG_YPARSE yLOG_note    ("requesed indexing");
      n = a_index;
   }
   /*---(handle trouble)-----------------*/
   else {
      DEBUG_YPARSE  yLOG_note    ("neither verb, cursor, or index search");
      DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(handle endpoints)---------------*/
   DEBUG_YPARSE yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      if (d_entry != NULL)  strcpy (d_entry, "(under)");
      S_cspec = 0;
      DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
      return rce;
   }
   --rce;  if (n >= S_nspec) {
      if (d_entry != NULL)  strcpy (d_entry, "(over)");
      S_cspec = S_nspec - 1;
      DEBUG_YPARSE  yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   if (a_spec <= 0) {
      for (i = 0; i < S_nspec; ++i) {
         DEBUG_YPARSE yLOG_complex ("loop"      , "%2d#, %2dn, %c, %s", i, n, S_specs [i].t_spec, S_specs [i].t_name);
         if (i == n) {
            DEBUG_YPARSE yLOG_note    ("found it");
            x_found = 'y';
            break;
         }
      }
   }
   /*---(not found)----------------------*/
   DEBUG_YPARSE  yLOG_char    ("x_found"   , x_found);
   --rce;  if (x_found != 'y') {
      if (d_entry != NULL)  strcpy (d_entry, "(n/a)");
      DEBUG_YPARSE yLOG_exitr   (a_func, rce);
      return rce;
   }
   /*---(create entry)-------------------*/
   if (d_entry  != NULL) {
      ystrldisplay (S_specs [n].t_name  , 10, x_name);
      ystrldisplay (S_specs [n].t_desc  , 15, x_desc);
      ystrldisplay (S_specs [n].t_format, 15, x_format);
      sprintf (d_entry, "%2d  %c  %-10.10s  %c  %2d  %-15.15s  %c  %2d  %-12.12s  Ï",
            n, S_specs [n].t_spec, x_name,
            S_specs [n].t_cat , x_desc,
            S_specs [n].t_varg, S_specs [n].t_save, S_specs [n].t_size, x_format);
   }
   /*---(save-back)----------------------*/
   S_cspec = n;
   if (r_spec   != NULL)  *r_spec   =  S_specs [n].t_spec;
   if (r_name   != NULL)  ystrlcpy (r_name   , S_specs [n].t_name  , LEN_LABEL);
   if (r_cat    != NULL)  *r_cat    =  S_specs [n].t_cat;
   if (r_desc   != NULL)  ystrlcpy (r_desc   , S_specs [n].t_desc  , LEN_LABEL);
   if (r_varg   != NULL)  *r_varg   =  S_specs [n].t_varg;
   if (r_save   != NULL)  *r_save   =  S_specs [n].t_save;
   if (r_size   != NULL)  *r_size   =  S_specs [n].t_size;
   if (r_format != NULL)  ystrlcpy (r_format , S_specs [n].t_format, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (a_func);
   return n;
}

char* yparse_spec_entry  (char a_spec, char a_dir, char a_index) { yparse_spec__search (__FUNCTION__, a_spec, a_dir, a_index, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, yparse_print);  return yparse_print; }
int   yparse_spec_size   (char a_spec)             {  int  l = 0;  yparse_spec__search (__FUNCTION__, a_spec, NULL , NULL   , NULL, NULL, NULL, &l  , NULL, NULL, NULL, NULL, NULL        );  return l; }

char
yparse_spec_string      (char a_spec)
{
   char        rce         =  -10;
   --rce;  if (a_spec == 0)  return rce;
   --rce;  if (strchr (S_strings, a_spec) == NULL)  return rce;
   return RC_POSITIVE;
}

char
yparse_spec_numeric     (char a_spec)
{
   char        rce         =  -10;
   --rce;  if (a_spec == 0)  return rce;
   --rce;  if (strchr (S_numbers, a_spec) == NULL)  return rce;
   return RC_POSITIVE;
}

char
yparse_spec_len         (tQUEUE *a_queue)
{
   int         i           =    0;
   int         n           =    1;   /* start with one for verb  */
   int         l           =    0;
   if (a_queue        == NULL)  return -1;
   if (a_queue->q_iverb <  0   )  return -2;
   /*> DEBUG_YPARSE   yLOG_info    ("spec"      , G_verbs [a_queue->q_iverb].v_specs);    <*/
   l = strlen (G_verbs [a_queue->q_iverb].v_specs);
   return l + 1;

   for (i = 0; i < MAX_COLS; ++i) {
      if (G_verbs [a_queue->q_iverb].v_specs [i] == '\0')   break;
      /*> if (G_verbs [a_queue->q_iverb].v_specs [i] == '-')    break;                    <*/
      ++n;
   }
   return n;
}

/*> char                                                                                                                      <* 
 *> yparse_spec__by_cursor     (char a_spec, char a_dir, int *r_size, char *r_format [LEN_LABEL], char d_entry [LEN_RECD]);   <* 
 *> {                                                                                                                         <* 
 *>    int         i           =    0;                                                                                        <* 
 *>    DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);                                                                             <* 
 *>    DEBUG_YPARSE  yLOG_schar   (a_spec);                                                                                   <* 
 *>    for (i = 0; i < S_nspec; ++i) {                                                                                        <* 
 *>       DEBUG_YPARSE  yLOG_schar   (S_specs [i].t_spec);                                                                    <* 
 *>       if (S_specs [i].t_spec != a_spec)  continue;                                                                        <* 
 *>       DEBUG_YPARSE  yLOG_snote   ("FOUND");                                                                               <* 
 *>       DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                                                          <* 
 *>       return S_specs [i].t_size;                                                                                          <* 
 *>    }                                                                                                                      <* 
 *>    DEBUG_YPARSE  yLOG_snote   ("nada");                                                                                   <* 
 *>    DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                                                             <* 
 *>    return 0;                                                                                                              <* 
 *> }                                                                                                                         <*/

/*> int                                                                               <* 
 *> yparse_spec_size           (char a_spec)                                          <* 
 *> {                                                                                 <* 
 *>    int         i           =    0;                                                <* 
 *>    DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);                                     <* 
 *>    DEBUG_YPARSE  yLOG_schar   (a_spec);                                           <* 
 *>    for (i = 0; i < S_nspec; ++i) {                                                <* 
 *>       DEBUG_YPARSE  yLOG_schar   (S_specs [i].t_spec);                            <* 
 *>       if (S_specs [i].t_spec != a_spec)  continue;                                <* 
 *>       DEBUG_YPARSE  yLOG_snote   ("FOUND");                                       <* 
 *>       DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                  <* 
 *>       return S_specs [i].t_size;                                                  <* 
 *>    }                                                                              <* 
 *>    DEBUG_YPARSE  yLOG_snote   ("nada");                                           <* 
 *>    DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                     <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                      input handling                          ----===*/
/*====================------------------------------------====================*/
static void      o___INPUT___________________o (void) {;};

char
yparse_spec__in_next    (void)
{
   if (s_qin.q_iverb <  0       )  return -2;
   if (s_qin.q_first <  0       )  return -3;
   if (s_qin.q_first >= MAX_COLS)  return -4;
   return G_verbs [s_qin.q_iverb].v_specs [s_qin.q_first - 1];
}



/*====================------------------------------------====================*/
/*===----                     output handling                          ----===*/
/*====================------------------------------------====================*/
static void      o___OUTPUT__________________o (void) {;};

char
yparse_spec__out_next    (void)
{
   char        x_spec      =  '-';
   if (s_qout.q_iverb <  0       )  return -2;
   if (s_qout.q_count <  0       )  return -3;
   if (s_qout.q_count >= MAX_COLS)  return -4;
   x_spec = G_verbs [s_qout.q_iverb].v_specs [s_qout.q_count - 1];
}

char
yparse_spec_output      (va_list a_vlist, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        x_spec      =  '-';
   char        x_char      =    0;
   int         x_int       =    0;
   llong       x_long      =    0;
   float       x_float     =  0.0;
   double      x_double    =  0.0;
   uchar      *x_str       = NULL;
   int         c           =    0;
   double      x_val       =  0.0;
   int         x_end       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(walk fields)--------------------*/
   DEBUG_YPARSE  yLOG_value   ("n"         , n);
   --rce;  for (i = 1; i < n; ++i) {
      x_spec = yparse_spec__out_next ();
      DEBUG_YPARSE  yLOG_complex ("loop"      , "%2d %c", i, x_spec);
      switch (x_spec) {
      case 'c' :
         x_char    = va_arg (a_vlist, int);
         rc = yPARSE_pushchar   (x_char);
         DEBUG_YPARSE   yLOG_complex ("char"      , "%d, %c, %3d, %c", i, x_spec, rc, x_char);
         break;
      case 's' : case 'i' : case ',' :
         x_int     = va_arg (a_vlist, int);
         rc = yPARSE_pushint    (x_int);
         DEBUG_YPARSE   yLOG_complex ("int"       , "%d, %c, %3d, %ld", i, x_spec, rc, x_int);
         break;
      case 'l' : case 'h' : case ';' :
         x_long    = va_arg (a_vlist, llong);
         rc = yPARSE_pushint    (x_long);
         DEBUG_YPARSE   yLOG_complex ("long"      , "%d, %c, %3d, %ld", i, x_spec, rc, x_long);
         break;
      case 'k' : case 'f' : case 'd' : case 'r' : case 't' : case 'e' :
         x_double  = va_arg (a_vlist, double);
         rc = yPARSE_pushfloat  (x_double);
         DEBUG_YPARSE   yLOG_complex ("double"    , "%d, %c, %3d, %lf", i, x_spec, rc, x_double);
         break;
      case 'C' : case 'S' : case 'T' : case 'U' : case 'L' :
      case '3' : case '4' : case 'D' : case '5' : case '6' :
      case '7' : case '8' : case 'H' : case 'F' : case 'O' :
         x_str     = va_arg (a_vlist, char*);
         rc = yPARSE_pushstr    (x_str);
         DEBUG_YPARSE   yLOG_complex ("string"    , "%d, %c, %3d, %s", i, x_spec, rc, x_str);
         break;
      default  :
         DEBUG_YPARSE   yLOG_complex ("unknown"   , "%d, %c, ---, -", i, x_spec);
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
      if (rc < 0)  {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++c;
   }
   /*---(check for end)------------------*/
   DEBUG_YPARSE   yLOG_value   ("c"         , c);
   /*> x_end = va_arg (a_vlist, int);                                                 <* 
    *> DEBUG_YPARSE  yLOG_value   ("x_end"     , x_end);                              <* 
    *> if (x_end != NULL) {                                                           <* 
    *>    DEBUG_YPARSE   yLOG_note    ("trailing argument beyond expected count");    <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);                            <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}

