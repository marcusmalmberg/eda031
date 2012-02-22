#ifndef VECTOR_NAME_SERVER_H
#define VECTOR_NAME_SERVER_H

#include <map>
#include "nameserverinterface.h"
using namespace std;

namespace cpp_lab4 {
	class MapNameServer : public NameServerInterface {
		public:
        	virtual ~MapNameServer();
        	virtual void insert(const HostName&, const IPAddress&);
        	virtual bool remove(const HostName&);
        	virtual IPAddress lookup(const HostName&) const;
		private:
			map<HostName, IPAddress> m;
	};
}

#endif
