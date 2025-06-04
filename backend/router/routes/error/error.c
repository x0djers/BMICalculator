#include <log.h>

#include "error.h"

#include <config/config.h>
#include <render/render.h>
#include <errors/errors.h>
#include <constants/constants.h>

void sendErrorMessage(struct mg_connection* connection,
                      const ErrorCode errorCode) {
	const char* headers = "Content-Type: " MIME_PLAIN "\r\n";
	mg_http_reply(connection,
              	  errorsHttpCodes[errorCode],
              	  headers,
              	  errorsMessages[errorCode]);
}

void handleErrorPage(struct mg_connection* connection,
					 const ErrorCode errorCode) {
	log_trace("Handling error page for code: %d (%s).",
			 errorsHttpCodes[errorCode], errorsMessages[errorCode]);

	char* errorPage = NULL;

	char httpErrorCode[8];
	sprintf(httpErrorCode, "%d", errorsHttpCodes[errorCode]);

	const char* renderKeys[] = {"errorCode", "errorDescription", NULL};
	const char* renderValues[] = {httpErrorCode,
								  errorsMessages[errorCode],
								  NULL};

	const ErrorCode renderPageStatus = renderTemplate(globalConfig.errorPage,
													  renderKeys,
													  renderValues,
													  &errorPage);

	if (renderPageStatus == NONE_ERROR && errorPage) {
		log_trace("Sending error page response with HTTP code %d",
				  errorsHttpCodes[errorCode]);
		const char* headers = "Content-Type: " MIME_HTML "\r\n";
		mg_http_reply(connection,
					  errorsHttpCodes[errorCode],
					  headers,
					  "%s",
					  errorPage);
		free(errorPage);
		log_trace("Error page successful sent.");
	} else {
		log_error("Template rendering failed with error code: %d",
				  renderPageStatus);
		sendErrorMessage(connection, errorCode);
	}
}
