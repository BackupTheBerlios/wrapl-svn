#include "system.h"

#define emit(FORMAT, ARGS...) IO$Stream$writef(Assembler->Output, FORMAT "\n", ## ARGS)

void encode_entry(assembler_t *Assembler) {
	//writef("section .t%d exec", Label);
	if (Assembler->NoOfUpScopes) {
		emit("\tlea esi, [closure(ecx).Scopes]");
	};
	emit("\tpush dword %d", Assembler->Size);
	emit("\tcall Riva$Memory$_alloc");
	emit("\tmov [esp], eax");
	if (Assembler->NoOfParams) {
		emit("\tpush edi");
		emit("\tpush esi");
	};
	if (Assembler->NoOfUpScopes) {
		emit("\tlea edi, [eax + %d]", Assembler->UpScopes);
		emit("\tmov ecx, %d", Assembler->NoOfUpScopes);
		emit("\trep movsd");
	};
	emit("\tlea edi, [eax + %d]", Assembler->Locals);
	emit("\tmov [eax + %d], edi", Assembler->Scopes);
	if (Assembler->NoOfParams) {
		emit("\tpop ebx");
		if (CmovSupport) {
			emit("\tmov edx, %d", Assembler->NoOfParams);
			emit("\tcmp edx, ebx");
			emit("\tcmova edx, ebx");
		} else {
			emit("\tsub ebx, %d", Assembler->NoOfParams);
			emit("\tsbb edx, edx");
			emit("\tand edx, ebx");
			emit("\tadd edx, %d", Assembler->NoOfParams);
		};
		emit("\tlea ecx, [edx * 2]");
		emit("\tpop esi");
		emit("\trep movsd");
		emit("\tneg edx");
		emit("\tlea ecx, [edx * 2 + 2 * %d]", Assembler->NoOfLocals);
		emit("\tmov eax, Std$Object$Nil");
		emit("\trep stosd");
	} else if (Assembler->NoOfLocals) {
		emit("\tmov ecx, 2 * %d", Assembler->NoOfLocals);
		emit("\tmov eax, Std$Object$Nil");
		emit("\trep stosd");
	};
	emit("\tpop eax");
	emit("\tmov [state(eax).Run], dword Wrapl$Runtime$_run_state");
	emit("\tmov [bstate(eax).Handler], dword Wrapl$Runtime$_resend_message");
	emit("\tpush ebp");
	emit("\tmov ebp, eax");
	emit("\txor edx, edx");
};

void label_t::encode(assembler_t *Assembler) {
	if (Referenced) {
		emit("..@L%x:", this);
	};
};

void link_inst_t::encode(assembler_t *Assembler) {
	emit("\tjmp ..@L%x", Link->final());
};

void init_trap_inst_t::encode(assembler_t *Assembler) {
	emit("\tlea eax, [ebp + %d]", Assembler->Temps + 8 * Trap + 4);
	emit("\tmov [eax - 4], eax");
	emit("\tmov [eax], dword ..@L%x", Failure->final());
};

void push_trap_inst_t::encode(assembler_t *Assembler) {
	emit("\tlea ebx, [ebp + %d]", Assembler->Temps + 8 * Temp);
	emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Trap);
	emit("\tmov [ebp + %d], ebx", Assembler->Temps + 8 * Trap);
	emit("\tmov [state(ebx).Run], dword ..@L%x", Failure->final());
	emit("\tmov [state(ebx).Chain], eax");
};

void resume_inst_t::encode(assembler_t *Assembler) {
	emit("\tadd esp, 12");
};

void scope_inst_t::encode(assembler_t *Assembler) {
	emit("\tpush dword %d", Size * 8);
	emit("\tcall Riva$Memory$_alloc");
	emit("\tpop ecx");
	emit("\tmov [ebp + %d], eax", Assembler->Scopes + 4 * Index);
	emit("\tmov edi, eax");
	emit("\tmov eax, Std$Object$Nil");
	emit("\tmov ecx, %d", Size * 2);
	emit("\trep stosd");
};

