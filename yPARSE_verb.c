/*============================[[    beg-code    ]]============================*/
/*········´ ´·············headers·´ ´·········································*/
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

/*
 *  readers and writers must accept two arguments...
 *  1) n       reference number (out is a sequence, in is file line number)
 *  2) a_verb  the string verb name to verify and prepare
 *  these two provide excellent, targeted debugging information
 *
 *
 *
 */


/*> #define     MAX_COLS      29                                                       <* 
 *> #define     MAX_VERBS     50                                                       <* 
 *> struct {                                                                           <* 
 *>    /+---(master)------------+/                                                     <* 
 *>    char        v_verb      [LEN_LABEL];     /+ verb name as used in files     +/   <* 
 *>    uchar       v_specs     [LEN_TITLE];     /+ field specifications           +/   <* 
 *>    uchar       v_mode;                      /+ one char yvikeys mode id       +/   <* 
 *>    char        v_mask;                      /+ field for reload/change        +/   <* 
 *>    /+---(handlers)----------+/                                                     <* 
 *>    int         (*v_reader)   (int n, char *a_verb);                                <* 
 *>    int         (*v_writer)   (int n, char *a_verb);                                <* 
 *>    float       v_seq;                       /+ writing sequence               +/   <* 
 *>    char        v_done;                      /+ written (y/n)                  +/   <* 
 *>    /+---(descriptive)-------+/                                                     <* 
 *>    char        v_flags     [LEN_TITLE];     /+ flags for use by program       +/   <* 
 *>    uchar       v_labels    [LEN_RECD];      /+ field labels for headers       +/   <* 
 *>    uchar       v_desc      [LEN_DESC ];     /+ long verb description          +/   <* 
 *>    /+---(done)--------------+/                                                     <* 
 *> }  static   G_verbs   [MAX_VERBS];                                                 <*/
tVERBS      G_verbs   [MAX_VERBS];
int         G_nverb   = 0;
int         G_cverb   = 0;
char       *G_nada    = "";





/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;};

char
yparse_verb__wipe       (char n)
{
   char        rce         =  -10;
   /*---(defense)-----------*/
   --rce;  if (n < 0)           return rce;
   --rce;  if (n >= MAX_VERBS)  return rce;
   /*---(master)------------*/
   ystrlcpy (G_verbs [n].v_verb   , "", LEN_LABEL);
   ystrlcpy (G_verbs [n].v_specs  , "", LEN_TITLE);
   G_verbs [n].v_mode    =  '·';
   G_verbs [n].v_mask    =   -1;
   /*---(handlers)----------*/
   G_verbs [n].v_reader  = NULL;
   G_verbs [n].v_writer  = NULL;
   G_verbs [n].v_seq     =  0.0;
   G_verbs [n].v_done    =  '-';
   /*---(descriptive)-------*/
   ystrlcpy (G_verbs [n].v_flags  , "", LEN_TITLE);
   ystrlcpy (G_verbs [n].v_labels , "", LEN_RECD);
   ystrlcpy (G_verbs [n].v_desc   , "", LEN_DESC);
   /*---(complete)----------*/
   return 0;
}

char
yparse_verb__purge      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   for (i = 0; i < MAX_VERBS; ++i) {
      yparse_verb__wipe (i);
   }
   G_nverb = 0;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yparse_verb_init        (void) { return yparse_verb__purge (); }
char yparse_verb_wrap        (void) { return yparse_verb__purge (); }



