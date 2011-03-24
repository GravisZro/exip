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
 * @file grammarAugment.c
 * @brief Implementation of Event Code Assignment and Undeclared Productions addition
 * @date Feb 3, 2011
 * @author Rumen Kyusakov
 * @version 0.1
 * @par[Revision] $Id$
 */

#include "grammarAugment.h"
#include "ioUtil.h"
#include "eventsEXI.h"

static int compareProductions(const void* prod1, const void* prod2);

errorCode assignCodes(struct EXIGrammar* grammar)
{
	uint16_t i = 0;
	uint16_t j = 0;

	for (i = 0; i < grammar->rulesDimension; i++)
	{
		qsort(grammar->ruleArray[i].prodArray, grammar->ruleArray[i].prodCount, sizeof(Production), compareProductions);
		grammar->ruleArray[i].bits[0] = getBitsNumber(grammar->ruleArray[i].prodCount - 1);
		for (j = 0; j < grammar->ruleArray[i].prodCount; j++)
		{
			grammar->ruleArray[i].prodArray[j].code = getEventCode1(j);
		}
	}
	return ERR_OK;
}

errorCode addUndeclaredProductions(AllocList* memList, unsigned char strict, struct EXIGrammar* grammar)
{
	return NOT_IMPLEMENTED_YET;
}

static int compareProductions(const void* prod1, const void* prod2)
{
	Production* p1 = (Production*) prod1;
	Production* p2 = (Production*) prod2;

	if(p1->event.eventType < p2->event.eventType)
		return -1;
	else if(p1->event.eventType > p2->event.eventType)
		return 1;
	else // the same event Type
	{
		if(p1->event.eventType == EVENT_AT_QNAME)
		{
			if(p1->lnRowID < p2->lnRowID)
				return -1;
			else if(p1->lnRowID > p2->lnRowID)
				return 1;
			else
			{
				if(p1->uriRowID < p2->uriRowID)
					return -1;
				else if(p1->uriRowID > p2->uriRowID)
					return 1;
				else
					return 0;
			}
		}
		else if(p1->event.eventType == EVENT_AT_URI)
		{
			if(p1->uriRowID < p2->uriRowID)
				return -1;
			else if(p1->uriRowID > p2->uriRowID)
				return 1;
			else
				return 0;
		}
		else if(p1->event.eventType == EVENT_SE_QNAME)
		{
			// TODO: figure out how it should be done
		}
		else if(p1->event.eventType == EVENT_SE_URI)
		{
			// TODO: figure out how it should be done
		}
		return 0;
	}
}