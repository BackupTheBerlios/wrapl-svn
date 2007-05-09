#include <gtk/gtk.h>
#include <Lang.h>

GLOBAL_FUNCTION(Run, 0) {
	gtk_main();
	return SUCCESS;
};

GLOBAL_FUNCTION(Quit, 0) {
	gtk_main_quit();
	return SUCCESS;
};

void __dummy(void) {};

void __init(void) {
	gtk_init(0, 0);
};