/*====================------------------------------------====================*/
/*===----                      searching for verbs                     ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;};


/*> char                                                                                                                                                                                                                                                                                  <* 
 *> yparse_verb_data        (char n, char r_verb [LEN_LABEL], char r_specs [LEN_LABEL], uchar *r_mode, char *r_mask, void **r_reader, void **r_writer, float *r_seq, char *r_done, char r_flags [LEN_TITLE], char r_labels [LEN_RECD], char r_desc [LEN_DESC], char d_entry [LEN_RECD])   <* 
 *> {                                                                                                                                                                                                                                                                                     <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                                                                                           <* 
 *>    char        rce         =  -10;                                                                                                                                                                                                                                                    <* 
 *>    char        x_verb      [LEN_LABEL] = "´···········";                                                                                                                                                                                                                              <* 
 *>    char        x_specs     [LEN_LABEL] = "´···········";                                                                                                                                                                                                                              <* 
 *>    char        x_reader    [LEN_TERSE] = "···";                                                                                                                                                                                                                                       <* 
 *>    char        x_writer    [LEN_TERSE] = "···";                                                                                                                                                                                                                                       <* 
 *>    char        x_flags     [LEN_LABEL] = "´···········";                                                                                                                                                                                                                              <* 
 *>    char        x_labels    [LEN_HUND]  = "´·················································";                                                                                                                                                                                        <* 
 *>    char        x_desc      [LEN_DESC]  = "´·····························";                                                                                                                                                                                                            <* 
 *>    /+---(default)------------------------+/                                                                                                                                                                                                                                           <* 
 *>    if (r_verb   != NULL)  strlcpy (r_verb   , "");                                                                                                                                                                                                                                    <* 
 *>    if (r_specs  != NULL)  strlcpy (r_specs  , "");                                                                                                                                                                                                                                    <* 
 *>    if (r_mode   != NULL)  *r_mode   =  '·';                                                                                                                                                                                                                                           <* 
 *>    if (r_mask   != NULL)  *r_mask   =   -1;                                                                                                                                                                                                                                           <* 
 *>    if (r_reader != NULL)  *r_reader = NULL;                                                                                                                                                                                                                                           <* 
 *>    if (r_writer != NULL)  *r_writer = NULL;                                                                                                                                                                                                                                           <* 
 *>    if (r_seq    != NULL)  *r_seq    =  0.0;                                                                                                                                                                                                                                           <* 
 *>    if (r_done   != NULL)  *r_done   =  '-';                                                                                                                                                                                                                                           <* 
 *>    if (r_flags  != NULL)  strlcpy (r_flags  , "------------");                                                                                                                                                                                                                        <* 
 *>    if (r_labels != NULL)  strlcpy (r_labels , "");                                                                                                                                                                                                                                    <* 
 *>    if (r_desc   != NULL)  strlcpy (r_desc   , "");                                                                                                                                                                                                                                    <* 
 *>    if (d_entry  != NULL)  strcpy (d_entry, "·-  ´···········  ´···········  -  -  ··· ···  -·-  -  ´···········  ´·················································  ´·····························  Ï");                                                                             <* 
 *>    /+---(title)--------------------------+/                                                                                                                                                                                                                                           <* 
 *>    if (n == 'T') {                                                                                                                                                                                                                                                                    <* 
 *>       if (d_entry  != NULL)  strcpy (d_entry, "##  ---verb-----  ---specs----  M  K  rdr wrt  seq  D  ---flags----  ---lables-----------------------------------------  ---desc-----------------------  Ï");                                                                          <* 
 *>       return RC_POSITIVE;                                                                                                                                                                                                                                                             <* 
 *>    }                                                                                                                                                                                                                                                                                  <* 
 *>    /+---(range trouble)------------------+/                                                                                                                                                                                                                                           <* 
 *>    --rce;  if (G_nverb == 0) {                                                                                                                                                                                                                                                        <* 
 *>       if (d_entry  != NULL)  strcpy (d_entry, "(empty)");                                                                                                                                                                                                                             <* 
 *>       return rce;                                                                                                                                                                                                                                                                     <* 
 *>    }                                                                                                                                                                                                                                                                                  <* 
 *>    --rce;  if (n <  0) {                                                                                                                                                                                                                                                              <* 
 *>       if (d_entry != NULL)  strcpy (d_entry, "(under)");                                                                                                                                                                                                                              <* 
 *>       return rce;                                                                                                                                                                                                                                                                     <* 
 *>    }                                                                                                                                                                                                                                                                                  <* 
 *>    --rce;  if (n >= G_nverb) {                                                                                                                                                                                                                                                        <* 
 *>       if (d_entry != NULL)  strcpy (d_entry, "(over)");                                                                                                                                                                                                                               <* 
 *>       return rce;                                                                                                                                                                                                                                                                     <* 
 *>    }                                                                                                                                                                                                                                                                                  <* 
 *>    /+---(create entry)-------------------+/                                                                                                                                                                                                                                           <* 
 *>    if (d_entry  != NULL) {                                                                                                                                                                                                                                                            <* 
 *>       ystrldisplay (G_verbs [n].v_verb  , 12, x_verb);                                                                                                                                                                                                                                <* 
 *>       ystrldisplay (G_verbs [n].v_specs , 12, x_specs);                                                                                                                                                                                                                               <* 
 *>       if (G_verbs [n].v_reader != NULL)  strcpy (x_reader, "SET");                                                                                                                                                                                                                    <* 
 *>       if (G_verbs [n].v_writer != NULL)  strcpy (x_writer, "SET");                                                                                                                                                                                                                    <* 
 *>       ystrldisplay (G_verbs [n].v_flags , 12, x_flags);                                                                                                                                                                                                                               <* 
 *>       ystrldisplay (G_verbs [n].v_labels, 50, x_labels);                                                                                                                                                                                                                              <* 
 *>       ystrldisplay (G_verbs [n].v_desc  , 30, x_desc);                                                                                                                                                                                                                                <* 
 *>       sprintf (d_entry, "%2d  %-12.12s  %-12.12s  %c  %c  %-3.3s %-3.3s  %3.1f  %c  %-12.12s  %-50.50s  %-30.30s  Ï",                                                                                                                                                                 <* 
 *>             n, x_verb, G_verbs [n].v_mode, G_verbs [n].v_mask,                                                                                                                                                                                                                        <* 
 *>             x_reader, x_writer, G_verbs [n].v_seq, G_verbs [n].v_done,                                                                                                                                                                                                                <* 
 *>             x_flags, x_label, x_desc);                                                                                                                                                                                                                                                <* 
 *>    }                                                                                                                                                                                                                                                                                  <* 
 *>    /+---(save-back)----------------------+/                                                                                                                                                                                                                                           <* 
 *>    if (r_verb   != NULL)  ystrlcpy (r_verb   , G_verbs [n].v_verb  , LEN_LABEL);                                                                                                                                                                                                      <* 
 *>    if (r_specs  != NULL)  ystrlcpy (r_specs  , G_verbs [n].v_specs , LEN_TITLE);                                                                                                                                                                                                      <* 
 *>    if (r_mode   != NULL)  *r_mode   =  G_verbs [n].v_mode;                                                                                                                                                                                                                            <* 
 *>    if (r_mask   != NULL)  *r_mask   =  G_verbs [n].v_mask;                                                                                                                                                                                                                            <* 
 *>    if (r_reader != NULL)  *r_reader =  G_verbs [n].v_reader;                                                                                                                                                                                                                          <* 
 *>    if (r_writer != NULL)  *r_writer =  G_verbs [n].v_writer;                                                                                                                                                                                                                          <* 
 *>    if (r_seq    != NULL)  *r_seq    =  G_verbs [n].v_seq;                                                                                                                                                                                                                             <* 
 *>    if (r_done   != NULL)  *r_done   =  G_verbs [n].v_done;                                                                                                                                                                                                                            <* 
 *>    if (r_flags  != NULL)  ystrlcpy (r_flags  , G_verbs [n].v_flags , LEN_TITLE);                                                                                                                                                                                                      <* 
 *>    if (r_labels != NULL)  ystrlcpy (r_labels , G_verbs [n].v_labels, LEN_RECD);                                                                                                                                                                                                       <* 
 *>    if (r_desc   != NULL)  ystrlcpy (r_desc   , G_verbs [n].v_desc  , LEN_DESC);                                                                                                                                                                                                       <* 
 *>    /+---(complete)-----------------------+/                                                                                                                                                                                                                                           <* 
 *>    return n;                                                                                                                                                                                                                                                                          <* 
*> }                                                                                                                                                                                                                                                                                     <*/

