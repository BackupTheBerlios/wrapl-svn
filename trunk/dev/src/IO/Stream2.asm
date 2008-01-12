%include "Util/TypedFunction.inc"

extern printf

datasect
format:
	db "Error: no method defined for %s", 0

%macro defaultfn 1
textsect
default_ %+ %1 :
	push %%str
	push format
	call printf
	add esp, byte 8
	ret
datasect
align 4
%%str:
	db '%1', 0
%endmacro

typed_func _flush, default_flush
typed_func _close, default_close
typed_func _eoi, default_eoi
typed_func _read, default_read
typed_func _readc, default_readc
typed_func _readn, default_readn
typed_func _readl, default_readl
typed_func _write, default_write
typed_func _writec, default_writec
typed_func _writes, default_writes
typed_func _writef, default_writef
typed_func _seek, default_seek
typed_func _tell, default_tell

defaultfn flush
defaultfn close
defaultfn eoi
defaultfn read
defaultfn readc
defaultfn readn
defaultfn readl
defaultfn write
defaultfn writec
defaultfn writes
defaultfn writef
defaultfn seek
defaultfn tell
