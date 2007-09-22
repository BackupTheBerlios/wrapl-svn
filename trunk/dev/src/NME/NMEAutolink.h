/**
 *	@file NMEAutolink.h
 *	@brief NME optional automatic link recognition (CamelCase and URL)
 *	@author Yves Piguet. Copyright 2007, Yves Piguet.
 */
 
/* License: new BSD license (see NME.h) */

#ifndef __NMEAutolink__
#define __NMEAutolink__

#ifdef __cplusplus
extern "C" {
#endif

#include "NME.h"

/** Autoconvert implementation for camelCase words
	@param[in] src source text with markup
	@param[in] srcLen source text length
	@param[in,out] i index in src (token to parse on input, next token on output)
	@param[in,out] context current context
	@param[in] userData pointer passed from the parser, as specified in NMEAutoconvert
	@return TRUE for conversion, else FALSE
*/
NMEBoolean NMEAutoconvertCamelCase(NMEConstText src, NMEInt srcLen,
		NMEInt *i,
		NMEContext *context,
		void *userData);

/// NMEAutoconvertCamelCase entry for table of NMEAutoconvert
#define NMEAutoconvertCamelCaseEntry \
	{NMEAutoconvertCamelCase, NULL}

/** Autoconvert implementation for URLs
	@param[in] src source text with markup
	@param[in] srcLen source text length
	@param[in,out] i index in src (token to parse on input, next token on output)
	@param[in,out] context current context
	@param[in] userData pointer passed from the parser, as specified in NMEAutoconvert
	@return TRUE for conversion, else FALSE
*/
NMEBoolean NMEAutoconvertURL(NMEConstText src, NMEInt srcLen,
		NMEInt *i,
		NMEContext *context,
		void *userData);

/// NMEAutoconvertURL entry for table of NMEAutoconvert
#define NMEAutoconvertURLEntry \
	{NMEAutoconvertURL, NULL}

#ifdef __cplusplus
}
#endif

#endif
