#include "StatFetch.h"
#include "cinder\app\AppBase.h"
namespace oem {
	StatFetch::StatFetch()
	{

	}
	StatFetch::~StatFetch()
	{

	}
	void StatFetch::setup()
	{
		ci::app::console() << "Setup called" << std::endl;

		mHost = "libcinder.org";
		mPort = 80;

		mHttpRequest = HttpRequest("GET", "/", HttpVersion::HTTP_1_0);
		mHttpRequest.setHeader("Host", mHost);
		mHttpRequest.setHeader("Accept", "*/*");
		mHttpRequest.setHeader("Connection", "close");



		//mHost = "api.worldoftanks.eu";
		//mHost = "www.google.com";
		//mPort = 80;
		/////wot/account/list/?application_id=demo&search=maurbeast
		//mHttpRequest = HttpRequest("GET", "/", HttpVersion::HTTP_1_0);
		//mHttpRequest.setHeader("Host", mHost);
		//mHttpRequest.setHeader("Accept", "*/*");
		//mHttpRequest.setHeader("Connection", "close");


		mClient = TcpClient::create(asio::io_service());
		mClient->connectConnectEventHandler(&StatFetch::onConnect, this);
		mClient->connectErrorEventHandler(&StatFetch::onError, this);
		mClient->connectResolveEventHandler(&StatFetch::onResolve, this);
	}
	void	StatFetch::write()
	{
		// This sample is meant to work with only one session at a time
		if (mSession && mSession->getSocket()->is_open()) {
			return;
		}
		mClient->connect(mHost, (uint16_t)mPort);
	}
	void	StatFetch::onClose()
	{


	}
	void	StatFetch::onConnect(TcpSessionRef session)
	{
		mHttpResponse = HttpResponse();
		mSession = session;
		mSession->connectCloseEventHandler(&StatFetch::onClose, this);
		mSession->connectErrorEventHandler(&StatFetch::onError, this);
		mSession->connectReadCompleteEventHandler(&StatFetch::onReadComplete, this);
		mSession->connectReadEventHandler(&StatFetch::onRead, this);
		mSession->connectWriteEventHandler(&StatFetch::onWrite, this);

		mSession->write(mHttpRequest.toBuffer());

	}
	void	StatFetch::onError(std::string err, size_t bytesTransferred)
	{


	}
	void	StatFetch::onRead(ci::Buffer buffer)
	{
		if (!mHttpResponse.hasHeader()) {
			mHttpResponse.parseHeader(HttpResponse::bufferToString(buffer));
			buffer = HttpResponse::removeHeader(buffer);
		}
		mHttpResponse.append(buffer);

		mSession->read();
	}

	void	StatFetch::onReadComplete()
	{
		std::string buffer = HttpResponse::bufferToString(mHttpResponse.getBody());
		mJson = ci::JsonTree(buffer);
		ci::JsonTree status(mJson.getChild("status"));
		mSession->close();
	}

	void	StatFetch::onResolve()
	{

	}
	void	StatFetch::onWrite(size_t bytesTransferred)
	{
		mSession->read();
	}
}