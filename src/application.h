#ifndef APPLICATION_H
#define APPLICATION_H

#include <adwaita.h>

#define TEMPLATE_TYPE_APPLICATION (template_application_get_type())

G_DECLARE_FINAL_TYPE(TemplateApplication, template_application, TEMPLATE, APPLICATION, AdwApplication);

TemplateApplication *template_application_new(void);

#endif                          // APPLICATION_H
