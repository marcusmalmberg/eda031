package testServer1;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * NewArticleDialog is used to enter the subject, author and text of a new
 * article
 */
class NewArticleDialog extends JDialog {
	private static final long serialVersionUID = 1;
	private GUI parent;
	private JButton okBtn, cancelBtn;
	private JTextField subjectField;
	private JTextField authorField;
	private JTextArea textArea;

	public NewArticleDialog(GUI parent) {
		super(parent, "Create article", true);
		this.parent = parent;
		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);

		JPanel p1 = new JPanel();
		subjectField = new JTextField(20);
		authorField = new JTextField(20);
		p1.add(new Label("Subject: "));
		p1.add(subjectField);
		p1.add(new Label("   Author: "));
		p1.add(authorField);
		add(p1, BorderLayout.NORTH);

		textArea = new JTextArea(20, 40);
		JScrollPane jsp = new JScrollPane(textArea);
		jsp.setBorder(BorderFactory.createTitledBorder("Article text"));
		add(jsp, BorderLayout.CENTER);

		JPanel p2 = new JPanel();
		okBtn = new JButton("OK");
		cancelBtn = new JButton("Cancel");
		p2.add(cancelBtn);
		p2.add(okBtn);
		add(p2, BorderLayout.SOUTH);

		ActionHandler handler = new ActionHandler();
		okBtn.addActionListener(handler);
		cancelBtn.addActionListener(handler);

		pack();
	}

	public void showDialog() {
		setLocation(parent.getX() + (parent.getWidth() - getWidth()) / 2,
				parent.getY() + (parent.getHeight() - getHeight()) / 2);
		subjectField.setText("");
		authorField.setText("");
		textArea.setText("");
		subjectField.requestFocusInWindow();
		setVisible(true);
	}

	private class ActionHandler implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			if (e.getSource() == okBtn) {
				parent.createArticle(parent.getSelectedGroup(), subjectField
						.getText(), authorField.getText(), textArea.getText());
			}
			setVisible(false);
		}
	}
}
