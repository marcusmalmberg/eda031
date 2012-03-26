#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

using namespace std;

namespace news_server {

	class Article {
	friend ostream& operator<<(ostream& out, const Article& a);
	public:
		Article(const size_t _id, const string& _title, const string& _author, const string& _text) :
			id(_id), title(_title), author(_author), text(_text);
	private:
		size_t id;
		string title;
		string author;
		string text;
	};

}

#endif
