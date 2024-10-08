#ifndef WINDOW_H
#define WINDOW_H

#include <adwaita.h>
#include "application.h"

#define TEMPLATE_TYPE_WINDOW (template_window_get_type())

G_DECLARE_FINAL_TYPE(TemplateWindow, template_window, TEMPLATE, WINDOW,
                     AdwApplicationWindow);

TemplateWindow *template_window_new(TemplateApplication * app);
void template_window_open(TemplateWindow * window, GFile * file);

#endif                          // WINDOW_H