static inline void load_closure(assembler_t *Assembler, operand_t *Operand) {
	int NoOfUpScopes = 0;
	for (upscope_t *UpScope = Operand->UpScopes; UpScope; UpScope = UpScope->Next) ++NoOfUpScopes;
	emit("\tpush %d", sizeof(closure_t) + 4 * NoOfUpScopes);
	emit("\tcall Riva$Memory$_alloc");
	emit("\tpop ecx");
	emit("\tmov dword value(eax).Type, WraplT");
	emit("\tmov dword closure(eax).Entry, %s", Operand->Entry);
	for (upscope_t *UpScope = Operand->UpScopes; UpScope; UpScope = UpScope->Next) {
		if (UpScope->Index < 0) {
			emit("\tmov ecx, [ebp + %d]", Assembler->UpScopes - 4 * UpScope->Index + 8);
		} else {
			emit("\tmov ecx, [ebp + %d]", Assembler->Scopes + 4 * UpScope->Index);
		};
		emit("\tmov [eax + %d], ecx", 8 + 4 * --NoOfUpScopes);
	};
	emit("\tmov ecx, eax");
};

void load_inst_t::encode(assembler_t *Assembler) {
	switch (Operand->Type) {
	case operand_t::CNST: {
		switch (Type) {
		case LOAD_VAL: {
			emit("\tmov ecx, %s", Operand->Value);
			break;
		};
		case LOAD_REF: {
			emit("\txor edx, edx");
			break;
		};
		case LOAD_ARG:
		case LOAD_BOTH: {
			emit("\tmov ecx, %s", Operand->Value);
			emit("\txor edx, edx");
			break;
		};
		};
		break;
	};
	case operand_t::GVAR: {
		switch (Type) {
		case LOAD_VAL: {
			emit("\tmov ecx, [%s]", Operand->Address);
			break;
		};
		case LOAD_REF:
		case LOAD_ARG: {
			emit("\tmov edx, %s", Operand->Address);
			break;
		};
		case LOAD_BOTH: {
			emit("\tmov edx, %s", Operand->Address);
			emit("\tmov ecx, [edx]");
			break;
		};
		};
		break;
	};
	case operand_t::LVAR: {
		switch (Type) {
		case LOAD_VAL: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tmov ecx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
				break;
			};
			case 0: {
				emit("\tmov ecx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index);
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov ecx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov ecx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				emit("\tmov ecx, [ecx + %d]", 8 * Operand->Index);
				break;
			};
			};
			break;
		};
		case LOAD_REF:
		case LOAD_ARG: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tlea edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
				break;
			};
			case 0: {
				emit("\tlea edx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index);
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov edx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov edx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				if (Operand->Index) {
					emit("\tadd edx, %d", 8 * Operand->Index);
				};
				break;
			};
			};
			break;
		};
		case LOAD_BOTH: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tlea edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
				emit("\tmov ecx, [edx]");
				break;
			};
			case 0: {
				emit("\tlea edx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index);
				emit("\tmov ecx, [edx]");
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov edx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov edx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				if (Operand->Index) {
					emit("\tadd edx, %d", 8 * Operand->Index);
				};
				emit("\tmov ecx, [edx]");
				break;
			};
			};
			break;
		};
		};
		break;
	};
	case operand_t::LREF: {
		switch (Type) {
		case LOAD_VAL: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tmov ecx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
				emit("\tmov ecx, [ecx]");
				break;
			};
			case 0: {
				emit("\tmov ecx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index + 4);
				emit("\tmov ecx, [ecx]");
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov ecx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov ecx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				emit("\tmov ecx, [ecx + %d]", 8 * Operand->Index + 4);
				emit("\tmov ecx, [ecx]");
				break;
			};
			};
			break;
		};
		case LOAD_REF:
		case LOAD_ARG: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tmov edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
				break;
			};
			case 0: {
				emit("\tmov edx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index + 4);
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov edx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov edx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				emit("\tmov edx, [edx + %d]", 8 * Operand->Index + 4);
				break;
			};
			};
			break;
		};
		case LOAD_BOTH: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tmov edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
				emit("\tmov ecx, [edx]");
				break;
			};
			case 0: {
				emit("\tmov edx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index + 4);
				emit("\tmov ecx, [edx]");
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov edx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov edx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				emit("\tmov edx, [edx + %d]", 8 * Operand->Index + 4);
				emit("\tmov ecx, [edx]");
				break;
			};
			};
			break;
		};
		};
		break;
	};
	case operand_t::TEMP: {
		switch (Type) {
		case LOAD_VAL: {
			emit("\tmov ecx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
			break;
		};
		case LOAD_REF: {
			emit("\tmov edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
			break;
		};
		case LOAD_ARG:
		case LOAD_BOTH: {
			emit("\tmov ecx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
			emit("\tmov edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
			break;
		};
		};
		break;
	};
	case operand_t::CLSR: {
		switch (Type) {
		case LOAD_VAL: {
			load_closure(Assembler, Operand);
			break;
		};
		case LOAD_REF: {
			emit("\txor edx, edx");
			break;
		};
		case LOAD_ARG:
		case LOAD_BOTH: {
			load_closure(Assembler, Operand);
			emit("\txor edx, edx");
			break;
		};
		};
		break;
	};
	};
};

static inline void store_reg(assembler_t *Assembler, operand_t *Operand) {
	switch (Operand->Type) {
	case operand_t::GVAR: {
		emit("\tmov [%s], ecx", Operand->Address);
		break;
	};
	case operand_t::LVAR: {
		switch (Operand->Loop) {
		case -1: {
			emit("\tmov [ebp + %d], ecx", Assembler->Temps + 8 * Operand->Index);
			break;
		};
		case 0: {
			emit("\tmov [ebp + %d], ecx", Assembler->Locals + 8 * Operand->Index);
			break;
		};
		default: {
			if (Operand->Loop < 0) {
				emit("\tmov eax, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
			} else {
				emit("\tmov eax, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
			};
			emit("\tmov [eax + %d], ecx", 8 * Operand->Index);
			break;
		};
		};
		break;
	};
	case operand_t::LREF: {
		switch (Operand->Loop) {
		case -1: {
			emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
            emit("\ttest eax, eax");
            emit("\tjz Wrapl$Runtime$_incorrect_assign");
			emit("\tmov [eax], ecx");
			break;
		};
		case 0: {
			emit("\tmov eax, [ebp + %d]", Assembler->Locals + 8 * Operand->Index + 4);
            emit("\ttest eax, eax");
            emit("\tjz Wrapl$Runtime$_incorrect_assign");
			emit("\tmov [eax], ecx");
			break;
		};
		default: {
			if (Operand->Loop < 0) {
				emit("\tmov eax, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
			} else {
				emit("\tmov eax, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
			};
			emit("\tmov eax, [eax + %d]", 8 * Operand->Index + 4);
            emit("\ttest eax, eax");
            emit("\tjz Wrapl$Runtime$_incorrect_assign");
			emit("\tmov [eax], ecx");
			break;
		};
		};
		break;
	};
	case operand_t::TEMP: {
		emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
        emit("\ttest eax, eax");
        emit("\tjz Wrapl$Runtime$_incorrect_assign");
		emit("\tmov [eax], ecx");
		break;
	};
	};
};

void store_con_inst_t::encode(assembler_t *Assembler) {
	switch (Type) {
	case LOAD_REF:
		emit("\txor edx, edx");
	case LOAD_NONE:
		switch (Operand->Type) {
		case operand_t::GVAR: {
			emit("\tmov dword [%s], %s", Operand->Address, Value);
			break;
		};
		case operand_t::LVAR: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tmov dword [ebp + %d], %s", Assembler->Temps + 8 * Operand->Index, Value);
				break;
			};
			case 0: {
				emit("\tmov dword [ebp + %d], %s", Assembler->Locals + 8 * Operand->Index, Value);
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov eax, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov eax, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				emit("\tmov dword [eax + %d], %s", 8 * Operand->Index, Value);
				break;
			};
			};
			break;
		};
		case operand_t::LREF: {
			switch (Operand->Loop) {
			case -1: {
				emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
                emit("\ttest eax, eax");
                emit("\tjz Wrapl$Runtime$_incorrect_assign");
				emit("\tmov dword [eax], %s", Value);
				break;
			};
			case 0: {
				emit("\tmov eax, [ebp + %d]", Assembler->Locals + 8 * Operand->Index + 4);
                emit("\ttest eax, eax");
                emit("\tjz Wrapl$Runtime$_incorrect_assign");
				emit("\tmov dword [eax], %s", Value);
				break;
			};
			default: {
				if (Operand->Loop < 0) {
					emit("\tmov eax, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
				} else {
					emit("\tmov eax, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
				};
				emit("\tmov eax, [eax + %d]", 8 * Operand->Index + 4);
                emit("\ttest eax, eax");
                emit("\tjz Wrapl$Runtime$_incorrect_assign");
				emit("\tmov dword [eax], %s", Value);
				break;
			};
			};
			break;
		};
		case operand_t::TEMP: {
			emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
            emit("\ttest eax, eax");
            emit("\tjz Wrapl$Runtime$_incorrect_assign");
			emit("\tmov dword [eax], %s", Value);
			break;
		};
		case operand_t::REGR: {
            emit("\ttest edx, edx");
            emit("\tjz Wrapl$Runtime$_incorrect_assign");
			emit("\tmov dword [edx], %s", Value);
			break;
		};
		};
		break;
	case LOAD_ARG: case LOAD_BOTH:
		emit("\txor edx, edx");
	case LOAD_VAL:
		emit("\tmov ecx, %s", Value);
		store_reg(Assembler, Operand);
		break;
	};
};

void store_val_inst_t::encode(assembler_t *Assembler) {
	store_reg(Assembler, Operand);
};

void store_ref_inst_t::encode(assembler_t *Assembler) {
	switch (Operand->Loop) {
	case -1: {
		emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Operand->Index + 4);
		break;
	};
	case 0: {
		emit("\tmov [ebp + %d], edx", Assembler->Locals + 8 * Operand->Index + 4);
		break;
	};
	default: {
		if (Operand->Loop < 0) {
			emit("\tmov eax, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
		} else {
			emit("\tmov eax, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
		};
		emit("\tmov [eax + %d], edx", 8 * Operand->Index + 4);
		break;
	};
	};
};

void store_arg_inst_t::encode(assembler_t *Assembler) {
	switch (Operand->Type) {
	case operand_t::CNST: {
		emit("\tmov dword [ebp + %d], %s", Assembler->Temps + 8 * Index, Operand->Value);
		emit("\tmov dword [ebp + %d], 0", Assembler->Temps + 8 * Index + 4);
		break;
	};
	case operand_t::GVAR: {
		emit("\tmov dword [ebp + %d], %s", Assembler->Temps + 8 * Index + 4, Operand->Value);
		break;
	};
	case operand_t::LVAR: {
		switch (Operand->Loop) {
		case -1: {
			emit("\tlea edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
			emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
			break;
		};
		case 0: {
			emit("\tlea edx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index);
			emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
			break;
		};
		default: {
			if (Operand->Loop < 0) {
				emit("\tmov edx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
			} else {
				emit("\tmov edx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
			};
			if (Operand->Index) {
				emit("\tadd edx, %d", 8 * Operand->Index);
			};
			emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
			break;
		};
		};
		break;
	};
	case operand_t::LREF: {
		switch (Operand->Loop) {
		case -1: {
			emit("\tmov edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
			emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
			break;
		};
		case 0: {
			emit("\tmov edx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index + 4);
			emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
			break;
		};
		default: {
			if (Operand->Loop < 0) {
				emit("\tmov edx, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
			} else {
				emit("\tmov edx, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
			};
			emit("\tmov edx, [edx + %d]", 8 * Operand->Index + 4);
			emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
			break;
		};
		};
		break;
	};
	case operand_t::TEMP: {
		emit("\tmov ecx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
		emit("\tmov edx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
		emit("\tmov [ebp + %d], ecx", Assembler->Temps + 8 * Index);
		emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
		break;
	};
	case operand_t::CLSR: {
		load_closure(Assembler, Operand);
		emit("\tmov [ebp + %d], ecx", Assembler->Temps + 8 * Index);
		emit("\tmov dword [ebp + %d], 0", Assembler->Temps + 8 * Index + 4);
		break;
	};
	case operand_t::REGR: {
		emit("\tmov [ebp + %d], ecx", Assembler->Temps + 8 * Index);
		emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
		break;
	};
	};
};

void fixup_arg_inst_t::encode(assembler_t *Assembler) {
	switch (Operand->Type) {
	case operand_t::CNST: {
		break;
	};
	case operand_t::GVAR: {
		emit("\tmov eax, [%s]", Operand->Address);
		emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
		break;
	};
	case operand_t::LVAR: {
		switch (Operand->Loop) {
		case -1: {
			emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
			emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
			break;
		};
		case 0: {
			emit("\tmov eax, [ebp + %d]", Assembler->Locals + 8 * Operand->Index);
			emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
			break;
		};
		default: {
			emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Index + 4);
			emit("\tmov eax, [eax]");
			emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
			break;
		};
		};
		break;
	};
	case operand_t::LREF: {
		emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Index + 4);
		emit("\tmov eax, [eax]");
		emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
		break;
	};
	case operand_t::TEMP: {
		emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Index + 4);
		emit("\ttest eax, eax");
		emit("\tjz ..@I%x", this);
		emit("\tmov eax, [eax]");
		emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
		emit("..@I%x:", this);
		break;
	};
	case operand_t::CLSR: {
		break;
	};
	case operand_t::REGR: {
		emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Index + 4);
		emit("\ttest eax, eax");
		emit("\tjz ..@I%x", this);
		emit("\tmov eax, [eax]");
		emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
		emit("..@I%x:", this);
		break;
	};
	};
};

void store_tmp_inst_t::encode(assembler_t *Assembler) {
	emit("\tmov [ebp + %d], ecx", Assembler->Temps + 8 * Index);
	emit("\tmov [ebp + %d], edx", Assembler->Temps + 8 * Index + 4);
};

void flush_inst_t::encode(assembler_t *Assembler) {
};

void invoke_inst_t::encode(assembler_t *Assembler) {
	if (Count) {
		emit("\tmov esi, %d", Count);
		emit("\tlea edi, [ebp + %d]", Assembler->Temps + 8 * Args);
	} else {
		emit("\txor esi, esi");
	};
	emit("\tpush %d", Assembler->Temps + 8 * Trap);
	emit("\tcall Wrapl$Runtime$_invoke_function");
};

void back_inst_t::encode(assembler_t *Assembler) {
	emit("\tmov edi, %d", Assembler->Temps + 8 * Trap);
	emit("\tjmp Wrapl$Runtime$_backtrack");
};

void ret_inst_t::encode(assembler_t *Assembler) {
	emit("\txor eax, eax");
	emit("\tpop ebp");
	emit("\tret");
};

void susp_inst_t::encode(assembler_t *Assembler) {
	emit("\tmov ebx, ebp");
	emit("\tmov [bstate(ebx).Val], ecx");
	emit("\tmov [bstate(ebx).Ref], edx");
	emit("\tmov [bstate(ebx).Code], dword ..@I%x", this);
	emit("\tor eax, -1");
	emit("\tpop ebp");
	emit("\tret");
	emit("..@I%x:", this);
};

void fail_inst_t::encode(assembler_t *Assembler) {
	emit("\txor eax, eax");
	emit("\tpop ebp");
	emit("\tinc eax");
	emit("\tret");
};

void recv_inst_t::encode(assembler_t *Assembler) {
	if (Handler) {
		emit("\tmov [bstate(ebp).Handler], dword ..@L%x", Handler->final());
	} else {
		emit("\tmov [bstate(ebp).Handler], dword Wrapl$Runtime$_resend_message");
	};
};

void send_inst_t::encode(assembler_t *Assembler) {
	emit("\tmov eax, 2");
	emit("\tjmp dword [bstate(ebp).Handler]");
};

void comp_inst_t::encode(assembler_t *Assembler) {
	switch (Operand->Type) {
	case operand_t::CNST: {
		emit("\tcmp ecx, %s", Operand->Value);
		break;
	};
	case operand_t::GVAR: {
		emit("\tcmp ecx, [%s]", Operand->Address);
		break;
	};
	case operand_t::LVAR: {
		switch (Operand->Loop) {
		case -1: {
			emit("\tcmp ecx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
			break;
		};
		case 0: {
			emit("\tcmp ecx, [ebp + %d]", Assembler->Locals + 8 * Operand->Index);
			break;
		};
		default: {
			if (Operand->Loop < 0) {
				emit("\tmov eax, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
			} else {
				emit("\tmov eax, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
			};
			emit("\tcmp ecx, [eax + %d]", 8 * Operand->Index);
			break;
		};
		};
		break;
	};
	case operand_t::LREF: {
		switch (Operand->Loop) {
		case -1: {
			emit("\tmov eax, [ebp + %d]", Assembler->Temps + 8 * Operand->Index + 4);
			emit("\tcmp ecx, [eax]");
			break;
		};
		case 0: {
			emit("\tmov eax, [ebp + %d]", Assembler->Locals + 8 * Operand->Index + 4);
			emit("\tcmp ecx, [eax]");
			break;
		};
		default: {
			if (Operand->Loop < 0) {
				emit("\tmov eax, [ebp + %d]", Assembler->UpScopes - 4 * Operand->Loop - 8);
			} else {
				emit("\tmov eax, [ebp + %d]", Assembler->Scopes + 4 * Operand->Loop);
			};
			emit("\tmov eax, [eax + %d]", 8 * Operand->Index + 4);
			emit("\tcmp ecx, [eax]");
			break;
		};
		};
		break;
	};
	case operand_t::TEMP: {
		emit("\tcmp ecx, [ebp + %d]", Assembler->Temps + 8 * Operand->Index);
		break;
	};
	case operand_t::CLSR: {
		emit("\tcmp ecx, 0");
		break;
	};
	};
	if (Equal) {
		emit("\tjne ..@%x", Failure);
	} else {
		emit("\tje ..@%x", Failure);
	};
};

typedef struct select_integer_entry_t {
	uint32_t Key;
	label_t *Label;
} select_integer_entry_t;

static void select_integer_entries_sort(select_integer_entry_t *A, select_integer_entry_t *B) {
	if (A >= B) return;
	select_integer_entry_t *C = A, *D = B;
	select_integer_entry_t T = *A, S = *B;
	while (C < D) {
		if (S.Key < T.Key) {
			*C = S;
			++C;
			S = *C;
		} else {
			*D = S;
			--D;
			S = *D;
		};
	};
	*C = T;
	select_integer_entries_sort(A, C - 1);
	select_integer_entries_sort(C + 1, B);
};

void select_integer_inst_t::encode(assembler_t *Assembler) {
	case_t *Case;

	emit("\tcmp dword value(ecx).Type, Std$Integer$SmallT");
	emit("\tjne Wrapl$Runtime$_incorrect_type");

	Case = Cases;
	int Min = Case->Min, Max = Case->Max;
	int Count = Max - Min + 1;
	while (Case = Case->Next) {
		if (Case->Min < Min) Min = Case->Min;
		if (Case->Max > Max) Max = Case->Max;
		Count += (Case->Max - Case->Min + 1);
	};
	int Range = Max - Min + 1;
	int DispFix = 1;
	if (Range > 2 * Count) {
		select_integer_entry_t Entries[2 * Count];
		uint32_t M = Count;
	next:
		memset(Entries, 0, M * sizeof(select_integer_entry_t));
		for (Case = Cases; Case; Case = Case->Next) {
			int32_t K = Case->Max;
			uint32_t T = K - Case->Min + 1;
			uint32_t I = ((K % M) + M) % M;
			do {
				if (Entries[I].Label) {
					if (Entries[I].Key == K) {
						printf("Stupid user has duplicate keys: %d\n", K);
					} else if (++M >= Count * 2) {
						M = 1; while (M < Count) M <<= 1;
						uint32_t A = (M - Count) / 2;
						uint32_t B = (M - Count) - A;
						select_integer_entry_t *Top = Entries;
						for (Case = Cases; Case; Case = Case->Next) {
							for (I = Case->Min; I <= Case->Max; ++I) {
								Top->Key = I;
								Top->Label = Case->Body;
								++Top;
							};
						};
						--Top;
						select_integer_entries_sort(Entries, Top);
						emit("\tmov eax, [ecx + 4]");
						emit("\tmov edx, %d", M / 2);
						emit("\tmov ebx, %d", M / 2 - 1);
						emit("..@I%x_1", this);
						emit("\tcmp eax, [ebx * 8 + ..@I%x_2]", this);
						emit("\tja ..@I%x_3", this);
						emit("\tjb ..@I%x_4", this);
						emit("\tjmp dword [ebx * 8 + ..@I%x_5]", this);
						emit("..@I%x_3:", this);
						emit("\tshr edx, 1");
						emit("\tjz ..@L%x", Default->final());
						emit("\tadd ebx, edx");
						emit("\tjmp ..@I%x_1", this);
						emit("..@L%x_4:", this);
						emit("\tshr edx, 1");
						emit("\tjz ..@L%x", Default->final());
						emit("\tsub ebx, edx");
						emit("\tjmp ..@I%x_1", this);
						emit("..@I%x_2", this);
						for (int I = 0; I < A; ++I) {
							emit("\tdd %d", Entries[0].Key);
							if (DispFix) {
								emit("..@I%x_5", this);
								DispFix = 0;
							};
							emit("\tdd ..@L%x", Entries[0].Label->final());
						};
						for (int I = 0; I < Count; ++I) {
							emit("\tdd %d", Entries[I].Key);
							if (DispFix) {
								emit("..@I%x_5:", this);
								DispFix = 0;
							};
							emit("\tdd ..@L%x", Entries[I].Label->final());
						};
						for (int I = 0; I < B; ++I) {
							emit("\tdd %d", Top->Key);
							if (DispFix) {
								emit("..@I%x_5:", this);
								DispFix = 0;
							};
							emit("\tdd\ ..@L%x", Top->Label->final());
						};
						return;
					};
					goto next;
				};
				Entries[I].Key = K;
				Entries[I].Label = Case->Body;
				I = I ? I - 1 : M - 1;
				--K;
			} while (--T);
		};
		emit("\tmov ecx, [ecx + 4]");
		emit("\tmov eax, ecx");
		emit("\txor edx, edx");
		emit("\tmov ebx, %d", M);
		emit("\tdiv ebx");
		emit("\tcmp [edx * 8 + ..@I%x_1], ecx", this);
		emit("\tjne ..@L%x", Default->final());
		emit("\tjmp dword [edx * 8 + ..@I%x_2]", this);
		emit("..@I%x_1:", this);
		for (int I = 0; I < M; ++I) {
			emit("\tdd %d", Entries[I].Key);
			if (DispFix) {
				emit("..@I%x_2:", this);
				DispFix = 0;
			};
			if (Entries[I].Label) {
				emit("\tdd ..@L%x", Entries[I].Label->final());
			} else {
				emit("\tdd ..@L%x", Default->final());
			};
		};
		return;
	} else {
		label_t *Labels[Range];
		memset(Labels, 0, Range * sizeof(label_t *));
		for (Case = Cases; Case; Case = Case->Next) {
			for (int I = Case->Min; I <= Case->Max; ++I) Labels[I - Min] = Case->Body;
		};
		emit("\tmov eax, [ecx + 4]");
		emit("\tsub eax, %d", Min);
		emit("\tjs ..@L%x", Default->final());
		emit("\tcmp eax, %d", Max - Min);
		emit("\tja ..@L%x", Default->final());
		emit("\tjmp dword [eax * 4 + ..@I%x_1]", this);
		emit("align 4");
		emit("..@I%x_1:", this);
		for (int I = 0; I < Range; ++I) {
			if (Labels[I]) {
				emit("\tdd ..@L%x", Labels[I]->final());
			} else {
				emit("\tdd ..@L%x", Default->final());
			}
		};
	};
};

void select_string_inst_t::encode(assembler_t *Assembler) {
	emit("\tcall Wrapl$Runtime$_select_string");
	emit("..@I%x_1:", this);
	if (Cases->Length) {
		emit("\tdd 0");
		emit("\tdd 0");
		emit("\tdd ..@L%x", Default->final());
	};
	for (case_t *Case = Cases; Case; Case = Case->Next) {
		emit("\tdd %d", Case->Length);
		emit("\tdd ..@SS%x", Case->Key);
		emit("\tdd ..@L%x", Case->Body->final());
	};
	emit("\tdd 0");
	emit("\tdd 0");
	emit("\tdd ..@L%x", Default->final());
	for (case_t *Case = Cases; Case; Case = Case->Next) {
		emit("..@SS%x:", Case->Key);
		for (int I = 0; I < Case->Length; ++I) emit("\tdb %d", Case->Key[I]);
	};
	emit("align 4");
};

void select_object_inst_t::encode(assembler_t *Assembler) {
	for (case_t *Case = Cases; Case; Case = Case->Next) {
		emit("\tcmp ecx, %s", Case->Object);
		emit("\tje ..@L%x", Case->Body->final());
	};
};

void store_link_inst_t::encode(assembler_t *Assembler) {
	emit("\tmov dword [ebp + %d], ..@L%x", Assembler->Temps + 8 * Temp, Target->final());
};

void jump_link_inst_t::encode(assembler_t *Assembler) {
	emit("\tjmp dword [ebp + %d]", Assembler->Temps + 8 * Temp);
};

void test_limit_inst_t::encode(assembler_t *Assembler) {
	emit("\tdec dword [ebp + %d]", Assembler->Temps + 8 * Temp);
	emit("\tjz ..@L%x", Target->final());
};

void limit_inst_t::encode(assembler_t *Assembler) {
	emit("\tcmp dword value(ecx).Type, Std$Integer$SmallT");
	emit("\tjne Wrapl$Runtime$_incorrect_type");
	emit("\tmov ecx, small_int(ecx).Value");
	emit("\tmov edi, %d", Assembler->Temps + 8 * Trap);
	emit("\ttest ecx, ecx");
	emit("\tjz Wrapl$Runtime$_backtrack");
	emit("\tmov [ebp + %d], ecx", Assembler->Temps + 8 * Temp);
};

void skip_inst_t::encode(assembler_t *Assembler) {
	emit("\tcmp dword value(ecx).Type, Std$Integer$SmallT");
	emit("\tjne Wrapl$Runtime$_incorrect_type");
	emit("\tmov ecx, small_int(ecx).Value");
	emit("\tmov [ebp + %d], ecx", Assembler->Temps + 8 * Temp);
};

void test_skip_inst_t::encode(assembler_t *Assembler) {
	emit("\tdec dword [ebp + %d]", Assembler->Temps + 8 * Temp);
	emit("\tmov edi, %d", Assembler->Temps + 8 * Trap);
	emit("\tjns Wrapl$Runtime$_backtrack");
	emit("\tinc dword [ebp + %d]", Assembler->Temps + 8 * Temp);
};

void type_of_inst_t::encode(assembler_t *Assembler) {
	switch (Type) {
	case LOAD_VAL: {
		emit("\tmov ecx, value(ecx).Type");
		break;
	};
	case LOAD_REF: {
		emit("\txor edx, edx");
		break;
	};
	case LOAD_ARG:
	case LOAD_BOTH: {
		emit("\tmov ecx, value(ecx).Type");
		emit("\txor edx, edx");
		break;
	};
	};
};

void new_list_inst_t::encode(assembler_t *Assembler) {
	emit("\tpush sizeof(list)");
	emit("\tcall Riva$Memory$_alloc");
	emit("\tpop edx");
	emit("\tmov dword [value(eax).Type], Std$List$T");
	emit("\tmov dword [list(eax).Access], 4");
	emit("\tmov [ebp + %d], eax", Assembler->Temps + 8 * Index);
};

void store_list_inst_t::encode(assembler_t *Assembler) {
	emit("\tmov ebx, ecx");
	emit("\tpush sizeof(listnode)");
	emit("\tcall Riva$Memory$_alloc");
	emit("\tpop edx");
	emit("\tmov [listnode(eax).Value], ebx");
	emit("\tmov edx, [ebp + %d]", Assembler->Temps + 8 * Index);
	emit("\tinc dword [list(edx).Length]");
	emit("\tmov ecx, [list(edx).Tail]");
	emit("\ttest ecx, ecx");
	emit("\tjz ..@I%x_1", this);
	emit("\tmov [listnode(eax).Prev], ecx");
	emit("\tmov [listnode(ecx).Next], eax");
	emit("\tjmp ..@I%x_2", this);
	emit("..@I%x_1:", this);
	emit("\tmov [list(edx).Head], eax");
	emit("\tmov [list(edx).Cache], eax");
	emit("\tinc dword [list(edx).Index]");
	emit("..@I%x_2:", this);
	emit("\tmov [list(edx).Tail], eax");
};

void encode_potential_breakpoint(assembler_t *Assembler, uint32_t LineNo) {
//	emit("mov eax, LineNo
//	emit("call &potential_breakpoint
};
