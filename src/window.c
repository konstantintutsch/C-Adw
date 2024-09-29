#include "window.h"

#include <adwaita.h>

#include <glib/gi18n.h>
#include <locale.h>

#include "answer.h"
#include "config.h"

/**
 * This function creates the main window for an AdwApplication.
 *
 * @param app The AdwApplication to create the window for.
 * @param about The AdwAboutDialogue of the application.
 *
 * @return A new AdwWindow
 */
AdwWindow *application_window_new(AdwApplication *app)
{
    // Base
    AdwWindow *window = ADW_WINDOW(adw_window_new());
    gtk_application_add_window(GTK_APPLICATION(app), GTK_WINDOW(window));
    gtk_window_set_default_size(GTK_WINDOW(window), 1100, 700);

    // Toolbar View
    AdwToolbarView *toolbar_view = ADW_TOOLBAR_VIEW(adw_toolbar_view_new());
    adw_window_set_content(window, GTK_WIDGET(toolbar_view));

    // Header Bar
    AdwHeaderBar *header_bar = ADW_HEADER_BAR(adw_header_bar_new());
    adw_toolbar_view_add_top_bar(toolbar_view, GTK_WIDGET(header_bar));
    adw_header_bar_set_title_widget(header_bar,
                                    adw_window_title_new(_("Template"), NULL));

    // Content
    GtkButton *greet = GTK_BUTTON(gtk_button_new());
    gtk_button_set_label(greet, _("Hey!"));
    adw_toolbar_view_set_content(toolbar_view, GTK_WIDGET(greet));
    g_signal_connect(greet, "clicked", G_CALLBACK(answer), NULL);

    return window;
}
