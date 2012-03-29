#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <string>
#include <vector>
#include "newsgroup.h"
#include "article.h"

using namespace std;

namespace news_server {

	class DBInterface {
	public:
		virtual vector<Newsgroup> list_ng() const = 0;
		virtual vector<Article> list_art(const size_t id) const = 0;
		virtual size_t create_ng(const string& name) = 0;
		virtual size_t delete_ng(const size_t id = 0;
		virtual pair<size_t, Article> get_art(const size_t ng_id, size_t art_id) const = 0;
		virtual size_t create_art(const size_t ng_id, const string& title, const string& author, const string& text) = 0;
		virtual size_t delete_art(const size_t ng_id, const size_t art_id) = 0;
	};

}

#endif
