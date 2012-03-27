#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include <iostream>

using namespace std;

namespace news_server {
	
	class BasePacket {
	public:
		BasePacket(MessageHandler h) : handler(h);
		virtual void read() = 0;
		virtual void write() = 0;
	private:
		MessageHandler handler;
	};

}

#endif
