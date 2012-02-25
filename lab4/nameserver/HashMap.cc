#include "HashMap.h"
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

namespace cpp_lab4 {

	typedef inner_vec::iterator iter_type;
	typedef inner_vec::const_iterator iter_type_const;
	typedef outer_vec::const_iterator outer_iter_type;
	typedef outer_vec::const_iterator outer_iter_type_const;

	struct first_equal : public binary_function<pair<HostName, IPAddress>, HostName, bool> {
		bool operator() (const pair<HostName, IPAddress>& p, const HostName& n) const {
			return p.first == n;
		}
	};

	struct first_equal_hash : public binary_function<pair<hash_type, inner_vec*>, hash_type, bool> {
		bool operator() (const pair<hash_type, inner_vec*>& p, const hash_type& n) const {
			return p.first == n;
		}
	};

	HashMap::HashMap(size_t sz) : size(sz) {}

	inner_vec* HashMap::getInnerVector(const hash_type hsh) {
		// Search for an existing bucket
		outer_iter_type itr = find_if(v.begin(), v.end(), bind2nd(first_equal_hash(), hsh));
		if(itr != v.end()) {
			return itr->second;
		}
		
		// No bucket existed for specified bucket. Creating new.
		inner_vec *vec = new inner_vec;
		pair<hash_type, inner_vec*> *p = new pair<hash_type, inner_vec*>(hsh, vec);
		v.push_back(*p);
		return vec;
	}

	void HashMap::put(const HostName& host, const IPAddress& ip) {

		// get hash for hostname
		size_t h = hash(host);

		// get the inner vector for the hash
		inner_vec *vec = getInnerVector(h);
		
		// Find host in the inner vector.
		iter_type itr = find_if(vec->begin(), vec->end(), bind2nd(first_equal(), host));

		// If found: don't add and return.
		if (itr != vec->end()) {
			return;
		}

		// Make a new pair
		pair<HostName, IPAddress> *p = new pair<HostName, IPAddress>(host, ip);

		// Add it to the inner vector
		vec->push_back(*p);
	}

	IPAddress HashMap::get(const HostName& host) const {
		size_t h = hash(host);
		
		outer_iter_type_const oitr = find_if(v.begin(), v.end(), bind2nd(first_equal_hash(), h));
		if(oitr != v.end()) {
			inner_vec vec = *oitr->second;

			iter_type_const itr = find_if(vec.begin(), vec.end(), bind2nd(first_equal(), host));
			if (itr != vec.end()) {
				return itr->second;
			}
		}

		return NON_EXISTING_ADDRESS;
	}

	bool HashMap::erase(const HostName& host) {
		size_t h = hash(host);
		inner_vec *vec = getInnerVector(h);

		iter_type itr = find_if(vec->begin(), vec->end(), bind2nd(first_equal(), host));
		if (itr != vec->end()) {
			vec->erase(itr);
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
