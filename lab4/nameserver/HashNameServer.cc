#include <map>
#include <utility>
#include <algorithm>
#include "HashNameServer.h"
using namespace std;

namespace cpp_lab4 {

	HashNameServer::~HashNameServer() {
	}

    void HashNameServer::insert(const HostName& host, const IPAddress& ip) {
		h[host] = ip;
	}

    bool HashNameServer::remove(const HostName& host) {
		size_t nRemoved = h.erase(host);
		return nRemoved > 0;
	}	

	IPAddress HashNameServer::lookup(const HostName& host) const {
		map<HostName, IPAddress>::const_iterator itr = h.find(host);
		if (itr != h.end()) {
			return itr->second;
		}
		return NON_EXISTING_ADDRESS;
	}

}
