#include <gtk/gtk.h>
/*#include "render.h" */


static GtkWidget *main_window;
static GtkWidget *p_window;

static void print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

static void playing_window_destroy(GtkWidget *widget, gpointer data) {
  GtkWidget *window;

  gtk_window_destroy(GTK_WINDOW(gtk_widget_get_parent(gtk_widget_get_parent(widget))));
  gtk_widget_set_visible(GTK_WIDGET(gtk_widget_get_parent(gtk_widget_get_parent(main_window))), true);
  gtk_widget_show(main_window);
}

static void playing_window(GtkWidget *widget, gpointer data) {
  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *drawing_area;

  window = gtk_application_window_new(GTK_APPLICATION(data));
  gtk_window_set_title(GTK_WINDOW(window), "Fenêtre de jeu");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
  
  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  label = gtk_label_new("C'est la fenêtre de jeu !");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  button = gtk_button_new_with_label("Revenir au menu");
  g_signal_connect(button, "clicked", G_CALLBACK(playing_window_destroy), window);
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

/*
  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, 200, 200);
  g_signal_connect(drawing_area, "draw", G_CALLBACK(render), NULL);
  gtk_grid_attach(GTK_GRID(grid), drawing_area, 0, 0, 0, 1);
  gtk_container_add(GTK_CONTAINER(window), drawing_area);
  */
  
  gtk_widget_show(window);
  gtk_widget_set_visible(GTK_WIDGET(gtk_widget_get_parent(gtk_widget_get_parent(widget))), false );

  p_window=window;
}


static void activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Tetris");

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_window_set_child (GTK_WINDOW (window), grid);

  button = gtk_button_new_with_label ("Jouer");
  g_signal_connect(button, "clicked", G_CALLBACK(playing_window), app);


  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Option");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label ("Quitter");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  main_window = window;

  gtk_widget_show (window);

}

int main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return(status);
}