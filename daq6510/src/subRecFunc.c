#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <dbDefs.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>

int time2StrDebug;

static long time2StrInit(aSubRecord *precord)
{
    if (time2StrDebug)
        printf("Record %s called time2StrInit(%p)\n",
               precord->name, (void*) precord);
    return 0;
}
static long time2StrProcess(aSubRecord *precord)
{
#define MAXN 80
#define N 20

  time_t result;
  struct tm tm;
  char timestring[MAXN];
  unsigned long tstamp;
  /* 2001-12-31 00:00:00 Labview - 2001-12-31 00:00:00 Unix */
  /* unsigned long offset = 3092601600-1009756800; */
  unsigned long offset = 0;

  if (time2StrDebug > 5) {
    printf("Record %s called time2StrProcess(%p)\n",
	   precord->name, (void*) precord);
    printf ("Input: %i\n", *((int *) precord->a));
    printf ("Fmt string: \"%s\"\n", (char *) precord->b);
  }

  tstamp = *(unsigned long *) precord->a;

  result = tstamp;
  result -= offset;
  localtime_r ((&result), &tm);
  strftime(timestring, MAXN, (char *) precord->b, &tm);
  strncpy ((char *) precord->vala, timestring, 40);
  if (time2StrDebug > 4) {  
    printf ("Output: p->vala: %p: %s\n", (void*) (precord->vala), 
	    (char *)  precord->vala);
    printf ("Old output: %s\n",  (char *)  precord->ovla);
  } 
  return 0;
}

/* Register these symbols for use by IOC code: */
epicsExportAddress(int, time2StrDebug);
epicsRegisterFunction(time2StrInit);
epicsRegisterFunction(time2StrProcess);

