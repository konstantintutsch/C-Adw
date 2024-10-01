#include "window.h"

#include <adwaita.h>

#include <glib/gi18n.h>
#include <locale.h>

#include "application.h"
#include "config.h"

/**
 * This class handles all window logic.
 */
typedef struct _TemplateWindow {
    AdwApplicationWindow parent;
} TemplateWindow;

G_DEFINE_TYPE(TemplateWindow, template_window, ADW_TYPE_APPLICATION_WINDOW)
/**
 * This function initializes a TemplateWindow object.
 *
 * @param window TemplateWindow to be initialized
 */
static void template_window_init(TemplateWindow *window)
{
    gtk_widget_init_template(GTK_WIDGET(window));
}

/**
 * This function initializes the TemplateWindow class.
 *
 * @param class TemplateWindowClass to be initialized
 */
static void template_window_class_init(TemplateWindowClass *class)
{
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class),
                                                UI_RESOURCE("window.ui"));
}

/**
 * This function creates a new TemplateWindow object.
 *
 * @param app TemplateApplication to create the new TemplateWindow for
 *
 * @return TemplateWindow
 */
TemplateWindow *template_window_new(TemplateWindow *app)
{
    return g_object_new(TEMPLATE_TYPE_WINDOW, "application", app, NULL);
}

/**
 * This function opens a TemplateWindow window.
 *
 * @param window Window to be opened
 * @param file File to be processed with the window
 */

void template_window_open(TemplateWindow *window, GFile *file)
{
}
