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
   char        t_mask      [LEN_TITLE];     /* masking for output when wrong  */
   /*---(done)--------------*/
};
static const tTYPES  S_specs [MAX_TYPES] = {
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
   { '-' , "nothing"     , '-' , "spacer"          , '-' , '-' ,     1 , ""                , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
   { 'c' , "char"        , 'n' , "single char"     , 'c' , 'c' ,     1 , "%c"              , 'u' ,               31   ,              255   ,                0.0 ,                0.0 , "¬"                        },
   { 's' , "short"       , 'n' , "short integer"   , 'i' , 's' ,     3 , "%3d"             , 'i' ,              -99   ,               99   ,                0.0 ,                0.0 , "¬¬¬"                      },
   { 'i' , "integer"     , 'n' , "normal integer"  , 'i' , 'i' ,     6 , "%6d"             , 'i' ,           -99999   ,            99999   ,                0.0 ,                0.0 , "¬¬¬¬¬¬"                   },
   { 'l' , "long"        , 'n' , "long integer"    , 'l' , 'L' ,    10 , "%10ld"           , 'L' ,       -999999999LL ,        999999999LL ,                0.0 ,                0.0 , "¬¬¬¬¬¬¬¬¬¬"               },
   { 'h' , "huge"        , 'n' , "llong integer"   , 'L' , 'L' ,    16 , "%16ld"           , 'L' , -999999999999998LL ,  999999999999998LL ,                0.0 ,                0.0 , "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬"         },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
   { ',' , "comma"       , 'n' , "comma"           , 'i' , 'i' ,    10 , ""                , 'i' ,         -9999999LL ,          9999999LL ,                0.0 ,                0.0 , "¬¬´¬¬¬´¬¬¬"               },
   { ';' , "hcomma"      , 'n' , "long comma"      , 'L' , 'L' ,    19 , ""                , 'L' ,  -99999999999998LL ,   99999999999998LL ,                0.0 ,                0.0 , "¬¬¬´¬¬¬´¬¬¬´¬¬¬´¬¬¬"      },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
   { 'u' , "micro"       , 'f' , "micro float"     , 'f' , 'f' ,     6 , "%6.3f"           , 'f' ,                0   ,                0   ,             -9.999 ,              9.999 , "¬¬á¬¬¬"                   },
   { 'n' , "nano"        , 'f' , "nano float"      , 'f' , 'f' ,     9 , "%9.6f"           , 'f' ,                0   ,                0   ,          -9.999999 ,           9.999999 , "¬¬á¬¬¬¬¬¬"                },
   { 'k' , "ykine"       , 'f' , "short float"     , 'f' , 'f' ,     6 , "%6.1f"           , 'f' ,                0   ,                0   ,             -999.9 ,              999.9 , "¬¬¬¬á¬"                   },
   { 'f' , "float"       , 'f' , "normal float"    , 'f' , 'f' ,     8 , "%8.2f"           , 'f' ,                0   ,                0   ,           -9999.99 ,            9999.99 , "¬¬¬¬¬á¬¬"                 },
   { 'd' , "double"      , 'f' , "double float"    , 'D' , 'D' ,    10 , "%11.3lf"         , 'f' ,                0   ,                0   ,        -999999.999 ,         999999.999 , "¬¬¬¬¬¬¬á¬¬¬"              },
   { 't' , "technical"   , 'f' , "technical"       , 'D' , 'D' ,    21 , ""                , 'D' ,                0   ,                0   ,  -999999999.999999 ,   999999999.999999 , "¬¬¬´¬¬¬´¬¬¬á¬¬¬´¬¬¬²¬"    },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
   { 'e' , "sml-exp"     , 'f' , "small exponent"  , 'f' , 'D' ,    10 , "%2.3e"           , '-' ,                0   ,                0   ,                0.0 ,                0.0 , "¬¬á¬¬¬e¬¬"                },
   { 'm' , "med-exp"     , 'f' , "normal exponent" , 'f' , 'D' ,    14 , "%2.7e"           , '-' ,                0   ,                0   ,                0.0 ,                0.0 , "¬¬á¬¬¬¬¬¬¬e¬¬"            },
   { 'b' , "big-exp"     , 'f' , "large exponent"  , 'D' , 'D' ,    19 , "%2.12e"          , '-' ,                0   ,                0   ,                0.0 ,                0.0 , "¬¬á¬¬¬¬¬¬¬¬¬¬¬¬e¬¬"       },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
   { 'C' , "one-char"    , 's' , "1 char string"   , 's' , 's' ,     1 , "%-1.1s"          , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'S' , "short"       , 's' , "short string"    , 's' , 's' ,     5 , "%-5.5s"          , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'T' , "terse"       , 's' , "terse string"    , 's' , 's' ,    10 , "%-10.10s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'U' , "user"        , 's' , "user string"     , 's' , 's' ,    12 , "%-12.12s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'L' , "label"       , 's' , "label string"    , 's' , 's' ,    20 , "%-20.20s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { '3' , "thirty"      , 's' , "thirty string"   , 's' , 's' ,    30 , "%-30.30s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { '4' , "forty"       , 's' , "forty string"    , 's' , 's' ,    40 , "%-40.40s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'D' , "desc"        , 's' , "desc string"     , 's' , 's' ,    50 , "%-50.50s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { '6' , "sixty"       , 's' , "sixty string"    , 's' , 's' ,    60 , "%-60.60s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { '7' , "seventy"     , 's' , "seventy string"  , 's' , 's' ,    70 , "%-70.70s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { '8' , "eighty"      , 's' , "eighty string"   , 's' , 's' ,    80 , "%-80.80s"        , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'H' , "hundred"     , 's' , "hundred string"  , 's' , 's' ,   100 , "%-100.100s"      , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'F' , "full"        , 's' , "two-hundred"     , 's' , 's' ,   200 , "%-200.200s"      , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'R' , "recd"        , 's' , "two-thousand"    , 's' , 's' ,  2000 , "%-2000.2000s"    , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   { 'O' , "open"        , 's' , "open string"     , 's' , 's' ,  2000 , "%s"              , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
   {  0  , "end-of-types", '-' , ""                , '-' , '-' ,     0 , ""                , '-' ,                0   ,                0   ,                0.0 ,                0.0 , ""                         },
   /*-A-   ---name-------  -C-   ---description----  -V-   -S-  -size-   ---format--------   -R-   ---------min-int---  ---------max-int---  -------min-float---  -------max-float---  ---mask------------------- */
};
static char  S_valid       [LEN_HUND]   = "";
static char  S_strings     [LEN_LABEL]  = "";
static char  S_integers    [LEN_LABEL]  = "";
static char  S_floats      [LEN_LABEL]  = "";
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
   ystrlcpy (S_strings , "", LEN_LABEL);
   ystrlcpy (S_integers, "", LEN_LABEL);
   ystrlcpy (S_floats  , "", LEN_LABEL);
   /*---(walk)---------------------------*/
   for (i = 0; i < MAX_TYPES; ++i) {
      DEBUG_YPARSE  yLOG_sint    (i);
      DEBUG_YPARSE  yLOG_snote   (S_specs [i].t_name);
      if (S_specs [i].t_spec ==  0 )  break;
      sprintf (t, "%c", S_specs [i].t_spec);
      ystrlcat (S_valid, t, LEN_HUND);
      if (S_specs [i].t_cat  == 'n')   ystrlcat (S_integers, t, LEN_LABEL);
      if (S_specs [i].t_cat  == 'f')   ystrlcat (S_floats  , t, LEN_LABEL);
      if (S_specs [i].t_cat  == 's')   ystrlcat (S_strings , t, LEN_LABEL);
      ++S_nspec;
   }
   DEBUG_YPARSE  yLOG_snote   (S_integers);
   DEBUG_YPARSE  yLOG_snote   (S_floats);
   DEBUG_YPARSE  yLOG_snote   (S_strings);
   DEBUG_YPARSE  yLOG_sint    (S_nspec);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char yparse_spec_wrap  (void)  { return 0; }



/*====================------------------------------------====================*/
/*===----                     searching specs                          ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;};

char
yparse_spec__search     (char a_func [LEN_TITLE], char a_spec, char a_dir, char a_index, char *r_spec, char r_name [LEN_LABEL], char *r_cat, char r_desc [LEN_LABEL], char *r_varg, char *r_save, char *r_size, char r_format [LEN_LABEL], char *r_ranged, llong *r_lmin, llong *r_lmax, double *r_dmin, double *r_dmax, char r_mask [LEN_TITLE], char d_entry [LEN_RECD])
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
   if (r_ranged != NULL)  *r_ranged =  '-';
   if (r_lmin   != NULL)  *r_lmin   =    0;
   if (r_lmax   != NULL)  *r_lmax   =    0;
   if (r_dmin   != NULL)  *r_dmin   =  0.0;
   if (r_dmax   != NULL)  *r_dmax   =  00;
   if (r_mask   != NULL)  strcpy (r_mask   , "");
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
   DEBUG_YPARSE  yLOG_info    ("t_name"    , S_specs [n].t_name);
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
   if (r_ranged != NULL)  *r_ranged =  S_specs [n].t_ranged;
   if (r_lmin   != NULL)  *r_lmin   =  S_specs [n].t_lmin;
   if (r_lmax   != NULL)  *r_lmax   =  S_specs [n].t_lmax;
   if (r_dmin   != NULL)  *r_dmin   =  S_specs [n].t_dmin;
   if (r_dmax   != NULL)  *r_dmax   =  S_specs [n].t_dmax;
   if (r_mask   != NULL)  ystrlcpy (r_mask   , S_specs [n].t_mask  , LEN_TITLE);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (a_func);
   return n;
}

char* yparse_spec_entry  (char a_spec, char a_dir, char a_index) { yparse_spec__search (__FUNCTION__, a_spec, a_dir, a_index, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, yparse_print);  return yparse_print; }
int   yparse_spec_size   (char a_spec)             {  int  l = 0;  yparse_spec__search (__FUNCTION__, a_spec, NULL , NULL   , NULL, NULL, NULL, NULL, NULL, NULL, &l  , NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL        );  return l; }

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
   if (strchr (S_integers, a_spec) != NULL)  return RC_POSITIVE;
   if (strchr (S_floats  , a_spec) != NULL)  return RC_POSITIVE;
   --rce;
   return rce;
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
yparse_spec__out_int    (char a_spec, llong a_val, char r_out [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   char        x_cat       =  '-';
   char        x_save      =  '-';
   int         x_size      =    0;
   char        x_format    [LEN_LABEL] = "";
   char        x_ranged    =  '-';
   llong       x_min       =    0;
   llong       x_max       =    0;
   char        x_mask      [LEN_TITLE] = "";
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(default)-----------------------*/
   if (r_out   != NULL)  strcpy (r_out, "");
   /*---(defense)-----------------------*/
   DEBUG_YPARSE yLOG_point   ("r_out"     , r_out);
   --rce;  if (r_out  == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(gather data)--------------------*/
   DEBUG_YPARSE   yLOG_char    ("a_spec"    , a_spec);
   rc = yparse_spec__search  ("yparse_spec_out", a_spec, -1, -1, NULL, x_name, &x_cat, NULL, NULL, &x_save, &x_size, x_format, &x_ranged, &x_min, &x_max, NULL, NULL, x_mask, NULL);
   DEBUG_YPARSE   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("x_name"    , x_name);
   DEBUG_YPARSE   yLOG_info    ("x_mask"    , x_mask);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_char    ("x_cat"     , x_cat);
   --rce;  if (x_cat != 'n') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_char    ("x_save"    , x_save);
   --rce;  if (x_save == 0 || strchr ("csilL", x_save) == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(range checking)-----------------*/
   DEBUG_YPARSE   yLOG_char    ("x_ranged"  , x_ranged);
   if (x_ranged != '-') {
      DEBUG_YPARSE   yLOG_value   ("a_val"     , a_val);
      DEBUG_YPARSE   yLOG_value   ("x_min"     , x_min);
      if (a_val < x_min) {
         ystrlcpy (r_out, x_mask, LEN_RECD);
         DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
         return RC_ACK;
      }
      DEBUG_YPARSE   yLOG_value   ("x_max"     , x_max);
      if (a_val > x_max) {
         ystrlcpy (r_out, x_mask, LEN_RECD);
         DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
         return RC_ACK;
      }
   }
   /*---(comma formats)------------------*/
   DEBUG_YPARSE yLOG_info    ("x_format"  , x_format);
   if (strchr (",;", a_spec) != NULL) {
      DEBUG_YPARSE yLOG_note    ("handling comma formats");
      rc = ystrl4comma (a_val, t, 0, 'c', '-', LEN_LABEL);
      DEBUG_YPARSE   yLOG_value   ("comma"     , rc);
      if (rc < 0)  {
         ystrlcpy (r_out, x_mask, LEN_RECD);
         DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
         return RC_ACK;
      }
      sprintf (r_out, "%*.*s", x_size, x_size, t);
      DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
   }
   /*---(normal formats)-----------------*/
   --rce;  switch (x_save) {
   case  'c' : sprintf (r_out, x_format, (uchar) a_val);        break;
   case  's' : sprintf (r_out, x_format, (short) a_val);        break;
   case  'i' : sprintf (r_out, x_format, (int)   a_val);        break;
   case  'l' : sprintf (r_out, x_format, (long)  a_val);        break;
   case  'L' : sprintf (r_out, x_format, (llong) a_val);        break;
   }
   /*---(debug)--------------------------*/
   DEBUG_YPARSE   yLOG_info    ("formatted" , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yparse_spec__out_float  (char a_spec, double a_val, char r_out [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   char        x_cat       =  '-';
   char        x_save      =  '-';
   int         x_size      =    0;
   char        x_format    [LEN_LABEL] = "";
   char        x_ranged    =  '-';
   double      x_min       =  0.0;
   double      x_max       =  0.0;
   char        x_mask      [LEN_TITLE] = "";
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(default)-----------------------*/
   if (r_out   != NULL)  strcpy (r_out, "");
   /*---(defense)-----------------------*/
   DEBUG_YPARSE yLOG_point   ("r_out"     , r_out);
   --rce;  if (r_out  == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(gather data)--------------------*/
   DEBUG_YPARSE   yLOG_char    ("a_spec"    , a_spec);
   rc = yparse_spec__search  ("yparse_spec_out", a_spec, -1, -1, NULL, x_name, &x_cat, NULL, NULL, &x_save, &x_size, x_format, &x_ranged, NULL, NULL, &x_min, &x_max, x_mask, NULL);
   DEBUG_YPARSE   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("x_name"    , x_name);
   DEBUG_YPARSE   yLOG_info    ("x_mask"    , x_mask);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_char    ("x_cat"     , x_cat);
   --rce;  if (x_cat != 'f') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_char    ("x_save"    , x_save);
   --rce;  if (x_save == 0 || strchr ("fD", x_save) == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(range checking)-----------------*/
   DEBUG_YPARSE   yLOG_char    ("x_ranged"  , x_ranged);
   if (x_ranged != '-') {
      DEBUG_YPARSE   yLOG_double  ("a_val"     , a_val);
      DEBUG_YPARSE   yLOG_double  ("x_min"     , x_min);
      if (a_val < x_min) {
         ystrlcpy (r_out, x_mask, LEN_RECD);
         DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
         return RC_ACK;
      }
      DEBUG_YPARSE   yLOG_double  ("x_max"     , x_max);
      if (a_val > x_max) {
         ystrlcpy (r_out, x_mask, LEN_RECD);
         DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
         return RC_ACK;
      }
   }
   /*---(normal formats)-----------------*/
   --rce;  switch (a_spec) {
   case  'u' : case  'n' : case  'k' : case  'f' :
      sprintf (r_out, x_format, (float) a_val);
      break;
   case  'd' :
      sprintf (r_out, x_format, (double) a_val);
      break;
   case  'e' : case  'm' : case  'b' :
      sprintf (t, x_format, (double) a_val);
      DEBUG_YPARSE   yLOG_info    ("t"         , t);
      DEBUG_YPARSE   yLOG_value   ("x_size"    , x_size);
      sprintf (r_out, "%*.*s", x_size, x_size, t);
      break;
   case  't' :
      DEBUG_YPARSE   yLOG_note    ("technical type");
      rc = ystrl4comma (a_val, t, 6, '#', '-', LEN_TITLE);
      DEBUG_YPARSE   yLOG_value   ("comma"     , rc);
      if (rc < 0)  {
         ystrlcpy (r_out, x_mask, LEN_RECD);
         DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
         return RC_ACK;
      }
      DEBUG_YPARSE   yLOG_info    ("t"         , t);
      DEBUG_YPARSE   yLOG_value   ("x_size"    , x_size);
      sprintf (r_out, "%*.*s", x_size, x_size, t);
      break;
   }
   /*---(debug)--------------------------*/
   DEBUG_YPARSE   yLOG_info    ("formatted" , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yparse_spec__out_string (char a_spec, char a_string [LEN_RECD], char r_out [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   char        x_cat       =  '-';
   char        x_save      =  '-';
   char        x_format    [LEN_LABEL] = "";
   char        t           [LEN_RECD]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(default)-----------------------*/
   if (r_out   != NULL)  strcpy (r_out, "");
   /*---(defense)-----------------------*/
   DEBUG_YPARSE yLOG_point   ("r_out"     , r_out);
   --rce;  if (r_out  == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(gather data)--------------------*/
   DEBUG_YPARSE   yLOG_char    ("a_spec"    , a_spec);
   rc = yparse_spec__search  ("yparse_spec_out", a_spec, -1, -1, NULL, x_name, &x_cat, NULL, NULL, &x_save, NULL, x_format, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   DEBUG_YPARSE   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("x_name"    , x_name);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_char    ("x_cat"     , x_cat);
   --rce;  if (x_cat != 's') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_char    ("x_save"    , x_save);
   --rce;  if (x_save != 's') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare field)------------------*/
   l = strlen (a_string);
   DEBUG_YPARSE   yLOG_value   ("l"         , l);
   if (l == 0)  ystrlcpy (t, "¤"     , LEN_RECD);
   else         ystrlcpy (t, a_string, LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("t"         , t);
   ystrlmark  (t, ySTR_HEATH, LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("marked"    , r_out);
   ystrlstore (t, LEN_RECD);
   DEBUG_YPARSE   yLOG_info    ("stored"    , r_out);
   DEBUG_YPARSE   yLOG_info    ("x_format"  , x_format);
   snprintf   (r_out, LEN_RECD, x_format, t);
   DEBUG_YPARSE   yLOG_info    ("formatted" , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yparse_spec_output      (tQUEUE *a_queue, va_list a_vlist, char a_speclist [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_nspec     =    0;
   int         i           =    0;
   char        x_name      [LEN_LABEL] = "";
   char        x_spec      =  '-';
   char        x_cat       =  '-';
   char        x_save      =  '-';
   llong       x_llong     =    0;
   double      x_double    =  0.0;
   uchar      *x_string    = NULL;
   char        x_out       [LEN_RECD]  = "";
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)-----------------------*/
   DEBUG_YPARSE yLOG_point   ("a_queue"   , a_queue);
   --rce;  if (a_queue     == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_point   ("a_vlist"   , a_vlist);
   --rce;  if (a_vlist     == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_point   ("a_speclist", a_speclist);
   --rce;  if (a_speclist  == NULL) {
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE yLOG_info    ("a_speclist", a_speclist);
   x_nspec = strlen (a_speclist) + 1;
   DEBUG_YPARSE yLOG_value   ("x_nspec"   , x_nspec);
   /*---(walk fields)--------------------*/
   --rce;  for (i = 1; i < x_nspec; ++i) {
      /*---(spec)------------------------*/
      x_spec = a_speclist [i - 1];
      DEBUG_YPARSE  yLOG_complex ("loop"      , "%2d %c", i, x_spec);
      /*---(gather)----------------------*/
      rc = yparse_spec__search  ("yparse_spec_out", x_spec, -1, -1, NULL, x_name, &x_cat, NULL, NULL, &x_save, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
      DEBUG_YPARSE   yLOG_value   ("search"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YPARSE   yLOG_info    ("x_name"    , x_name);
      /*---(retrieve)--------------------*/
      DEBUG_YPARSE   yLOG_char    ("x_save"    , x_save);
      --rce;  switch (x_save) {
      case 'c' : x_llong   = (uchar) va_arg (a_vlist, int);    break;
      case 'i' : x_llong   = va_arg (a_vlist, int);    break;
      case 'l' : x_llong   = va_arg (a_vlist, long);   break;
      case 'L' : x_llong   = va_arg (a_vlist, llong);  break;
      case 'f' : x_double  = va_arg (a_vlist, float);  break;
      case 'D' : x_double  = va_arg (a_vlist, double); break;
      case 's' : x_string  = va_arg (a_vlist, char*);  break;
      default  :
                 DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
                 return rce;
                 break;
      }
      /*---(handle)----------------------*/
      DEBUG_YPARSE   yLOG_char    ("x_cat"     , x_cat);
      --rce;  switch (x_cat) {
      case 'n' :
         rc = yparse_spec__out_int    (x_spec, x_llong , x_out);   break;
         DEBUG_YPARSE   yLOG_complex (x_name      , "%d, %c, %lld, %4d, å%sæ", i, x_spec, x_llong , rc, x_out);
      case 'f' :
         rc = yparse_spec__out_float  (x_spec, x_double, x_out);   break;
         DEBUG_YPARSE   yLOG_complex (x_name      , "%d, %c, %lf, %4d, å%sæ" , i, x_spec, x_double, rc, x_out);
      case 's' :
         rc = yparse_spec__out_string (x_spec, x_string, x_out);   break;
         DEBUG_YPARSE   yLOG_complex (x_name      , "%d, %c, %s, %4d, å%sæ"  , i, x_spec, x_string,rc, x_out);
      default  :
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
      /*---(trouble)---------------------*/
      --rce;  if (rc < 0) {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(enqueue)------------------------*/
      rc = yparse_queue_enqueue (a_queue, x_out);
      DEBUG_YPARSE   yLOG_value   ("enqueue"   , rc);
      --rce;  if (rc < 0) {
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(next)------------------------*/
      ++c;
      /*---(done)------------------------*/
   }
   /*---(check for end)------------------*/
   DEBUG_YPARSE   yLOG_value   ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}
