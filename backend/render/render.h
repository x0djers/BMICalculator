#ifndef RENDER_H
#define RENDER_H

#include <errors/errors.h>

ErrorCode renderTemplate(const char *templatePath,
                         const char **keys,
                         const char **values,
                         char **renderedTemplate);

#endif
