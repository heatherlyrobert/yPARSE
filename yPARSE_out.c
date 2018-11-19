/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



static      tQUEUE      out;



/*> char                                                                              <* 
 *> yparse_queue_init       (tQUEUE *a_queue)                                         <* 
 *> {                                                                                 <* 
 *>    /+---(initialize)---------------------+/                                       <* 
 *>    a_queue->head     = NULL;                                                      <* 
 *>    a_queue->tail     = NULL;                                                      <* 
 *>    a_queue->first    = 0;                                                         <* 
 *>    a_queue->count    = 0;                                                         <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> yparse_queue_purge      (tQUEUE *a_queue)                                         <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    tNODE      *x_curr      = NULL;                                                <* 
 *>    /+---(walk-through)-------------------+/                                       <* 
 *>    x_curr = a_queue->head;                                                        <* 
 *>    while (x_curr != NULL) {                                                       <* 
 *>       DEBUG_YPARSE  yLOG_senter  (__FUNCTION__);                                  <* 
 *>       yparse_dequeue (a_queue, NULL);                                             <* 
 *>       x_curr = a_queue->head;                                                     <* 
 *>       DEBUG_YPARSE  yLOG_sexit   (__FUNCTION__);                                  <* 
 *>    }                                                                              <* 
 *>    /+---(initialize)---------------------+/                                       <* 
 *>    yparse_in_init  (a_queue);                                                     <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/
