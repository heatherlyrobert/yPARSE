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
yparse_queue__wipe      (tQUEUE *a_queue, char a_type)
{  /*---(design notes)-------------------*/
   /*
    *   * = everything
    *   i = init
    *   r = reset
    *   p = purge
    *
    *
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   tNODE      *x_curr      = NULL;
   /*---(naming)-------------------------*/
   if (a_type != 0 && strchr ("*"   , a_type) != 0) {
      a_queue->q_dir      =  '-';
      strcpy (a_queue->q_label, "");
   }
   /*---(handler)------------------------*/
   if (a_type != 0 && strchr ("*i"  , a_type) != 0) {
      a_queue->q_handler  = NULL;
   }
   /*---(master data)--------------------*/
   if (a_type != 0 && strchr ("*ipr", a_type) != 0) {
      a_queue->q_iverb    =   -1;
      a_queue->q_good     =  '-';
      a_queue->q_hidden   =  '-';
   }
   /*---(file)---------------------------*/
   if (a_type != 0 && strchr ("*i"  , a_type) != 0) {
      strcpy (a_queue->q_loc, "");
      a_queue->q_file     = NULL;
   }
   /*---(statistics)---------------------*/
   if (a_type != 0 && strchr ("*ir" , a_type) != 0) {
      a_queue->q_tline    =    0;
      a_queue->q_nline    =    0;
      a_queue->q_cline    =    0;
   }
   /*---(record)-------------------------*/
   if (a_type != 0 && strchr ("*ipr", a_type) != 0) {
      ystrlcpy (a_queue->q_recd , ""     , LEN_RECD);
      a_queue->q_len      =    0;
   }
   /*---(fields)-------------------------*/
   if (a_type != 0 && strchr ("pr", a_type) != 0) {
      x_curr = a_queue->q_head;
      while (x_curr != NULL) {
         yparse_queue_dequeue (a_queue, NULL);
         x_curr = a_queue->q_head;
      }
   }
   /*---(field counters)-----------------*/
   if (a_type != 0 && strchr ("*ipr", a_type) != 0) {
      a_queue->q_head     = NULL;
      a_queue->q_tail     = NULL;
      a_queue->q_count    =    0;
      a_queue->q_first    =   -1;
      a_queue->q_last     =   -1;
      a_queue->q_curr     =    0;
   }
   /*---(complete)-----------------------*/
   return 1;
}

char yparse_queue_purge      (tQUEUE *a_queue) { return yparse_queue__wipe (a_queue, 'p'); }
char yparse_queue_reset      (tQUEUE *a_queue) { return yparse_queue__wipe (a_queue, 'r'); }

char
yparse_queue_init       (tQUEUE *a_queue, char a_dir, char a_label [LEN_SHORT])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_queue == NULL)                                  return rce;
   /*---(purge everything)---------------*/
   yparse_queue__wipe (a_queue, '*');
   /*---(defense)------------------------*/
   --rce;  if (a_dir   == 0    || strchr ("IO", a_dir) == NULL)  return rce;
   --rce;  if (a_label == NULL || a_label [0] == '\0')           return rce;
   /*---(master data)--------------------*/
   a_queue->q_dir      = a_dir;
   ystrlcpy (a_queue->q_label, a_label, LEN_SHORT);
   /*---(complete)-----------------------*/
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        access to files                       ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESS__________________o (void) {;};

