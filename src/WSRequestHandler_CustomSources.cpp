#include "CustomSources.h"
#include "WSRequestHandler.h"

void WSRequestHandler::HandleAddMediaSource(WSRequestHandler* req) {
  CustomSources::HandleAddMediaSource(req);
}

void WSRequestHandler::HandleRemoveSource(WSRequestHandler* req) {
  CustomSources::HandleRemoveSource(req);
}

void WSRequestHandler::HandleAddBrowserSource(WSRequestHandler* req) {
   CustomSources::HandleAddBrowserSource(req);
}

void WSRequestHandler::HandleClearSession(WSRequestHandler* req) {
   CustomSources::HandleClearSession(req);
}

void WSRequestHandler::HandleClearScene(WSRequestHandler* req) {
   CustomSources::HandleClearScene(req);
}

void WSRequestHandler::HandleRefreshSource(WSRequestHandler* req) {
   CustomSources::RefreshSource(req);
}
