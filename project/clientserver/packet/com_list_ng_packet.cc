namespace news_server {

	void ComListNgPacket::read_data(const istream& in) {
		size_t tok;
		in >> tok;
	}

	void ComListNgPacket::write_data(ostream& out) {
		out << Protocol::COM_LIST_NG << " " << Protocol::COM_END;
	}

}
