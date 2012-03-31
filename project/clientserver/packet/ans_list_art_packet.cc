namespace protocol {

	void AnsListArtPacket::read(const Connection* conn) {
		ans = MessageHandler::read_cmd(conn);
		if (ans == Protocol::ANS_ACK) {
			size_t size = MessageHandler::read_num(conn);
			for (size_t i = 0; i < size; ++i) {
				Article a;
				a.id = MessageHandler::read_num(conn);
				a.title = MessageHandler::read_str(conn);
				arts.push_back(a);
			}
		} else {
			err = MessageHandler::read_cmd(conn);
		}
	}

	void AnsListArtPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::ANS_LIST_ART);
		MessageHandler::write_cmd(ans);
		if (ans == Protocol::ANS_ACK) {
			size_t size = arts.size();
			for (size_t i = 0; i < size; ++i) {
				Article a = arts[i];
				MessageHandler::write_num(conn, a.id);
				MessageHandler::write_str(conn, a.title);
			}			
		} else {
			MessageHandler::write_cmd(err);		
		}
		MessageHandler::write_cmd(conn, Protocol::ANS_END);
	}

}
