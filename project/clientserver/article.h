#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

using namespace std;

namespace news_server {

	class Article {
	friend ostream& operator<<(ostream& out, const Article& a);
	public:
		void read();
	private:
		size_t id;
		string title;
		string author;
		string text;
	}

}

#endif
