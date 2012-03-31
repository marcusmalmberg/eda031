namespace protocol {

	void ComListNgPacket::read(const Connection* conn) {
		MessageHandler::read_cmd(conn);
	}

	void ComListNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_LIST_NG);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
