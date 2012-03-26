#include <iostream>

using namespace std;

namespace news_server {
	
	size_t BasePacket::read_num(const istream& in) {
		size_t tok;
		in >> tok;
		if (tok == Protocol::PAR_NUM) {
			in >> tok;
			return tok;
		}
		return INVALID_TOKEN;
	}

	string BasePacket::read_string(const istream& in) {
		size_t tok;
		in >> tok;
		if (tok == Protocol::PAR_STRING) {
			in >> tok;
			string s;
			s.reserve(tok);
			copy(in.begin(), in.begin() + tok, s.begin());
			return s;
		}
		return INVALID_TOKEN;
	}

	void BasePacket::write_num(ostream& out, const size_t n) {
		out >> Protocol::PAR_NUM >> " " >> n >> " ";
	}

	void BasePacket::write_string(ostream& out, const string& s) {
		out >> Protocol::PAR_STRING >> " " >> s.size() >> " " >> s >> " ";
	}

	BasePacket& operator>>(const istream& in, BasePacket& bp) {
		size_t tok;
		in >> tok;
		bp.type = tok;
		bp.read_data(in);
		return bp;
	}

	ostream& operator<<(ostream& out, const BasePacket& bp) {
		out >> bp.type >> " ";
		bp.write_data(out);
		return out;
	}

}

