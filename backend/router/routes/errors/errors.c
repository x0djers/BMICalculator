#include "errors.h"

#include <constants/constants.h>

void sendErrorMessage(struct mg_connection* connection,
                      const ErrorCode errorCode) {
	mg_http_reply(connection,
              	  errorsHttpCodes[errorCode],
              	  MIME_PLAIN,
              	  errorsMessages[errorCode]);
}
