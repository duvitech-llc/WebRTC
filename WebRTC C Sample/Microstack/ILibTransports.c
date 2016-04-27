/*   
Copyright 2015 Intel Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "ILibParsers.h"
#include "ILibTransports.h"
#include "ILibAsyncSocket.h"
#include "ILibWebClient.h"
#include "ILibWebRTC.h"
#include "ILibWrapperWebRTC.h"
#include "ILibWebServer.h"

enum ILibAsyncSocket_SendStatus ILibTransports_Send(void* transport, char* buffer, int bufferLength, enum ILibAsyncSocket_MemoryOwnership ownership, ILibTransports_DoneFlag done)
{
	enum ILibAsyncSocket_SendStatus retVal = ILibAsyncSocket_SEND_ON_CLOSED_SOCKET_ERROR;

	switch(((ILibChainHeader*)transport)->IdentifierFlags)
	{
		case ILibTransports_AsyncSocket:
			retVal = ILibAsyncSocket_Send(transport, buffer, bufferLength, ownership);
			break;
		case ILibTransports_WebClient_StreamingRequestToken:
			retVal = ILibWebClient_StreamRequestBody(transport, buffer, bufferLength, ownership, done==ILibTransports_DoneFlag_COMPLETE?1:0) != 0 ? ILibAsyncSocket_ALL_DATA_SENT : ILibAsyncSocket_NOT_ALL_DATA_SENT_YET;
			break;
		case ILibTransports_WebSocket:
			retVal = (enum ILibAsyncSocket_SendStatus)ILibWebServer_WebSocket_Send((struct ILibWebServer_Session*)transport, buffer, bufferLength, ILibWebServer_WebSocket_DataType_BINARY, ownership, done == ILibTransports_DoneFlag_COMPLETE ? ILibWebServer_WebSocket_FragmentFlag_Complete : ILibWebServer_WebSocket_FragmentFlag_Incomplete);
			break;
		case ILibTransports_Raw_WebRTC:
			retVal = (enum ILibAsyncSocket_SendStatus)ILibSCTP_Send(transport, 0, buffer, bufferLength);
			break;
		case ILibTransports_WebRTC_DataChannel:
			ILibWrapper_WebRTC_DataChannel_Send((ILibWrapper_WebRTC_DataChannel*)transport, buffer, bufferLength);
			break;
	}

	return(retVal);
}