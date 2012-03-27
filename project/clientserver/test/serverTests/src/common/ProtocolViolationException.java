package common;

/**
 * ProtocolViolationException is thrown when the message handler or the command
 * handler detects a protocol violation in an answer from the server. This is an
 * Error which is never caught, so the program will be terminated if the
 * exception is thrown.
 */

public class ProtocolViolationException extends Error {
	private static final long serialVersionUID = 1;

	/**
	 * Create a ProtocolViolationException.
	 * 
	 * @param method
	 *            The method in which the violation was detected
	 * @param expectedCode
	 *            The expected protocol code
	 * @param receivedCode
	 *            The received code
	 */
	public ProtocolViolationException(String method, int expectedCode,
			int receivedCode) {
		super(method + ". Expected " + translateToString(expectedCode)
				+ ", received " + translateToString(receivedCode));
	}

	/**
	 * Create a ProtocolViolationException.
	 * 
	 * @param method
	 *            The method in which the violation was detected
	 * @param message
	 *            A string specifying the violation
	 */
	public ProtocolViolationException(String method, String message) {
		super(method + ". " + message + ".");
	}

	private static String translateToString(int code) {
		String s = Protocol.codeString(code);
		if (s == "") {
			s = "Unspecified code: (" + String.valueOf(code) + ")";
		}
		return s;
	}
}
