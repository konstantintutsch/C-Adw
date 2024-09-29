#include "application.h"

#include <adwaita.h>

#include <glib/gi18n.h>
#include <locale.h>

#include "window.h"
#include "config.h"

/**
 * This function activates an AdwApplication.
 *
 * @param app The AdwApplication to be activated.
 */
void application_activate(AdwApplication *app)
{
    /* Window */
    AdwWindow *window = application_window_new(app);
    gtk_window_present(GTK_WINDOW(window));
}

/**
 * This function initializes an AdwApplication.
 *
 * @param The AdwApplication to be initialized.
 */
void application_initialize(AdwApplication *app)
{
    g_signal_connect(app, "activate", G_CALLBACK(application_activate), NULL);
}

/**
 * This function creates a new AdwApplication.
 *
 * @return A new AdwApplication
 */
AdwApplication *application_new()
{
    return adw_application_new(PROJECT_ID, G_APPLICATION_DEFAULT_FLAGS);
}
