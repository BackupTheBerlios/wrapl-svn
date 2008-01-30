#include "scanner.h"
#include "missing.h"
#include <Riva.h>
#include <Std.h>

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "compiler.h"
#include "parser.h"

const char *Tokens[] = {
	"<none>", //tkNONE                            0
	";", //tkSEMICOLON                       1
	"DEF", //tkDEF                             2
	"VAR", //tkVAR                             3
	"MOD", //tkMOD                             4
	"<ident>", //tkIDENT                           5
	"END", //tkEND                             6
	".", //tkDOT                             7
	"<eoi>", //tkEOI                             8
	"IMP", //tkIMP                             9
	"AS", //tkAS                             10
	"USE", //tkUSE                            11
	",", //tkCOMMA                          12
	"*", //tkMULTIPLY                       13
	"!", //tkEXCLAIM                        14
	"<-", //tkASSIGN                         15
	"(", //tkLPAREN                         16
	")", //tkRPAREN                         17
	"RECV", //tkRECV                           18
	"DO", //tkDO                             19
	"RET", //tkRET                            20
	"BACK", //tkBACK                           21
	"FAIL", //tkFAIL                           22
	"SUSP", //tkSUSP                           23
	"WHEN", //tkWHEN                           24
	"REP", //tkREP                            25
	"EXIT", //tkEXIT                           26
	"STEP", //tkSTEP                           27
	"EVERY", //tkEVERY                          28
	"NOT", //tkNOT                            29
	"WHILE", //tkWHILE                          30
	"UNTIL", //tkUNTIL                          31
	"SEND", //tkSEND                           32
	"YIELD", //tkYIELD                          33
	"ALL", //tkALL                            34
	"<", //tkLESS                           35
	">", //tkGREATER                        36
	"TO", //tkTO                             37
	"IS", //tkIS                             38
	"@", //tkAT                             39
	"=", //tkEQUAL                          40
	"//", //tkELSE                           41
	"=>", //tkTHEN                           42
	"&", //tkAND                            43
	"\\", //tkBACKSLASH                      44
	"==", //tkEXACTLY                        45
	"~==", //tkNOTEXACTLY                     46
	"~=", //tkNOTEQ                          47
	"<=", //tkLSEQ                           48
	">=", //tkGREQ                           49
	"IN", //tkIN                             50
	"<:", //tkSUBTYPE                        51
	"+", //tkPLUS                           52
	"-", //tkMINUS                          53
	"/", //tkDIVIDE                         54
	"%", //tkMODULO                         55
	"^", //tkPOWER                          56
	"!!", //tkPARTIAL                        57
	"?", //tkQUERY                          58
	"|", //tkOR                             59
	"OF", //tkOF                             60
	"~", //tkINVERSE                        61
	"#", //tkHASH                           62
	"<symbol>", //tkSYMBOL                         63
	"[", //tkLBRACKET                       64
	"]", //tkRBRACKET                       65
	"<constant>", //tkCONST                          66
	"$", //tkSELF                           67
	"NIL", //tkNIL                            68
	"{", //tkLBRACE                         69
	"}", //tkRBRACE                         70
	"<<=", //tkREFASSIGN                      71
	"..", //tkDOTDOT                         72
	"<block>", //tkSTRBLOCK                       73
	"SKIP", //tkSKIP                           74
};

scanner_t::scanner_t(IO$Stream_t *Source) {
	this->Source = Source;
	NextChar = "";
	NextToken.Type = 0;
	NextToken.LineNo = 0;
};

void scanner_t::flush() {
	NextChar = "";
	NextToken.Type = 0;
//	NextToken.LineNo = 0;
};

