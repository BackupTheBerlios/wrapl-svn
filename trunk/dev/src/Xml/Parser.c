#include <Std.h>
#include <Riva/Memory.h>
#include <expat.h>

typedef struct parser_t {
	Std$Type_t *Type;
	XML_Parser Handle;
	Std$Object_t *UserData;
	Std$Function_t *StartElementHandler;
	Std$Function_t *EndElementHandler;
	Std$Function_t *CharacterDataHandler;
} parser_t;

typedef struct callback_t {
	Std$Function_t *Function;
	Std$Object_t *Object;
} callback_t;

TYPE(T);

static void startelementhandler(parser_t *Parser, const XML_Char *Name, const XML_Char **Attrs) {
	if (Parser->StartElementHandler != Std$Object$Nil) {
		Std$Function_result Result0;
		int NoOfAttrs = 0;
		for (const XML_Char **Attr = Attrs; Attr[0]; ++Attr) ++NoOfAttrs;
#ifdef WINDOWS
		Std$Function_argument *Args0 = Riva$Memory$alloc(sizeof(Std$Function_argument) * NoOfAttrs);
#else
		Std$Function_argument Args0[NoOfAttrs];
#endif
		for (int I = 0; I < NoOfAttrs; ++I) {
			Args0[I].Val = Std$String$copy(Attrs[I]);
			Args0[I].Ref = 0;
		};
		Std$Function$invoke(Std$Table$Make, NoOfAttrs, &Result0, Args0);
		Std$Function$call(Parser->StartElementHandler, 3, &Result0, Parser->UserData, &Parser->UserData, Std$String$copy(Name), 0, Result0.Val, 0);
	};
};

static void endelementhandler(parser_t *Parser, const XML_Char *Name) {
	if (Parser->EndElementHandler != Std$Object$Nil) {
		Std$Function_result Result0;
		Std$Function$call(Parser->EndElementHandler, 2, &Result0, Parser->UserData, &Parser->UserData, Std$String$copy(Name), 0);
	};
};

static void characterdatahandler(parser_t *Parser, const XML_Char *String, int Length) {
	if (Parser->CharacterDataHandler != Std$Object$Nil) {
		Std$Function_result Result0;
		Std$Function$call(Parser->CharacterDataHandler, 2, &Result0, Parser->UserData, &Parser->UserData, Std$String$copy_length(String, Length), 0);
	};	
};

GLOBAL_FUNCTION(New, 0) {
	parser_t *Parser = new(parser_t);
	Parser->Type = T;
	Parser->Handle = XML_ParserCreate(0);
	XML_SetUserData(Parser->Handle, Parser);

	Parser->UserData = Std$Object$Nil;
	Parser->StartElementHandler = Std$Object$Nil;
	Parser->EndElementHandler = Std$Object$Nil;
	Parser->CharacterDataHandler = Std$Object$Nil;

	XML_SetElementHandler(Parser->Handle, startelementhandler, endelementhandler);
	XML_SetCharacterDataHandler(Parser->Handle, characterdatahandler);

	Result->Val = Parser;
	return SUCCESS;
};

METHOD("parse", TYP, T, TYP, Std$String$T) {
	XML_Parser *Parser = ((parser_t *)Args[0].Val)->Handle;
	Std$String_t *String = Args[1].Val;
	for (int I = 0; I < String->Count; ++I) {
		XML_Parse(Parser, String->Blocks[I].Chars.Value, String->Blocks[I].Length.Value, 0);
	};
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("finish", TYP, T) {
	XML_Parser *Parser = ((parser_t *)Args[0].Val)->Handle;
	XML_Parse(Parser, 0, 0, 1);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("userdata", TYP, T) {
	parser_t *Parser = Args[0].Val;
	Result->Val = *(Result->Ref = &Parser->UserData);
	return SUCCESS;
};

METHOD("onstartelement", TYP, T) {
	parser_t *Parser = Args[0].Val;
	Result->Val = *(Result->Ref = &Parser->StartElementHandler);
	return SUCCESS;
};

METHOD("onendelement", TYP, T) {
	parser_t *Parser = Args[0].Val;
	Result->Val = *(Result->Ref = &Parser->EndElementHandler);
	return SUCCESS;
};

METHOD("oncharacterdata", TYP, T) {
	parser_t *Parser = Args[0].Val;
	Result->Val = *(Result->Ref = &Parser->CharacterDataHandler);
	return SUCCESS;
};
