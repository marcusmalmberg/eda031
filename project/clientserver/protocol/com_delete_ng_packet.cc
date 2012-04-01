namespace protocol {

	void ComDeleteNgPacket::read(const Connection* conn) {
		id = MessageHandler::read_num(conn);
		MessageHandler::read_cmd(conn);
	}

	void ComDeleteNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(Protocol::COM_DELETE_NG);
		MessageHandler::write_num(id);
		MessageHandler::write_cmd(Protocol::COM_END);
	}

}
