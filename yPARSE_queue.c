/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*---1----- -----2----- -----3----- -----4----- ----------comments------------*/
/*> typedef     struct      cQUEUE      tQUEUE;                                       <* 
 *> struct      cQUEUE {                                                              <* 
 *>    int         ref;                                                               <* 
 *>    char       *item;                                                              <* 
 *>    tQUEUE     *next;                                                              <* 
 *>    tQUEUE     *prev;                                                              <* 
 *> };                                                                                <* 
 *> static      tQUEUE     *s_head      = NULL;                                       <* 
 *> static      tQUEUE     *s_tail      = NULL;                                       <* 
 *> static      int         s_first     =    0;                                       <* 
 *> static      int         s_count     =    0;                                       <*/



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
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   /*---(defense)------------------------*/
   --rce;  if (a_item   == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("nothing to save");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YPARSE  yLOG_snote   (a_item);
   /*---(create)-------------------------*/
   x_new = (tNODE *) malloc (sizeof (tNODE));
   DEBUG_YPARSE  yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YPARSE  yLOG_snote   ("malloc failed");
      DEBUG_YPARSE  yLOG_sexitr  (__FUNCTION__, rce);
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
   DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> remove item from front of queue ----[ leaf   [fe.A43.223.40]*/ /*-[11.0000.020.!]-*/ /*-[--.---.---.--]-*/
yparse_dequeue          (tQUEUE *a_queue, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_save      = NULL;
   /*---(defense)------------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_item);
   if (a_item != NULL)  strlcpy (a_item, "", LEN_RECD);
   /*---(no entries)---------------------*/
   DEBUG_YPARSE  yLOG_spoint  (a_queue->head);
   --rce;  if (a_queue->head == NULL)  {
      DEBUG_YPARSE  yLOG_snote   ("empty queue");
      return rce;
   }
   /*---(copy and clear)-----------------*/
   if (a_item != NULL)  strlcpy (a_item, a_queue->head->item, LEN_RECD);
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

char
yparse_peek             (tQUEUE *a_queue, const int a_ref, char *a_item)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_curr      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_item == NULL)  return rce;
   /*---(defense)------------------------*/
   strlcpy (a_item, "", LEN_LABEL);
   /*---(search)-------------------------*/
   x_curr = a_queue->head;
   while (x_curr != NULL) {
      if (x_curr->ref == a_ref) {
         strlcpy (a_item, x_curr->item, LEN_RECD);
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
   /*---(walk-through)-------------------*/
   x_curr = a_queue->head;
   while (x_curr != NULL) {
      DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);
      yparse_dequeue (a_queue, NULL);
      x_curr = a_queue->head;
      DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);
   }
   /*---(master data)--------------------*/
   a_queue->good     = '-';
   a_queue->hidden   = '-';
   /*---(clear node variables)-----------*/
   a_queue->head     = NULL;
   a_queue->tail     = NULL;
   a_queue->first    = 0;
   a_queue->count    = 0;
   /*---(complete)-----------------------*/
   return 0;
}

char
yparse_init             (tQUEUE *a_queue, char *a_label)
{
   /*---(name)---------------------------*/
   if (a_label != NULL)  strlcpy (a_queue->label, a_label, LEN_LABEL);
   else                  strlcpy (a_queue->label, "???"  , LEN_LABEL);
   /*---(master data)--------------------*/
   strlcpy (a_queue->verb , ""     , LEN_LABEL);
   a_queue->good     = '-';
   a_queue->hidden   = '-';
   /*---(counts)-------------------------*/
   a_queue->nline    =   0;
   a_queue->cline    =   0;
   /*---(clear node variables)-----------*/
   a_queue->head     = NULL;
   a_queue->tail     = NULL;
   a_queue->first    = 0;
   a_queue->count    = 0;
   /*---(complete)-----------------------*/
   return 0;
}



/*> char yPARSE_push  (char *a_item) { return yparse__enqueue (a_item); }             <*/



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char yPARSE__unit_answer [ LEN_STR  ];

char*      /*----: unit testing accessor for clean validation interface ------*/
yparse__unit_queue      (tQUEUE *a_queue, char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_RECD];
   /*---(preprare)-----------------------*/
   strlcpy  (yPARSE__unit_answer, "QUEUE unit       : question not understood", LEN_STR);
   if (a_queue == NULL) {
      strlcpy  (yPARSE__unit_answer, "QUEUE unit       : queue not specified", LEN_STR);
   }
   /*---(answer)------------------------------------------*/
   if      (strcmp (a_question, "line"     ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s line       : total %2d, curr %2d", a_queue->label, a_queue->nline, a_queue->cline);
   }
   else if (strcmp (a_question, "field"    ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s field      : total %2d, curr %2d", a_queue->label, a_queue->count, a_queue->first);
   }
   else if (strcmp (a_question, "entry"    ) == 0) {
      if (a_queue->count < 1 || a_num < a_queue->first || a_num >= a_queue->count) {
         sprintf (yPARSE__unit_answer, "%-3.3s entry    %d : null", a_queue->label, a_num);
      } else {
         rc = yparse_peek (a_queue, a_num, t);
         if (rc < 0) {
            sprintf (yPARSE__unit_answer, "%-3.3s entry    %d : trouble finding", a_queue->label, a_num);
         } else {
            sprintf (yPARSE__unit_answer, "%-3.3s entry    %d : %2d[%s]", a_queue->label, a_num, strlen (t), t);
         }
      }
   }
   else if (strcmp (a_question, "verb"     ) == 0) {
      sprintf (yPARSE__unit_answer, "%-3.3s verb       : %2d[%s]", a_queue->label, strlen (myPARSE.verb), myPARSE.verb);
   }
   /*---(complete)----------------------------------------*/
   return yPARSE__unit_answer;
}
