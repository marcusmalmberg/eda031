#include "ans_get_art_packet.h"

namespace protocol {

	bool AnsGetArtPacket::read(const Connection* conn) {
		ans = MessageHandler::read_cmd(conn);
		if (ans == Protocol::ANS_ACK) {
			a.title = MessageHandler::read_str(conn);
			a.author = MessageHandler::read_str(conn);
			a.text = MessageHandler::read_str(conn);
		} else {
			err = MessageHandler::read_cmd(conn);
		}
		if (MessageHandler::read_cmd(conn) != Protocol::ANS_END) {
	        return false;
        }
        return true;
	}

	void AnsGetArtPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::ANS_GET_ART);
		MessageHandler::write_cmd(conn, ans);
		if (ans == Protocol::ANS_ACK) {
			MessageHandler::write_str(conn, a.title);
			MessageHandler::write_str(conn, a.author);
			MessageHandler::write_str(conn, a.text);
		} else {
			MessageHandler::write_cmd(conn, err);		
		}
		MessageHandler::write_cmd(conn, Protocol::ANS_END);
	}

}
