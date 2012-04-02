#include "ans_delete_ng_packet.h"

namespace protocol {

	bool AnsDeleteNgPacket::read(const Connection* conn) {
		ans = MessageHandler::read_cmd(conn);
		if (ans == Protocol::ANS_NAK) {
			err = MessageHandler::read_cmd(conn);
		}
		if (MessageHandler::read_cmd(conn) != Protocol::ANS_END) {
			return false;
		}
		return true;
	}

	void AnsDeleteNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::ANS_DELETE_NG);
		MessageHandler::write_cmd(conn, ans);
		if (ans == Protocol::ANS_NAK) {
			MessageHandler::write_cmd(conn, err);
		}
		MessageHandler::write_cmd(conn, Protocol::ANS_END);
	}

}
