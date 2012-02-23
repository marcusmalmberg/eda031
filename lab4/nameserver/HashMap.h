#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string>
#include <vector>
#include "nameserverinterface.h"

using namespace std;

namespace cpp_lab4 {
	typedef vector<pair<HostName, IPAddress> > inner_vec;

	class HashMap {
		public:
			HashMap(size_t size);
			void put(const HostName& host, const IPAddress& ip);
			IPAddress get(const HostName& host) const;
			bool erase(const HostName& host);
		private: 
			vector<inner_vec> v;
			size_t hash(const HostName& host) const;
			size_t size;
	};
}

#endif
