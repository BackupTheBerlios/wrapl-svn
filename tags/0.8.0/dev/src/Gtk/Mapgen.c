#include <Riva.h>
#include <Util/StringTable.h>
#include <stdio.h>

static Util$StringTable_t GTypeModules[] = {Util$StringTable$INIT};

void __init() {
	FILE *MapFile = fopen("Types.map", "r");
	while (!feof(MapFile)) {
		const char *GtkName, *RivaName;
		if (fscanf(MapFile, "%a[a-zA-Z0-9] = %a[^\n]\n", &GtkName, &RivaName) == 2) {
			printf("Adding type: %s -> %s\n", GtkName, RivaName);
			Util$StringTable$put(GTypeModules, GtkName, (void *)RivaName);
		};
	};
	fclose(MapFile);
	FILE *OutFile = fopen("TypeMap.c", "w");
	fprintf(OutFile, "#include <Util/StringTable.h>\n\n");
	fprintf(OutFile, "static Util$StringTable_node __Entries__[%d] = {\n", GTypeModules->Size);
	for (int I = 0; I < GTypeModules->Size; ++I) {
		Util$StringTable_node *Node = GTypeModules->Entries + I;
		if (Node->Key) {
			fprintf(OutFile, "\t{\"%s\", %d, 0x%x, \"%s\"},\n", Node->Key, Node->Length, Node->Hash, Node->Value);
		} else {
			fprintf(OutFile, "\t{0, 0, 0, 0},\n");
		};
	};
	fprintf(OutFile, "};\n\n");
	fprintf(OutFile, "Util$StringTable_t Table[] = {Util$StringTable$T, %d, %d, __Entries__};\n", GTypeModules->Size, GTypeModules->Space);
	fclose(OutFile);
};
