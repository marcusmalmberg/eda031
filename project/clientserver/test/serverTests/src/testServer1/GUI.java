package testServer1;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

import common.CommandHandler;
import common.ConnectionClosedException;
import common.LogWindow;
import common.Logger;
import common.NullLogWindow;
import common.Protocol;

/** GUI is the graphical user interface for the news client */
public class GUI extends JFrame {
	private static final long serialVersionUID = 1;
	private CommandHandler comHand; // command handler
	private JButton showLogButton;
	private DefaultListModel groupModel;
	private JList groupList; // the list of newsgroups
	private DefaultListModel articleModel;
	private JList articleList; // the list of articles
	private JTextArea articleText; // the article text
	private Logger logWindow; // the log window
	private NewArticleDialog newArticleDialog; // create article popup

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
	public GUI(String title, CommandHandler comHand, boolean logged) {
		super(title);
		this.comHand = comHand;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JButton listNGButton = new JButton("List newsgroups");
		JButton createNGButton = new JButton("New newsgroup");
		JButton deleteNGButton = new JButton("Delete newsgroup");
		JButton createArtButton = new JButton("New article");
		JButton deleteArtButton = new JButton("Delete article");
		showLogButton = new JButton("Show log");
		if (!logged) {
			showLogButton.setText("No log");
			showLogButton.setEnabled(false);
		}

		JPanel buttonPanel = new JPanel();
		buttonPanel.add(listNGButton);
		buttonPanel.add(createNGButton);
		buttonPanel.add(deleteNGButton);
		buttonPanel.add(createArtButton);
		buttonPanel.add(deleteArtButton);
		buttonPanel.add(showLogButton);
		add(buttonPanel, BorderLayout.NORTH);

		groupModel = new DefaultListModel();
		groupList = new JList(groupModel);
		groupList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		articleModel = new DefaultListModel();
		articleList = new JList(articleModel);
		articleList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		JPanel listPanel = new JPanel();
		listPanel.setLayout(new GridLayout(1, 2));
		JScrollPane jsp1 = new JScrollPane(groupList);
		jsp1.setBorder(BorderFactory.createTitledBorder("Groups"));
		listPanel.add(jsp1);
		JScrollPane jsp2 = new JScrollPane(articleList);
		jsp2.setBorder(BorderFactory.createTitledBorder("Articles"));
		listPanel.add(jsp2);

		articleText = new JTextArea(20, 80);
		articleText.setEditable(false);

		JScrollPane jsp3 = new JScrollPane(articleText);
		jsp3.setBorder(BorderFactory.createTitledBorder("Article"));
		JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
				listPanel, jsp3);
		splitPane.setOneTouchExpandable(false);
		add(splitPane, BorderLayout.CENTER);

		newArticleDialog = new NewArticleDialog(this);

		ActionHandler handler = new ActionHandler();
		listNGButton.addActionListener(handler);
		createNGButton.addActionListener(handler);
		deleteNGButton.addActionListener(handler);
		createArtButton.addActionListener(handler);
		deleteArtButton.addActionListener(handler);
		showLogButton.addActionListener(handler);

		ListHandler listHand = new ListHandler();
		groupList.addListSelectionListener(listHand);
		articleList.addListSelectionListener(listHand);

		pack();

		if (logged) {
			logWindow = new LogWindow();
			((JFrame) logWindow).setLocation(getX() + getWidth(), getY());
		} else {
			logWindow = new NullLogWindow();
		}
		comHand.setLogWindow(logWindow);

