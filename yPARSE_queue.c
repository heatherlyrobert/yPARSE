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
   /*> if (a_type != 0 && strchr ("*ipr", a_type) != 0) {                             <* 
    *>    x_curr = a_queue->q_head;                                                   <* 
    *>    while (x_curr != NULL) {                                                    <* 
    *>       yparse_dequeue (a_queue, NULL);                                          <* 
    *>       x_curr = a_queue->q_head;                                                <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(field counters)-----------------*/
   if (a_type != 0 && strchr ("*ipr", a_type) != 0) {
      a_queue->q_head     = NULL;
      a_queue->q_tail     = NULL;
      a_queue->q_first    =    0;
      a_queue->q_count    =    0;
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
   --rce;  if (a_action == 0 || strchr ("<>", a_action) == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("queue action not understood, <=in or >=out only");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
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
   x_new->n_ref  = a_queue->q_count;
   x_new->n_item = strdup (a_item);
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
      x_save  = a_queue->q_head->n_next;
      x_save->n_prev = NULL;
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
      x_save  = a_queue->q_tail->n_prev;
      x_save->n_next = NULL;
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
      if (x_curr->n_ref == a_ref) {
         ystrlcpy (a_item, x_curr->n_item, LEN_RECD);
         return 0;
      }
      x_curr = x_curr->n_next;
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
      sprintf (yPARSE__unit_answer, "%-3.3s verb         : %2d[%s]", a_queue->q_label, strlen (myPARSE.y_verb), myPARSE.y_verb);
   }
   else if (strcmp (a_question, "written"  ) == 0) {
      yparse_queue__line (a_num, t);
      sprintf (yPARSE__unit_answer, "%-3.3s written (%2d) : %2d[%s]", a_queue->q_label, a_num, strlen (t), t);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}
