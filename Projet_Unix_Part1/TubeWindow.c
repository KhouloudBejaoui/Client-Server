#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

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
    const gchar *file = "/home/khouloud/Desktop/projetUnix/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_path(provider, g_filename_to_utf8(file, strlen(file), &bytes_read, &bytes_written, &error), NULL);
    g_object_unref(provider);
}
int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    GtkWidget *title1;
    GtkWidget *nombres;
    GtkWidget *window;
    GtkWidget *image1;
    GtkWidget *fixed;
    GtkWidget *type;
    load_css();

    // ouverture de fichier et lecture de résultat
    FILE *file;
    char ch[50];
    char res[100] = "";
    file = fopen("/home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/src/file.txt", "r");
    // erreur d'ouverture
    if (file == NULL)
    {
        printf("Erreur! lors de l'ouverture du fichier");
        exit(1);
    }
    // lire chaine
    while (fgets(ch, 50, file))
    {

        strcat(res, ch);
    }
    // fermeture de fichier
    fclose(file);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    nombres = gtk_label_new(res);

    gtk_fixed_put(GTK_FIXED(fixed), nombres, 50, 50);

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "Résultat avec Tube nommé");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
