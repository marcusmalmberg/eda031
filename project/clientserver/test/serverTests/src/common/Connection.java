package common;

import java.io.*;
import java.net.*;

/**
 * A Connection represents a connection to the server. Modeled after the
 * corresponding C++ class used in the IRP project.
 */
public class Connection {
	/** Returned from read() if the server closes the connection */
	public static final int CONNECTION_CLOSED = 1000;
	private Socket mySocket;
	private InputStream input;
	private OutputStream output;

	/**
	 * Create a connection.
	 * 
	 * @param host
	 *            The name of the host on which the server runs
	 * @param port
	 *            The port number on which the server listens
	 */
	public Connection(String host, int port) {
		mySocket = null;
		try {
			mySocket = new Socket(host, port);
			input = mySocket.getInputStream();
			output = mySocket.getOutputStream();
		} catch (IOException e) {
			// failure to open => mySocket==null, checked in isConnected()
		}
	}

	/**
	 * Check if the connection succeeded.
	 * 
	 * @return True/false
	 */
	public boolean isConnected() {
		return mySocket != null;
	}

	/**
	 * Write a byte to the server.
	 * 
	 * @param data
	 *            The byte to write
	 * @throws IOException
	 *             If the connection was not opened
	 */
	public void write(char data) throws IOException {
		if (mySocket == null) {
			error("write attempted on a not properly opened Connection");
		}
		output.write(data);
	}

	/**
	 * Read a byte from the server.
	 * 
	 * @return The received byte, or CONNECTION_CLOSED if the server closed the
	 *         connection
	 */
	public int read() {
		if (mySocket == null) {
			error("read attempted on a not properly opened Connection");
		}
		try {
			int data = input.read();
			return data != -1 ? data : CONNECTION_CLOSED;
		} catch (IOException e) {
			// server failure, return CONNECTION_CLOSED
			return CONNECTION_CLOSED;
		}
	}

	private void error(String msg) {
		System.err.println(msg);
		System.exit(0);
	}
}
