package common;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LogWindow extends JFrame implements Logger {
	private static final long serialVersionUID = 1;
	private JTextArea text;

	public LogWindow() {
		super();

		text = new JTextArea(30, 60);
		text.setEditable(false);
		add(new JScrollPane(text), BorderLayout.CENTER);

		addWindowListener(new WindowHandler());
		pack();
	}

	public void startSend() {
		text.append("Sent: ");
	}

	public void stopSend() {
		text.append("\n");
	}

	public void startReceive() {
		text.append("Received: ");
	}

	public void stopReceive() {
		text.append("\n\n");
	}

	public void logByte(int b) {
		text.append(String.valueOf(b) + " ");
	}

	public void logChar(char c) {
		text.append(c + " ");
	}

	public void logCode(int code) {
		text.append(Protocol.codeString(code) + " ");
	}

	public void logMessage(String msg) {
		text.append("\n\n*** " + msg + " ***\n\n");
	}

	private class WindowHandler extends WindowAdapter {
		public void windowClosing(WindowEvent e) {
			setVisible(false);
		}
	}
}
