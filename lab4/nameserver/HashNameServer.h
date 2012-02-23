#ifndef HASH_NAME_SERVER_H
#define HASH_NAME_SERVER_H

#include "HashMap.h"
#include "nameserverinterface.h"
using namespace std;

namespace cpp_lab4 {
	class HashNameServer : public NameServerInterface {
		public:
			HashNameServer(size_t size);
        	virtual ~HashNameServer();
        	virtual void insert(const HostName&, const IPAddress&);
        	virtual bool remove(const HostName&);
        	virtual IPAddress lookup(const HostName&) const;
		private:
			HashMap m;
	};
}

#endif
