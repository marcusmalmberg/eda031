#ifndef VECTOR_NAME_SERVER_H
#define VECTOR_NAME_SERVER_H

#include <vector>
#include "nameserverinterface.h"
using namespace std;

namespace cpp_lab4 {
	class VectorNameServer : public NameServerInterface {
		public:
        	virtual ~VectorNameServer();
        	virtual void insert(const HostName&, const IPAddress&);
        	virtual bool remove(const HostName&);
        	virtual IPAddress lookup(const HostName&) const;
		private:
			vector<pair<HostName, IPAddress> > v;
	};
}

#endif
