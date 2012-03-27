package common;

/**
 * Interface for log windows.
 */

public interface Logger {
	/** Log start of transmission */
	void startSend();

	/** Log end of transmission */
	void stopSend();

	/** Log start of reception */
	void startReceive();

	/** Log end of reception */
	void stopReceive();

	/**
	 * Log a byte, as an int.
	 * 
	 * @param b
	 *            The byte to log
	 */
	void logByte(int b);

	/**
	 * Log a character, as character.
	 * 
	 * @param c
	 *            The character to log
	 */
	void logChar(char c);

	/**
	 * Log a command code or error code, as string.
	 * 
	 * @param code
	 *            The code to log
	 */
	void logCode(int code);

	/**
	 * Log a message.
	 * 
	 * @param msg
	 *            The message to log
	 */
	void logMessage(String msg);

	/**
	 * Show/hide the log window.
	 * 
	 * @param b
	 *            Show (true), hide (false)
	 */
	void setVisible(boolean b);
}
