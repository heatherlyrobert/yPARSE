/*============================[[    beg-code    ]]============================*/
/*········´ ´·············headers·´ ´·········································*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yparse__unit_quiet      (void)
{
   yparse_config_clear ();
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [ 1]  = {"yPARSE_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("yparse", 'y');
   yURG_by_name  ("ystr"  , 'y');
   yparse_config_clear ();
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yparse__unit_end        (void)
{
   yLOGS_end     ();
   return 0;
}

char*
yparse_config_status    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_ready     [LEN_TERSE] = "FROZEN·";
   char        x_verbs     [LEN_TERSE] = "manual·";
   char        x_reuse     [LEN_TERSE] = "onetime";
   char        x_in        [LEN_PATH]  = "";
   char        x_out       [LEN_PATH]  = "";
   char        x_del       [LEN_LABEL] = "´·········";
   char        x_ver       [LEN_TERSE] = "···";
   char        x_fill      [LEN_TERSE] = "´·····";
   yPARSE_qin_info   (NULL, x_in , NULL, NULL);
   yPARSE_qout_info  (NULL, x_out, NULL, NULL);
   if      (myPARSE.y_ready   == 'y')            strcpy (x_ready , "ready··");
   if      (myPARSE.y_verbs   == YPARSE_AUTO  )  strcpy (x_verbs , "auto···");
   else if (myPARSE.y_verbs   == YPARSE_SIMPLE)  strcpy (x_verbs , "simple·");
   if      (myPARSE.y_reusing == YPARSE_REUSING) strcpy (x_reuse , "reusing");
   if      (strcmp (myPARSE.y_dellist, YPARSE_FIELDS)     == 0)  strcpy (x_del, "field·····");
   else if (strcmp (myPARSE.y_dellist, YPARSE_FUNCTIONS)  == 0)  strcpy (x_del, "function··");
   else if (strcmp (myPARSE.y_dellist, YPARSE_TRADITIONS) == 0)  strcpy (x_del, "tradition·");
   else if (strcmp (myPARSE.y_dellist, "")                != 0)  strcpy (x_del, "custom····");
   if      (myPARSE.y_verber != NULL)  strcpy (x_ver , "SET");
   if      (myPARSE.y_fill   == YPARSE_FILL)   strcpy (x_fill, "fill··");
   if (strcmp (x_in , "") == 0)   strcpy (x_in  , "····················");
   if (strcmp (x_out, "") == 0)   strcpy (x_out , "····················");
   sprintf (yPARSE__unit_answer, "%c/%-7.7s  %c/%-7.7s  verber %-3.3s  %c/%-7.7s  ·inå%-20.20sæ  outå%-20.20sæ  %c/%-10.10s %c/%-6.6s  Ï",
         myPARSE.y_ready, x_ready, myPARSE.y_verbs, x_verbs, x_ver, myPARSE.y_reusing, x_reuse,
         x_in, x_out, myPARSE.y_deltype, x_del, myPARSE.y_fill, x_fill);
   return yPARSE__unit_answer;
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
yparse_queue_status     (tQUEUE *a_queue)
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