static char *scan_string_next(scanner_t *Scanner, const char **Next, int Index) {
	char Char;
	switch (Char = *(*Next)++) {
	case 0: Scanner->raise_error(Scanner->NextToken.LineNo, "Error: end of input in string");
	case '\"': {
		char *String = new char[Index + 1];
		String[Index] = 0;
		return String;
	};
	case '\\': {
		switch (Char = *(*Next)++) {
		case 'n': Char = '\n'; break;
		case 'r': Char = '\r'; break;
		case 'b': Char = '\b'; break;
		case 't': Char = '\t'; break;
		case 'x': {
			char Code;
			switch (Code = *(*Next)++) {
			case '0' ... '9': Char = 16 * (Code - '0'); break;
			case 'A' ... 'F': Char = 16 * (Code - 'A'); break;
			case 'a' ... 'f': Char = 16 * (Code - 'a'); break;
			default: Scanner->raise_error(Scanner->NextToken.LineNo, "Error: invalid character code in string");
			};
			switch (Code = *(*Next)++) {
			case '0' ... '9': Char += Code; break;
			case 'A' ... 'F': Char += Code; break;
			case 'a' ... 'f': Char += Code; break;
			default: Scanner->raise_error(Scanner->NextToken.LineNo, "Error: invalid character code in string");
			};
		};
		};
	};
	// FALLTHROUGH IS DELIBERATE!
	default: {
		char *String = scan_string_next(Scanner, Next, Index + 1);
		String[Index] = Char;
		return String;
	};
	};
};

static Std$String_t *scan_string_block0_next(scanner_t *Scanner, int Index, bool *ExprMode) {
    Start: char Char = *(Scanner->NextChar++);
    switch (Char) {
    case 0: {
        Scanner->NextChar = IO$Stream$readl(Scanner->Source);
        if (Scanner->NextChar == 0) Scanner->raise_error(Scanner->NextToken.LineNo, "Error: end of input in block string");
        ++Scanner->NextToken.LineNo;
        Std$String_t *String = scan_string_block0_next(Scanner, Index + 1, ExprMode);
        ((char *)String->Blocks->Chars.Value)[Index] = '\n';
        return String;
    };
    case '\\': {
        Char = *(Scanner->NextChar++);
        switch (Char) {
        case 0: {
            Scanner->NextChar = IO$Stream$readl(Scanner->Source);
            if (Scanner->NextChar == 0) Scanner->raise_error(Scanner->NextToken.LineNo, "Error: end of input in block string");
            ++Scanner->NextToken.LineNo;
            goto Start;
        };
        case 'n': Char = '\n'; break;
        case 'r': Char = '\r'; break;
        case 't': Char = '\t'; break;
        case 'x': {
            char Code;
            switch (Code = *(Scanner->NextChar++)) {
            case '0' ... '9': Char = 16 * (Code - '0'); break;
            case 'A' ... 'F': Char = 16 * (Code - 'A'); break;
            case 'a' ... 'f': Char = 16 * (Code - 'a'); break;
            default: Scanner->raise_error(Scanner->NextToken.LineNo, "Error: invalid character code in string");
            };
            switch (Code = *(Scanner->NextChar++)) {
            case '0' ... '9': Char += Code; break;
            case 'A' ... 'F': Char += Code; break;
            case 'a' ... 'f': Char += Code; break;
            default: Scanner->raise_error(Scanner->NextToken.LineNo, "Error: invalid character code in string");
            };
        };
        };
        Std$String_t *String = scan_string_block0_next(Scanner, Index + 1, ExprMode);
        ((char *)String->Blocks->Chars.Value)[Index] = Char;
        return String;
    };
    case '{': {
        *ExprMode = true;
        if (Index > 0) {
            char *Chars = Riva$Memory$alloc_atomic(Index + 1);
            Chars[Index] = 0;
            return Std$String$new_length(Chars, Index);
        } else {
            return 0;
        };
    };
    case '\'': {
        *ExprMode = false;
        if (Index > 0) {
            char *Chars = Riva$Memory$alloc_atomic(Index + 1);
            Chars[Index] = 0;
            return Std$String$new_length(Chars, Index);
        } else {
            return 0;
        };
    };
    default: {
        Std$String_t *String = scan_string_block0_next(Scanner, Index + 1, ExprMode);
        ((char *)String->Blocks->Chars.Value)[Index] = Char;
        return String;
    };
    };
};
static void scan_string_block0(scanner_t *Scanner) {
	expr_t Head;
    Head.Next = 0;
    expr_t *Tail = &Head;
	bool ExprMode = false;
	Std$String_t *String = scan_string_block0_next(Scanner, 0, &ExprMode);
    if (String) {
		if (ExprMode == false) {
			Scanner->NextToken.Type = tkCONST;
			Scanner->NextToken.Const = (Std$Object_t *)String;
			return;
		} else {
			Tail = (Tail->Next = new const_expr_t(Scanner->Token.LineNo, (Std$Object_t *)String));
		};
	};
    while (ExprMode) {
        Scanner->NextToken.Type = 0;
        Tail = (Tail->Next = accept_expr(Scanner));
        Scanner->accept(tkRBRACE);
        ExprMode = false;
		Std$String_t *String = scan_string_block0_next(Scanner, 0, &ExprMode);
	    if (String) Tail = (Tail->Next = new const_expr_t(Scanner->Token.LineNo, (Std$Object_t *)String));
	};
	Scanner->NextToken.Type = tkSTRBLOCK;
	Scanner->NextToken.Const = (Std$Object_t *)Head.Next;
};

