#ifndef DB_MEMORY_H
#define DB_MEMORY_H

#include <vector>
#include <map>
#include "db_interface.h"
#include "newsgroup.h"
#include "article.h"

using namespace std;

namespace news_server {

	class DBMemory : public DBInterface {
	private:
		vector<Newsgroup> ngs;
		map<size_t, vector<Article>> arts;
		size_t ng_next_id;
		map<size_t, size_t> art_next_id;
	};

}

#endif
