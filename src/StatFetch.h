#include <string>
#include "boost\algorithm\string.hpp"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "TcpClient.h"				
#include "cinder\Json.h"
#include "cinder\Utilities.h"
#include "CinderAsio.h"

namespace oem {
	class StatFetch
	{
	public:
		StatFetch();
		~StatFetch();
		void						setup();
		void						write();
	private:
		std::string					mUserName;
		int							mAccountId;
		ci::JsonTree				mJson;
		TcpClientRef				mClient;
		TcpSessionRef				mSession;
		std::string					mHost;
		int32_t						mPort;
		HttpRequest					mHttpRequest;
		HttpResponse				mHttpResponse;
		void						onClose();
		void						onConnect(TcpSessionRef session);
		void						onError(std::string err, size_t bytesTransferred);
		void						onRead(ci::Buffer buffer);
		void						onReadComplete();
		void						onResolve();
		void						onWrite(size_t bytesTransferred);
	};
}