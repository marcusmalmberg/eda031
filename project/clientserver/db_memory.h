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
	public:
		vector<Newsgroup> list_ng() const;
		vector<Article> list_art(const size_t id) const;
		size_t create_ng(const string& name);
		size_t delete_ng(const size_t id);
		pair<size_t, Article> get_art(const size_t ng_id, size_t art_id) const;
		size_t create_art(const size_t ng_id, const string& title, const string& author, const string& text);
		size_t delete_art(const size_t ng_id, const size_t art_id);
	private:
		vector<Newsgroup> ngs;
		map<size_t, vector<Article>> arts;
		size_t ng_next_id;
		map<size_t, size_t> art_next_id;
	};

}

#endif
