#include <string>

using namespace std;

namespace protocol {

	void AnsListNgPacket::read(const Connection* conn) {
		size_t n = MessageHandler::read_num(conn);
		for (size_t i = 0; i < n; ++i) {
			size_t id = MessageHandler::read_num(conn);
			string name = MessageHandler::read_str(conn);
			Newsgroup ng(id, name);
			ngs.push_back(ng);
		}
		MessageHandler::read_cmd(conn);
	}

	void AnsListNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::ANS_LIST_NG);
		size_t n = ngs.size();
		MessageHandler::write_num(conn, n);
		for (size_t i = 0; i < n; ++i) {
			MessageHandler::write_num(conn, ngs[i].id);
			MessageHandler::write_str(conn, ngs[i].name);
		}
		MessageHandler::write_cmd(conn, Protocol::ANS_END);
	}

}
