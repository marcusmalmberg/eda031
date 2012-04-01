#include <algorithm>

#include "db_memory.h"
#include "protocol/protocol.h"

using namespace std;
using namespace protocol;

namespace news_server {

	vector<Newsgroup> DBMemory::list_ng() const {
		return ngs;
	}

	pair<size_t, vector<Article>> DBMemory::list_art(const size_t id) const {
		auto itr = arts.find(id);
		if (itr == arts.end()) {
			vector<Article> v;
			return make_pair(Protocol::ERR_NG_DOES_NOT_EXIST, v);
		}
		return make_pair(Protocol::ANS_ACK, itr->second);
	}

	size_t DBMemory::create_ng(const string& name) {
		auto itr = find_if(ngs.begin(), ngs.end(), [&] (Newsgroup ng) {return ng.name == name;});
		if (itr != ngs.end()) {
			return Protocol::ERR_NG_ALREADY_EXISTS;
		}
		arts[ng_next_id];
		Newsgroup ng(ng_next_id++, name);
		ngs.push_back(ng);		
		return Protocol::ANS_ACK;
	}

	size_t DBMemory::delete_ng(const size_t id) {
		auto itr = find_if(ngs.begin(), ngs.end(), [&] (Newsgroup ng) {return ng.id == id;});
		if (itr == ngs.end()) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
		}
		ngs.erase(itr);
		arts.erase(id);
		return Protocol::ANS_ACK;
	}
	
	pair<size_t, Article> DBMemory::get_art(const size_t ng_id, size_t art_id) const {
		auto itr_ng = arts.find(ng_id);
		if (itr_ng == arts.end()) {
			Article a;
			return make_pair(Protocol::ERR_NG_DOES_NOT_EXIST, a);
		}
		const vector<Article>& as = itr_ng->second;
		auto itr_art = find_if(as.begin(), as.end(), [&] (Article a) {return a.id == art_id;});
		if (itr_art == as.end()) {
			Article a;
			return make_pair(Protocol::ERR_ART_DOES_NOT_EXIST, a);
		}
		return make_pair(Protocol::ANS_ACK, *itr_art);
	}

	size_t DBMemory::create_art(const size_t ng_id, const string& title, const string& author, const string& text) {
		auto itr_ng = arts.find(ng_id);
		if (itr_ng == arts.end()) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
		}
		vector<Article>& as = itr_ng->second;
		Article a(art_next_id[ng_id]++, title, author, text);
		as.push_back(a);
		return Protocol::ANS_ACK;
	}

	size_t DBMemory::delete_art(const size_t ng_id, const size_t art_id) {
		auto itr_ng = arts.find(ng_id);
		if (itr_ng == arts.end()) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
		}
		vector<Article>& as = itr_ng->second;
		auto itr_art = find_if(as.begin(), as.end(), [&] (Article a) {return a.id == art_id;});
		if (itr_art == as.end()) {
			return Protocol::ERR_ART_DOES_NOT_EXIST;
		}
		as.erase(itr_art);
		return Protocol::ANS_ACK;
	}

}
