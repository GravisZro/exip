/*==================================================================================*\
|                                                                                    |
|                    EXIP - Efficient XML Interchange Processor                      |
|                                                                                    |
|------------------------------------------------------------------------------------|
| Copyright (c) 2010, EISLAB - Luleå University of Technology                        |
| All rights reserved.                                                               |
|                                                                                    |
| Redistribution and use in source and binary forms, with or without                 |
| modification, are permitted provided that the following conditions are met:        |
|     * Redistributions of source code must retain the above copyright               |
|       notice, this list of conditions and the following disclaimer.                |
|     * Redistributions in binary form must reproduce the above copyright            |
|       notice, this list of conditions and the following disclaimer in the          |
|       documentation and/or other materials provided with the distribution.         |
|     * Neither the name of the EISLAB - Luleå University of Technology nor the      |
|       names of its contributors may be used to endorse or promote products         |
|       derived from this software without specific prior written permission.        |
|                                                                                    |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND    |
| ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED      |
| WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE             |
| DISCLAIMED. IN NO EVENT SHALL EISLAB - LULEÅ UNIVERSITY OF TECHNOLOGY BE LIABLE    |
| FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES |
| (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;       |
| LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND        |
| ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT         |
| (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS      |
| SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                       |
|                                                                                    |
|                                                                                    |
|                                                                                    |
\===================================================================================*/

/**
 * @file p_ASCII_stringManipulate.c
 * @brief String manipulation functions used for UCS <-> ASCII transformations
 * Note! This file is platform dependent.
 * @date Sep 3, 2010
 * @author Rumen Kyusakov
 * @version 0.1
 * @par[Revision] $Id$
 */

#include "../include/stringManipulate.h"
#include <string.h>
#include <stdio.h>

/**
 * Simple translation working only for ASCII characters
 */
errorCode UCSToChar(unsigned int code_point, CharType* ch)
{
	*ch = (CharType) code_point;
	return ERR_OK;
}

errorCode getEmptyString(StringType* emptyStr)
{
	emptyStr->length = 0;
	emptyStr->str = NULL;

	return ERR_OK;
}

errorCode asciiToString(char* inStr, StringType* outStr)
{
	outStr->length = strlen(inStr);
	if(outStr->length > 0)  // If == 0 -> empty string
	{
		outStr->str = EXIP_MALLOC(sizeof(CharType)*(outStr->length));
		if(outStr->str == NULL)
			return MEMORY_ALLOCATION_ERROR;
		memcpy(outStr->str, inStr, outStr->length);
	}
	else
		outStr->str = NULL;
	return ERR_OK;
}

char str_equal(StringType str1, StringType str2)
{
	if(str1.length != str2.length)
		return 0;
	else
	{
		if(str1.length == 0)
		{
			if(str1.str == NULL && str2.str == NULL)
				return 1;
			else
				return 0;
		}
		else
		{
			int i = 0;
			for(i = 0; i < str1.length; i++)
			{
				if(str1.str[i] != str2.str[i])
					return 0;
			}
			return 1;
		}
	}
}

void printString(StringType* inStr)
{
	if(inStr->length == 0)
		return;
	int i = 0;
	for(i = 0; i < inStr->length; i++)
	{
		DEBUG_CHAR_OUTPUT(inStr->str[i]);
	}
}