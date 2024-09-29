#include "answer.h"

#include <adwaita.h>

#include <glib/gi18n.h>
#include <locale.h>

#include "config.h"

/**
 * This function answers the user.
 */
void answer()
{
    g_message(_("Hello, World!"));
}
