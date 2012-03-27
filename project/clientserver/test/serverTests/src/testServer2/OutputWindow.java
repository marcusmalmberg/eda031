package testServer2;

import javax.swing.JTextArea;

class OutputWindow extends JTextArea {
	private static final long serialVersionUID = 1;

	public OutputWindow(int rows, int cols) {
		super(rows, cols);
		setEditable(false);
		println("NOTE -- \tthe server database must be empty before you run");
		println("        \tthe tests. Otherwise, the first test will fail.");
		println();
	}

	public void print(String msg) {
		append(msg);
	}

	public void println(String msg) {
		append(msg + "\n");
		setCaretPosition(getDocument().getLength());
	}

	public void println() {
		append("\n");
		setCaretPosition(getDocument().getLength());
	}
}
