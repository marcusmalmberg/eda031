#ifndef HASH_NAME_SERVER_H
#define HASH_NAME_SERVER_H

#include <map>
#include "nameserverinterface.h"
using namespace std;

namespace cpp_lab4 {
	class HashNameServer : public NameServerInterface {
		public:
        	HashNameServer(int size);
			virtual ~HashNameServer();
        	virtual void insert(const HostName&, const IPAddress&);
        	virtual bool remove(const HostName&);
        	virtual IPAddress lookup(const HostName&) const;
		private:
			map<HostName, IPAddress> h;
	};
}

#endif
