/*--------------------------------------------------------------------*/
/* ishlex.c                                                           */
/* Author: Jingran Zhou                                               */
/*--------------------------------------------------------------------*/

#include "dynarray.h"
#include "token.h"
#include "ish.h"
#include "lexAnalyzer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------------*/

/* The name of the executable binary file. */
static const char *pcPgmName;

/*--------------------------------------------------------------------*/

/* Return the value of the global variable pcPgmName, which means the 
   name of the program. */

const char* getPgmName()
{
   assert(pcPgmName != NULL);

   return pcPgmName;
}

/*--------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   char *pcLine;
   DynArray_T oTokens;
   int iRet;

   pcPgmName = argv[0];

   printf("%% ");
   while ((pcLine = LexAnalyzer_readLine(stdin)) != NULL)
   {
      printf("%s\n", pcLine);
      iRet = fflush(stdout);
      if (iRet == EOF)
         {perror(pcPgmName); exit(EXIT_FAILURE);}
      /* Lexical analysis. */
      oTokens = LexAnalyzer_lexLine(pcLine);
      if (oTokens != NULL)
      {
         LexAnalyzer_writeTokens(oTokens);
         LexAnalyzer_freeTokens(oTokens);
         DynArray_free(oTokens);
      }

      free(pcLine);
      printf("%% ");
   }
   printf("\n");
   return 0;
}
