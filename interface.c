#include <gtk/gtk.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "./Projet_Unix_Part2/src/serv_cli.h"

// gcc `pkg-config --cflags gtk+-3.0` -o prog interface.c `pkg-config --libs gtk+-3.0`

void load_css(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;

    GdkScreen *scrw;
    // load css
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    scrw = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(scrw, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gsize bytes_written, bytes_read;
    const gchar *file = "style.css";
    GError *error = 0;
    gtk_css_provider_load_from_path(provider, g_filename_to_utf8(file, strlen(file), &bytes_read, &bytes_written, &error), NULL);
    g_object_unref(provider);
}
void button_click1()
{
    system("/home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/start/tube_run.sh");
}
void button_click2()
{

    system("/home/khouloud/Desktop/projetUnix/Projet_Unix_Part2/start/socket_run.sh");
}
int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

 system("gnome-terminal -e 'sh -c \"gcc -o /home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/build/server /home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/src/server.c && /home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/build/server\"'");

system("gnome-terminal -e 'sh -c \"gcc -o /home/khouloud/Desktop/projetUnix/Projet_Unix_Part2/build/server /home/khouloud/Desktop/projetUnix/Projet_Unix_Part2/src/server.c && /home/khouloud/Desktop/projetUnix/Projet_Unix_Part2/build/server\"'");

    GtkWidget *Label = NULL;
    gchar *TexteConverti = NULL;
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *img;
    GtkWidget *fixed;

    load_css();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    fixed = gtk_fixed_new();
    TexteConverti = g_locale_to_utf8(" Bienvenue \n Communication Client/Serveur ", -1, NULL, NULL, NULL); // Convertion du texte avec les balises
    Label = gtk_label_new(TexteConverti);                                                                // Application de la convertion à notre label
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);                                         // On centre notre texte
    button1 = gtk_button_new_with_mnemonic("Avec tube nommé");
    button2 = gtk_button_new_with_label("Avec les sockets : Tcp");
    gtk_widget_set_size_request(GTK_WIDGET(button2), 70, 70);
    gtk_widget_set_size_request(GTK_WIDGET(button1),70, 70);
    gtk_container_add(GTK_CONTAINER(window), fixed);
    //img = gtk_image_new_from_file("/home/khouloud/Desktop/projetUnix/bg.jpg");
    //gtk_fixed_put(GTK_FIXED(fixed), img, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), Label, 190, 50);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 200, 150);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 210, 250);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "Acceuil");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        g_signal_connect_swapped(button1, "clicked", G_CALLBACK(button_click1), window);
    g_signal_connect_swapped(button2, "clicked", G_CALLBACK(button_click2), window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    // a loop
    gtk_main();
    return 0;
}
   
