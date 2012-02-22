#include <vector>
#include <utility>
#include <algorithm>
#include "VectorNameServer.h"
using namespace std;

namespace cpp_lab4 {
	typedef vector<pair<HostName, IPAddress> >::iterator iter_type;
	typedef vector<pair<HostName, IPAddress> >::const_iterator iter_type_const;

	struct first_equal : public binary_function<pair<HostName, IPAddress>, HostName, bool> {
		bool operator() (const pair<HostName, IPAddress>& p, const HostName& n) const {
			return p.first == n;
		}
	};

	VectorNameServer::~VectorNameServer() {
	}

    void VectorNameServer::insert(const HostName& host, const IPAddress& ip) {
		pair<HostName, IPAddress>* p = new pair<HostName, IPAddress>(host, ip);
		v.push_back(*p);
	}

    bool VectorNameServer::remove(const HostName& host) {
		iter_type itr = find_if(v.begin(), v.end(), bind2nd(first_equal(), host));
		if (itr != v.end()) {
			v.erase(itr);
			return true;
		}
		return false;
	}	

	IPAddress VectorNameServer::lookup(const HostName& host) const {
		iter_type_const itr = find_if(v.begin(), v.end(), bind2nd(first_equal(), host));
		if (itr != v.end()) {
			return itr->second;
		}
		return NON_EXISTING_ADDRESS;
	}

}
