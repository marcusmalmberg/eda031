#ifndef DB_FILE_H
#define DB_FILE_H

#include <vector>

#include "db_interface.h"
#include "newsgroup.h"
#include "article.h"

using namespace std;

namespace news_server {

	class DBFile : public DBInterface {
	public:
		DBFile();
		vector<Newsgroup> list_ng() const;
		pair<size_t, vector<Article>> list_art(const size_t id) const;
		size_t create_ng(const string& name);
		size_t delete_ng(const size_t id);
		pair<size_t, Article> get_art(const size_t ng_id, size_t art_id) const;
		size_t create_art(const size_t ng_id, const string& title, const string& author, const string& text);
		size_t delete_art(const size_t ng_id, const size_t art_id);
	private:
		string root;
	};

}

#endif