char yparse_verb_count  (void)  { return G_nverb; }

char
yparse_verb__search     (char a_verb [LEN_LABEL], char a_dir, char a_index, char r_verb [LEN_LABEL], char r_specs [LEN_LABEL], uchar *r_mode, char *r_mask, void **r_reader, void **r_writer, float *r_seq, char *r_done, char r_flags [LEN_TITLE], char r_labels [LEN_RECD], char r_desc [LEN_DESC], char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        n           =    0;
   char        x_found     =  '-';
   char        x_verb      [LEN_LABEL] = "´···········";
   char        x_specs     [LEN_LABEL] = "´···········";
   char        x_reader    [LEN_TERSE] = "···";
   char        x_writer    [LEN_TERSE] = "···";
   char        x_flags     [LEN_LABEL] = "´···········";
   char        x_labels    [LEN_HUND]  = "´·················································";
   char        x_desc      [LEN_DESC]  = "´·····························";
   /*---(header)-------------------------*/
   DEBUG_YPARSE yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_verb   != NULL)  strcpy (r_verb   , "");
   if (r_specs  != NULL)  strcpy (r_specs  , "");
   if (r_mode   != NULL)  *r_mode   =  '·';
   if (r_mask   != NULL)  *r_mask   =   -1;
   if (r_reader != NULL)  *r_reader = NULL;
   if (r_writer != NULL)  *r_writer = NULL;
   if (r_seq    != NULL)  *r_seq    =  0.0;
   if (r_done   != NULL)  *r_done   =  '-';
   if (r_flags  != NULL)  strcpy (r_flags  , "");
   if (r_labels != NULL)  strcpy (r_labels , "");
   if (r_desc   != NULL)  strcpy (r_desc   , "");
   if (d_entry  != NULL)  strcpy (d_entry, "·-  ´···········  ´···········  -  ·-  ··· ···  -·-  -  ´···········  ´·················································  ´·····························  Ï");
   /*---(title)--------------------------*/
   if (a_dir == 'T') {
      if (d_entry  != NULL)  strcpy (d_entry, "##  ---verb-----  ---specs----  M  mk  rdr wrt  seq  D  ---flags----  ---lables-----------------------------------------  ---desc-----------------------  Ï");
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(quick-out)----------------------*/
   DEBUG_YPARSE  yLOG_value   ("G_nverb"   , G_nverb);
   --rce;  if (G_nverb == 0) {
      if (d_entry  != NULL)  strcpy (d_entry, "(empty)");
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YPARSE yLOG_char    ("a_dir"     , a_dir);
   DEBUG_YPARSE yLOG_value   ("a_index"   , a_index);
   /*---(handlen verb)-------------------*/
   --rce;  if (a_verb != NULL) {
      DEBUG_YPARSE yLOG_note    ("requested name search");
      for (i = 0; i < G_nverb; ++i) {
         if (G_verbs [i].v_verb [0] != a_verb [0])      continue;
         if (strcmp (G_verbs [i].v_verb, a_verb) != 0)  continue;
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
      n = G_cverb;
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
         n = G_nverb - 1;
         break;
      default         :
         DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
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
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle endpoints)---------------*/
   DEBUG_YPARSE yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      if (d_entry != NULL)  strcpy (d_entry, "(under)");
      G_cverb = 0;
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (n >= G_nverb) {
      if (d_entry != NULL)  strcpy (d_entry, "(over)");
      G_cverb = G_nverb - 1;
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   if (a_verb == NULL) {
      for (i = 0; i < G_nverb; ++i) {
         DEBUG_YPARSE yLOG_complex ("loop"      , "%2d#, %2dn, %s", i, n, G_verbs [i].v_verb);
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
      DEBUG_YPARSE yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create entry)-------------------*/
   if (d_entry  != NULL) {
      ystrldisplay (G_verbs [n].v_verb  , 12, x_verb);
      ystrldisplay (G_verbs [n].v_specs , 12, x_specs);
      if (G_verbs [n].v_reader != NULL)  strcpy (x_reader, "SET");
      if (G_verbs [n].v_writer != NULL)  strcpy (x_writer, "SET");
      ystrldisplay (G_verbs [n].v_flags , 12, x_flags);
      ystrldisplay (G_verbs [n].v_labels, 50, x_labels);
      ystrldisplay (G_verbs [n].v_desc  , 30, x_desc);
      sprintf (d_entry, "%2d  %-12.12s  %-12.12s  %c  %2d  %-3.3s %-3.3s  %3.1f  %c  %-12.12s  %-50.50s  %-30.30s  Ï",
            n, x_verb, x_specs, G_verbs [n].v_mode, G_verbs [n].v_mask,
            x_reader, x_writer, G_verbs [n].v_seq, G_verbs [n].v_done,
            x_flags, x_labels, x_desc);
   }
   /*---(save-back)----------------------*/
   G_cverb = n;
   if (r_verb   != NULL)  ystrlcpy (r_verb   , G_verbs [n].v_verb  , LEN_LABEL);
   if (r_specs  != NULL)  ystrlcpy (r_specs  , G_verbs [n].v_specs , LEN_TITLE);
   if (r_mode   != NULL)  *r_mode   =  G_verbs [n].v_mode;
   if (r_mask   != NULL)  *r_mask   =  G_verbs [n].v_mask;
   if (r_reader != NULL)  *r_reader =  G_verbs [n].v_reader;
   if (r_writer != NULL)  *r_writer =  G_verbs [n].v_writer;
   if (r_seq    != NULL)  *r_seq    =  G_verbs [n].v_seq;
   if (r_done   != NULL)  *r_done   =  G_verbs [n].v_done;
   if (r_flags  != NULL)  ystrlcpy (r_flags  , G_verbs [n].v_flags , LEN_TITLE);
   if (r_labels != NULL)  ystrlcpy (r_labels , G_verbs [n].v_labels, LEN_RECD);
   if (r_desc   != NULL)  ystrlcpy (r_desc   , G_verbs [n].v_desc  , LEN_DESC);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return n;
}

char* yparse_verb_entry  (char a_verb [LEN_LABEL], char a_dir, char a_index) { yparse_verb__search (a_verb, a_dir, a_index, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, yparse_print);  return yparse_print; }

char
yparse_verb_by_name     (char a_verb [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_senter  (__FUNCTION__);
   /*---(short-cut)----------------------*/
   DEBUG_YPARSE   yLOG_spoint  (a_verb);
   --rce;  if (a_verb == NULL || a_verb [0] == '\0') {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_snote   (a_verb);
   /*---(walk entries)-------------------*/
   for (i = 0; i < G_nverb; ++i) {
      if (G_verbs [i].v_verb [0] != a_verb [0])      continue;
      if (strcmp (G_verbs [i].v_verb, a_verb) != 0)  continue;
      DEBUG_YPARSE   yLOG_snote   ("FOUND");
      return i;
   }
   /*---(complete)-----------------------*/
   --rce;
   DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
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
   /*> DEBUG_YPARSE   yLOG_sint    (n);                                               <*/
   /*> DEBUG_YPARSE   yLOG_snote   (x_last);                                          <*/
   /*> if (n >= 0 && strcmp (a_verb, x_last) == 0) {                                  <* 
    *>    if (a_queue != NULL)  a_queue->q_iverb = n;                                   <* 
    *>    DEBUG_YPARSE   yLOG_snote   ("short-cut");                                  <* 
    *>    DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);                                 <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <*/
   /*---(find entry)---------------------*/
   DEBUG_YPARSE   yLOG_sint    (G_nverb);
   --rce;  if (G_nverb <= 0) {
      DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   n = -1;
   for (i = 0; i < G_nverb; ++i) {
      if (G_verbs [i].v_verb [0] != a_verb [0])      continue;
      if (strcmp (G_verbs [i].v_verb, a_verb) != 0)  continue;
      DEBUG_YPARSE   yLOG_snote   ("FOUND");
      n = i;
      break;
   }
   /*---(save)---------------------------*/
   ystrlcpy (x_last, a_verb, LEN_LABEL);
   if (a_queue != NULL) {
      a_queue->q_iverb   = n;
      if (n >= 0) {
         if (a_queue == &s_qin)  a_queue->q_handler = G_verbs [n].v_reader;
         else                    a_queue->q_handler = G_verbs [n].v_writer;
      } else {
         a_queue->q_handler = NULL;
      }
   }
   DEBUG_YPARSE   yLOG_sint    (n);
   DEBUG_YPARSE   yLOG_snote   (x_last);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_sexit   (__FUNCTION__);
   return n;
}

char yparse_verb_mask        (int n) { return G_verbs [n].v_mask; }

/*> char                                                                              <* 
 *> yparse_specs_next_write  (void)                                                   <* 
 *> {                                                                                 <* 
 *>    if (s_qout.q_iverb <  0       )  return -2;                                    <* 
 *>    if (s_qout.q_count <  0       )  return -3;                                    <* 
 *>    if (s_qout.q_count >= MAX_COLS)  return -4;                                    <* 
 *>    return G_verbs [s_qout.q_iverb].v_specs [s_qout.q_count - 1];                  <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> yparse_specs_next_read  (void)                                                    <* 
 *> {                                                                                 <* 
 *>    if (s_qin.q_iverb <  0       )  return -2;                                     <* 
 *>    if (s_qin.q_first <  0       )  return -3;                                     <* 
 *>    if (s_qin.q_first >= MAX_COLS)  return -4;                                     <* 
 *>    return G_verbs [s_qin.q_iverb].v_specs [s_qin.q_first - 1];                    <* 
 *> }                                                                                 <*/

/*> char                                                                                            <* 
 *> yparse_specs_len        (tQUEUE *a_queue)                                                       <* 
 *> {                                                                                               <* 
 *>    int         i           =    0;                                                              <* 
 *>    int         n           =    1;   /+ start with one for verb  +/                             <* 
 *>    if (a_queue        == NULL)  return -1;                                                      <* 
 *>    if (a_queue->q_iverb <  0   )  return -2;                                                    <* 
 *>    /+> DEBUG_YPARSE   yLOG_info    ("spec"      , G_verbs [a_queue->q_iverb].v_specs);    <+/   <* 
 *>    for (i = 0; i < MAX_COLS; ++i) {                                                             <* 
 *>       if (G_verbs [a_queue->q_iverb].v_specs [i] == '£')   break;                               <* 
 *>       /+> if (G_verbs [a_queue->q_iverb].v_specs [i] == '-')    break;                    <+/   <* 
 *>       ++n;                                                                                      <* 
 *>    }                                                                                            <* 
 *>    return n;                                                                                    <* 
 *> }                                                                                               <*/

char
yPARSE_handler_max      (char a_mode, char *a_verb, float a_seq, uchar *a_specs, char a_mask, void *a_reader, void *a_writer, uchar *a_flags, uchar *a_labels, uchar *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_found     =    0;
   int         n           =    0;
   char        x_specs     [LEN_TITLE] = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_char    ("y_ready"   , myPARSE.y_ready);
   --rce;  if (myPARSE.y_ready != 'y') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   --rce;  if (a_verb  == NULL || a_verb  [0] == '\0') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("a_verb"    , a_verb);
   DEBUG_YPARSE   yLOG_point   ("a_specs"   , a_specs);
   --rce;  if (a_specs == NULL || a_specs [0] == '\0') {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_info    ("a_specs"   , a_specs);
   /*---(note)---------------------------*/
   if (a_desc != NULL) {
      DEBUG_YPARSE   yLOG_info    ("a_desc"    , a_desc);
   }
   /*---(check verb)---------------------*/
   --rce;  if (myPARSE.y_verbs  != YPARSE_MANUAL) {
      rc = ystrlgood (a_verb, ySTR_ALNUM, LEN_USER);
      if (rc < 0) {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check existing)-----------------*/
   n = x_found = yparse_verb_find (NULL, a_verb);
   DEBUG_YPARSE   yLOG_value   ("G_nverb"   , G_nverb);
   DEBUG_YPARSE   yLOG_value   ("find"      , n);
   if (n < 0)  n = G_nverb;
   DEBUG_YPARSE   yLOG_value   ("n"         , n);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_specs"   , a_specs);
   if (a_specs != NULL && strlen (a_specs) >  0) {
      ystrlcpy (x_specs, a_specs, LEN_TITLE);
   }
   ystrltrim (x_specs, ySTR_BOTH, LEN_TITLE);
   /*> ystrlddel (x_specs, '-', LEN_TITLE);                                           <*/
   DEBUG_YPARSE   yLOG_info    ("x_specs"   , x_specs);
   --rce;  for (i = 0; i < strlen (x_specs); ++i) {
      l = yparse_spec_size (x_specs [i]);
      DEBUG_YPARSE   yLOG_complex ("entry"     , "%2d, %c, %d", i, x_specs [i], l);
      if (l > 0)  continue;
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE   yLOG_point   ("a_reader"  , a_reader);
   DEBUG_YPARSE   yLOG_point   ("a_writer"  , a_writer);
   /*> --rce;  if (a_reader == NULL && a_writer == NULL) {                            <* 
    *>    DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);                            <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(copy values)--------------------*/
   if (a_mode   != 0   )  G_verbs [n].v_mode    = a_mode;
   ystrlcpy (G_verbs [n].v_verb  , a_verb  , LEN_LABEL);
   if (a_seq    >  0.0 )  G_verbs [n].v_seq     = a_seq;
   ystrlcpy (G_verbs [n].v_specs , x_specs , LEN_TITLE);
   G_verbs [n].v_mask    = a_mask;
   if (a_reader != NULL)  G_verbs [n].v_reader  = a_reader;
   if (a_writer != NULL)  G_verbs [n].v_writer  = a_writer;
   if (a_flags  != NULL)  ystrlcpy (G_verbs [n].v_flags , a_flags , LEN_TITLE);
   if (a_labels != NULL)  ystrlcpy (G_verbs [n].v_labels, a_labels, LEN_RECD);
   if (a_desc   != NULL)  ystrlcpy (G_verbs [n].v_desc  , a_desc  , LEN_DESC);
   /*---(update)-------------------------*/
   if (x_found < 0)  ++G_nverb;
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_handler_remove   (char *a_verb)
{
   int         i           =    0;
   int         n           =   -1;
   for (i = 0; i < G_nverb; ++i) {
      if (G_verbs [i].v_verb [0] != a_verb [0])      continue;
      if (strcmp (G_verbs [i].v_verb, a_verb) != 0)  continue;
      DEBUG_YPARSE   yLOG_snote   ("FOUND");
      n = i;
      break;
   }
   if (n >= 0)  yparse_verb__wipe (n);
   return 0;
}

char*
yPARSE_verb             (int a_num)
{
   if (a_num <  0      )   return G_nada;
   if (a_num >= G_nverb)   return G_nada;
   return G_verbs [a_num].v_verb;
}




/*====================------------------------------------====================*/
/*===----                        major drivers                         ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVERS_________________o (void) {;};

char
yPARSE_write_all        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE  yLOG_value   ("G_nverb"   , G_nverb);
   /*---(prepare)------------------------*/
   for (i = 0; i < G_nverb; ++i)  G_verbs [i].v_done = '-';
   /*---(call writers)-------------------*/
   while (1) {
      /*---(find next)-------------------*/
      x_lowest = 999999.0;
      x_next   = -1;
      for (i = 0; i < G_nverb; ++i) {
         if (G_verbs [i].v_done == 'y'    )   continue;
         if (G_verbs [i].v_seq >=  x_lowest)  continue;
         x_lowest = G_verbs [i].v_seq;
         x_next   = i;
      }
      if (x_lowest > 999.0)  break;
      if (x_next   < 0    )  break;
      G_verbs [x_next].v_done = 'y';
      /*---(filter)----------------------*/
      DEBUG_INPT  yLOG_info    ("verb"      , G_verbs [x_next].v_verb);
      DEBUG_INPT  yLOG_point   ("reader"    , G_verbs [x_next].v_writer);
      if (G_verbs [x_next].v_writer == NULL)  continue;
      /*---(handle)----------------------*/
      rc = G_verbs [x_next].v_writer (s_qout.q_nfull, G_verbs [x_next].v_verb);
      if (rc >= 0)  c += rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yPARSE_read_all         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =   -1;
   int         c           =    0;
   float       x_lowest    =  0.0;
   int         x_next      =   -1;
   char        x_verb      [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   while (1) {
      rc = yPARSE_read_one (NULL, NULL);
      if (rc == 0)  {
         DEBUG_YPARSE   yLOG_note    ("end-of-file");
         break;
      }
      /*> printf ("%s\n", myPARSE.y_recd);                                              <*/
      if (rc <  0)  {
         DEBUG_YPARSE   yLOG_note    ("trouble reading record");
         continue;
      }
      yparse_peek_verb (&n, x_verb);
      DEBUG_YPARSE  yLOG_value   ("index"     , n);
      if (n < 0)  {
         DEBUG_YPARSE   yLOG_note    ("verb not recognized");
         continue;
      }
      DEBUG_YPARSE  yLOG_info    ("verb"      , x_verb);
      DEBUG_YPARSE  yLOG_point   ("reader"    , G_verbs [n].v_reader);
      if (G_verbs [n].v_reader == NULL) {
         DEBUG_YPARSE   yLOG_note    ("reader not assigned");
         continue;
      }
      rc = G_verbs [n].v_reader (s_qin.q_nfull, x_verb);
      if (rc < 0)  {
         DEBUG_YPARSE   yLOG_note    ("handler not successful");
         continue;
      }
      ++c;
   }
   /*---(limits)-------------------------*/
   DEBUG_YPARSE  yLOG_value   ("c"         , c);
   if (c > 99)  c = 99;
   DEBUG_YPARSE  yLOG_value   ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_verb       (char *a_question, char *a_verb, int a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(preprare)-----------------------*/
   ystrlcpy  (yparse_print, "VERB unit        : question not understood", LEN_STR);
   /*---(check existing)-----------------*/
   if      (strcmp (a_question, "count"    ) == 0) {
      sprintf (yparse_print, "VERB count       : %d", G_nverb);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      n = a_seq;
      if (n < 0 || n >= MAX_VERBS)       sprintf (yparse_print, "VERB entry  (--) : out of range");
      else if (G_verbs [n].v_verb [0] == '£') sprintf (yparse_print, "VERB entry  (%2d) : verb slot not used", n);
      else sprintf (yparse_print, "VERB entry  (%2d) : %c, %-12.12s [%-12.12s] %cr %cw %3.1fs %2dm [%-20.20s] [%-10.10s]", n, G_verbs [n].v_mode, G_verbs [n].v_verb, G_verbs [n].v_specs, (G_verbs [n].v_reader != NULL) ? 'y' : '-', (G_verbs [n].v_writer != NULL) ? 'y' : '-', G_verbs [n].v_seq, G_verbs [n].v_mask, G_verbs [n].v_labels, G_verbs [n].v_desc);
   }
   /*---(answer)------------------------------------------*/
   else if (strcmp (a_question, "by_name"  ) == 0) {
      if (a_verb == NULL || a_verb [0] == '\0') {
         sprintf (yparse_print, "VERB name   (--) : verb not given");
      } else {
         n = yparse_verb_find (NULL, a_verb);
         if (n < 0) sprintf (yparse_print, "VERB name   (--) : %s is unknown", a_verb);
         else       sprintf (yparse_print, "VERB name   (%2d) : %c, %-12.12s [%-12.12s] %cr %cw %3.1fs %2dm [%-20.20s] [%-10.10s]", n, G_verbs [n].v_mode, G_verbs [n].v_verb, G_verbs [n].v_specs, (G_verbs [n].v_reader != NULL) ? 'y' : '-', (G_verbs [n].v_writer != NULL) ? 'y' : '-', G_verbs [n].v_seq, G_verbs [n].v_mask, G_verbs [n].v_labels, G_verbs [n].v_desc);
      }
   }
   /*> else if (strcmp (a_question, "section"  ) == 0) {                              <* 
    *>    ystrlcpy    (t, s_sect, LEN_RECD);                                          <* 
    *>    ystrlencode (t, ySTR_NORM, LEN_RECD);                                       <* 
    *>    sprintf (yparse_print, "VERB section     : %2d[%s]", strlen (t), t);        <* 
    *> }                                                                              <*/
   /*> else if (strcmp (a_question, "divider"  ) == 0) {                              <* 
    *>    ystrlcpy    (t, s_div, LEN_RECD);                                           <* 
    *>    ystrlencode (t, ySTR_NORM, LEN_RECD);                                       <* 
    *>    sprintf (yparse_print, "VERB divider     : %2d[%s]", strlen (t), t);        <* 
    *> }                                                                              <*/
   /*> else if (strcmp (a_question, "footer"   ) == 0) {                              <* 
    *>    ystrlcpy    (t, s_foot, LEN_RECD);                                          <* 
    *>    ystrlencode (t, ySTR_NORM, LEN_RECD);                                       <* 
    *>    sprintf (yparse_print, "VERB footer      : %2d[%s]", strlen (t), t);        <* 
    *> }                                                                              <*/
   /*---(complete)----------------------------------------*/
   return yparse_print;
}



