#include "HashMap.h"
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

namespace cpp_lab4 {

	struct first_equal : public binary_function<pair<HostName, IPAddress>, HostName, bool> {
		bool operator() (const pair<HostName, IPAddress>& p, const HostName& n) const {
			return p.first == n;
		}
	};

	HashMap::HashMap(size_t sz) : v(vector<inner_vec>(sz)), size(sz) {}

	void HashMap::put(const HostName& host, const IPAddress& ip) {

		// get hash for hostname
		size_t h = hash(host);

		// get the inner vector for the hash
		inner_vec& vec = v[h];
		
		// Find host in the inner vector.
		inner_vec::iterator itr = find_if(vec.begin(), vec.end(), bind2nd(first_equal(), host));

		// If found: don't add and return.
		if (itr != vec.end()) {
			return;
		}

		// Make a new pair
		pair<HostName, IPAddress> *p = new pair<HostName, IPAddress>(host, ip);

		// Add it to the inner vector
		vec.push_back(*p);
	}

	IPAddress HashMap::get(const HostName& host) const {
		size_t h = hash(host);
		inner_vec vec = v[h];
		inner_vec::const_iterator itr = find_if(vec.begin(), vec.end(), bind2nd(first_equal(), host));
		if (itr != vec.end()) {
			return itr->second;
		}
		return NON_EXISTING_ADDRESS;
	}

	bool HashMap::erase(const HostName& host) {
		size_t h = hash(host);
		inner_vec& vec = v[h];

		inner_vec::iterator itr = find_if(vec.begin(), vec.end(), bind2nd(first_equal(), host));
		if (itr != vec.end()) {
			vec.erase(itr);
			return true;
		}
		
		return false;
	}

	size_t HashMap::hash(const HostName& host) const {
		size_t res = 0;
		HostName::const_iterator i = host.begin();
		++i;
		++i;
		++i;
		++i;
		for (; i < host.end(); ++i) {
			res += *i;
		}
		return res % size;
	}

}
