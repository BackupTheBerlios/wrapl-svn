/**
 *	@file NMEGtk.h
 *	@brief Support for GTK+ .
 *	@author Yves Piguet. Copyright 2007, Yves Piguet
 */
 
#ifndef __NMEGtk__
#define __NMEGtk__

#ifdef __cplusplus
extern "C" {
#endif

#include "NME.h"
#include "NMEStyle.h"

#include <gtk/gtk.h>

#define kMaxHeadingLevel 4
#define kMaxListLevel 4

typedef struct
{
	GtkTextBuffer *textBuffer;
	GtkTextTag *boldTag, *italicTag, *underlineTag, *superTag, *subTag, *monoTag;
	GtkTextTag *headingTag[kMaxHeadingLevel], *indentTag[kMaxListLevel];
} NMEGtk;

/** Initialize NMEGtk data structure.
	@param[out] nmegtk data structure used by NMEGtkApplyStyle
	@param[in] textBuffer text buffer style is applied to
	@param[in] charSize standard text character size, used as the basis for
	heading sizes and superscript/subscript offsets
*/
void NMEGtkInit(NMEGtk *nmegtk, GtkTextBuffer *textBuffer, int charSize);

/** Apply styles collected by NMEStyle to a GTK+ text buffer
	@param[in] nmegtk data structure initialized by NMEGtkInit
	@param[in] spanTable table of style spans created by NMEProcess with NMEStyle
	@param[in] offset offset of NME output in textBuffer
*/
void NMEGtkApplyStyle(NMEGtk const *nmegtk,
		NMEStyleTable const *spanTable,
		NMEInt offset);

#ifdef __cplusplus
}
#endif

#endif
