/**
 *	@file NMEMain.c
 *	@brief Test program for Nyctergatis Markup Engine.
 *	@author Yves Piguet. Copyright 2007, Yves Piguet.
 *
 *	@section Usage Usage
 *	This program filters standard input and writes the result to
 *	sandard output. It can be called as follows to convert file
 *	readme.nme to HTML file readme.html:
 *	@code
 *	./nme <readme.nme >readme.html
 *	@endcode
 *	Here is the list of options it supports:
 *	- \c --1eol           single eol as paragraph breaks
 *	- \c --2eol           double eol as paragraph breaks (default)
 *	- \c --autocclink     automatic conversion of camelCase words to links
 *	- \c --autourl        automatic conversion of URLs to links
 *	- \c --body           naked body without header and footer
 *	- \c --editfrag \e index \e length \e beg \e end
 *                        edit a fragment of the source code; in output,
 *                        replace what corresponds to input fragment starting
 *                        at \e index of length \e length with this unmodified
 *                        input fragment surrounded by \e beg and \e end
 *	- \c --headernum1     numbering of level-1 headers
 *	- \c --headernum2     numbering of level-2 headers
 *	- \c --fontsize \e s  font size (0=default)
 *	- \c --help           this help message
 *	- \c --html           HTML output (default)
 *	- \c --jspwiki        JSPWiki output
 *	- \c --latex          LaTeX output
 *	- \c --man            man page output
 *	- \c --mediawiki      Mediawiki output
 *	- \c --nme            NME output
 *	- \c --null           no output (still process input)
 *	- \c --strictcreole   dble tt, u, sub/sup, DL, ind par and esc and eble tt nowiki
 *  - \c --structdiv      display division structure
 *  - \c --structpar      display paragraph structure
 *	- \c --rtf            RTF output
 *	- \c --text           plain text output
 *	- \c --xref           headings have hyperlink target labels
 */

/* License: new BSD license (see NME.h) */

// To compile: gcc -o nme NME.c NMEAutolink.c NMEMain.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NME.h"
#include "NMEAutolink.h"
#include "NMEPluginRot13.h"
#include "NMEPluginReverse.h"
#include "NMEPluginUppercase.h"
#include "NMEPluginCalendar.h"
#include "NMEPluginRaw.h"
#include "NMEPluginTOC.h"

/// Fixed size allocated for source :-(
#define SIZE (128 * 1024)

// Cf. www.wikimatrix.org

/// Format strings for Mediawiki output (NOT FINISHED!)
static NMEOutputFormat const NMEOutputFormatMediawiki =
{
	" ",	// space
	0,	// indentSpaces
	10,	// defFontSize
	'%',	// ctrlChar
	"", "",	// doc
	6,	// highest heading level
	"%%{l}=%%", "%%{l}=%%\n",	// heading
	"", "\n\n",	// par
	"<br>",	// line break
	"", "\n",	// pre
	" ", "\n",	// pre line
	"", "%%{l=1}\n%%",	// UL
	"%%{l}*%% ", "\n",	// UL line
	"", "%%{l=1}\n%%",	// OL
	"%%{l}#%% ", "\n",	// OL line
	"", "%%{l=1}\n%%",	// DL
	"%%{l};%% ", "\n",	// DT
	NULL,	// emptyDT
	": ", "\n",	// DD
	"", "%%{l=1}\n%%",	// indented section
	"%%{l}:%% ", "\n",	// indented par
	"{|\n", "|}\n",	// table
	"|-\n", "",	// table row
	"!", "\n",	// table header cell
	"|", "\n",	// table normal cell
	"----\n\n",	// hr									??
	"'''", "'''",	// bold
	"''", "''",	// italic
	"__", "__",	// underline							??
	"<sup>", "</sup>",	// superscript
	"<sub>", "</sub>",	// subscript
	"<code>", "</code>",	// monospace
	"[", "]", "|", FALSE,	// URL
	"[[Image:", "]]", "|", FALSE, TRUE,	// image
	NULL,	// interwiki
	NULL,
	NULL, NULL,	// char encoder							??
	NULL, NULL,	// char pre encoder						??
	65, NULL, NULL,	// wordwrap
	NULL, NULL, NULL, NULL,	// process hooks
	NULL,	// plugins
	NULL	// autoconverts
};

