#include "application.h"

#include <adwaita.h>

#include <glib/gi18n.h>
#include <locale.h>

#include "window.h"
#include "config.h"

/**
 * This class handles all application logic.
 */
struct _TemplateApplication {
    AdwApplication parent;
};

G_DEFINE_TYPE(TemplateApplication, template_application, ADW_TYPE_APPLICATION);

/**
 * This function shows the About Dialogue of an GApplication.
 *
 * @param action Action that was activated to call this function
 * @param parameter Parameters passed
 * @param user_data User data passed
 */
static void template_application_show_about(GSimpleAction *action,
                                            GVariant *parameter,
                                            gpointer user_data)
{
    TemplateApplication *app = TEMPLATE_APPLICATION(user_data);
    TemplateWindow *active_window =
        TEMPLATE_WINDOW(gtk_application_get_active_window
                        (GTK_APPLICATION(app)));

    AdwAboutDialog *about =
        ADW_ABOUT_DIALOG(adw_about_dialog_new_from_appdata
                         (ROOT_RESOURCE(_PROJECT_ID(".metainfo.xml")),
                          "1.0.0"));

    // Show version suffix
    adw_about_dialog_set_version(about, PROJECT_VERSION);

    // Details
    adw_about_dialog_set_comments(about,
                                  _
                                  ("A simple template for LibAdwaita C applications"));

    // Credits
    const char *developers[] =
        { "Konstantin Tutsch <mail@konstantintutsch.com>", NULL };
    adw_about_dialog_set_developers(about, developers);
    const char *designers[] =
        { "GNOME Design Team https://welcome.gnome.org/team/design/",
        "Konstantin Tutsch <mail@konstantintutsch.com>", NULL
    };
    adw_about_dialog_set_designers(about, designers);
    adw_about_dialog_set_translator_credits(about, _("translator-credits"));
    const char *libraries[] =
        { "The GNOME Project https://www.gnome.org", NULL };
    adw_about_dialog_add_acknowledgement_section(about, _("Dependencies"),
                                                 libraries);

    // Legal
    adw_about_dialog_set_copyright(about, "© 2024 Konstantin Tutsch");

    adw_dialog_present(ADW_DIALOG(about), GTK_WIDGET(active_window));
}

/**
 * This function initializes a TemplateApplication object.
 *
 * @param app TemplateApplication to be initialized
 */
static void template_application_init(TemplateApplication *app)
{
    // Register resources
    GResource *resource = g_resource_load(GRESOURCE_FILE, NULL);
    g_resources_register(resource);

    // Add actions
    g_autoptr(GSimpleAction) about_action = g_simple_action_new("about", NULL);
    g_signal_connect(about_action, "activate",
                     G_CALLBACK(template_application_show_about), app);
    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_action));
}

/**
 * This function activates a GApplication object.
 *
 * @param app GApplication to be activated
 */
static void template_application_activate(GApplication *app)
{
    TemplateWindow *window;

    window = template_window_new(TEMPLATE_APPLICATION(app));
    gtk_window_present(GTK_WINDOW(window));
}

/**
 * This function opens a new instance of a GApplication object.
 *
 * @param app GApplication to be opened
 * @param files GFiles passed
 * @param n_files Number of GFiles passed
 * @param hint Hint how files from GFiles will be processed
 */
static void template_application_open(GApplication *app, GFile **files,
                                      int n_files, const char *hint)
{
    GList *windows;
    TemplateWindow *window;

    windows = gtk_application_get_windows(GTK_APPLICATION(app));
    if (!windows)
        window = template_window_new(TEMPLATE_APPLICATION(app));
    window = TEMPLATE_WINDOW(windows->data);

    for (int i = 0; i < n_files; i++)
        template_window_open(window, files[i]);

    gtk_window_present(GTK_WINDOW(window));
}

/**
 * This function initializes a TemplateApplication class.
 *
 * @param class TemplateApplicationClass to be initialized
 */
static void template_application_class_init(TemplateApplicationClass *class)
{
    G_APPLICATION_CLASS(class)->activate = template_application_activate;
    G_APPLICATION_CLASS(class)->open = template_application_open;
}

/**
 * This function creates a new TemplateApplication object.
 *
 * @return TemplateApplication
 */
TemplateApplication *template_application_new()
{
    return g_object_new(TEMPLATE_TYPE_APPLICATION, "application-id", PROJECT_ID,
                        G_APPLICATION_DEFAULT_FLAGS, G_APPLICATION_HANDLES_OPEN,
                        NULL);
}
