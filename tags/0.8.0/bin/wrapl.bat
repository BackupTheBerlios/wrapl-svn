@riva %~f0 %*
MOD Main;

IMP Std.String;
IMP Std.Symbol;
IMP IO.Terminal USE In, Out;
IMP Wrapl;
IMP Sys.Module;

Out:write("Interactive Wrapl Version: " + Wrapl.Version + "\n");

VAR session <- Wrapl.SessionNew(In);
VAR result;

REP (
	Out:write("--> ");
	(result <- Wrapl.SessionEval(session)) => (
		Out:write(result);
		RECV msg DO msg IN Symbol.NoMethodMessageT => (
			VAR mod;
			(mod <- Module.FromVal(result)) => (
				Out:writes(mod[1]:map("/", "."), ".", mod[2]);
			) // (
				Out:write("<value>");
			);
		) // (
			SEND msg;
		);
	) // (
		Out:write("failure");
	);
	RECV msg DO msg IN Wrapl.ErrorMessageT => (
		Out:writes("console", msg);
	) // (
		Out:write("Unhandled message: ");
		Out:write(msg);
		RECV msg2 DO Out:write("<value>");
	);
);

END Main.
