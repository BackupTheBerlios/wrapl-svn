/**
 *	@file NMEMFC.h
 *	@brief Support for MFC (Windows) .
 *	@author Yves Piguet. Copyright 2007, Yves Piguet
 */
 
#ifndef __NMEMFC__
#define __NMEMFC__

#include "NME.h"
#include "NMEStyle.h"

#include <afxrich.h>

/** Replace selection in a CRichEditCtrl with NME text converted
	to styled text.
	@param[in,out] c MFC rich text control
	@param[in] input text with NME markup
	@param[in] inputLength length of input, or negative if input is
	null-terminated
	@para[in] replaceSel if TRUE, replace selection, else replace whole text
	@para[in] plainTextCharFormat character format of plain text (if NULL, use
	default character format of c)
*/
void NMEMFCSetRichText(CRichEditCtrl &c,
		char const *input, int inputLength = -1,
		bool replaceSel = FALSE,
		CHARFORMAT const *plainTextCharFormat = NULL);

/** Replace selection in a CRichEditCtrl with NME text converted
	to styled text.
	@param[in,out] c MFC rich text control
	@param[in] input text as UCS-16 with NME markup
	@param[in] inputLength length of input, or negative if input is
	null-terminated
	@para[in] replaceSel if TRUE, replace selection, else replace whole text
	@para[in] plainTextCharFormat character format of plain text (if NULL, use
	default character format of c)
*/
void NMEMFCSetRichText(CRichEditCtrl &c,
		WCHAR const *input, int inputLength = -1,
		bool replaceSel = FALSE,
		CHARFORMAT const *plainTextCharFormat = NULL);

#endif
