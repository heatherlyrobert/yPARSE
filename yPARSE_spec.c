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
   char        t_spec;                      /* unique one char id             */
   char        t_name      [LEN_LABEL];     /* short name                     */
   int         t_cat;                       /* category -- string, numeric    */
   int         t_size;                      /* width                          */
   char        t_desc      [LEN_LABEL];     /* description                    */
   char        t_varg;                      /* use with vargs                 */
   char        t_save;                      /* save-to type                   */
   char        t_format    [LEN_LABEL];     /* actual format string           */
};
static tTYPES  S_specs [MAX_TYPES] = {
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
   { '-', "nothing"     , 'n',     1, "spacer"          , '-', '-', ""                },
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
   { 'c', "char"        , 'n',     1, "single char"     , 'i', 'c', "%c"              },
   { 's', "short"       , 'n',     3, "short integer"   , 'i', 's', "%3d"             },
   { 'i', "integer"     , 'n',     6, "normal integer"  , 'i', 'i', "%6d"             },
   { 'l', "long"        , 'n',    10, "long integer"    , 'L', 'L', "%10d"            },
   { 'h', "huge"        , 'n',    16, "long integer"    , 'L', 'L', "%16ld"           },
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
   { ',', "comma"       , 'n',    10, "comma"           , 'i', 'i', "%10d"            },
   { ';', "hcomma"      , 'n',    19, "long comma"      , 'L', 'L', "%19ld"           },
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
   { 'u', "micro"       , 'n',     6, "micro float"     , 'f', 'f', "%6.3f"           },
   { 'n', "nano"        , 'n',     9, "nano float"      , 'f', 'f', "%9.6f"           },
   { 'k', "ykine"       , 'n',     6, "short float"     , 'f', 'f', "%6.1f"           },
   { 'f', "float"       , 'n',     8, "normal float"    , 'f', 'f', "%8.2f"           },
   { 'd', "double"      , 'n',    10, "double float"    , 'd', 'd', "%10.3lf"         },
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
   { 't', "technical"   , 'n',    18, "technical"       , 'd', 'd', "%18.6lf"         },
   { 'e', "sml-exp"     , 'n',    10, "tech float"      , 'd', 'd', "%2.3e"           },
   { 'm', "med-exp"     , 'n',    14, "tech float"      , 'd', 'd', "%2.7e"           },
   { 'b', "big-exp"     , 'n',    19, "exponent"        , 'd', 'd', "%2.12e"          },
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
   { 'C', "one-char"    , 's',     1, "1 char string"   , 's', 's', "%-1.1s"          },
   { 'S', "short"       , 's',     5, "short string"    , 's', 's', "%-5.5s"          },
   { 'T', "terse"       , 's',    10, "terse string"    , 's', 's', "%-10.10s"        },
   { 'U', "user"        , 's',    12, "user string"     , 's', 's', "%-12.12s"        },
   { 'L', "label"       , 's',    20, "label string"    , 's', 's', "%-20.20s"        },
   { '3', "thirty"      , 's',    30, "thirty string"   , 's', 's', "%-30.30s"        },
   { '4', "forty"       , 's',    40, "forty string"    , 's', 's', "%-40.40s"        },
   { 'D', "desc"        , 's',    50, "desc string"     , 's', 's', "%-50.50s"        },
   { '6', "sixty"       , 's',    60, "sixty string"    , 's', 's', "%-40.40s"        },
   { '7', "seventy"     , 's',    70, "seventy string"  , 's', 's', "%-70.70s"        },
   { '8', "eighty"      , 's',    80, "eighty string"   , 's', 's', "%-80.80s"        },
   { 'H', "hundred"     , 's',   100, "hundred string"  , 's', 's', "%-100.100s"      },
   { 'F', "full"        , 's',   200, "two-hundred"     , 's', 's', "%-200.200s"      },
   { 'R', "recd"        , 's',  2000, "two-thousand"    , 's', 's', "%-2000.2000s"    },
   { 'O', "open"        , 's',    60, "open string"     , 's', 's', "%s"              },
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
   {  0 , "end-of-types", '-',     0, ""                , '-', '-', ""                },
   /*-A-  ---name-------  -C- -size-  ---description----  -V-  -S-  ---format-------- */
};
static char  S_strings     [LEN_LABEL]  = "";
static char  S_numbers     [LEN_LABEL]  = "";
static int   S_nspec       =    0;
static int   S_cspec       =    0;


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

char
yparse_spec__search     (char a_func [LEN_TITLE], char a_spec, char a_dir, char a_index, char *r_spec, char r_name [LEN_LABEL], char *r_cat, char *r_size, char r_desc [LEN_LABEL], char *r_varg, char *r_save, char r_format [LEN_LABEL], char d_entry [LEN_RECD])
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
   if (r_size   != NULL)  *r_size   =    0;
   if (r_desc   != NULL)  strcpy (r_desc   , "");
   if (r_varg   != NULL)  *r_varg   =  '-';
   if (r_save   != NULL)  *r_save   =  '-';
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
      if (d_entry  != NULL)  strcpy (d_entry, "##  A  ---name---  C  sz  ---desc--------  V  S  ---format------  Ï");
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
      if (d_entry  != NULL)  strcpy (d_entry, "##  A  ---name---  C  sz  ---desc--------  V  S  ---format------  Ï");
      sprintf (d_entry, "%2d  %c  %-10.10s  %c  %2d  %-15.15s  %c  %2d  %-12.12s  Ï",
            n, S_specs [n].t_spec, x_name,
            S_specs [n].t_cat , S_specs [n].t_size, x_desc,
            S_specs [n].t_varg, S_specs [n].t_save, x_format);
   }
   /*---(save-back)----------------------*/
   S_cspec = n;
   if (r_spec   != NULL)  *r_spec   =  S_specs [n].t_spec;
   if (r_name   != NULL)  ystrlcpy (r_name   , S_specs [n].t_name  , LEN_LABEL);
   if (r_cat    != NULL)  *r_cat    =  S_specs [n].t_cat;
   if (r_size   != NULL)  *r_size   =  S_specs [n].t_size;
   if (r_desc   != NULL)  ystrlcpy (r_desc   , S_specs [n].t_desc  , LEN_LABEL);
   if (r_varg   != NULL)  *r_varg   =  S_specs [n].t_varg;
   if (r_save   != NULL)  *r_save   =  S_specs [n].t_save;
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
yparse_spec_next_write   (void)
{
   if (s_qout.q_iverb <  0       )  return -2;
   if (s_qout.q_count <  0       )  return -3;
   if (s_qout.q_count >= MAX_COLS)  return -4;
   return G_verbs [s_qout.q_iverb].v_specs [s_qout.q_count - 1];
}

char
yparse_spec_next_read   (void)
{
   if (s_qin.q_iverb <  0       )  return -2;
   if (s_qin.q_first <  0       )  return -3;
   if (s_qin.q_first >= MAX_COLS)  return -4;
   return G_verbs [s_qin.q_iverb].v_specs [s_qin.q_first - 1];
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


