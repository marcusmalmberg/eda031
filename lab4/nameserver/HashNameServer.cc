#include "HashNameServer.h"

using namespace std;

namespace cpp_lab4 {

	HashNameServer::HashNameServer(size_t size) : m(HashMap(size)) {}
	
	HashNameServer::~HashNameServer() {}

    void HashNameServer::insert(const HostName& host, const IPAddress& ip) {
		m.put(host, ip);
	}

    bool HashNameServer::remove(const HostName& host) {
		return false;//m.erase(host);
	}	

	IPAddress HashNameServer::lookup(const HostName& host) const {
		return 1;//m.get(host);
	}

}
