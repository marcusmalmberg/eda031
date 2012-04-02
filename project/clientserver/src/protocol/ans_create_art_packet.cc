#include "ans_create_art_packet.h"

namespace protocol {

	bool AnsCreateArtPacket::read(const Connection* conn) {
		ans = MessageHandler::read_cmd(conn);
		if (ans == Protocol::ANS_NAK) {
			err = MessageHandler::read_cmd(conn);
		}
		if (MessageHandler::read_cmd(conn) != Protocol::ANS_END) {
			return false;
		}
		return true;
	}

	void AnsCreateArtPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::ANS_CREATE_ART);
		MessageHandler::write_cmd(conn, ans);
		if (ans == Protocol::ANS_NAK) {
			MessageHandler::write_cmd(conn, err);
		}
		MessageHandler::write_cmd(conn, Protocol::ANS_END);
	}

}
