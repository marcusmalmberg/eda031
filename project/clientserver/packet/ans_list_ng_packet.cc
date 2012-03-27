namespace news_server {

	void AnsListNgPacket::read_data(const istream& in) {
		size_t n = read_num(in);
		for (size_t i = 0; i < n; ++i) {
			size_t id = read_num(in);
			string name = read_str(in);
			Newsgroup ng(id, name);
			ngs.push_back(ng);
		}
	}

	void AnsListNgPacket::write_data(ostream& out) {
		out << Protocol::ANS_LIST_NG << " ";
		size_t n = ngs.size();
	   	write_num(out, n);
		for (size_t i = 0; i < n; ++i) {
			write_num(out, ngs[i].id);
			write_str(out, ngs[i].name);
		}
		out << Protocol::ANS_END;
	}

}
