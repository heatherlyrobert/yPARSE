/*============================[[    beg-code    ]]============================*/
#include    "yPARSE.h"
#include    "yPARSE_priv.h"



/*====================------------------------------------====================*/
/*===----                   generalize functions                       ----===*/
/*====================------------------------------------====================*/
static void      o___GENERALIZED_____________o (void) {;}

static char
yparse_opener           (uchar a_auto, uchar *a_in, uchar *a_out, void *a_verber, char a_read, char a_reuse)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_complex ("args"      , "%p, %p, %p, %c, %c", a_in, a_out, a_verber, a_read, a_reuse);
   /*---(initialize)---------------------*/
   if (rc == 0) {
      rc = yPARSE_init (a_auto, a_verber, a_reuse);
      DEBUG_YPARSE   yLOG_value   ("init"      , rc);
   }
   if (rc == 0) {
      rc = yPARSE_delimiters (YPARSE_FIELD);
      DEBUG_YPARSE   yLOG_value   ("delimiters", rc);
   }
   /*---(open)---------------------------*/
   --rce;  if (a_in != NULL && a_out != NULL) {
      if (strcmp (a_in, a_out) == 0) {
         DEBUG_YPARSE   yLOG_note    ("input and output file can not be the same");
         rc = rce;
      }
   }
   if (rc == 0 && a_in  != NULL) {
      DEBUG_YPARSE   yLOG_note    ("openning reading file");
      rc = yPARSE_open_in  (a_in);
      DEBUG_YPARSE   yLOG_value   ("open in"   , rc);
   }
   if (rc == 0 && a_out != NULL) {
      DEBUG_YPARSE   yLOG_note    ("openning writing file");
      rc = yPARSE_open_out (a_out, NULL, NULL);
      DEBUG_YPARSE   yLOG_value   ("open out"  , rc);
   }
   /*---(read all)-----------------------*/
   if (rc == 0 && a_read == YPARSE_READALL) {
      rc = yPARSE_read_all ();
      DEBUG_YPARSE   yLOG_value   ("read all"  , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yPARSE_close            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   yPARSE_close_in  ();
   yPARSE_close_out ();
   yPARSE_wrap ();
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      simple interface                        ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE__________________o (void) {;}

char
yPARSE_simple           (uchar *a_in, uchar *a_out)
{
   return yparse_opener (YPARSE_MANUAL, a_in, a_out, NULL, YPARSE_NOREAD, YPARSE_ONETIME);
}

char
yPARSE_printf           (uchar *a_verb, uchar *a_format, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   /*---(handler)------------------------*/
   rc = yPARSE_handler (a_verb, a_format, NULL);
   DEBUG_YPARSE   yLOG_value   ("handler"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verb)---------------------------*/
   rc = yPARSE_pushverb (a_verb);
   DEBUG_YPARSE   yLOG_value   ("verb"      , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(column count)-------------------*/
   n = yparse_specs_len (&s_qout);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   --rce;  if (n < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create variadic)----------------*/
   va_start (x_vlist, a_format);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   /*---(cycle fields)-------------------*/
   rc = yparse_out_variadic (x_vlist, n);
   DEBUG_YPARSE   yLOG_value   ("variadic"  , rc);
   --rce;  if (n < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(destroy variadic)---------------*/
   va_end (x_vlist);
   DEBUG_YPARSE   yLOG_note    ("va_end successful");
   /*---(write)--------------------------*/
   rc = yPARSE_write (NULL, NULL);
   DEBUG_YPARSE   yLOG_value   ("write"     , rc);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yPARSE_scanf            (uchar *a_verb, uchar *a_format, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   rc = yPARSE_handler (a_verb, a_format, NULL);
   DEBUG_YPARSE   yLOG_value   ("handler"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(force verb)---------------------*/
   s_qin.iverb = yparse_verb_find (NULL, a_verb);
   DEBUG_YPARSE   yLOG_value   ("iverb"     , s_qin.iverb);
   --rce;  if (s_qin.iverb < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> yPARSE_toss ();                                                                <*/
   /*---(column count)-------------------*/
   n = yparse_specs_len (&s_qin);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   --rce;  if (n < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create variadic)----------------*/
   va_start (x_vlist, a_format);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   /*---(cycle fields)-------------------*/
   rc = yparse_in_variadic (x_vlist, n);
   DEBUG_YPARSE   yLOG_value   ("variadic"  , rc);
   --rce;  if (n < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(destroy variadic)---------------*/
   va_end (x_vlist);
   DEBUG_YPARSE   yLOG_note    ("va_end successful");
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     auto-read interface                      ----===*/
/*====================------------------------------------====================*/
static void      o___AUTO_READ_______________o (void) {;}

char
yPARSE_autoread         (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_MANUAL, a_in, a_out, a_verber, YPARSE_READALL, YPARSE_ONETIME);
}

char
yparse_autoread_manual  (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_MANUAL, a_in, a_out, a_verber, YPARSE_NOREAD, YPARSE_ONETIME);
}



/*====================------------------------------------====================*/
/*===----                      planned interface                       ----===*/
/*====================------------------------------------====================*/
static void      o___PLANNED_________________o (void) {;}

char
yPARSE_planned          (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_AUTO, a_in, a_out, a_verber, YPARSE_NOREAD , YPARSE_ONETIME);
}

char
yPARSE_header           (uchar *a_full, uchar *a_desc, uchar *a_title, uchar *a_vernum, uchar *a_vertxt, int a_epoch)
{
   return 0;
}

char
yPARSE_handler          (uchar *a_verb, char *a_specs, void *a_reader)
{
   return yPARSE_handler_max ('-', a_verb, 0.0, a_specs, -1, a_reader, NULL, NULL, NULL, NULL);
}

char
yPARSE_handler_plus    (uchar *a_verb, uchar *a_specs, float a_seq, void *a_reader, void *a_writer, uchar *a_labels)
{
   return yPARSE_handler_max ('-', a_verb, a_seq, a_specs, -1, a_reader, a_writer, NULL, a_labels, NULL);
}

char
yPARSE_vscanf           (uchar *a_verb, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =  -10;
   char        n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check on verb)------------------*/
   --rce;  if (s_qin.first == 0) {
      s_qin.iverb = yparse_verb_find (NULL, a_verb);
      DEBUG_YPARSE   yLOG_value   ("iverb"     , s_qin.iverb);
      if (s_qin.iverb < 0)  {
         DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yPARSE_toss ();
   }
   /*---(column count)-------------------*/
   n = yparse_specs_len (&s_qin);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   /*---(cycle columns)------------------*/
   va_start (x_vlist, a_verb);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   rc = yparse_in_variadic (x_vlist, n);
   va_end (x_vlist);
   s_qin.good = 'R';
   /*---(complete)-----------------------*/
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yPARSE_vprintf        (uchar *a_verb, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   va_list     x_vlist;
   /*---(header)-------------------------*/
   DEBUG_YPARSE  yLOG_enter   (__FUNCTION__);
   /*---(verb)---------------------------*/
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   if (a_verb != NULL) DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
   rc = yPARSE_pushverb (a_verb);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(column count)-------------------*/
   n = yparse_specs_len (&s_qout);
   DEBUG_YPARSE   yLOG_value   ("ncol"      , n);
   /*---(call variadic)------------------*/
   va_start (x_vlist, a_verb);
   DEBUG_YPARSE   yLOG_note    ("va_start successful");
   yparse_out_variadic (x_vlist, n);
   va_end (x_vlist);
   /*---(write)--------------------------*/
   rc = yPARSE_write (NULL, NULL);
   if (rc < 0)  {
      DEBUG_YPARSE   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YPARSE  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      reusing interface                       ----===*/
/*====================------------------------------------====================*/
static void      o___REUSING_________________o (void) {;}

char
yPARSE_reusing          (uchar *a_in, uchar *a_out, void *a_verber)
{
   return yparse_opener (YPARSE_AUTO, a_in, a_out, a_verber, YPARSE_NOREAD , YPARSE_REUSING);
}



/*====================------------------------------------====================*/
/*===----                      mock test helpers                       ----===*/
/*====================------------------------------------====================*/
static void      o___MOCK_TEST_______________o (void) {;}

static char    *i_verb        [LEN_LABEL];
static char    *i_label       [LEN_LABEL];
static char    *i_terse       [LEN_TERSE];
static int      i_int         = 0;
static llong    i_long        = 0;
static float    i_float       = 0.0;
static double   i_double      = 0.0;
static char     i_char        = 0;
static double   i_exp         = 0.0;
static char    *i_desc        [LEN_DESC];
static char    *i_string      [LEN_RECD];

static char    *s_verb           = NULL;
static char    *s_label          = NULL;
static char    *s_terse          = NULL;
static int     *s_int            = NULL;
static llong   *s_long           = NULL;
static float   *s_float          = NULL;
static double  *s_double         = NULL;
static char    *s_char           = NULL;
static double  *s_exp            = NULL;
static char    *s_desc           = NULL;
static char    *s_string         = NULL;

#define    MAX_MOCK   50
static struct {
   char       *d_verb      [LEN_LABEL];
   char       *d_label     [LEN_LABEL];
   char        d_terse     [LEN_TERSE];
   int         d_int;
   llong       d_long;
   float       d_float;
   double      d_double;
   char        d_char;
   double      d_exp;
   char       *d_desc      [LEN_DESC];
   char       *d_string    [LEN_RECD];
} s_mocks [MAX_MOCK];
static char   s_nmock   = 0;

char
yparse__mock_clear      (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      strlcpy (s_mocks [i].d_verb      , "", LEN_LABEL);
      strlcpy (s_mocks [i].d_label     , "", LEN_LABEL);
      strlcpy (s_mocks [i].d_terse     , "", LEN_LABEL);
      s_mocks [i].d_int       = 0;
      s_mocks [i].d_long      = 0;
      s_mocks [i].d_float     = 0.0;
      s_mocks [i].d_double    = 0.0;
      s_mocks [i].d_char      = 0;
      s_mocks [i].d_exp       = 0.0;
      strlcpy (s_mocks [i].d_desc      , "", LEN_DESC);
      strlcpy (s_mocks [i].d_string    , "", LEN_RECD);
   }
   s_nmock = 0;
   return 0;
}

char
yparse__mock_external   (char *a_verb, char *a_label, char *a_terse, int *a_int, llong *a_long, float *a_float, double *a_double, char *a_char, double *a_exp, char *a_desc, char *a_str)
{
   s_verb    = a_verb;
   s_label   = a_label;
   s_terse   = a_terse;
   s_int     = a_int;
   s_long    = a_long;
   s_float   = a_float;
   s_double  = a_double;
   s_char    = a_char;
   s_exp     = a_exp;
   s_desc    = a_desc;
   s_string  = a_str;
   return 0;
}

char
yparse__mock_internal   (void)
{
   s_verb    = i_verb;
   s_label   = i_label;
   s_terse   = i_terse;
   s_int     = &i_int;
   s_long    = &i_long;
   s_float   = &i_float;
   s_double  = &i_double;
   s_char    = &i_char;
   s_exp     = &i_exp;
   s_desc    = i_desc;
   s_string  = i_string;
   return 0;
}

char
yparse__mock_verber     (int n, uchar *a_verb, char a_exist, void *a_handler)
{
   char rc = 0;
   strlcpy (s_verb, a_verb, LEN_USER);
   if      (strcmp (a_verb, "tiny"    ) == 0) {
      rc = yPARSE_scanf  (a_verb, "i"         , s_int);
      yPARSE_printf ("tiny"     , "i"         , *s_int);
   }
   else if (strcmp (a_verb, "small"   ) == 0) {
      rc = yPARSE_scanf  (a_verb, "TL"        , s_terse, s_label);
      yPARSE_printf ("small"    , "TL"        , s_terse, s_label);
   }
   else if (strcmp (a_verb, "medium"  ) == 0) {
      rc = yPARSE_scanf  (a_verb, "TidcO"     , s_terse, s_int, s_double, s_char, s_string);
      yPARSE_printf ("medium"   , "TidcO"     , s_terse, *s_int, *s_double, *s_char, s_string);
   }
   else if (strcmp (a_verb, "large"   ) == 0) {
      rc = yPARSE_scanf  (a_verb, "LTfdcileLO", s_label, s_terse, s_float, s_double, s_char, s_int, s_long, s_exp, s_desc, s_string);
      yPARSE_printf ("large"    , "LTfdcileLO", s_label, s_terse, *s_float, *s_double, *s_char, *s_int, *s_long, *s_exp, s_desc, s_string);
   }
   else if (strcmp (a_verb, "sample"  ) == 0) {
      rc = yPARSE_scanf  (a_verb, "LifcO"     , s_label, s_int, s_float, s_char, s_desc);
      yPARSE_printf ("sample"   , "LifcO"     , s_label, *s_int, *s_float, *s_char, s_desc);
   }
   else {
      rc = -100;
   }
   return rc;
}

char
yparse__mock_rtiny      (int n, uchar *a_verb)
{
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   if (a_verb != NULL) DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
   yPARSE_vscanf (a_verb, s_int);
   strlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   s_mocks [s_nmock].d_int     = *s_int;
   ++s_nmock;
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yparse__mock_wtiny      (int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   DEBUG_YPARSE   yLOG_enter   (__FUNCTION__);
   DEBUG_YPARSE   yLOG_point   ("a_verb"    , a_verb);
   if (a_verb != NULL) DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
   for (i = 0; i < MAX_MOCK; ++i) {
      DEBUG_YPARSE   yLOG_info    ("check"     , s_mocks [i].d_verb);
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      DEBUG_YPARSE  yLOG_info    ("a_verb"    , a_verb);
      yPARSE_vprintf (a_verb, s_mocks [i].d_int);
      ++c;
   }
   DEBUG_YPARSE   yLOG_exit    (__FUNCTION__);
   return c;
}

char
yparse__mock_rsmall     (int n, uchar *a_verb)
{
   yPARSE_vscanf (a_verb, s_terse, s_label);
   strlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   strlcpy (s_mocks [s_nmock].d_terse     , s_terse   , LEN_TERSE);
   strlcpy (s_mocks [s_nmock].d_label     , s_label   , LEN_LABEL);
   ++s_nmock;
   return 0;
}

char
yparse__mock_wsmall     (int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      yPARSE_vprintf (a_verb, s_mocks [i].d_terse, s_mocks [i].d_label);
      ++c;
   }
   return c;
}

char
yparse__mock_rmedium    (int n, uchar *a_verb)
{
   yPARSE_vscanf (a_verb, s_terse, s_int, s_double, s_char, s_string);
   strlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   strlcpy (s_mocks [s_nmock].d_terse     , s_terse   , LEN_TERSE);
   s_mocks [s_nmock].d_int     = *s_int;
   s_mocks [s_nmock].d_double  = *s_double;
   s_mocks [s_nmock].d_char    = *s_char;
   strlcpy (s_mocks [s_nmock].d_string    , s_string  , LEN_RECD);
   ++s_nmock;
   return 0;
}

char
yparse__mock_wmedium    (int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      yPARSE_vprintf (a_verb, s_mocks [i].d_terse, s_mocks [i].d_int, s_mocks [i].d_double, s_mocks [i].d_char, s_mocks [i].d_string);
      ++c;
   }
   return c;
}

char
yparse__mock_rlarge     (int n, uchar *a_verb)
{
   yPARSE_vscanf (a_verb, s_terse, s_int, s_double, s_char, s_string);
   strlcpy (s_mocks [s_nmock].d_verb      , a_verb    , LEN_LABEL);
   strlcpy (s_mocks [s_nmock].d_terse     , s_terse   , LEN_TERSE);
   strlcpy (s_mocks [s_nmock].d_label     , s_label   , LEN_LABEL);
   s_mocks [s_nmock].d_float   = *s_float;
   s_mocks [s_nmock].d_double  = *s_double;
   s_mocks [s_nmock].d_char    = *s_char;
   s_mocks [s_nmock].d_int     = *s_int;
   s_mocks [s_nmock].d_long    = *s_long;
   s_mocks [s_nmock].d_exp     = *s_exp;
   strlcpy (s_mocks [s_nmock].d_desc      , s_desc    , LEN_DESC);
   strlcpy (s_mocks [s_nmock].d_string    , s_string  , LEN_RECD);
   ++s_nmock;
   return 0;
}

char
yparse__mock_wlarge     (int n, uchar *a_verb)
{
   int         i           =    0;
   int         c           =    0;
   for (i = 0; i < MAX_MOCK; ++i) {
      if (strcmp (s_mocks [i].d_verb, a_verb) != 0)  continue;
      yPARSE_vprintf (a_verb, s_mocks [i].d_terse, s_mocks [i].d_label, s_mocks [i].d_float, s_mocks [i].d_double, s_mocks [i].d_char, s_mocks [i].d_int, s_mocks [i].d_long, s_mocks [i].d_exp, s_mocks [i].d_desc, s_mocks [i].d_string);
      ++c;
   }
   return c;
}



