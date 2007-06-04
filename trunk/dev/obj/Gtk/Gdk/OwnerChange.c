#include <Gtk/Gdk/OwnerChange.h>

TYPE(T);

Gtk$Gdk$OwnerChange_t NewOwner[] = {{T, GDK_OWNER_CHANGE_NEW_OWNER}};
Gtk$Gdk$OwnerChange_t Destroy[] = {{T, GDK_OWNER_CHANGE_DESTROY}};
Gtk$Gdk$OwnerChange_t Close[] = {{T, GDK_OWNER_CHANGE_CLOSE}};
