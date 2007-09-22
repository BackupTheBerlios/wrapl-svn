/**
 *	@file NMEGtk.c
 *	@brief Support for GTK+ .
 *	@author Yves Piguet. Copyright 2007, Yves Piguet.
 */

/* License: new BSD license (see file NME.h) */

#include "NMEGtk.h"
#include <stdio.h>

void NMEGtkInit(NMEGtk *nmegtk, GtkTextBuffer *textBuffer, int charSize)
{
	int i;
	
	nmegtk->textBuffer = textBuffer;
	
	nmegtk->boldTag = gtk_text_buffer_create_tag(textBuffer, "bold", NULL);
	g_object_set(G_OBJECT(nmegtk->boldTag), "weight", PANGO_WEIGHT_BOLD, NULL);
	nmegtk->italicTag = gtk_text_buffer_create_tag(textBuffer, "italic", NULL);
	g_object_set(G_OBJECT(nmegtk->italicTag), "style", PANGO_STYLE_ITALIC, NULL);
	nmegtk->underlineTag = gtk_text_buffer_create_tag(textBuffer, "underline", NULL);
	g_object_set(G_OBJECT(nmegtk->underlineTag), "underline", PANGO_UNDERLINE_SINGLE, NULL);
	nmegtk->superTag = gtk_text_buffer_create_tag(textBuffer, "superscript", NULL);
	g_object_set(G_OBJECT(nmegtk->superTag), "rise", charSize / 2, NULL);
	nmegtk->subTag = gtk_text_buffer_create_tag(textBuffer, "subscript", NULL);
	g_object_set(G_OBJECT(nmegtk->subTag), "rise", -charSize / 3, NULL);
	nmegtk->monoTag = gtk_text_buffer_create_tag(textBuffer, "monospace", NULL);
	g_object_set(G_OBJECT(nmegtk->monoTag), "font", "monospace", NULL);
	nmegtk->headingTag[0] = gtk_text_buffer_create_tag(textBuffer, "h1", NULL);
	g_object_set(G_OBJECT(nmegtk->headingTag[0]),
			"weight", PANGO_WEIGHT_BOLD,
			"scale", PANGO_SCALE_XX_LARGE,
			"pixels-above-lines", charSize / PANGO_SCALE,
			"justification", GTK_JUSTIFY_CENTER,
			NULL);
	nmegtk->headingTag[1] = gtk_text_buffer_create_tag(textBuffer, "h2", NULL);
	g_object_set(G_OBJECT(nmegtk->headingTag[1]),
			"weight", PANGO_WEIGHT_BOLD,
			"scale", PANGO_SCALE_X_LARGE,
			"pixels-above-lines", 2 * charSize / 3 / PANGO_SCALE,
			NULL);
	nmegtk->headingTag[2] = gtk_text_buffer_create_tag(textBuffer, "h3", NULL);
	g_object_set(G_OBJECT(nmegtk->headingTag[2]),
			"weight", PANGO_WEIGHT_BOLD,
			"scale", PANGO_SCALE_LARGE,
			"pixels-above-lines", charSize / 2 / PANGO_SCALE,
			NULL);
	nmegtk->headingTag[3] = gtk_text_buffer_create_tag(textBuffer, "h4", NULL);
	g_object_set(G_OBJECT(nmegtk->headingTag[3]), "weight", PANGO_WEIGHT_BOLD,
			"pixels-above-lines", charSize / 3 / PANGO_SCALE,
			NULL);
	for (i = 0; i < kMaxListLevel; i++)
	{
		char name[16];
		
		sprintf(name, "indent%d", i + 1);
		nmegtk->indentTag[i] = gtk_text_buffer_create_tag(textBuffer, name, NULL);
		g_object_set(G_OBJECT(nmegtk->indentTag[i]),
				"indent", (i + 1) * charSize / PANGO_SCALE,
				NULL);
	}
}

void NMEGtkApplyStyle(NMEGtk const *nmegtk,
		NMEStyleTable const *spanTable,
		NMEInt offset)
{
	GtkTextIter start, end;
	GtkTextTag *tag;
	int i;
	
	for (i = 0; i < spanTable->n; i++)
	{
		switch (spanTable->span[i].style)
		{
			case kNMEStyleCharBold:
			case kNMEStyleCharDT:
			case kNMEStyleCharTH:
				tag = nmegtk->boldTag;
				break;
			case kNMEStyleCharItalic:
				tag = nmegtk->italicTag;
				break;
			case kNMEStyleCharUnderline:
				tag = nmegtk->underlineTag;
				break;
			case kNMEStyleCharSuperscript:
				tag = nmegtk->superTag;
				break;
			case kNMEStyleCharSubscript:
				tag = nmegtk->subTag;
				break;
			case kNMEStyleCharMonospace:
				tag = nmegtk->monoTag;
				break;
			case kNMEStyleParHeading:
				if (spanTable->span[i].level <= kMaxHeadingLevel)
					tag = nmegtk->headingTag[spanTable->span[i].level - 1];
				else
					tag = nmegtk->headingTag[kMaxHeadingLevel - 1];
				break;
			case kNMEStyleParUL:
			case kNMEStyleParOL:
			case kNMEStyleParDL:
			case kNMEStyleParDT:
			case kNMEStyleParIndentedPar:
				if (spanTable->span[i].level <= kMaxListLevel)
					tag = nmegtk->indentTag[spanTable->span[i].level - 1];
				else
					tag = nmegtk->indentTag[kMaxHeadingLevel - 1];
				break;
			default:
				tag = NULL;
				break;
		}
		
		if (tag)
		{
			gtk_text_buffer_get_iter_at_offset(nmegtk->textBuffer, &start,
					spanTable->span[i].begin + offset);
			gtk_text_buffer_get_iter_at_offset(nmegtk->textBuffer, &end,
					spanTable->span[i].end + offset);
			gtk_text_buffer_apply_tag(nmegtk->textBuffer, tag, &start, &end);
		}
	}
}
