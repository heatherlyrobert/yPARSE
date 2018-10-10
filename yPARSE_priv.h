/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"




extern char yPARSE__unit_answer [ LEN_STR  ];


typedef  struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   int         logger;                          /* yURG debugging handle      */
};
extern   tACCESSOR  myPARSE;


/*--------- ----------- ----------- ----------- ------------------------------*/
char        yparse__enqueue         (char *a_item);
char        yparse__dequeue         (char *a_item);

char        yparse__popable         (void);

char*       yparse__unit_queue      (char *a_question, int a_num);


char        yparse__unit_quiet      (void);
char        yparse__unit_loud       (void);
char        yparse__unit_end        (void);
