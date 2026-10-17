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



typedef     struct stat       tSTAT;



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;};

char
yparse_queue_purge      (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----+-----+-*/
   tNODE      *x_curr      = NULL;
   /*---(walk-through)-------------------*/
   x_curr = a_queue->q_head;
   while (x_curr != NULL) {
      yparse_dequeue (a_queue, NULL);
      x_curr = a_queue->q_head;
   }
   /*---(master data)--------------------*/
   a_queue->q_iverb    =   -1;
   a_queue->q_good     =  '-';
   a_queue->q_hidden   =  '-';
   /*---(record)-------------------------*/
   ystrlcpy (a_queue->q_recd , ""     , LEN_RECD);
   a_queue->q_len      =    0;
   /*---(fields)-------------------------*/
   a_queue->q_head     = NULL;
   a_queue->q_tail     = NULL;
   a_queue->q_first    =    0;
   a_queue->q_count    =    0;
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse_queue_init       (tQUEUE *a_queue, char a_dir, char a_label [LEN_SHORT])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_queue == NULL)                                  return rce;
   --rce;  if (a_dir   == 0    || strchr ("IO", a_dir) == NULL)  return rce;
   --rce;  if (a_label == NULL || a_label [0] == '\0')           return rce;
   /*---(master data)--------------------*/
   a_queue->q_dir      = a_dir;
   ystrlcpy (a_queue->q_label, a_label, LEN_SHORT);
   a_queue->q_handler  = NULL;
   a_queue->q_iverb    =   -1;
   a_queue->q_good     =  '-';
   a_queue->q_hidden   =  '-';
   /*---(file)---------------------------*/
   strcpy (a_queue->q_loc, "");
   a_queue->q_file     = NULL;
   a_queue->q_tline    =    0;
   a_queue->q_nline    =    0;
   a_queue->q_cline    =    0;
   /*---(record)-------------------------*/
   ystrlcpy (a_queue->q_recd , ""     , LEN_RECD);
   a_queue->q_len      =    0;
   /*---(fields)-------------------------*/
   a_queue->q_head     = NULL;
   a_queue->q_tail     = NULL;
   a_queue->q_first    =    0;
   a_queue->q_count    =    0;
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse_queue_reset      (tQUEUE *a_queue)
{
   /*---(header)-------------------------*/
   yparse_queue_purge (a_queue);
   /*---(file)---------------------------*/
   a_queue->q_tline    =    0;
   a_queue->q_nline    =    0;
   a_queue->q_cline    =    0;
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse_queue_rando      (tQUEUE *a_queue)
{
   /*---(master data)--------------------*/
   a_queue->q_dir      = '*';
   strcpy (a_queue->q_label, "abc");
   a_queue->q_handler  = 0x01;
   a_queue->q_iverb    =    2;
   a_queue->q_good     =  'g';
   a_queue->q_hidden   =  'h';
   /*---(file)---------------------------*/
   strcpy (a_queue->q_loc, "test file");
   a_queue->q_file     = 0x05;
   a_queue->q_tline    =    6;
   a_queue->q_nline    =    7;
   a_queue->q_cline    =    8;
   /*---(record)-------------------------*/
   strcpy (a_queue->q_recd , "lots of fields");
   a_queue->q_len      =    9;
   /*---(fields)-------------------------*/
   a_queue->q_head     = NULL;
   a_queue->q_tail     = NULL;
   a_queue->q_first    =   12;
   a_queue->q_count    =   13;
   /*---(complete)-----------------------*/
   return 0;
}

char*
yparse_queue_entry      (tQUEUE *a_queue)
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
   /*---(quick-out)----------------------*/
   if (a_queue == 'T') {
      strcpy (yPARSE__unit_answer, "D label vrb had  G H  ---location--------- ptr tot acp cur  len ---record-------------------------------  ---head--- ---tail--- fst cnt  Ï");
      DEBUG_YDLST   yLOG_sexit   (__FUNCTION__);
      return yPARSE__unit_answer;
   }
   /*---(defaults)-----------------------*/
   strcpy (yPARSE__unit_answer, "- ´···· ··- ···  - -  ´··················· ··· ··- ··- ··-  ··- ´·······································  ´········· ´········· ··- ··-  Ï");
   /*---(prepare)------------------------*/
   if (a_queue->q_label    != NULL)  snprintf (x_label, LEN_TERSE, "%s·····", a_queue->q_label);
   if (a_queue->q_handler  != NULL)  strcpy   (x_handler, "SET");
   if (a_queue->q_loc  [0] != '\0')  snprintf (x_loc  , 21       , "%s········································", a_queue->q_loc);
   if (a_queue->q_file     != NULL)  strcpy   (x_file   , "SET");
   if (a_queue->q_recd [0] != '\0')  snprintf (x_recd , 41       , "%s········································", a_queue->q_recd);
   if (a_queue->q_head     != NULL)  snprintf (x_head , 11, "%s··········", a_queue->q_head->n_item);
   if (a_queue->q_tail     != NULL)  snprintf (x_tail , 11, "%s··········", a_queue->q_tail->n_item);
   sprintf (yPARSE__unit_answer, "%c %-5.5s %3d %-3.3s  %c %c  %-20.20s %-3.3s %3d %3d %3d  %3d %-40.40s  %-10.10s %-10.10s %3d %3d  Ï",
         a_queue->q_dir, x_label, a_queue->q_iverb, x_handler,
         a_queue->q_good, a_queue->q_hidden,
         x_loc, x_file, a_queue->q_tline, a_queue->q_nline, a_queue->q_cline,
         a_queue->q_len, x_recd,
         x_head, x_tail, a_queue->q_first, a_queue->q_count);
   /*---(complete)-----------------------*/
   return yPARSE__unit_answer;
}



