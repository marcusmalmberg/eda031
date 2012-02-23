#include "HashMap.h"
#include <utility>
#include <algorithm>

using namespace std;

namespace cpp_lab4 {

	typedef inner_vec::iterator iter_type;
	typedef inner_vec::const_iterator iter_type_const;

	struct first_equal : public binary_function<pair<HostName, IPAddress>, HostName, bool> {
		bool operator() (const pair<HostName, IPAddress>& p, const HostName& n) const {
			return p.first == n;
		}
	};

	HashMap::HashMap(size_t sz) : size(sz) {}

	void HashMap::put(const HostName& host, const IPAddress& ip) {
		size_t h = hash(host);
		inner_vec vec = v[h];
		iter_type itr = find_if(vec.begin(), vec.end(), bind2nd(first_equal(), host));
		if (itr != vec.end()) {
			return;
		}
		vec.push_back(make_pair(host, ip));
	}

	IPAddress HashMap::get(const HostName& host) const {
		size_t h = hash(host);
		inner_vec vec = v[h];
		iter_type_const itr = find_if(vec.begin(), vec.end(), bind2nd(first_equal(), host));
		if (itr != vec.end()) {
			return itr->second;
		}
		return NON_EXISTING_ADDRESS;
	}

	bool HashMap::erase(const HostName& host) {
		size_t h = hash(host);
		inner_vec vec = v[h];
		iter_type itr = find_if(vec.begin(), vec.end(), bind2nd(first_equal(), host));
		if (itr != vec.end()) {
			vec.erase(itr);
			return true;
		}
		return false;
	}

	size_t HashMap::hash(const HostName& host) const {
		size_t res = 0;
		for (HostName::const_iterator i = host.begin(); i < host.end(); ++i) {
			res += *i;
		}
		return res % size;
	}

}
