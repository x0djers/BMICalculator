#ifndef RENDER_H
#define RENDER_H

#include <errors/errors.h>

ErrorCode renderTemplate(const char *templatePath,
                         char **keys,
                         char **values,
                         char **renderedTemplate);

#endif
