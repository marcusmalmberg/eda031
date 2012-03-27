package common;

/**
 * A ConnectionClosedException is thrown when the message handler detects that
 * the server has closed the connection
 */
public class ConnectionClosedException extends Exception {
	private static final long serialVersionUID = 1;

	public ConnectionClosedException() {
		super("Server closed connection");
	}
}
