#include <map>
#include <utility>
#include <algorithm>
#include "MapNameServer.h"
using namespace std;

namespace cpp_lab4 {

	struct first_equal : public binary_function<pair<HostName, IPAddress>, HostName, bool> {
		bool operator() (const pair<HostName, IPAddress>& p, const HostName& n) const {
			return p.first == n;
		}
	};

	MapNameServer::~MapNameServer() {
	}

    void MapNameServer::insert(const HostName& host, const IPAddress& ip) {
		m[host] = ip;
	}

    bool MapNameServer::remove(const HostName& host) {
		size_t nRemoved = m.erase(host);
		return nRemoved > 0;
	}	

	IPAddress MapNameServer::lookup(const HostName& host) const {
		map<HostName, IPAddress>::const_iterator itr = m.find(host);
		if (itr != m.end()) {
			return itr->second;
		}
		return NON_EXISTING_ADDRESS;
	}

}