static Std$String_t *scan_string_block_next(scanner_t *Scanner, const char *End, int EndLength, const char **Current, int Index) {
	char *Line = IO$Stream$readl(Scanner->Source);
	if (Line) {
		++Scanner->NextToken.LineNo;
	} else {
		Scanner->raise_error(Scanner->NextToken.LineNo, "Error: end of input in block string");
	};
	Std$String_t *String;
	if (strncmp(Line, End, EndLength) == 0) {
		*Current = Line + EndLength;
		String = (Std$String_t *)Riva$Memory$alloc(sizeof(Std$String_t) + Index * sizeof(Std$String_block));
		String->Type = Std$String$T;
		String->Length.Type = Std$Integer$SmallT;
		String->Count = Index;
	} else {
		String = scan_string_block_next(Scanner, End, EndLength, Current, Index + 1);
		int Length = strlen(Line);
		Line[Length] = '\n';
		++Length;
		String->Length.Value += Length;
		String->Blocks[Index].Length.Type = Std$Integer$SmallT;
		String->Blocks[Index].Length.Value = Length;
		String->Blocks[Index].Chars.Type = Std$Address$T;
		String->Blocks[Index].Chars.Value = Line;
	};
	return String;
};

#include "keywords.c"

extern Riva$Module_t Riva$Symbol[];

