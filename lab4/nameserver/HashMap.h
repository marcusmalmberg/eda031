#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string>
#include <vector>
#include "nameserverinterface.h"

using namespace std;

namespace cpp_lab4 {
	typedef vector<pair<HostName, IPAddress> > inner_vec;
	typedef size_t hash_type;
	typedef vector<pair<hash_type, inner_vec*> > outer_vec;

	class HashMap {
		public:
			HashMap(size_t size);
			void put(const HostName& host, const IPAddress& ip);
			IPAddress get(const HostName& host) const;
			bool erase(const HostName& host);
		private: 
			outer_vec v;
			size_t hash(const HostName& host) const;
			inner_vec* getInnerVector(const hash_type hash); 
			size_t size;
	};
}

#endif
