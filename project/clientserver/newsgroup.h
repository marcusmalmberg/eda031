#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>

using namespace std;

namespace news_server {

	class Newsgroup {
	public:
		size_t id;
		string name;
		Newsgroup(const size_t _id, const string& _name) : id(_id), name(_name) {};
	};

}

#endif
