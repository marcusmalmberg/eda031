#include <string>
#include "article.h"

using namespace std;

namespace news_server {

	ostream& operator<<(ostream& out, const Article& a) {
		out << id << ". " << title << " From: " << author;
	}

}

