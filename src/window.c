#include "window.h"

#include <adwaita.h>
#include <glib/gi18n.h>
#include <locale.h>
#include "application.h"
#include "config.h"

/**
 * This structure handles data of a window.
 */
struct _TemplateWindow {
    AdwApplicationWindow parent;
};

G_DEFINE_TYPE(TemplateWindow, template_window, ADW_TYPE_APPLICATION_WINDOW);

/**
 * This function initializes a TemplateWindow.
 *
 * @param window Window to be initialized
 */
static void template_window_init(TemplateWindow *window)
{
    gtk_widget_init_template(GTK_WIDGET(window));
}

/**
 * This function initializes a TemplateWindow class.
 *
 * @param class Window class to be initialized
 */
static void template_window_class_init(TemplateWindowClass *class)
{
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class),
                                                UI_RESOURCE("window.ui"));
}

/**
 * This function creates a new TemplateWindow.
 *
 * @param app Application to create the new window for
 *
 * @return TemplateWindow
 */
TemplateWindow *template_window_new(TemplateApplication *app)
{
    return g_object_new(TEMPLATE_TYPE_WINDOW, "application", app, NULL);
}

/**
 * This function opens a TemplateWindow.
 *
 * @param window Window to be opened
 * @param file File to be processed with the window
 */

void template_window_open(TemplateWindow *window, GFile *file)
{
}
