#include <Gtk/Gdk/Spawn.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Screen.h>
/***********************************/
GLOBAL_FUNCTION(CommandLineOnScreen, 3) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *command_line = Std$String$flatten(Args[1].Val);
	GError** error = 0;
	int result = gdk_spawn_command_line_on_screen(screen, command_line, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(OnScreen, 9) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *working_directory = Std$String$flatten(Args[1].Val);
	const char * const * argv;
	const char * const * envp;
	GSpawnFlags flags = 0;
	GSpawnChildSetupFunc child_setup = 0;
	void *user_data = ((Std$Address_t *)Args[6].Val)->Value;
	gint* child_pid = 0;
	GError** error = 0;
	int result = gdk_spawn_on_screen(screen, working_directory, argv, envp, flags, child_setup, user_data, child_pid, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(OnScreenWithPipes, 12) {
	GdkScreen * screen = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *working_directory = Std$String$flatten(Args[1].Val);
	const char * const * argv;
	const char * const * envp;
	GSpawnFlags flags = 0;
	GSpawnChildSetupFunc child_setup = 0;
	void *user_data = ((Std$Address_t *)Args[6].Val)->Value;
	gint* child_pid = 0;
	gint* standard_input = 0;
	gint* standard_output = 0;
	gint* standard_error = 0;
	GError** error = 0;
	int result = gdk_spawn_on_screen_with_pipes(screen, working_directory, argv, envp, flags, child_setup, user_data, child_pid, standard_input, standard_output, standard_error, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

