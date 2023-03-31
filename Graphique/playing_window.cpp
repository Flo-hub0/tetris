#include <menu2.h>
#include <gtk/gtk.h>

static void playing_window(GtkApplication *app, gpointer  user_data){
    *GtkWidget window;
    *GtkWidget game_window;
    *GtkWidget button;
    *GtkWidget grid;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Tetris");

}