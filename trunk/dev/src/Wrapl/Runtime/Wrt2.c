#include <Std.h>
#include <Riva.h>

SYMBOL($AS, "@");

GLOBAL_FUNCTION(CreateStringBlock, 0) {
	for (int I = 0; I < Count; ++I) {
		Std$Object_t *Arg = Args[I].Val;
		if (Arg->Type != Std$String$T) {
			int Status = Std$Function$call((Std$Object_t *)$AS, 2, Result, Arg, 0, Std$String$T, 0);
			if (Status >= FAILURE) return Status;
			Args[I].Val = Result->Val;
		};
	};
	int NoOfBlocks = 0, Length = 0;
	for (int I = 0; I < Count; ++I) {
		Std$String_t *String = (Std$String_t *)Args[I].Val;
		NoOfBlocks += String->Count;
		Length += String->Length.Value;
	};
	Std$String_t *String = (Std$String_t *)Riva$Memory$alloc(sizeof(Std$String_t) + (NoOfBlocks + 1) * sizeof(Std$String_block));
	String->Type = Std$String$T;
	String->Length.Type = Std$Integer$SmallT;
	String->Length.Value = Length;
	String->Count = NoOfBlocks;
	void *Block = String->Blocks;
	for (int I = 0; I < Count; ++I) {
		Std$String_t *String0 = (Std$String_t *)Args[I].Val;
#ifdef LINUX
		Block = mempcpy(Block, String0->Blocks, String0->Count * sizeof(Std$String_block));
#else
		int Length = String0->Count * sizeof(Std$String_block);
		memcpy(Block, String0->Blocks, Length);
		Block = Block + Length;
#endif
	};
	Result->Val = (Std$Object_t *)String;
	Result->Ref = 0;
	return SUCCESS;
};

