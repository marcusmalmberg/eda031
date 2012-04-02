#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "db_file.h"
#include "protocol/protocol.h"

using namespace std;
using namespace protocol;

namespace news_server {

	vector<Newsgroup> DBFile::list_ng() const {
		vector<Newsgroup> ngs;
		ifstream in("list");
		string line;
		while (in) {
			getline(in, line);
			istringstream iss(line);
			string sub;
			iss >> sub;
			size_t id = atoi(sub.c_str());
			iss >> noskipws >> sub;
			Newsgroup ng(id, sub);
			ngs.push_back(ng);
		}
		in.close();
		return ngs;
	}

	pair<size_t, vector<Article>> DBFile::list_art(const size_t id) const {
		struct stat buf;
		ostringstream oss;
		oss << id;
		string dir = oss.str();
		int status = stat(dir.c_str(), &buf);
		if (status != 0 || !S_ISDIR(buf.st_mode)) {
			vector<Article> v;
			return make_pair(Protocol::ERR_NG_DOES_NOT_EXIST, v);
		}
		vector<Article> arts;
		string list = dir;
		list += "/list";
		ifstream in(list);
		string line;
		while (in) {
			getline(in, line);
			istringstream iss(line);
			string sub;
			iss >> sub;
			size_t id = atoi(sub.c_str());
			iss >> noskipws >> sub;
			Article a(id, sub, "", "");
			arts.push_back(a);
		}
		in.close();
		return make_pair(Protocol::ANS_ACK, arts);
	}

	size_t DBFile::create_ng(const string& name) {
		vector<Newsgroup> ngs = list_ng();
		size_t ng_curr_id = 0;
		auto itr = find_if(ngs.begin(), ngs.end(), [&] (Newsgroup ng)-> bool  {
				ng_curr_id = ng.id;
				return ng.name == name;
		});
		if (itr != ngs.end()) {
			return Protocol::ERR_NG_ALREADY_EXISTS;
		}
		ofstream out("list", ios_base::out | ios_base::app);
		size_t ng_next_id = ng_curr_id + 1;
		out << ng_next_id << " " << name << endl;
		out.close();
		ostringstream oss;
		oss << ng_next_id;
		string dir = oss.str();
		mode_t mode = 0777;
		mkdir(dir.c_str(), mode);
		return Protocol::ANS_ACK;
	}

	size_t DBFile::delete_ng(const size_t id) {
		vector<Newsgroup> ngs = list_ng();
		auto itr = find_if(ngs.begin(), ngs.end(), [&] (Newsgroup ng) {return ng.id == id;});
		if (itr == ngs.end()) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
		}
		ngs.erase(itr);
		ostringstream oss;
		oss << id;
		string dir = oss.str();
		ofstream out("list");
		for_each(ngs.begin(), ngs.end(), [&] (Newsgroup ng) {
			out << ng.id << " " << ng.name << endl;
			ostringstream oss;
			oss << dir << "/" << ng.id;
			string file = oss.str();
			remove(file.c_str());
		});
		out.close();
		rmdir(dir.c_str());
		return Protocol::ANS_ACK;
	}
	
	pair<size_t, Article> DBFile::get_art(const size_t ng_id, size_t art_id) const {
		//auto itr_ng = arts.find(ng_id);
		//if (itr_ng == arts.end()) {
		//	Article a;
		//	return make_pair(Protocol::ERR_NG_DOES_NOT_EXIST, a);
		//}
		//const vector<Article>& as = itr_ng->second;
		//auto itr_art = find_if(as.begin(), as.end(), [&] (Article a) {return a.id == art_id;});
		//if (itr_art == as.end()) {
			Article a;
			return make_pair(Protocol::ERR_ART_DOES_NOT_EXIST, a);
		//}
		//return make_pair(Protocol::ANS_ACK, *itr_art);
	}

	size_t DBFile::create_art(const size_t ng_id, const string& title, const string& author, const string& text) {
	//	auto itr_ng = arts.find(ng_id);
	//	if (itr_ng == arts.end()) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
	//	}
	//	vector<Article>& as = itr_ng->second;
	//	Article a(art_next_id[ng_id]++, title, author, text);
	//	as.push_back(a);
	//	return Protocol::ANS_ACK;
	}

	size_t DBFile::delete_art(const size_t ng_id, const size_t art_id) {
//		auto itr_ng = arts.find(ng_id);
//		if (itr_ng == arts.end()) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
//		}
//		vector<Article>& as = itr_ng->second;
//		auto itr_art = find_if(as.begin(), as.end(), [&] (Article a) {return a.id == art_id;});
//		if (itr_art == as.end()) {
//			return Protocol::ERR_ART_DOES_NOT_EXIST;
//		}
//		as.erase(itr_art);
//		return Protocol::ANS_ACK;
	}

}