bool scanner_t::parse(int Type) {
	if (NextToken.Type == 0) {
		const char *Current = NextChar;
		const char *Start;
		scan_loop: {
			Start = Current;
			switch (*Current) {
			case 0: Current = IO$Stream$readl(Source);
				if (Current == 0) {
					NextToken.Type = tkEOI; goto scan_done;
				} else {
					NextToken.LineNo++; goto scan_loop;
				};
			case '\x01' ... ' ': ++Current; goto scan_loop;
			case '0' ... '9': Start = Current++; goto scan_integer;
			case 'A' ... 'Z': case 'a' ... 'z': case '_': Start = Current++; goto scan_identifier;
			case ':': ++Current; goto scan_symbol;
			case '\"': ++Current;
				NextToken.Type = tkCONST;
				NextToken.Const = (Std$Object_t *)Std$String$new(scan_string_next(this, &Current, 0));
				goto scan_done;
                        case '\'':
                                NextChar = ++Current;
				scan_string_block0(this);
				Current = NextChar;
				goto scan_done;
			case '=': ++Current;
				switch (*Current) {
				case '=': ++Current; NextToken.Type = tkEXACTLY; goto scan_done;
				case '>': ++Current; NextToken.Type = tkTHEN; goto scan_done;
				default: NextToken.Type = tkEQUAL; goto scan_done;
				};
			case '~': ++Current;
				switch (*Current) {
				case '=': ++Current;
					switch (*Current) {
					case '=': ++Current; NextToken.Type = tkNOTEXACTLY; goto scan_done;
					default: NextToken.Type = tkNOTEQ; goto scan_done;
					};
				default: NextToken.Type = tkINVERSE; goto scan_done;
				};
			case '}': ++Current; NextToken.Type = tkRBRACE; goto scan_done;
			case '|': ++Current; NextToken.Type = tkOR; goto scan_done;
			case '{': ++Current; NextToken.Type = tkLBRACE; goto scan_done;
			case '^': ++Current; NextToken.Type = tkPOWER; goto scan_done;
			case ']': ++Current; NextToken.Type = tkRBRACKET; goto scan_done;
			case '\\': ++Current; NextToken.Type = tkBACKSLASH; goto scan_done;
			case '[': ++Current; NextToken.Type = tkLBRACKET; goto scan_done;
			case '@': ++Current; NextToken.Type = tkAT; goto scan_done;
			case '?': ++Current; NextToken.Type = tkQUERY; goto scan_done;
			case ';': ++Current; NextToken.Type = tkSEMICOLON; goto scan_done;
			case '>': ++Current;
				switch (*Current) {
				case '>': ++Current; goto scan_block_string;
				case '=': ++Current; NextToken.Type = tkGREQ; goto scan_done;
				default: NextToken.Type = tkGREATER; goto scan_done;
				};
			case '/': ++Current;
				switch (*Current) {
				case '/': ++Current; NextToken.Type = tkELSE; goto scan_done;
				default: NextToken.Type = tkDIVIDE; goto scan_done;
				};
			case '<': ++Current;
				switch (*Current) {
				case '<': ++Current; if (*Current == '=') {
					++Current; NextToken.Type = tkREFASSIGN; goto scan_done;
				} else {
					--Current; NextToken.Type = tkLESS; goto scan_done;
				};
				case '=': ++Current; NextToken.Type = tkLSEQ; goto scan_done;
				case '-': ++Current; NextToken.Type = tkASSIGN; goto scan_done;
				case ':': ++Current; NextToken.Type = tkSUBTYPE; goto scan_done;
				default: NextToken.Type = tkLESS; goto scan_done;
				};
			case '.': Start = Current++;
				switch (*Current) {
				case '0' ... '9': ++Current; goto scan_real_mantissa;
				case '.': ++Current; NextToken.Type = tkDOTDOT; goto scan_done;
				default: NextToken.Type = tkDOT; goto scan_done;
				};
			case '-': Start = Current++;
				switch (*Current) {
				case '0' ... '9': ++Current; goto scan_integer;
				case '.': ++Current; goto scan_real_mantissa;
				case '=': ++Current; goto scan_comment;
				case '-': Current = IO$Stream$readl(Source);
					if (Current == 0) {
						NextToken.Type = tkEOI; goto scan_done;
					} else {
						++NextToken.LineNo; goto scan_loop;
					};
				default: NextToken.Type = tkMINUS; goto scan_done;
				};
			case ',': ++Current; NextToken.Type = tkCOMMA; goto scan_done;
			case '+': ++Current; NextToken.Type = tkPLUS; goto scan_done;
			case '*': ++Current; NextToken.Type = tkMULTIPLY; goto scan_done;
			case ')': ++Current; NextToken.Type = tkRPAREN; goto scan_done;
			case '(': ++Current; NextToken.Type = tkLPAREN; goto scan_done;
			case '&': ++Current; NextToken.Type = tkAND; goto scan_done;
			case '%': ++Current; NextToken.Type = tkMODULO; goto scan_done;
			case '!': ++Current; NextToken.Type = tkEXCLAIM; goto scan_done;
			case '#': ++Current; NextToken.Type = tkHASH; goto scan_done;
			case '$': ++Current; NextToken.Type = tkSELF; goto scan_done;
			default: raise_error(NextToken.LineNo, "Error: invalid character \'%c\'", *Current);
			};
			scan_integer: {
				switch(*Current) {
				case '0' ... '9': ++Current; goto scan_integer;
				case '.': ++Current; goto scan_real_mantissa;
				case 'e': case 'E': ++Current; goto scan_real_exponent;
				default: {
					int Length = Current - Start;
					char Buffer[Length + 1];
					memcpy(Buffer, Start, Length);
					Buffer[Length] = 0;
					NextToken.Type = tkCONST;
					NextToken.Const = Std$Integer$new_string(Buffer);
					goto scan_done;
				};
				};
			};
			scan_real_mantissa: {
				switch(*Current) {
				case '0' ... '9': ++Current; goto scan_real_mantissa;
				case 'e': case 'E': ++Current; goto scan_real_exponent_sign;
				default: {
					int Length = Current - Start;
					char Buffer[Length + 1];
					memcpy(Buffer, Start, Length);
					Buffer[Length] = 0;
					NextToken.Type = tkCONST;
					NextToken.Const = (Std$Object_t *)Std$Real$new_string(Buffer);
					goto scan_done;
				};
				};
			};
			scan_real_exponent_sign: {
				switch(*Current) {
				case '0' ... '9': ++Current; goto scan_real_exponent;
				case '+': case '-': ++Current; goto scan_real_exponent;
				default: raise_error(NextToken.LineNo, "Error: invalid character in literal");
				};
			};
			scan_real_exponent: {
				switch(*Current) {
				case '0' ... '9': ++Current; goto scan_real_exponent;
				default: {
					int Length = Current - Start;
					char Buffer[Length + 1];
					memcpy(Buffer, Start, Length);
					Buffer[Length] = 0;
					NextToken.Type = tkCONST;
					NextToken.Const = (Std$Object_t *)Std$Real$new_string(Buffer);
					goto scan_done;
				};
				};
			};
			scan_identifier: {
				switch(*Current) {
				case 'A' ... 'Z': case 'a' ... 'z': case '_': case '0' ... '9': ++Current; goto scan_identifier;
				default: {
					int Length = Current - Start;
					char *Identifier = new char[Length + 1];
					memcpy(Identifier, Start, Length);
					Identifier[Length] = 0;
					const struct keyword_t *Keyword = keyword::lookup(Identifier, Length);
					if (Keyword) {
						NextToken.Type = Keyword->Token;
					} else {
						NextToken.Type = tkIDENT;
						NextToken.Ident = Identifier;
					};
					goto scan_done;
				};
				};
			};
			scan_symbol: {
				switch (*Current) {
				case '?': {
					++Current;
					NextToken.Type = tkSYMBOL;
					NextToken.Const = (Std$Object_t *)Std$Symbol$new_string("<anon>");
					goto scan_done;
				};
				case 'A' ... 'Z': case 'a' ... 'z': case '_': Start = Current++; goto scan_symbol_identifier;
				case '\"': {
					++Current;
					int Type; void *Value;
					Riva$Module$import(Riva$Symbol, scan_string_next(this, &Current, 0), &Type, &Value);
					NextToken.Type = tkSYMBOL;
					NextToken.Const = (Std$Object_t *)Value;
					goto scan_done;
				};
				default: raise_error(NextToken.LineNo, "Error: invalid character in symbol");
				};
			};
			scan_symbol_identifier: {
				switch(*Current) {
				case 'A' ... 'Z': case 'a' ... 'z': case '_': case '0' ... '9': ++Current; goto scan_symbol_identifier;
				default: {
					int Length = Current - Start;
					char *Identifier = new char[Length + 1];
					memcpy(Identifier, Start, Length);
					Identifier[Length] = 0;
					int Type; void *Value;
					Riva$Module$import(Riva$Symbol, Identifier, &Type, &Value);
					NextToken.Type = tkSYMBOL;
					NextToken.Const = (Std$Object_t *)Value;
					goto scan_done;
				};
				};
			};
			scan_block_string: {
				const char *End = Current;
				NextToken.Type = tkCONST;
				NextToken.Const = (Std$Object_t *)scan_string_block_next(this, End, strlen(End), &Current, 0);
				goto scan_done;
			};
			scan_comment: {
				int Level = 1;
				comment_loop: {
					switch (*Current++) {
					case 0: Start = Current = IO$Stream$readl(Source);
						if (Current == 0) {
							raise_error(NextToken.LineNo, "Error: end of input in comment");
						} else {
							++NextToken.LineNo;
						};
						goto comment_loop;
					case '=':
						switch (*Current++) {
						case '-': if (--Level == 0) goto scan_loop;
						default: goto comment_loop;
						};
					case '-':
						switch (*Current++) {
						case '-': Start = Current = IO$Stream$readl(Source);
							if (Current == 0) {
								// RAISE ERROR HERE!!!
							} else {
								++NextToken.LineNo;
							};
						case '=': ++Level;
							goto comment_loop;
						};
					};
					goto comment_loop;
				};
			};
		};
	scan_done:
		NextChar = Current;
	};
	if (NextToken.Type == Type) {
		Token = NextToken;
		NextToken.Type = 0;
		return true;
	} else {
		return false;
	};
};

void scanner_t::accept(int Type) {
	if (!parse(Type)) raise_error(NextToken.LineNo, "Error: expected \"%s\" not \"%s\"", Tokens[Type], Tokens[NextToken.Type]);
};

void scanner_t::raise_error(int LineNo, const char *Format, ...) {
	va_list Args;
	va_start(Args, Format);
	vasprintf((char **)&Error.Message, Format, Args);
	va_end(Args);
	Error.LineNo = LineNo;
	longjmp(Error.Handler, 1);
};
