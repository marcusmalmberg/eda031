package testServer2;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import common.LogWindow;
import common.Logger;
import common.NullLogWindow;

/** GUI is the graphical user interface for the news client */
public class GUI extends JFrame {
	private static final long serialVersionUID = 1;
	private JButton runTestsButton;
	private JButton showLogButton;
	private OutputWindow output; // the test output
	private Logger logWindow; // the log window
	private TestDriver testDriver;

	/**
	 * Create a GUI.
	 * 
	 * @param title
	 *            The title of the window
	 * @param comHand
	 *            Handles the commands
	 * @param logged
	 *            True if the log window is to be created
	 */
	public GUI(String title, ExtendedCommandHandler comHand, boolean logged) {
		super(title);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		runTestsButton = new JButton("Run all tests");
		showLogButton = new JButton("Show log");
		if (!logged) {
			showLogButton.setText("No log");
			showLogButton.setEnabled(false);
		}

		Panel buttonPanel = new Panel();
		buttonPanel.add(runTestsButton);
		buttonPanel.add(showLogButton);
		add(buttonPanel, BorderLayout.NORTH);

		output = new OutputWindow(40, 80);
		add(new JScrollPane(output), BorderLayout.CENTER);

		testDriver = new TestDriver(output, comHand);

		ActionHandler handler = new ActionHandler();
		runTestsButton.addActionListener(handler);
		showLogButton.addActionListener(handler);

		pack();

		if (logged) {
			logWindow = new LogWindow();
			((Frame) logWindow).setLocation(getX() + getWidth(), getY());
		} else {
			logWindow = new NullLogWindow();
		}
		comHand.setLogWindow(logWindow);

		setVisible(true);
	}

	/** event handlers */
	private class ActionHandler implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			JButton source = (JButton) e.getSource();
			if (source == runTestsButton) {
				runTestsButton.setEnabled(false);
				testDriver.runTests();
			} else if (source == showLogButton) {
				if (showLogButton.getText().equals("Show log")) {
					showLogButton.setText("Hide log");
					logWindow.setVisible(true);
				} else if (showLogButton.getText().equals("Hide log")) {
					showLogButton.setText("Show log");
					logWindow.setVisible(false);
				}
			}
		}
	}
}