/*====================------------------------------------====================*/
/*===----                        access to files                       ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESS__________________o (void) {;};

char
yparse_queue__defense   (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         l           =    0;
   /*---(config check)-------------------*/
   DEBUG_YPARSE  yLOG_schar   (myPARSE.ready);
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("must call yPARSE_config () first");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(queue check)--------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue);
   --rce;  if (a_queue == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("null queue");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_queue->q_label);
   /*---(queue label check)--------------*/
   l = ystrllen (a_queue->q_label, LEN_SHORT);
   DEBUG_YPARSE  yLOG_sint    (l);
   --rce;  if (l <= 0  || l >= LEN_LABEL) {
      DEBUG_YPARSE  yLOG_snote   ("file label empty");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check location)-----------*/
   DEBUG_YPARSE  yLOG_snote   (a_queue->q_loc);
   --rce;  switch (a_queue->q_label [0]) {
   case 'I'  :
      if (strcmp (a_queue->q_loc, "") != 0) {
         DEBUG_YPARSE  yLOG_snote   ("file loc already filled");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      break;
   case 'O'  :
      if (strcmp (a_queue->q_loc, "") == 0) {
         DEBUG_YPARSE  yLOG_snote   ("file location is empty");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      break;
   default   :
      DEBUG_YPARSE  yLOG_snote   ("unknown direction");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(check file use)-----------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_file);
   --rce;  switch (a_queue->q_label [0]) {
   case 'I'  :
      if (a_queue->q_file != NULL) {
         DEBUG_YPARSE  yLOG_snote   ("file already open");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      break;
   case 'O'  :
      if (a_queue->q_file == NULL) {
         DEBUG_YPARSE  yLOG_snote   ("file already closed");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      break;
   }
   /*---(complete)-----------------*/
   DEBUG_YPARSE  yLOG_snote   ("successful");
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char         /*-> open file for reading and prep -----[ leaf   [ge.723.023.20]*/ /*-[01.0000.013.!]-*/ /*-[--.---.---.--]-*/
yparse_open             (tQUEUE *a_queue, char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   char        x_dir       [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_queue__defense (a_queue);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_loc);
   --rce;  if (a_queue->q_loc != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("file loc already filled");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_file);
   --rce;  if (a_queue->q_file != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("file already open");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_name);
   /*---(direction)----------------------*/
   --rce;  switch (a_queue->q_label [0]) {
   case 'I'  :
      DEBUG_YPARSE  yLOG_snote   ("reading");
      ystrlcpy (x_dir, "rt", LEN_LABEL);
      if (strcmp ("stdin"  , a_name) == 0) {
         a_queue->q_file  = stdin;
         ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
         DEBUG_YPARSE  yLOG_snote   ("ready");
         DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      break;
   case 'O'  :
      DEBUG_YPARSE  yLOG_snote   ("writing");
      ystrlcpy (x_dir, "wt", LEN_LABEL);
      if (strcmp ("stdout" , a_name) == 0) {
         a_queue->q_file  = stdout;
         ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
         DEBUG_YPARSE  yLOG_snote   ("ready");
         DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      if (strcmp ("unit"   , a_name) == 0) {
         a_queue->q_file  = NULL;
         ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
         DEBUG_YPARSE  yLOG_snote   ("unit testing");
         DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      break;
   default   :
      DEBUG_YPARSE  yLOG_snote   ("unknown dir");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      break;
   }
   /*---(verify file)--------------------*/
   rc = yENV_exists (a_name);
   DEBUG_YPARSE  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   ("successful");
   /*> --rce;  if (a_queue->q_label [0] == 'I') {                                       <* 
    *>    DEBUG_YPARSE   yLOG_snote   (a_name);                                       <* 
    *>    rc = stat (a_name, &s);                                                     <* 
    *>    DEBUG_YPARSE   yLOG_sint    (rc);                                           <* 
    *>    --rce;  if (rc < 0) {                                                       <* 
    *>       DEBUG_YPARSE   yLOG_snote   ("file not found");                          <* 
    *>       DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);                         <* 
    *>       return rce;                                                              <* 
    *>    }                                                                           <* 
    *>    DEBUG_YPARSE yLOG_sint    (s.st_mode);                                      <* 
    *>    --rce;  if (!S_ISREG (s.st_mode)) {                                         <* 
    *>       DEBUG_YPARSE   yLOG_snote   ("not a file");                              <* 
    *>       DEBUG_YPARSE   yLOG_sexitr  (__FUNCTION__, rce);                         <* 
    *>       return rce;                                                              <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(open file)----------------------*/
   a_queue->q_file = fopen (a_name, x_dir);
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_file);
   --rce;  if (a_queue->q_file == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("could not be openned");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   ("successful");
   /*---(prepare)------------------*/
   DEBUG_YPARSE  yLOG_snote   ("globals");
   ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
   /*---(complete)-----------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> close file for reading and wrap ----[ leaf   [ge.411.011.20]*/ /*-[01.0000.013.!]-*/ /*-[--.---.---.--]-*/
yparse_close            (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_queue__defense (a_queue);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_loc);
   --rce;  if (a_queue->q_loc == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("file loc empty");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_queue->q_loc);
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_file);
   --rce;  if (a_queue->q_file == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("file already closed");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for pipes)----------------*/
   if (strcmp ("stdin" , a_queue->q_loc) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("stdin");
      a_queue->q_file = NULL;
      strcpy (a_queue->q_loc, "");
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   if (strcmp ("stdout", a_queue->q_loc) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("stdout");
      a_queue->q_file = NULL;
      strcpy (a_queue->q_loc, "");
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(close file)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_file);
   if (a_queue->q_file == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("nothing to do");
   } else {
      DEBUG_YPARSE  yLOG_snote   ("close file");
      fclose  (a_queue->q_file);
   }
   a_queue->q_file = NULL;
   /*---(prepare)------------------*/
   DEBUG_YPARSE  yLOG_snote   ("globals");
   strcpy (a_queue->q_loc, "");
   /*---(complete)-----------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}




/*====================------------------------------------====================*/
/*===----                   data structure primatives                  ----===*/
/*====================------------------------------------====================*/

/*> char                                                                              <* 
 *> yparse_queue__check     (char *a_name, char a_mode)                               <* 
 *> {  /+---(locals)-----------+-----------+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    int         rci         =    0;                                                <* 
 *>    tSTAT       st;                                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_FILE   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_FILE   yLOG_point   ("a_name"    , a_name);                              <* 
 *>    --rce;  if (a_name == NULL || a_name [0] == '\0') {                            <* 
 *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_FILE   yLOG_info    ("a_name"    , a_name);                              <* 
 *>    DEBUG_FILE   yLOG_char    ("a_mode"    , a_mode);                              <* 
 *>    --rce;  if (a_mode == 0 || strchr ("IO", a_mode) == NULL) {                    <* 
 *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(get the file information)-------+/                                       <* 
 *>    rci = lstat (a_name, &st);                                                     <* 
 *>    DEBUG_FILE   yLOG_value   ("lstat"     , rci);                                 <* 
 *>    --rce; if (rci < 0) {                                                          <* 
 *>       if (a_mode == 'I') {                                                        <* 
 *>          DEBUG_FILE   yLOG_note    ("file does not exist, can not read");         <* 
 *>          DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                <* 
 *>          return rce;                                                              <* 
 *>       }                                                                           <* 
 *>       DEBUG_FILE   yLOG_note    ("writing data to a brand new file");             <* 
 *>       DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                   <* 
 *>       return 0;                                                                   <* 
 *>    } else {                                                                       <* 
 *>       if (a_mode == 'O') {                                                        <* 
 *>          DEBUG_FILE   yLOG_note    ("file exists, writing over existing file");   <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    /+---(check regular file)-------------+/                                       <* 
 *>    --rce;  if (S_ISREG (st.st_mode)) {                                            <* 
 *>       DEBUG_FILE   yLOG_note    ("refers to a regular file, perfect");            <* 
 *>    }                                                                              <* 
 *>    /+---(check symlink)------------------+/                                       <* 
 *>    else if (S_ISLNK (st.st_mode)) {                                               <* 
 *>       DEBUG_FILE   yLOG_note    ("file can not be a symlink to another file");    <* 
 *>       DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                   <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    else  {                                                                        <* 
 *>       if      (S_ISDIR (st.st_mode)) {                                            <* 
 *>          DEBUG_FILE   yLOG_note    ("file is a directory, not allowwed");         <* 
 *>       } else if (S_ISCHR (st.st_mode)) {                                          <* 
 *>          DEBUG_FILE   yLOG_note    ("file is a char dev, not allowwed");          <* 
 *>       } else if (S_ISBLK (st.st_mode)) {                                          <* 
 *>          DEBUG_FILE   yLOG_note    ("file is a block dev, not allowwed");         <* 
 *>       } else if (S_ISFIFO(st.st_mode)) {                                          <* 
 *>          DEBUG_FILE   yLOG_note    ("file is a fifo/pipe, not allowwed");         <* 
 *>       } else if (S_ISSOCK(st.st_mode)) {                                          <* 
 *>          DEBUG_FILE   yLOG_note    ("file is a socket, not allowwed");            <* 
 *>       } else  {                                                                   <* 
 *>          DEBUG_FILE   yLOG_note    ("file is not recognized, not allowwed");      <* 
 *>       }                                                                           <* 
 *>       DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                   <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                   data structure primatives                  ----===*/
/*====================------------------------------------====================*/
static void      o___PRIMATIVE_______________o (void) {;};

char         /*-> add item to end of queue -----------[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_enqueue          (tQUEUE *a_queue, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_new       = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_item   == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("nothing to save");
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_item);
   /*---(create)-------------------------*/
   x_new = (tNODE *) malloc (sizeof (tNODE));
   DEBUG_YPARSE  yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("malloc failed");
      return rce;
   }
   /*---(saving)-------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("saving");
   x_new->ref  = a_queue->q_count;
   x_new->n_item = strdup (a_item);
   x_new->next = NULL;
   x_new->prev = NULL;
   /*---(attatch)------------------------*/
   if (a_queue->q_head == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("first");
      a_queue->q_head       = x_new;
      a_queue->q_tail       = x_new;
   } else  {
      DEBUG_YPARSE  yLOG_snote   ("append");
      a_queue->q_tail->next = x_new;
      x_new->prev         = a_queue->q_tail;
      a_queue->q_tail       = x_new;
   }
   ++a_queue->q_count;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_first);
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_count);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> remove item from front of queue ----[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_dequeue          (tQUEUE *a_queue, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_save      = NULL;
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_snote   ("dequeue");
   DEBUG_YPARSE  yLOG_spoint  (a_queue);
   --rce;  if (a_queue == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("null queue");
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   if (a_item != NULL)  ystrlcpy (a_item, "", LEN_RECD);
   /*---(no entries)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_head);
   --rce;  if (a_queue->q_head == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(copy and clear)-----------------*/
   if (a_item != NULL)  ystrlcpy (a_item, a_queue->q_head->n_item, LEN_RECD);
   if (a_queue->q_head->n_item != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("free item");
      free (a_queue->q_head->n_item);
   }
   /*---(single entry)-------------------*/
   if (a_queue->q_tail == a_queue->q_head) {
      DEBUG_YPARSE  yLOG_snote   ("single item");
      free (a_queue->q_head);
      a_queue->q_tail  = a_queue->q_head = NULL;
   }
   /*---(multi entry)--------------------*/
   else {
      DEBUG_YPARSE  yLOG_snote   ("multiple items");
      x_save  = a_queue->q_head->next;
      x_save->prev = NULL;
      free (a_queue->q_head);
      a_queue->q_head  = x_save;
   }
   ++a_queue->q_first;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_first);
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_count);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> look at item in front of queue -----[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_topqueue         (tQUEUE *a_queue, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_save      = NULL;
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue);
   --rce;  if (a_queue == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("null queue");
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   if (a_item != NULL)  ystrlcpy (a_item, "", LEN_RECD);
   /*---(no entries)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_head);
   --rce;  if (a_queue->q_head == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(copy)---------------------------*/
   if (a_item != NULL)  ystrlcpy (a_item, a_queue->q_head->n_item, LEN_RECD);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> remove item from front of queue ----[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_queue_tail       (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_save      = NULL;
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue);
   --rce;  if (a_queue == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("null queue");
      return rce;
   }
   /*---(no entries)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_tail);
   --rce;  if (a_queue->q_tail == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(check for empty)----------------*/
   if (a_queue->q_tail->n_item != NULL && strlen (a_queue->q_tail->n_item) > 0) {
      DEBUG_YPARSE  yLOG_snote   ("real item at tail, done");
      return 0;
   }
   /*---(clear)--------------------------*/
   if (a_queue->q_tail->n_item != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("free item");
      free (a_queue->q_tail->n_item);
   }
   /*---(single entry)-------------------*/
   if (a_queue->q_head == a_queue->q_tail) {
      DEBUG_YPARSE  yLOG_snote   ("single item");
      free (a_queue->q_head);
      a_queue->q_head  = a_queue->q_tail = NULL;
   }
   /*---(multi entry)--------------------*/
   else {
      DEBUG_YPARSE  yLOG_snote   ("multiple items");
      x_save  = a_queue->q_tail->prev;
      x_save->next = NULL;
      free (a_queue->q_tail);
      a_queue->q_tail  = x_save;
   }
   --a_queue->q_count;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_first);
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_count);
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse_peek             (tQUEUE *a_queue, const int a_ref, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_curr      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_item == NULL)  return rce;
   /*---(defense)------------------------*/
   ystrlcpy (a_item, "", LEN_LABEL);
   /*---(search)-------------------------*/
   x_curr = a_queue->q_head;
   while (x_curr != NULL) {
      if (x_curr->ref == a_ref) {
         ystrlcpy (a_item, x_curr->n_item, LEN_RECD);
         return 0;
      }
      x_curr = x_curr->next;
   }
   /*---(complete)-----------------------*/
   return -1;
}


/*> char yPARSE_push  (char *a_item) { return yparse__enqueue (a_item); }             <*/



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char yPARSE__unit_answer [ LEN_STR  ];

char         /*--> write the heartbeat ---------------------------------------*/
yparse_queue__line      (int n, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   int         x_len       =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(prepre)-------------------------*/
   if (a_recd != NULL)  ystrlcpy (a_recd, ""    , LEN_RECD);
   /*---(open)---------------------------*/
   DEBUG_RPTG   yLOG_info    ("file"      , s_qout.q_loc);
   if (strcmp (s_qout.q_loc, "") != 0)  f = fopen (s_qout.q_loc, "rt");
   else                                 f = fopen ("/tmp/yPARSE_out.txt", "rt");
   DEBUG_RPTG   yLOG_point   ("f"         , f);
   --rce;  if (rc < 0) {
      DEBUG_RPTG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write)--------------------------*/
   --rce;  while (1) {
      fgets (x_recd, LEN_RECD, f);
      if (feof (f)) {
         DEBUG_RPTG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (c >= n)  break;
      ++c;
   }
   /*---(close)--------------------------*/
   rc = fclose (f);
   DEBUG_RPTG   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_RPTG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(fix-up)-------------------------*/
   x_len = strlen (x_recd);
   if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
   ystrlencode (x_recd, ySTR_NORM, LEN_RECD);
   /*---(save back)----------------------*/
   if (a_recd != NULL)  ystrlcpy (a_recd, x_recd, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_RPTG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_queue      (tQUEUE *a_queue, char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(preprare)-----------------------*/
   ystrlcpy  (yPARSE__unit_answer, "QUEUE unit       : question not understood", LEN_STR);
   if (a_queue == NULL) {
      ystrlcpy  (yPARSE__unit_answer, "QUEUE unit       : queue not specified", LEN_STR);
   }
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "verb"     ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s verb         : %2d[%s]", a_queue->q_label, a_queue->q_iverb, yPARSE_verb (a_queue->q_iverb));
   }
   else if (strcmp (a_question, "line"     ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s line         : total %2d, curr %2d", a_queue->q_label, a_queue->q_nline, a_queue->q_cline);
   }
   else if (strcmp (a_question, "field"    ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s field        : total %2d, curr %2d, good %c", a_queue->q_label, a_queue->q_count, a_queue->q_first, a_queue->q_good);
   }
   else if (strcmp (a_question, "record"   ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s record       : %2d[%s]", a_queue->q_label, a_queue->q_len, a_queue->q_recd);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      if (a_queue->q_count < 1 || a_num < a_queue->q_first || a_num >= a_queue->q_count) {
         sprintf (yPARSE__unit_answer, "%-3.3s entry   (%2d) : null", a_queue->q_label, a_num);
      } else {
         rc = yparse_peek (a_queue, a_num, t);
         if (rc < 0) {
            sprintf (yPARSE__unit_answer, "%-3.3s entry   (%2d) : trouble finding", a_queue->q_label, a_num);
         } else {
            sprintf (yPARSE__unit_answer, "%-3.3s entry   (%2d) : %2d[%s]", a_queue->q_label, a_num, strlen (t), t);
         }
      }
   }
   else if (strcmp (a_question, "verb"     ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s verb         : %2d[%s]", a_queue->q_label, strlen (myPARSE.verb), myPARSE.verb);
   }
   else if (strcmp (a_question, "written"  ) == 0) {
      yparse_queue__line (a_num, t);
      sprintf (yPARSE__unit_answer, "%-3.3s written (%2d) : %2d[%s]", a_queue->q_label, a_num, strlen (t), t);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}
