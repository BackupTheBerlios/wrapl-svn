#include <Std.h>
#include <Riva.h>
#include <NME.h>

typedef struct format_t {
	Std$Type_t *Type;
	NMEOutputFormat *Format;
} format_t;

TYPE(FormatT);

format_t FormatText[] = {{FormatT, &NMEOutputFormatText}};
format_t FormatNull[] = {{FormatT, &NMEOutputFormatNull}};
format_t FormatNME[] = {{FormatT, &NMEOutputFormatNME}};
format_t FormatHTML[] = {{FormatT, &NMEOutputFormatHTML}};
format_t FormatRTF[] = {{FormatT, &NMEOutputFormatRTF}};
format_t FormatLaTeX[] = {{FormatT, &NMEOutputFormatLaTeX}};
format_t FormatMan[] = {{FormatT, &NMEOutputFormatMan}};

GLOBAL_FUNCTION(Process, 2) {
	NMEInt TextLen = ((Std$String_t *)Args[0].Val)->Length.Value;
	NMEConstText Text = Std$String$flatten(Args[0].Val);
	NMEInt BufLen = TextLen * 2;
	NMEText Buf = Riva$Memory$alloc(BufLen);
	NMEOutputFormat *Format = ((format_t *)Args[1].Val)->Format;
	NMEText Output;
	NMEInt OutputLen;
	for (;;) switch (NMEProcess(Text, TextLen, Buf, BufLen, kNMEProcessOptDefault, "\n", Format, -1, &Output, &OutputLen)) {
	case kNMEErrOk:
		Result->Val = Std$String$new_length(Output, OutputLen);
		return SUCCESS;
	case kNMEErrNotEnoughMemory:
		BufLen = 2 * BufLen;
		Buf = Riva$Memory$alloc(BufLen);
		break;
	case kNMEErrBadMarkup:
		Result->Val = Std$String$new("bad markup");
		return MESSAGE;
	case kNMEErrInternal:
		Result->Val = Std$String$new("internal error");
		return MESSAGE;
	default:
		Result->Val = Std$String$new("unknown error");
		return MESSAGE;
	};
};

