namespace news_server {

	void ComCreateNgPacket::read_data(Connection* conn) {
		name = MessageHandler::read_string(conn);
		size_t cmd = MessageHandler::read_cmd(conn);
	}

	void ComCreateNgPacket::write_data(Connection* conn) {
		MessageHandler::write_cmd(Protocol::COM_CREATE_NG);
		MessageHandler::write_str(name);
		MessageHandler::write_cmd(Protocol::COM_END);
	}

}
