#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <string>
#include <vector>
#include "newsgroup.h"
#include "article.h"

using namespace std;

namespace news_server {

	class DBInterface {

		virtual vector<Newsgroup> list_newsgroups() = 0;

		virtual vector<Article> list_articles(const Newsgroup& ng) = 0;

		virtual size_t create_newsgroup(const string& name) = 0;

		virtual size_t delete_newsgroup(const Newsgroup& ng) = 0;

		virtual read_article(size_t id) = 0;

		virtual size_t write_article(const Article& a) = 0;

		virtual size_t delete_article(const Article& a) = 0;

	}

}

#endif