char
yparse_queue__defense   (tQUEUE *a_queue, char a_action)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(config check)-------------------*/
   DEBUG_YPARSE  yLOG_schar   (myPARSE.y_ready);
   --rce;  if (myPARSE.y_ready != 'y')  {
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
   /*---(queue action)-------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_action);
   --rce;  if (a_action == 0 || strchr ("<>´", a_action) == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("queue action not understood, <=in, >=out, or ´=neither only");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------*/
   if (a_action == '´') {
      DEBUG_YPARSE  yLOG_snote   ("just a simple check");
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(check direction)----------*/
   DEBUG_YPARSE  yLOG_schar   (a_queue->q_dir);
   --rce;  if (a_queue->q_dir == 0 || strchr ("IO", a_queue->q_dir) == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("queue direction not legal");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(queue label check)--------------*/
   DEBUG_YPARSE  yLOG_snote   (a_queue->q_label);
   l = ystrllen (a_queue->q_label, LEN_SHORT);
   DEBUG_YPARSE  yLOG_sint    (l);
   --rce;  if (l <= 0  || l >= LEN_SHORT) {
      DEBUG_YPARSE  yLOG_snote   ("file label empty or too long (>4 char)");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check loc/file)-----------*/
   DEBUG_YPARSE  yLOG_snote   (a_queue->q_loc);
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_file);
   /*---(check input)--------------*/
   --rce;  if (a_action == '<') {
      if (strcmp (a_queue->q_loc, "") != 0) {
         DEBUG_YPARSE  yLOG_snote   ("file loc already filled");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (a_queue->q_file != NULL) {
         DEBUG_YPARSE  yLOG_snote   ("file already open");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check output)-------------*/
   --rce;  if (a_action == '>') {
      if (strcmp (a_queue->q_loc, "") == 0) {
         DEBUG_YPARSE  yLOG_snote   ("file location is empty");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (a_queue->q_file == NULL) {
         DEBUG_YPARSE  yLOG_snote   ("file already closed");
         DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------*/
   DEBUG_YPARSE  yLOG_snote   ("data apropiate");
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char         /*-> open file for reading and prep -----[ leaf   [ge.723.023.20]*/ /*-[01.0000.013.!]-*/ /*-[--.---.---.--]-*/
yparse_queue_open       (tQUEUE *a_queue, char a_name [LEN_PATH])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      = YENV_NONE;
   char        x_dir       [LEN_SHORT] = "";
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_queue__defense (a_queue, '<');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_info    ("a_name"    , a_name);
   /*---(check for special files)--------*/
   --rce;  switch (a_queue->q_dir) {
   case 'I'  :
      DEBUG_YPARSE  yLOG_note    ("openning for input/reading");
      ystrlcpy (x_dir, "rt", LEN_LABEL);
      if (strcmp ("stdin"  , a_name) == 0) {
         ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
         a_queue->q_file  = stdin;
         DEBUG_YPARSE  yLOG_note    ("stdin is ready");
         DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
         return 2;
      }
      break;
   case 'O'  :
      DEBUG_YPARSE  yLOG_note    ("openning for output/writing");
      ystrlcpy (x_dir, "wt", LEN_LABEL);
      if (strcmp ("stdout" , a_name) == 0) {
         ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
         a_queue->q_file  = stdout;
         DEBUG_YPARSE  yLOG_note    ("stdout is ready");
         DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
         return 3;
      }
      if (strcmp ("unit"   , a_name) == 0) {
         ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
         a_queue->q_file  = NULL;
         DEBUG_YPARSE  yLOG_note    ("unit-testing null file is ready");
         DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
         return 4;
      }
      break;
   }
   /*---(verify file and type)-----------*/
   x_type = yENV_exists (a_name);
   DEBUG_YPARSE  yLOG_char    ("exists"    , x_type);
   --rce;  if (x_type < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_char    ("x_type"    , x_type);
   --rce;  switch (x_type) {
   case YENV_DIR  :
   case YENV_BLOCK: case YENV_CHAR : case YENV_IPSOC: case YENV_PIPE :
   case YENV_WTF  :
      DEBUG_YPARSE  yLOG_note    ("found a specialty filesystem type");
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   case YENV_REG  : case YENV_HARD : case YENV_SYM  :
      DEBUG_YPARSE  yLOG_note    ("found regular file, hardlink, or symlink");
      break;
   case YENV_NONE :
      DEBUG_YPARSE  yLOG_note    ("no file found");
      break;
   }
   /*---(check status)-------------------*/
   --rce;  if (a_queue->q_dir == 'I') {
      if (x_type == YENV_NONE) {
         DEBUG_YPARSE  yLOG_note    ("input file does not exist");
         DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      } else {
         DEBUG_YPARSE  yLOG_note    ("input file exists");
      }
   } else {
      if (x_type == YENV_NONE) {
         DEBUG_YPARSE  yLOG_note    ("ouput file does not exist, will create");
      } else {
         DEBUG_YPARSE  yLOG_note    ("ouput file exists, will overwrite");
      }
   }
   /*---(open file)----------------------*/
   a_queue->q_file = fopen (a_name, x_dir);
   DEBUG_YPARSE  yLOG_point   ("q_file"    , a_queue->q_file);
   --rce;  if (a_queue->q_file == NULL) {
      DEBUG_YPARSE  yLOG_note    ("file could not be openned");
      strcpy (a_queue->q_loc, "");
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------*/
   ystrlcpy (a_queue->q_loc, a_name, LEN_PATH);
   /*---(complete)-----------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> close file for reading and wrap ----[ leaf   [ge.411.011.20]*/ /*-[01.0000.013.!]-*/ /*-[--.---.---.--]-*/
yparse_queue_close      (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_queue__defense (a_queue, '>');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for pipes)----------------*/
   if (strcmp ("stdin" , a_queue->q_loc) == 0) {
      DEBUG_YPARSE  yLOG_note    ("deassigning stdin (not close)");
      a_queue->q_file = NULL;
      strcpy (a_queue->q_loc, "");
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return 2;
   }
   if (strcmp ("stdout", a_queue->q_loc) == 0) {
      DEBUG_YPARSE  yLOG_note    ("deassigning stdout (not close)");
      a_queue->q_file = NULL;
      strcpy (a_queue->q_loc, "");
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return 3;
   }
   if (strcmp ("unit"  , a_queue->q_loc) == 0) {
      DEBUG_YPARSE  yLOG_note    ("deassigning unit (not close)");
      a_queue->q_file = NULL;
      strcpy (a_queue->q_loc, "");
      DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
      return 4;
   }
   /*---(close file)---------------------*/
   DEBUG_YPARSE  yLOG_point   ("q_file"    , a_queue->q_file);
   fclose  (a_queue->q_file);
   strcpy (a_queue->q_loc, "");
   a_queue->q_file = NULL;
   DEBUG_YPARSE  yLOG_point   ("q_file"    , a_queue->q_file);
   /*---(complete)-----------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                   data structure primatives                  ----===*/
/*====================------------------------------------====================*/
static void      o___PRIMATIVE_______________o (void) {;};

char
yparse_queue_enqueue    (tQUEUE *a_queue, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = yparse_queue__defense   (a_queue, '´');
   DEBUG_YPARSE  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   --rce;  if (a_item   == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("nothing to save");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_item);
   /*---(full queue)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_last);
   --rce;  if (a_queue->q_last >= MAX_NODE)  {
      DEBUG_YPARSE  yLOG_snote   ("already full");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   x_new = (tNODE *) malloc (sizeof (tNODE));
   DEBUG_YPARSE  yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("malloc failed");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground pointers)----------------*/
   x_new->n_next = NULL;
   x_new->n_prev = NULL;
   /*---(attatch)------------------------*/
   if (a_queue->q_head == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("first");
      a_queue->q_head       = x_new;
      a_queue->q_tail       = x_new;
   } else  {
      DEBUG_YPARSE  yLOG_snote   ("append");
      a_queue->q_tail->n_next = x_new;
      x_new->n_prev           = a_queue->q_tail;
      a_queue->q_tail         = x_new;
   }
   /*---(update counters)----------------*/
   ++a_queue->q_count;
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_count);
   ++a_queue->q_last;
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_last);
   if (a_queue->q_first <  0) a_queue->q_first = 0;
   if (a_queue->q_count == 1) a_queue->q_first = a_queue->q_last;
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_first);
   /*---(populate)-----------------------*/
   DEBUG_YPARSE  yLOG_snote   ("saving");
   x_new->n_ref  = a_queue->q_last;
   x_new->n_item = strdup (a_item);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char         /*-> remove item from front of queue ----[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_queue_dequeue    (tQUEUE *a_queue, char *r_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_save      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_item != NULL)  strcpy (r_item, "");
   /*---(defense)------------------------*/
   rc = yparse_queue__defense   (a_queue, '´');
   DEBUG_YPARSE  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(empty queue)--------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_count);
   --rce;  if (a_queue->q_count <= 0) {
      DEBUG_YPARSE  yLOG_snote   ("empty, nothing to do");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(empty queue)--------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->q_head);
   --rce;  if (a_queue->q_head == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy and clear)-----------------*/
   if (r_item != NULL)  ystrlcpy (r_item, a_queue->q_head->n_item, LEN_RECD);
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
      x_save  = a_queue->q_head->n_next;
      x_save->n_prev = NULL;
      free (a_queue->q_head);
      a_queue->q_head  = x_save;
   }
   /*---(update counters)----------------*/
   --a_queue->q_count;
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_count);
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_last);
   if (a_queue->q_count > 0)  ++a_queue->q_first;
   DEBUG_YPARSE  yLOG_sint    (a_queue->q_first);
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                         searching methods                    ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;};

char
yparse_queue_count      (tQUEUE *a_queue)
{
   char        rc          =    0;
   rc = yparse_queue__defense   (a_queue, '´');
   if (rc < 0)  return rc;
   return a_queue->q_count;
}

char 
yparse_queue_by_cursor  (tQUEUE *a_queue, char a_dir, char a_seq, tNODE **r_node, char r_item [LEN_RECD], char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    1;
   char        n           =    0;
   char        c           =    0;
   char        x_prev      [LEN_DESC]  = "´·····························";
   char        x_curr      [LEN_DESC]  = "´·····························";
   char        x_next      [LEN_DESC]  = "´·····························";
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_node  != NULL)  *r_node  = NULL;
   if (r_item  != NULL)  strcpy (r_item , "");
   if (d_entry != NULL)  strcpy (d_entry, "");
   /*---(defense)------------------------*/
   rc = yparse_queue__defense   (a_queue, '´');
   DEBUG_YPARSE  yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      if (d_entry != NULL)  strcpy (d_entry, "(run yPARSE_config and yparse_queue_init first)");
      DEBUG_YPARSE  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------------*/
   if (a_dir == 'T') {
      if (d_entry != NULL)  strcpy (d_entry, "seq  ref  ---curr-----------------------  ---prev-----------------------  ---next-----------------------  Ï");
      DEBUG_YDLST   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (d_entry != NULL)  strcpy (d_entry, "··-  ··-  ´·····························  ´·····························  ´·····························  Ï");
   /*---(quick-out)----------------------*/
   DEBUG_YPARSE  yLOG_value   ("q_count"   , a_queue->q_count);
   --rce;  if (a_queue->q_count == 0) {
      if (d_entry != NULL)  strcpy (d_entry, "(empty)");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(preparse)-----------------------*/
   n = a_queue->q_curr;
   DEBUG_YDLST  yLOG_value   ("n"         , n);
   /*---(handle cursor)------------------*/
   DEBUG_YDLST  yLOG_char    ("a_dir"     , a_dir);
   DEBUG_YDLST  yLOG_value   ("a_seq"     , a_seq);
   --rce;  if (a_dir >  0) {
      DEBUG_YDLST  yLOG_note    ("requested cursoring");
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
         n = a_queue->q_count - 1;
         break;
      default         :
         DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(handle index)-------------------*/
   else if (a_seq >= 0) {
      DEBUG_YDLST  yLOG_note    ("requesed indexing");
      n = a_seq;
   }
   /*---(handle trouble)-----------------*/
   else {
      DEBUG_YDLST   yLOG_note    ("neither cursor or index");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle endpoints)---------------*/
   DEBUG_YDLST  yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      if (d_entry != NULL)  strcpy (d_entry, "(under)");
      a_queue->q_curr = 0;
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (n >= MAX_NODE) {
      if (d_entry != NULL)  strcpy (d_entry, "(over)");
      a_queue->q_curr = a_queue->q_count - 1;
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   x_node = a_queue->q_head;
   while (x_node != NULL) {
      DEBUG_YDLST  yLOG_info    ("n_item"    , x_node->n_item);
      if (c == n) {
         DEBUG_YDLST  yLOG_note    ("found it");
         break;
      }
      ++c;
      x_node = x_node->n_next;
   }
   if (x_node == NULL) {
      if (d_entry != NULL)  strcpy (d_entry, "(n/a)");
      DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(save-back)----------------------*/
   a_queue->q_curr = n;
   if (r_node  != NULL)  *r_node  = x_node;
   if (r_item  != NULL)  ystrlcpy (r_item , x_node->n_item, LEN_RECD);
   /*---(output)-------------------------*/
   if (d_entry != NULL) {
      DEBUG_YDLST  yLOG_note    ("requested d_entry");
      if (x_node->n_prev != NULL) {
         if (x_node->n_prev->n_item != NULL) snprintf (x_prev, 31, "%s······························", x_node->n_prev->n_item);
         else                                strcpy   (x_prev, "(null)························");
      }
      if (x_node->n_item != NULL) snprintf (x_curr, 31, "%s······························", x_node->n_item);
      if (x_node->n_next != NULL) {
         if (x_node->n_next->n_item != NULL) snprintf (x_next, 31, "%s······························", x_node->n_next->n_item);
         else                                strcpy   (x_next, "(null)························");
      }
      sprintf (d_entry, "%3d  %3d  %-30.30s  %-30.30s  %-30.30s  Ï", n, x_node->n_ref, x_curr, x_prev, x_next);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}

char* yparse_queue_entry     (tQUEUE *a_queue, char a_dir)                         { yparse_queue_by_cursor (a_queue, a_dir, -1, NULL, NULL, yparse_print); return yparse_print; }
char  yparse_queue_top       (tQUEUE *a_queue, char r_item [LEN_RECD])             { return yparse_queue_by_cursor (a_queue, '[', -1, NULL, r_item, NULL); }
char  yparse_queue_peek      (tQUEUE *a_queue, char a_seq, char r_item [LEN_RECD]) { return yparse_queue_by_cursor (a_queue, -1, a_seq, NULL, r_item, NULL); }

