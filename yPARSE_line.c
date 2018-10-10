/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
typedef     struct      cLINE       tLINE;
struct      cLINE {
   int         line;
   char       *recd;
   int         uses;
   tLINE      *next;
   tLINE      *prev;
};
/*--------- ----------- ----------- ----------- ------------------------------*/
static      tLINE      *s_head      = NULL;
static      tLINE      *s_tail      = NULL;
static      int         s_nline     =    0;



/*====================------------------------------------====================*/
/*===----                      incomming lines                         ----===*/
/*====================------------------------------------====================*/
static void      o___LINES___________________o (void) {;};

char
yPARSE_getline          (const int a_line, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   tLINE      *s_curr      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_recd == NULL)  return rce;
   /*---(prepare)------------------------*/
   strlcpy (a_recd, "", LEN_RECD);
   s_curr = s_tail;
   /*---(find)---------------------------*/
   while (s_curr != NULL) {
      if (a_line == s_curr->line) {
         ++(s_curr->uses);
         strlcpy (a_recd, s_curr->recd, LEN_RECD);
         return 0;
      }
      s_curr = s_curr->prev;
   }
   /*---(complete)-----------------------*/
   return -1;
}

char
yPARSE_addline          (const int a_line, const char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   tLINE      *s_curr      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_recd == NULL)  return rce;
   /*---(create)-------------------------*/
   s_curr = (tLINE *) malloc (sizeof (tLINE));
   --rce;  if (s_curr == NULL)  return rce;
   /*---(defaults)-----------------------*/
   s_curr->line = a_line;
   s_curr->recd = strdup (a_recd);
   s_curr->next = NULL;
   s_curr->prev = NULL;
   s_curr->uses =    0;
   /*---(attatch)------------------------*/
   if (s_head == NULL) {
      s_head  = s_curr;
      s_tail  = s_curr;
      s_nline = 1;
   } else  {
      s_tail->next = s_curr;
      s_curr->prev = s_tail;
      s_tail       = s_curr;
      ++s_nline;
   }
   /*---(complete)-----------------------*/
   return 0;
}

