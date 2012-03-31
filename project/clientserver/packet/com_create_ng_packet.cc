namespace protocol {

	void ComCreateNgPacket::read(const Connection* conn) {
		name = MessageHandler::read_string(conn);
		MessageHandler::read_cmd(conn);
	}

	void ComCreateNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(Protocol::COM_CREATE_NG);
		MessageHandler::write_str(name);
		MessageHandler::write_cmd(Protocol::COM_END);
	}

}
