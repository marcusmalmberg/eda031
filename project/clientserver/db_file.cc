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

	DBFile::DBFile() : root("db") {
		mkdir(root.c_str(), 0777);
	}

	vector<Newsgroup> DBFile::list_ng() const {
		vector<Newsgroup> ngs;
		string list = root;
		list += "/list";
		ifstream in(list.c_str());
		string line;
		while (getline(in, line)) {
			istringstream iss(line);
			string sub;
			iss >> sub;
			size_t id = atoi(sub.c_str());
			string name;
			iss >> name;
			while (iss >> sub) {
				name += " ";
				name += sub;
			}
			Newsgroup ng(id, name);
			ngs.push_back(ng);
		}
		in.close();
		return ngs;
	}

	pair<size_t, vector<Article>> DBFile::list_art(const size_t id) const {
		struct stat buf;
		ostringstream oss;
		oss << root << "/" << id << "/";
		string dir = oss.str();
		int status = stat(dir.c_str(), &buf);
		if (status != 0 || !S_ISDIR(buf.st_mode)) {
			vector<Article> v;
			return make_pair(Protocol::ERR_NG_DOES_NOT_EXIST, v);
		}
		vector<Article> arts;
		string list = dir;
		list += "list";
		ifstream in(list.c_str());
		string line;
		while (getline(in, line)) {
			istringstream iss(line);
			string sub;
			iss >> sub;
			size_t id = atoi(sub.c_str());
			string title;
			iss >> title;
			while (iss >> sub) {
				title += " ";
				title += sub;
			}
			Article a(id, title, "", "");
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
		string list = root;
		list += "/list";
		ofstream out(list.c_str(), ios_base::out | ios_base::app);
		size_t ng_next_id = ng_curr_id + 1;
		out << ng_next_id << " " << name << endl;
		out.close();
		ostringstream oss;
		oss << root << "/" << ng_next_id;
		string dir = oss.str();
		mkdir(dir.c_str(), 0777);
		return Protocol::ANS_ACK;
	}

	size_t DBFile::delete_ng(const size_t id) {
		vector<Newsgroup> ngs = list_ng();
		auto itr = find_if(ngs.begin(), ngs.end(), [&] (Newsgroup ng) {return ng.id == id;});
		if (itr == ngs.end()) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
		}
		ngs.erase(itr);
		string list = root;
		list += "/list";
		ofstream out(list.c_str());
		for_each(ngs.begin(), ngs.end(), [&] (Newsgroup ng) {
			out << ng.id << " " << ng.name << endl;
		});
		out.close();
		vector<Article> arts = list_art(id).second;
		ostringstream oss;
		oss << root << "/" << id << "/";
		string dir = oss.str();
		list = dir;
		list += "list";
		remove(list.c_str());
		for_each(arts.begin(), arts.end(), [&] (Article a) {
			ostringstream oss;
			oss << dir << a.id;
			string file = oss.str();
			remove(file.c_str());
		});
		rmdir(dir.c_str());
		return Protocol::ANS_ACK;
	}
	
	pair<size_t, Article> DBFile::get_art(const size_t ng_id, size_t art_id) const {
		struct stat buf;
		ostringstream oss;
		oss << root << "/" << ng_id << "/";
		string dir = oss.str();
		int status;
		status = stat(dir.c_str(), &buf);
		if (status != 0 || !S_ISDIR(buf.st_mode)) {
			Article a;
			return make_pair(Protocol::ERR_NG_DOES_NOT_EXIST, a);
		}
		oss << art_id;
		string file = oss.str();
		status = stat(file.c_str(), &buf);
		if (status != 0 || !S_ISREG(buf.st_mode)) {
			Article a;
			return make_pair(Protocol::ERR_ART_DOES_NOT_EXIST, a);
		}
		ifstream in(file.c_str());
		string title, author, text;
	    getline(in, title);
	    getline(in, author);
		getline(in, text);
		string s;
		while (getline(in, s)) {
			text += "\n";
			text += s;
		}
		in.close();
		Article a(art_id, title, author, text);
		return make_pair(Protocol::ANS_ACK, a);
	}

	size_t DBFile::create_art(const size_t ng_id, const string& title, const string& author, const string& text) {
		pair<size_t, vector<Article>> p = list_art(ng_id);
		if (p.first != Protocol::ANS_ACK) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
		}
		vector<Article> arts = p.second;
		size_t art_curr_id = 0;
		for_each(arts.begin(), arts.end(), [&] (Article a) {
			art_curr_id = a.id;
		});
		size_t art_next_id = art_curr_id + 1;
		ostringstream oss;
		oss << root << "/" << ng_id << "/";
		string dir = oss.str();
		string list = dir;
		list += "list";
		ofstream out(list.c_str(), ios_base::out | ios_base::app);
		out << art_next_id << " " << title << endl;
		ostringstream oss2;
		oss2 << dir << art_next_id;
		string file = oss2.str();
		ofstream out2(file.c_str());
		out2 << title << endl;
		out2 << author << endl;
		out2 << text << endl;
		return Protocol::ANS_ACK;
	}

	size_t DBFile::delete_art(const size_t ng_id, const size_t art_id) {
		pair<size_t, vector<Article>> p = list_art(ng_id);
		if (p.first != Protocol::ANS_ACK) {
			return Protocol::ERR_NG_DOES_NOT_EXIST;
		}
		vector<Article> arts = p.second;
		auto itr = find_if(arts.begin(), arts.end(), [&] (Article a) {return a.id == art_id;});
		if (itr == arts.end()) {
			return Protocol::ERR_ART_DOES_NOT_EXIST;
		}
		arts.erase(itr);
		ostringstream oss;
		oss << root << "/" << ng_id << "/";
		string dir = oss.str();
		string list = dir;
		list += "list";
		ofstream out(list.c_str());
		for_each(arts.begin(), arts.end(), [&] (Article a) {
			out << a.id << " " << a.title << endl;
		});
		out.close();
		oss << art_id;
		string file = oss.str();
		remove(file.c_str());
		return Protocol::ANS_ACK;
	}

}
