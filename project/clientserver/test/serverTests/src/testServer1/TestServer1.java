package testServer1;

import common.CommandHandler;
import common.Connection;
import common.MessageHandler;

/** Client for the news server, used to test the server implementation */
public class TestServer1 {
	public static void main(String[] args) {
		boolean logged = false;
		String machine = "";
		String port = "";
		int portNumber = 0;
		boolean error = false;

		if (args.length == 2) {
			logged = true;
			machine = args[0];
			port = args[1];
		} else if (args.length == 3 && args[0].equals("-nolog")) {
			logged = false;
			machine = args[1];
			port = args[2];
		} else {
			error = true;
		}

		try {
			portNumber = Integer.parseInt(port);
		} catch (NumberFormatException e) {
			error = true;
		}

		if (error) {
			System.err.println("Usage: java -jar "
					+ "TestServer1.jar " + "[-nolog] server port");
			System.exit(1);
		}

		Connection conn = new Connection(machine, portNumber);
		if (!conn.isConnected()) {
			System.err.println("Connection attempt failed");
			System.exit(1);
		}

		MessageHandler mh = new MessageHandler(conn);
		CommandHandler comHand = new CommandHandler(mh);
		new GUI("News Client - server tester", comHand, logged);
	}
}
