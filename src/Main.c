/* Include gtk
#include <gtk/gtk.h>

static void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  // Create a new button
  GtkWidget *button = gtk_button_new_with_label ("Hello, World!");
  // When the button is clicked, close the window passed as an argument
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_close), window);
  gtk_window_set_child (GTK_WINDOW (window), button);
  gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
} */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    /*define variables for user input*/
    char menu_option;    

    do
    {
        /*print out the main menu, taking in user input to select a function*/
        printf("Main Menu\n");
        printf("0: Haiku Verification\n");
        printf("1: Couplet Verification\n");
        printf("e: Exit Program\n");
        printf(" Please enter an option from the main menu: ");
        scanf(" %c", &menu_option);

        switch (menu_option)
        {
        case '0':
            
            break;
        case '1':
            
            break;
        case 'e':
            /*stop program execution*/
            break;
        default:
            /*handle invalid menu choices*/
            printf("invalid input");
            break;
        }

    } while (menu_option != 'e');