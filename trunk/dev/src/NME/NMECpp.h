/**
 *	@file NMECpp.h
 *	@author Yves Piguet. Copyright 2007, Yves Piguet.
 *	@brief C++ class wrapper for NME.h.
 */

#ifndef __NMECpp__
#define __NMECpp__

#include "NME.h"
#include <string.h>

/** NME error class, used by NME::getOutput */
class NMEError
{
	public:
		NMEErr err;	///< error code
		
		/** Constructor
		@param[in] err error code
		*/
		NMEError(NMEErr err)
		{
			this->err = err;
		}
		
		/** Get error code
		@return error code
		*/
		NMEErr code()
		{
			return err;
		}
};

/** NME parser class (objects can be used for multiple conversions, by
changing input and/or output format before getting output again) */
class NME
{
	public:
		
		/** Default constructor.
		*/
		NME()
		{
			input = NULL;
			buf = NULL;
			output = NULL;
			format = NMEOutputFormatText;
			fontSize = 0;
		}
		
		/** Constructor with input.
		@param[in] input address of input
		@param[in] inputLength input length in bytes (if not specified, input
		is a null-terminated string)
		*/
		NME(char const *input, int inputLength = -1)
		{
			this->input = input;
			if (inputLength >= 0)
				this->inputLength = inputLength;
			else
				this->inputLength = strlen(input);
			buf = output = NULL;
			format = NMEOutputFormatText;
			fontSize = 0;
		}
		
		/** Destructor. */
		~NME()
		{
			if (buf)
				delete [] buf;
		}
		
		/** Set (or change) input.
		@param[in] input address of input
		@param[in] inputLength input length in bytes (if not specified, input
		is a null-terminated string)
		*/
		void setInput(char const *input, int inputLength = -1)
		{
			this->input = input;
			if (inputLength >= 0)
				this->inputLength = inputLength;
			else
				this->inputLength = strlen(input);
			output = NULL;
		}
		
		/** Set (or change) output format.
		@param[in] format output format
		*/
		void setFormat(NMEOutputFormat const &format)
		{
			this->format = format;
			output = NULL;
		}
		
		/** Set (or change) output font size.
		@param[in] fontSize font size (default is default output font size)
		*/
		void setFontSize(NMEInt fontSize = 0)
		{
			this->fontSize = fontSize;
			output = NULL;
		}
		
		/** Get parser output, generating it if needed.
		@param[out] output address of output (null-terminated)
		@param[out] outputLength length of output in bytes, excluding null terminator
		(optional)
		*/
		void getOutput(NMEConstText *output, NMEInt *outputLength = NULL)
		{
			if (this->output)
			{
				if (output)
					*output = this->output;
				if (outputLength)
					*outputLength = this->outputLength;
				return;
			}
			
			if (!input || inputLength == 0)
			{
				if (output)
					*output = "";
				if (outputLength)
					*outputLength = 0;
			}
			
			if (!buf)
			{
				bufSize = 1024 + 2 * inputLength;
				buf = new NMEChar[bufSize];
			}
			
			for (;;)
			{
				NMEInt len;
				NMEErr err = NMEProcess(input, inputLength,
						buf, bufSize,
						kNMEProcessOptDefault, "\n", &format, fontSize,
						&this->output, &this->outputLength);
				if (err == kNMEErrOk)
				{
					if (output)
						*output = this->output;
					if (outputLength)
						*outputLength = this->outputLength;
					return;
				}
				else if (err == kNMEErrNotEnoughMemory)
				{
					if (bufSize >= 65536 + 10 * inputLength)
						throw NMEError(kNMEErrNotEnoughMemory);
					delete [] buf;
					bufSize *= 2;
					buf = new NMEChar[bufSize];
				}
				else
					throw NMEError(err);
			}
		}
		
	protected:
		
		NMEConstText input;	// belong to caller
		NMEInt inputLength;
		
		NMEText buf;	// belong to NME object
		NMEInt bufSize;
		
		NMEText output;	// in buf
		NMEInt outputLength;
		
		NMEOutputFormat format;
		NMEInt fontSize;
};

#endif
