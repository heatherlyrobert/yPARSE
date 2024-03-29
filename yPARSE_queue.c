/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



typedef     struct stat       tSTAT;



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
   x_new->ref  = a_queue->count;
   x_new->item = strdup (a_item);
   x_new->next = NULL;
   x_new->prev = NULL;
   /*---(attatch)------------------------*/
   if (a_queue->head == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("first");
      a_queue->head       = x_new;
      a_queue->tail       = x_new;
   } else  {
      DEBUG_YPARSE  yLOG_snote   ("append");
      a_queue->tail->next = x_new;
      x_new->prev         = a_queue->tail;
      a_queue->tail       = x_new;
   }
   ++a_queue->count;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (a_queue->first);
   DEBUG_YPARSE  yLOG_sint    (a_queue->count);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> add item to end of queue -----------[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_enqueue_full     (tQUEUE *a_queue, char *a_item)
{
   char        rc          =    0;
   DEBUG_FILE   yLOG_senter  (__FUNCTION__);
   rc = yparse_enqueue (a_queue, a_item);
   if (rc < 0) {
      DEBUG_FILE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YPARSE  yLOG_spoint  (a_queue->head);
   --rce;  if (a_queue->head == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(copy and clear)-----------------*/
   if (a_item != NULL)  ystrlcpy (a_item, a_queue->head->item, LEN_RECD);
   if (a_queue->head->item != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("free item");
      free (a_queue->head->item);
   }
   /*---(single entry)-------------------*/
   if (a_queue->tail == a_queue->head) {
      DEBUG_YPARSE  yLOG_snote   ("single item");
      free (a_queue->head);
      a_queue->tail  = a_queue->head = NULL;
   }
   /*---(multi entry)--------------------*/
   else {
      DEBUG_YPARSE  yLOG_snote   ("multiple items");
      x_save  = a_queue->head->next;
      x_save->prev = NULL;
      free (a_queue->head);
      a_queue->head  = x_save;
   }
   ++a_queue->first;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (a_queue->first);
   DEBUG_YPARSE  yLOG_sint    (a_queue->count);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> add item to end of queue -----------[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_dequeue_full     (tQUEUE *a_queue, char *a_item)
{
   char        rc          =    0;
   DEBUG_FILE   yLOG_senter  (__FUNCTION__);
   rc = yparse_dequeue (a_queue, a_item);
   if (rc < 0) {
      DEBUG_FILE   yLOG_sexitr  (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YPARSE  yLOG_spoint  (a_queue->head);
   --rce;  if (a_queue->head == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(copy)---------------------------*/
   if (a_item != NULL)  ystrlcpy (a_item, a_queue->head->item, LEN_RECD);
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
   DEBUG_YPARSE  yLOG_spoint  (a_queue->tail);
   --rce;  if (a_queue->tail == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(check for empty)----------------*/
   if (a_queue->tail->item != NULL && strlen (a_queue->tail->item) > 0) {
      DEBUG_YPARSE  yLOG_snote   ("real item at tail, done");
      return 0;
   }
   /*---(clear)--------------------------*/
   if (a_queue->tail->item != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("free item");
      free (a_queue->tail->item);
   }
   /*---(single entry)-------------------*/
   if (a_queue->head == a_queue->tail) {
      DEBUG_YPARSE  yLOG_snote   ("single item");
      free (a_queue->head);
      a_queue->head  = a_queue->tail = NULL;
   }
   /*---(multi entry)--------------------*/
   else {
      DEBUG_YPARSE  yLOG_snote   ("multiple items");
      x_save  = a_queue->tail->prev;
      x_save->next = NULL;
      free (a_queue->tail);
      a_queue->tail  = x_save;
   }
   --a_queue->count;
   /*---(report)-------------------------*/
   DEBUG_YPARSE  yLOG_sint    (a_queue->first);
   DEBUG_YPARSE  yLOG_sint    (a_queue->count);
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
   x_curr = a_queue->head;
   while (x_curr != NULL) {
      if (x_curr->ref == a_ref) {
         ystrlcpy (a_item, x_curr->item, LEN_RECD);
         return 0;
      }
      x_curr = x_curr->next;
   }
   /*---(complete)-----------------------*/
   return -1;
}



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;};

char
yparse_purge            (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----+-----+-*/
   tNODE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(walk-through)-------------------*/
   x_curr = a_queue->head;
   while (x_curr != NULL) {
      yparse_dequeue_full (a_queue, NULL);
      x_curr = a_queue->head;
   }
   /*---(master data)--------------------*/
   a_queue->iverb    =   -1;
   a_queue->good     =  '-';
   a_queue->hidden   =  '-';
   /*---(record)-------------------------*/
   ystrlcpy (a_queue->recd , ""     , LEN_RECD);
   a_queue->len      =    0;
   /*---(fields)-------------------------*/
   a_queue->head     = NULL;
   a_queue->tail     = NULL;
   a_queue->first    =    0;
   a_queue->count    =    0;
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse_reset            (tQUEUE *a_queue)
{
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   yparse_purge (a_queue);
   /*---(file)---------------------------*/
   a_queue->tline    =    0;
   a_queue->nline    =    0;
   a_queue->cline    =    0;
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;

}

char
yparse_init             (tQUEUE *a_queue, char *a_label)
{
   /*---(name)---------------------------*/
   if (a_label != NULL)  ystrlcpy (a_queue->label, a_label, LEN_LABEL);
   else                  ystrlcpy (a_queue->label, "???"  , LEN_LABEL);
   /*---(master data)--------------------*/
   a_queue->iverb    =   -1;
   a_queue->good     =  '-';
   a_queue->hidden   =  '-';
   /*---(file)---------------------------*/
   a_queue->loc      = NULL;
   a_queue->file     = NULL;
   a_queue->tline    =    0;
   a_queue->nline    =    0;
   a_queue->cline    =    0;
   /*---(record)-------------------------*/
   ystrlcpy (a_queue->recd , ""     , LEN_RECD);
   a_queue->len      =    0;
   /*---(fields)-------------------------*/
   a_queue->head     = NULL;
   a_queue->tail     = NULL;
   a_queue->first    =    0;
   a_queue->count    =    0;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___FILES___________________o (void) {;};

char
yparse__check           (char *a_name, char a_mode)
{  /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rci         =    0;
   tSTAT       st;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_FILE   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("a_name"    , a_name);
   DEBUG_FILE   yLOG_char    ("a_mode"    , a_mode);
   --rce;  if (a_mode == 0 || strchr ("IO", a_mode) == NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get the file information)-------*/
   rci = lstat (a_name, &st);
   DEBUG_FILE   yLOG_value   ("lstat"     , rci);
   --rce; if (rci < 0) {
      if (a_mode == 'I') {
         DEBUG_FILE   yLOG_note    ("file does not exist, can not read");
         DEBUG_FILE   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      DEBUG_FILE   yLOG_note    ("writing data to a brand new file");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return 0;
   } else {
      if (a_mode == 'O') {
         DEBUG_FILE   yLOG_note    ("file exists, writing over existing file");
      }
   }
   /*---(check regular file)-------------*/
   --rce;  if (S_ISREG (st.st_mode)) {
      DEBUG_FILE   yLOG_note    ("refers to a regular file, perfect");
   }
   /*---(check symlink)------------------*/
   else if (S_ISLNK (st.st_mode)) {
      DEBUG_FILE   yLOG_note    ("file can not be a symlink to another file");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   else  {
      if      (S_ISDIR (st.st_mode)) {
         DEBUG_FILE   yLOG_note    ("file is a directory, not allowwed");
      } else if (S_ISCHR (st.st_mode)) {
         DEBUG_FILE   yLOG_note    ("file is a char dev, not allowwed");
      } else if (S_ISBLK (st.st_mode)) {
         DEBUG_FILE   yLOG_note    ("file is a block dev, not allowwed");
      } else if (S_ISFIFO(st.st_mode)) {
         DEBUG_FILE   yLOG_note    ("file is a fifo/pipe, not allowwed");
      } else if (S_ISSOCK(st.st_mode)) {
         DEBUG_FILE   yLOG_note    ("file is a socket, not allowwed");
      } else  {
         DEBUG_FILE   yLOG_note    ("file is not recognized, not allowwed");
      }
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse__openclose       (tQUEUE *a_queue)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   /*---(defense)------------------------*/
   --rce;  if (myPARSE.ready != 'y')  {
      DEBUG_YPARSE   yLOG_snote   ("must call yPARSE_config () first");
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_queue);
   --rce;  if (a_queue == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("null queue");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = ystrllen (a_queue->label, LEN_LABEL);
   DEBUG_YPARSE  yLOG_sint    (x_len);
   --rce;  if (x_len <= 0  || x_len >= LEN_LABEL) {
      DEBUG_YPARSE  yLOG_snote   ("file label empty");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_queue->label);
   /*---(complete)-----------------*/
   return 0;
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
   rc = yparse__openclose (a_queue);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_queue->loc);
   --rce;  if (a_queue->loc != NULL) {
      DEBUG_YPARSE  yLOG_snote   ("file loc already filled");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_queue->file);
   --rce;  if (a_queue->file != NULL) {
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
   --rce;  switch (a_queue->label [0]) {
   case 'I'  :
      DEBUG_YPARSE  yLOG_snote   ("reading");
      ystrlcpy (x_dir, "rt", LEN_LABEL);
      if (strcmp ("stdin"  , a_name) == 0) {
         a_queue->file  = stdin;
         a_queue->loc   = strdup (a_name);
         DEBUG_YPARSE  yLOG_snote   ("ready");
         DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      break;
   case 'O'  :
      DEBUG_YPARSE  yLOG_snote   ("writing");
      ystrlcpy (x_dir, "wt", LEN_LABEL);
      if (strcmp ("stdout" , a_name) == 0) {
         a_queue->file  = stdout;
         a_queue->loc   = strdup (a_name);
         DEBUG_YPARSE  yLOG_snote   ("ready");
         DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      if (strcmp ("unit"   , a_name) == 0) {
         a_queue->file  = NULL;
         a_queue->loc   = strdup (a_name);
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
   rc = yparse__check (a_name, a_queue->label [0]);
   DEBUG_YPARSE  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   ("successful");
   /*> --rce;  if (a_queue->label [0] == 'I') {                                       <* 
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
   a_queue->file = fopen (a_name, x_dir);
   DEBUG_YPARSE  yLOG_spoint  (a_queue->file);
   --rce;  if (a_queue->file == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("could not be openned");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   ("successful");
   /*---(prepare)------------------*/
   DEBUG_YPARSE  yLOG_snote   ("globals");
   a_queue->loc   = strdup (a_name);
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
   rc = yparse__openclose (a_queue);
   --rce;  if (rc < 0) {
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_spoint  (a_queue->loc);
   --rce;  if (a_queue->loc == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("file loc empty");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_queue->loc);
   DEBUG_YPARSE  yLOG_spoint  (a_queue->file);
   --rce;  if (a_queue->file == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("file already closed");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for pipes)----------------*/
   if (strcmp ("stdin" , a_queue->loc) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("stdin");
      a_queue->file = NULL;
      free (a_queue->loc);
      a_queue->loc  = NULL;
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   if (strcmp ("stdout", a_queue->loc) == 0) {
      DEBUG_YPARSE  yLOG_snote   ("stdout");
      a_queue->file = NULL;
      free (a_queue->loc);
      a_queue->loc  = NULL;
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(close file)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->file);
   if (a_queue->file == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("nothing to do");
   } else {
      DEBUG_YPARSE  yLOG_snote   ("close file");
      fclose  (a_queue->file);
   }
   a_queue->file = NULL;
   /*---(prepare)------------------*/
   DEBUG_YPARSE  yLOG_snote   ("globals");
   free (a_queue->loc);
   a_queue->loc  = NULL;
   /*---(complete)-----------------*/
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
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
   DEBUG_RPTG   yLOG_info    ("file"      , s_qout.loc);
   if (s_qout.loc != NULL)  f = fopen (s_qout.loc, "rt");
   else                     f = fopen ("/tmp/yPARSE_out.txt", "rt");
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
      sprintf (yPARSE__unit_answer, "%-3.3s verb         : %2d[%s]", a_queue->label, a_queue->iverb, yPARSE_verb (a_queue->iverb));
   }
   else if (strcmp (a_question, "line"     ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s line         : total %2d, curr %2d", a_queue->label, a_queue->nline, a_queue->cline);
   }
   else if (strcmp (a_question, "field"    ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s field        : total %2d, curr %2d, good %c", a_queue->label, a_queue->count, a_queue->first, a_queue->good);
   }
   else if (strcmp (a_question, "record"   ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s record       : %2d[%s]", a_queue->label, a_queue->len, a_queue->recd);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      if (a_queue->count < 1 || a_num < a_queue->first || a_num >= a_queue->count) {
         sprintf (yPARSE__unit_answer, "%-3.3s entry   (%2d) : null", a_queue->label, a_num);
      } else {
         rc = yparse_peek (a_queue, a_num, t);
         if (rc < 0) {
            sprintf (yPARSE__unit_answer, "%-3.3s entry   (%2d) : trouble finding", a_queue->label, a_num);
         } else {
            sprintf (yPARSE__unit_answer, "%-3.3s entry   (%2d) : %2d[%s]", a_queue->label, a_num, strlen (t), t);
         }
      }
   }
   else if (strcmp (a_question, "verb"     ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s verb         : %2d[%s]", a_queue->label, strlen (myPARSE.verb), myPARSE.verb);
   }
   else if (strcmp (a_question, "written"  ) == 0) {
      yparse_queue__line (a_num, t);
      sprintf (yPARSE__unit_answer, "%-3.3s written (%2d) : %2d[%s]", a_queue->label, a_num, strlen (t), t);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}