/** Table of character substitutions for JSPWiki */
static NMEEncodeCharDict const jspwikiCharDict[] =
{
	{'*', "~*"},
	{'#', "~#"},
	{'\\', "~\\"},
	{'_', "~_"},
	{'!', "~!"},
	{'{', "~{"},
	{'}', "~}"},
	{'~', "~~"},
	{0, NULL}
};

/// Format strings for JSPWiki output
static NMEOutputFormat const NMEOutputFormatJSPWiki =
{
	" ",	// space
	0,	// indentSpaces
	10,	// defFontSize
	'?',	// ctrlChar
	"", "",	// doc
	3,	// highest heading level
	"??{4-l}!?? ", "\n",	// heading
	"", "\n\n",	// par
	"\\\\",	// line break
	"{{{\n", "}}}\n\n",	// pre
	"", "\n",	// pre line
	"", "??{l=1}\n??",	// UL
	"??{l}*?? ", "\n",	// UL line
	"", "??{l=1}\n??",	// OL
	"??{l}#?? ", "\n",	// OL line
	"", "??{l=1}\n??",	// DL
	"%%(text-indent:?{20*l}px)\n__", ":__ ",	// DT
	"%%(text-indent:?{20*l}px)\n",	// emptyDT
	"", "\n%%\n\n",	// DD
	"", "",	// indented section
	"%%(text-indent:?{20*l}px)\n", "\n%%\n\n",	// indented par
	"", "\n",	// table
	"", "\n",	// table row
	"|| ", "",	// table header cell
	"| ", "",	// table normal cell
	"----\n\n",	// hr
	"__", "__",	// bold
	"''", "''",	// italic
	"%%(text-decoration:underline)", "%%",	// underline
	"%%(vertical-align:sup)", "%%",	// superscript
	"%%(vertical-align:sub)", "%%",	// subscript
	"{{", "}}",	// monospace
	"[", "]", "|", TRUE,	// URL
	"", "", NULL, FALSE, FALSE,	// image
	NULL,	// interwiki
	NULL,
	NMEEncodeCharFunDict, (void *)jspwikiCharDict,	// char encoder
	NULL, NULL,	// char pre encoder
	65, NULL, NULL,	// wordwrap
	NULL, NULL, NULL, NULL,	// process hooks
	NULL,	// plugins
	NULL	// autoconverts
};

/// User data of NMEPluginTOCEntry
static NMEPluginTocData tocData;

/// Table of plugins for conversion to HTML
static NMEPlugin const pluginsHTML[] =
{
	NMEPluginReverseEntry,
	NMEPluginRot13Entry,
	NMEPluginUppercaseEntry,
	NMEPluginRawEntry("rawinpar", FALSE),
	NMEPluginRawEntry("rawoutpar", TRUE),
	NMEPluginCalendarEntry,
	NMEPluginTOCEntry(&tocData),
	
	NMEPluginTableEnd
};

/// Table of plugins for conversion to all formats but HTML/XML
static NMEPlugin const plugins[] =
{
	NMEPluginReverseEntry,
	NMEPluginRot13Entry,
	NMEPluginUppercaseEntry,
	NMEPluginCalendarEntry,
	
	NMEPluginTableEnd
};

/// Table of autoconvert functions
static NMEAutoconvert autoconverts[16];

/// Table of interwiki definitions
static NMEInterwiki const interwikis[] =
{
	{"Dictionary:",
		"http://www.dict.org/bin/Dict?Database=*&Form=Dict1&Strategy=*&Query="},
	{"Foldoc:", "http://www.foldoc.org/foldoc/foldoc.cgi?"},
	{"Google:", "http://www.google.com/search?q="},
	{"WhoIs:", "http://www.whois.sc/"},
	{"WikiPedia:", "http://en.wikipedia.org/wiki/"},
	{NULL, NULL}
};

/// Data passed to hookDump
typedef struct
{
	NMEInt nesting;
} HookDumpData;

/// Hook for dumping information about input
static NMEErr hookDump(NMEInt level,
		NMEInt item,
		NMEBoolean enter,
		NMEConstText markup,
		NMEInt srcIndex,
		NMEContext *context,
		void *data)
{
	if (!enter)
		((HookDumpData *)data)->nesting--;
	printf("%*s", 2 * ((HookDumpData *)data)->nesting, " ");
	if (level > 0)
		printf("%-4s L%d %c %.5d\n", markup, level, enter ? '<' : '>', srcIndex);
	else
		printf("%-4s    %c %.5d\n", markup, enter ? '<' : '>', srcIndex);
	if (enter)
		((HookDumpData *)data)->nesting++;
	return kNMEErrOk;
}

