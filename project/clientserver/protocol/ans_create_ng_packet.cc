#include "ans_create_ng_packet.h"

namespace protocol {

	void AnsCreateNgPacket::read(const Connection* conn) {
		ans = MessageHandler::read_cmd(conn);
		if (ans == Protocol::ANS_NAK) {
			err = MessageHandler::read_cmd(conn);
		}
		MessageHandler::read_cmd(conn);
	}

	void AnsCreateNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::ANS_CREATE_NG);
		MessageHandler::write_cmd(conn, ans);
		if (ans == Protocol::ANS_NAK) {
			MessageHandler::write_cmd(conn, err);
		}
		MessageHandler::write_cmd(conn, Protocol::ANS_END);
	}

}
