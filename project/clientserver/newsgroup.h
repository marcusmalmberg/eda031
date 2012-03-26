#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <vector>

using namespace std;

namespace news_server {

	class Newsgroup {
	public:
		Newsgroup(const size_t _id, const string& _name) : id(_id), name(_name);
	private:
		size_t id;
		string name;
	};

}

#endif
