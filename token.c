/*--------------------------------------------------------------------*/
/* token.h                                                            */
/* Author: Jingran Zhou                                               */
/*--------------------------------------------------------------------*/

#include "token.h"
#include "ish.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/*--------------------------------------------------------------------*/

/* A- Token is either a number or a word, expressed as a string. */
struct Token
{
   /* The type of the token. */
   enum TokenType eType;

   /* The string which is the token's value. */
   char *pcValue;
};

/*--------------------------------------------------------------------*/

#ifndef NDEBUG

/* Check the invariants of oToken. Return 1 (TRUE) iff oToken is valid 
   and 0 (FALSE) otherwise. */

static int Token_isValid(Token_T oToken)
{
   if (oToken->eType != TOKEN_SPECIAL &&
       oToken->eType != TOKEN_ORDINARY) return 0;
   if (oToken->pcValue == NULL) return 0;
   return 1;
}

#endif

/*--------------------------------------------------------------------*/

/* Return the token type of oToken. */

enum TokenType Token_getType(Token_T oToken)
{
   assert(oToken != NULL);
   assert(Token_isValid(oToken));

   return oToken->eType;
}

/*--------------------------------------------------------------------*/

/* Return the value of oToken, which is a string. */

char* Token_getString(Token_T oToken)
{
   assert(oToken != NULL);
   assert(Token_isValid(oToken));

   return oToken->pcValue;
}

/*--------------------------------------------------------------------*/

/* Set the type of oToken to eNewType. */

void Token_setType(Token_T oToken, enum TokenType eNewType)
{
   assert(oToken != NULL);
   assert(Token_isValid(oToken));
   assert(eNewType == TOKEN_SPECIAL || eNewType == TOKEN_ORDINARY);
   
   oToken->eType = eNewType;
   assert(Token_isValid(oToken));
}

/*--------------------------------------------------------------------*/

/* Print oToken properly. */

void Token_print(Token_T oToken)
{
   assert(oToken != NULL);
   assert(Token_isValid(oToken));
   
   if (oToken->eType == TOKEN_ORDINARY)
      printf("Token: %s (ordinary)\n", oToken->pcValue);
   else
      printf("Token: %s (special)\n", oToken->pcValue);

   assert(Token_isValid(oToken));
}

/*--------------------------------------------------------------------*/

/* Create and return a token whose type is eTokenType and whose
   value consists of string pcValue.  The caller owns the token. */

Token_T Token_new(enum TokenType eTokenType,
   char *pcValue)
{
   Token_T oToken;

   assert(pcValue != NULL);
   assert(eTokenType == TOKEN_SPECIAL || eTokenType == TOKEN_ORDINARY);

   oToken = (struct Token*)malloc(sizeof(struct Token));
   if (oToken == NULL)
   {perror(getPgmName()); exit(EXIT_FAILURE);}
   
   oToken->eType = eTokenType;
   oToken->pcValue =
      (char*)malloc(sizeof(char) * (strlen(pcValue)+1));
   if (oToken->pcValue == NULL)
      {perror(getPgmName()); exit(EXIT_FAILURE);}
   strcpy(oToken->pcValue, pcValue);

   assert(Token_isValid(oToken));
   return oToken;
}

/*--------------------------------------------------------------------*/

/* Free oToken. */

void Token_free(Token_T oToken)
{
   assert(oToken != NULL);
   assert(Token_isValid(oToken));
   
   free(oToken->pcValue);
   free(oToken);
}

/*--------------------------------------------------------------------*/

/* Returns 1 (TRUE) if oToken is a stdin-redirect token. */

int Token_isStdIn(Token_T oToken)
{
   assert(oToken != NULL);
   assert(Token_isValid(oToken));
      
   if (strcmp(oToken->pcValue, "<") == 0) return 1;
   return 0;
}

/*--------------------------------------------------------------------*/

/* Returns 1 (TRUE) if oToken is a stdout-redirect token. */

int Token_isStdOut(Token_T oToken)
{
   assert(oToken != NULL);
   assert(Token_isValid(oToken));
      
   if (strcmp(oToken->pcValue, ">") == 0) return 1;
   return 0;
}