/// Data passed to hookEdit
typedef struct
{
	NMEInt index;
	NMEInt length;
	NMEConstText begin;
	NMEConstText end;
	NMEBoolean done;	///< set to TRUE once the fragment has been processed
} HookEditData;

/// Hook for editing a fragment of input source
static NMEErr hookEdit(NMEInt level,
		NMEInt item,
		NMEBoolean enter,
		NMEConstText markup,
		NMEInt srcIndex,
		NMEContext *context,
		void *data)
{
	HookEditData *hookEditData = (HookEditData *)data;
	NMEErr err;
	
	if (!hookEditData->done
			&& srcIndex >= hookEditData->index)
	{
		if (srcIndex < hookEditData->index + hookEditData->length)
		{
			if (!NMEAddString(hookEditData->begin, -1, '\0', context))
				return kNMEErrNotEnoughMemory;
			err = NMECopySource(hookEditData->length - (hookEditData->index - srcIndex),
					TRUE, TRUE, context);
			if (err != kNMEErrOk)
				return err;
			if (!NMEAddString(hookEditData->end, -1, '\0', context))
				return kNMEErrNotEnoughMemory;
		}
		
		hookEditData->done = TRUE;
	}
	return kNMEErrOk;
}

/// Application entry point
int main(int argc, char **argv)
{
	NMEText src = NULL, buf, dest;
	NMEInt srcLen, destLen;
	NMEOutputFormat outputFormat = NMEOutputFormatHTML;
	NMEInt options = kNMEProcessOptDefault;
	NMEBoolean autoURLLink = FALSE, autoCCLink = FALSE;
	int i;
	int fontSize = 0;
	HookDumpData hookDumpData;
	HookTOCData hookTOCData;
	HookEditData hookEditData;
	NMEErr err;
	
	outputFormat.plugins = pluginsHTML;
	
	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i], "--body"))
			options |= kNMEProcessOptNoPreAndPost;
		else if (!strcmp(argv[i], "--1eol"))
			options |= kNMEProcessOptNoMultilinePar;
		else if (!strcmp(argv[i], "--2eol"))
			options &= ~kNMEProcessOptNoMultilinePar;
		else if (!strcmp(argv[i], "--xref"))
			options |= kNMEProcessOptXRef;
		else if (!strcmp(argv[i], "--autocclink"))
			autoCCLink = TRUE;
		else if (!strcmp(argv[i], "--autourllink"))
			autoURLLink = TRUE;
		else if (!strcmp(argv[i], "--nme"))
		{
			outputFormat = NMEOutputFormatNME;
			outputFormat.plugins = plugins;
		}
		else if (!strcmp(argv[i], "--html"))
		{
			outputFormat = NMEOutputFormatHTML;
			outputFormat.plugins = pluginsHTML;
		}
		else if (!strcmp(argv[i], "--jspwiki"))
		{
			outputFormat = NMEOutputFormatJSPWiki;
			outputFormat.plugins = plugins;
		}
		else if (!strcmp(argv[i], "--latex"))
		{
			outputFormat = NMEOutputFormatLaTeX;
			outputFormat.plugins = plugins;
		}
		else if (!strcmp(argv[i], "--mediawiki"))
		{
			outputFormat = NMEOutputFormatMediawiki;
			outputFormat.plugins = plugins;
		}
		else if (!strcmp(argv[i], "--null"))
		{
			outputFormat = NMEOutputFormatNull;
			outputFormat.plugins = NULL;
		}
		else if (!strcmp(argv[i], "--rtf"))
		{
			outputFormat = NMEOutputFormatRTF;
			outputFormat.plugins = plugins;
		}
		else if (!strcmp(argv[i], "--editfrag") && i + 4 < argc)
		{
			outputFormat.parHookFun = hookEdit;
			hookEditData.index = strtol(argv[++i], NULL, 0);
			hookEditData.length = strtol(argv[++i], NULL, 0);
			hookEditData.begin = argv[++i];
			hookEditData.end = argv[++i];
			hookEditData.done = FALSE;
			outputFormat.hookData = (void *)&hookEditData;
		}
		else if (!strcmp(argv[i], "--structpar"))
		{
			outputFormat = NMEOutputFormatNull;
			outputFormat.parHookFun = hookDump;
			outputFormat.divHookFun = NULL;
			hookDumpData.nesting = 0;
			outputFormat.hookData = (void *)&hookDumpData;
		}
		else if (!strcmp(argv[i], "--structdiv"))
		{
			outputFormat = NMEOutputFormatNull;
			outputFormat.parHookFun = NULL;
			outputFormat.divHookFun = hookDump;
			hookDumpData.nesting = 0;
			outputFormat.hookData = (void *)&hookDumpData;
		}
		else if (!strcmp(argv[i], "--text"))
		{
			outputFormat = NMEOutputFormatText;
			outputFormat.plugins = plugins;
		}
		else if (!strcmp(argv[i], "--man"))
		{
			outputFormat = NMEOutputFormatMan;
			outputFormat.plugins = plugins;
		}
		else if (!strcmp(argv[i], "--fontsize") && i + 1 < argc)
			fontSize = strtol(argv[++i], NULL, 0);
		else if (!strcmp(argv[i], "--headernum1"))
			options |= kNMEProcessOptH1Num;
		else if (!strcmp(argv[i], "--headernum2"))
			options |= kNMEProcessOptH2Num;
		else if (!strcmp(argv[i], "--strictcreole"))
			options |= kNMEProcessOptNoEscape | kNMEProcessOptNoUnderline
					| kNMEProcessOptNoMonospace | kNMEProcessOptNoSubSuperscript
					| kNMEProcessOptNoIndentedPar | kNMEProcessOptNoDL
					| kNMEProcessOptVerbatimMono;
		else if (!strcmp(argv[i], "--toc"))
			NMESetTOCOutputFormat(&outputFormat, &hookTOCData);
		else
		{
			if (strcmp(argv[i], "--help"))
				fprintf(stderr, "Unknown option %s\n", argv[i]);
			fprintf(stderr, "Usage: %s [options]\n"
						"Filter NME stdin and renders it to another format.\n"
						"--1eol           single eol as paragraph breaks\n"
						"--2eol           double eol as paragraph breaks (default)\n"
						"--autocclink     automatic conversion of camelCase words to links\n"
						"--autourllink    automatic conversion of URLs to links\n"
						"--body           naked body without header and footer\n"
						"--editfrag i l b e  edit a fragment of the source code; in output,\n"
						"                 replace what corresponds to input fragment starting\n"
						"                 at i of length l with this unmodified input fragment\n"
						"                 surrounded by b and e\n"
						"--headernum1     numbering of level-1 headers\n"
						"--headernum2     numbering of level-2 headers\n"
						"--fontsize s     font size (0=default)\n"
						"--help           this help message\n"
						"--html           HTML output (default)\n"
						"--jspwiki        JSPWiki output\n"
						"--latex          LaTeX output\n"
						"--man            man page output\n"
						"--mediawiki      MediaWiki output\n"
						"--nme            NME output\n"
						"--null           no output (still process input)\n"
						"--strictcreole   disable monospace, underline, subscript,\n"
						"                 superscript, definition lists, indented\n"
						"                 paragraphs and escape; and enable nowiki\n"
						"                 monospace\n"
						"--structdiv      display division structure\n"
						"--structpar      display paragraph structure\n"
						"--rtf            RTF output\n"
						"--text           plain text output\n"
						"--xref           headings have hyperlink target labels\n",
					argv[0]);
			exit(0);
		}
	
	outputFormat.interwikis = interwikis;
	if (autoCCLink || autoURLLink)
	{
		int n = 0;
		
		if (autoCCLink)
			autoconverts[n++].cb = NMEAutoconvertCamelCase;
		if (autoURLLink)
			autoconverts[n++].cb = NMEAutoconvertURL;

		outputFormat.autoconverts = autoconverts;
	}
	
	src = malloc(SIZE);
	if (!src)
		exit(1);
	srcLen = fread(src, 1, SIZE, stdin);
	if (srcLen < 0)
	{
		free(src);
		exit(2);
	}
	
	buf = malloc(SIZE);
	if (!buf)
		exit(1);
	
	tocData.src = src;
	tocData.srcLen = srcLen;
	
	err = NMEProcess(src, srcLen,
			buf, SIZE,
			options, "\n", &outputFormat, fontSize,
			&dest, &destLen);
	
	if (err == kNMEErrOk)
		printf("%.*s", destLen, dest);
	else
		printf("Error %d\n", err);
	
	free((void *)buf);
	free((void *)src);
	
	return 0;
}
