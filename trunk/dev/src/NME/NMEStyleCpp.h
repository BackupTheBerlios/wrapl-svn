/**
 *	@file NMEStyleCpp.h
 *	@author Yves Piguet. Copyright 2007, Yves Piguet.
 *	@brief C++ class wrapper for NME.h and NMEStyle.h (inherits from class NME).
 */

#ifndef __NMEStyleCpp__
#define __NMEStyleCpp__

#include "NMECpp.h"
#include "NMEStyle.h"
#include <string.h>

/** NMEStyle parser class with separate text and style (objects can be
used for multiple conversions, by changing input and/or output format
before getting output again) */
class NMEStyle: public NME
{
	public:
		
		/** Default constructor.
		*/
		NMEStyle(): NME()
		{
			styleTable = NULL;
		}
		
		/** Constructor with input.
		@param[in] input address of input
		@param[in] inputLength input length in bytes (if not specified, input
		is a null-terminated string)
		*/
		NMEStyle(char const *input, int inputLength = -1): NME(input, inputLength)
		{
			styleTable = NULL;
		}
		
		/** Set style table offset mode.
		@param[in] unicodeStyleOffsets true to have offsets in style table in UCS-16
		(16-bit unicode), false to have offsets in bytes (UTF-8 or any other ASCII extension)
		*/
		void setUnicodeStyleOffsets(bool unicodeStyleOffsets = true)
		{
			this->unicodeStyleOffsets = unicodeStyleOffsets;
		}
		
		/** Get parser output, generating it if needed.
		@param[out] output address of output (null-terminated)
		@param[out] outputLength length of output in bytes, excluding null terminator
		(optional)
		*/
		void getOutput(NMEConstText *output, NMEInt *outputLength = NULL)
		{
			if (!styleTable)
			{
				format.parHookFun = format.spanHookFun = NMEStyleSpanHook;
				styleTableSize = sizeof(NMEStyleTable) + inputLength;
				styleTable = (NMEStyleTable *) new char[styleTableSize];
				NMEStyleInit(styleTable, styleTableSize,
						unicodeStyleOffsets);
				format.hookData = (void *)styleTable;
			}
			
			for (;;)
			{
				try
				{
					NME::getOutput(output, outputLength);
					break;
				}
				catch (NMEError e)
				{
					if (e.code() == (NMEErr)kNMEErrStyleTableTooSmall)
					{
						if (styleTableSize >= 65536 + 10 * inputLength)
							throw e;
						delete [] (char *)styleTable;
						styleTableSize *= 2;
						styleTable = (NMEStyleTable *) new char[styleTableSize];
						NMEStyleInit(styleTable, styleTableSize,
								unicodeStyleOffsets);
						format.hookData = (void *)styleTable;
					}
					else
						throw e;
				}
			}
		}
		
		/** Get style table.
		@return style table
		*/
		NMEStyleTable const *getStyleTable()
		{
			// parse input if not done yet
			if (!output)
				getOutput(NULL);	// ignore output
			return styleTable;
		}
		
	private:
		
		bool unicodeStyleOffsets;
		NMEStyleTable *styleTable;
		NMEInt styleTableSize;
};

#endif
