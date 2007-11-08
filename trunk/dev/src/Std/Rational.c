#include <Std.h>
#include <Riva/Memory.h>
#include <gmp.h>

TYPE(T);

Std$Rational_t *_alloc(void) {
	Std$Rational_t *R = new(Std$Rational_t);
	R->Type = T;
	mpq_init(R->Value);
	return R;
};

Std$Rational_t *_new(mpq_t *V) {
	Std$Rational_t *R = new(Std$Rational_t);
	R->Type = T;
	mpq_init(R->Value);
	mpq_set(R->Value, V);
	return R;
};

METHOD("Rational.New", TYP, Std$String$T) {
	Std$Rational_t *R = new(Std$Rational_t);
	R->Type = T;
	mpq_init(R->Value);
	mpq_set_str(R->Value, Std$String$flatten(Args[0].Val), 10);
	mpq_canonicalize(R->Value);
	Result->Val = R;
	return SUCCESS;
};

METHOD("Rational.New", TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	Std$Rational_t *R = new(Std$Rational_t);
	R->Type = T;
	mpq_init(R->Value);
	mpq_set_si(R->Value, ((Std$Integer_smallt *)Args[0].Val)->Value, ((Std$Integer_smallt *)Args[1].Val)->Value);
	mpq_canonicalize(R->Value);
	Result->Val = R;
	return SUCCESS;
};

METHOD("Rational.New", TYP, Std$Integer$SmallT, TYP, Std$Integer$BigT) {
};

METHOD("Rational.New", TYP, Std$Integer$BigT, TYP, Std$Integer$SmallT) {
};

METHOD("Rational.New", TYP, Std$Integer$BigT, TYP, Std$Integer$BigT) {
};