		setVisible(true);
	}

	private void connectionClosed() {
		logWindow.logMessage("Server closed connection");
	}

	public int getSelectedGroup() {
		return groupList.getSelectedIndex();
	}

	private void listGroups() {
		try {
			groupModel.removeAllElements();
			articleModel.removeAllElements();
			articleText.setText("");
			String[] groupNames = comHand.listGroups();
			for (int i = 0; i < groupNames.length; i++) {
				groupModel.addElement((i + 1) + " : " + groupNames[i]);
			}
		} catch (ConnectionClosedException e) {
			connectionClosed();
		}
	}

	private void createGroup(String title) {
		try {
			int status = comHand.createGroup(title);
			if (status == 0) {
				listGroups();
			} else {
				showError(status);
			}
		} catch (ConnectionClosedException e) {
			connectionClosed();
		}
	}

	private void deleteGroup(int groupIndex) {
		try {
			int status = comHand.deleteGroup(groupIndex);
			if (status == 0) {
				listGroups();
			} else {
				showError(status);
			}
		} catch (ConnectionClosedException ex) {
			connectionClosed();
		}
	}

	private void listArticles(int groupIndex) {
		try {
			articleModel.removeAllElements();
			articleText.setText("");
			String[] articleNames = comHand.listArticles(groupIndex);
			if (articleNames == null) {
				showError(Protocol.ERR_NG_DOES_NOT_EXIST); // FUSK
			} else {
				for (int i = 0; i < articleNames.length; i++) {
					articleModel.addElement((i + 1) + " : " + articleNames[i]);
				}
			}
		} catch (ConnectionClosedException ex) {
			connectionClosed();
		}
	}

	public void createArticle(int groupIndex, String title, String author,
			String text) {
		try {
			int status = comHand.createArticle(groupIndex, title, author, text);
			if (status == 0) {
				listArticles(groupIndex);
			} else {
				showError(status);
			}
		} catch (ConnectionClosedException ex) {
			connectionClosed();
		}
	}

	private void deleteArticle(int groupIndex, int articleIndex) {
		try {
			int status = comHand.deleteArticle(groupIndex, articleIndex);
			if (status == 0) {
				listArticles(groupIndex);
			} else {
				showError(status);
			}
		} catch (ConnectionClosedException ex) {
			connectionClosed();
		}
	}

	private void getArticle(int groupIndex, int articleIndex) {
		try {
			String[] articleContents = comHand.getArticle(groupIndex,
					articleIndex);
			if (articleContents.length == 3) {
				articleText.setText("Subject: " + articleContents[0] + "\n"
						+ "Author:  " + articleContents[1] + "\n" + "\n"
						+ articleContents[2]);
			} else {
				showError(Integer.parseInt(articleContents[0]));
			}
		} catch (ConnectionClosedException ex) {
			connectionClosed();
		}
	}

	private void showError(int errorCode) {
		String errorString;
		switch (errorCode) {
		case Protocol.ERR_NG_ALREADY_EXISTS:
			errorString = "Newsgroup already exists";
			break;
		case Protocol.ERR_NG_DOES_NOT_EXIST:
			errorString = "Newsgroup does not exist";
			break;
		case Protocol.ERR_ART_DOES_NOT_EXIST:
			errorString = "Article does not exist";
			break;
		default:
			errorString = Protocol.codeString(errorCode);
		}
		JOptionPane.showMessageDialog(this, errorString, "Error",
				JOptionPane.ERROR_MESSAGE);
	}

	/** event handlers */
	private class ActionHandler implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			JButton source = (JButton) e.getSource();
			String buttonText = source.getText();
			if (buttonText.equals("List newsgroups")) {
				listGroups();
			} else if (buttonText.equals("New newsgroup")) {
				String groupName = (String) JOptionPane.showInputDialog(
						GUI.this, "Name of new group:", "New Group",
						JOptionPane.PLAIN_MESSAGE);
				if (groupName != null && groupName.length() > 0) {
					createGroup(groupName.trim());
				}
			} else if (buttonText.equals("Delete newsgroup")) {
				int selectedGroup = groupList.getSelectedIndex();
				if (selectedGroup != -1) {
					deleteGroup(selectedGroup);
				}
			} else if (buttonText.equals("New article")) {
				if (groupList.getSelectedIndex() != -1) {
					newArticleDialog.showDialog();
				}
			} else if (buttonText.equals("Delete article")) {
				int selectedGroup = groupList.getSelectedIndex();
				int selectedArticle = articleList.getSelectedIndex();
				if (selectedGroup != -1 && selectedArticle != -1) {
					deleteArticle(selectedGroup, selectedArticle);
				}
			} else if (buttonText.equals("Show log")) {
				showLogButton.setText("Hide log");
				logWindow.setVisible(true);
			} else if (buttonText.equals("Hide log")) {
				showLogButton.setText("Show log");
				logWindow.setVisible(false);
			}
		}
	}

	private class ListHandler implements ListSelectionListener {
		public void valueChanged(ListSelectionEvent e) {
			int selectedGroup = groupList.getSelectedIndex();
			if (selectedGroup == -1) {
				return;
			}
			if (e.getSource() == groupList) {
				listArticles(selectedGroup);
			} else {
				int selectedArticle = articleList.getSelectedIndex();
				if (selectedArticle != -1) {
					getArticle(selectedGroup, selectedArticle);
				}
			}
		}
	}
}
