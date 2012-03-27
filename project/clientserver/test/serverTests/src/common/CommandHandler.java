package common;

/**
 * CommandHandler handles the commands that the client issues
 * 
 * Fix: 2003-02-20, introduced "non-existing id's" for non-existing groups and
 * articles (really only necessary in TestServer2)
 */
public class CommandHandler {
	private MessageHandler mh; // messages
	private Logger logWindow; // log window
	protected int[] groupIds; // received group id's in group listings
	protected int[] articleIds; // - article id's in article listings
	private static final int NE_GROUP_ID = 999999; // these id's do not
	private static final int NE_ART_ID = 888888; // exist

	/**
	 * Create a command handler.
	 * 
	 * @param mh
	 *            The message handler
	 */
	public CommandHandler(MessageHandler mh) {
		this.mh = mh;
	}

	/**
	 * Set the log window where commands are logged
	 * 
	 * @param logWindow
	 *            The log window
	 */
	public void setLogWindow(Logger logWindow) {
		this.logWindow = logWindow;
		mh.setLogWindow(logWindow);
	}

	/**
	 * Handle the List groups command.
	 * 
	 * @return The group names
	 * @throws ConnectionClosedException
	 *             If the server dies
	 * @throws ProtocolViolationException
	 *             If the answer from the client does not follow the protocol
	 */
	public String[] listGroups() throws ConnectionClosedException,
			ProtocolViolationException {
		logWindow.startSend();
		mh.sendCode(Protocol.COM_LIST_NG);
		mh.sendCode(Protocol.COM_END);
		logWindow.stopSend();

		logWindow.startReceive();
		int code = mh.recvCode();
		checkCode("List groups", Protocol.ANS_LIST_NG, code);

		int nbrGroups = mh.recvIntParameter();
		checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
		groupIds = new int[nbrGroups];
		String[] groupNames = new String[nbrGroups];
		for (int i = 0; i < nbrGroups; i++) {
			groupIds[i] = mh.recvIntParameter();
			groupNames[i] = mh.recvStringParameter();
		}
		code = mh.recvCode();
		checkCode("List groups", Protocol.ANS_END, code);
		logWindow.stopReceive();
		return groupNames;
	}

	/**
	 * Handle the Create group command.
	 * 
	 * @param title
	 *            The title of the group to create
	 * @return Error code or 0 if no error
	 * @throws ConnectionClosedException
	 *             If the server dies
	 * @throws ProtocolViolationException
	 *             If the answer from the client does not follow the protocol
	 */
	public int createGroup(String title) throws ConnectionClosedException,
			ProtocolViolationException {
		logWindow.startSend();
		mh.sendCode(Protocol.COM_CREATE_NG);
		mh.sendStringParameter(title);
		mh.sendCode(Protocol.COM_END);
		logWindow.stopSend();

		int errorCode = 0;
		logWindow.startReceive();
		int code = mh.recvCode();
		checkCode("Create group", Protocol.ANS_CREATE_NG, code);
		code = mh.recvCode();
		if (code != Protocol.ANS_ACK) {
			checkCondition(code == Protocol.ANS_NAK, "Create group",
					"Did not receive ANS_ACK or ANS_NAK");
			errorCode = mh.recvCode();
		}
		code = mh.recvCode();
		checkCode("Create group", Protocol.ANS_END, code);
		logWindow.stopReceive();
		return errorCode;
	}

	/**
	 * Handle the Delete group command.
	 * 
	 * @param groupIndex
	 *            Internal index of previously listed group
	 * @return Error code or 0 if no error
	 * @throws ConnectionClosedException
	 *             If the server dies
	 * @throws ProtocolViolationException
	 *             If the answer from the client does not follow the protocol
	 */
	public int deleteGroup(int groupIndex) throws ConnectionClosedException,
			ProtocolViolationException {
		int groupId = getGroupId(groupIndex);
		logWindow.startSend();
		mh.sendCode(Protocol.COM_DELETE_NG);
		mh.sendIntParameter(groupId);
		mh.sendCode(Protocol.COM_END);
		logWindow.stopSend();

		int errorCode = 0;
		logWindow.startReceive();
		int code = mh.recvCode();
		checkCode("Delete group", Protocol.ANS_DELETE_NG, code);
		code = mh.recvCode();
		if (code != Protocol.ANS_ACK) {
			checkCondition(code == Protocol.ANS_NAK, "Create group",
					"Did not receive ANS_ACK or ANS_NAK");
			errorCode = mh.recvCode();
		}
		code = mh.recvCode();
		checkCode("Delete group", Protocol.ANS_END, code);
		logWindow.stopReceive();
		return errorCode;
	}

	/**
	 * Handle the List article command.
	 * 
	 * @param groupIndex
	 *            Internal index of previously listed group
	 * @return The article names, null if group does not exist
	 * @throws ConnectionClosedException
	 *             If the server dies
	 * @throws ProtocolViolationException
	 *             If the answer from the client does not follow the protocol
	 */
	public String[] listArticles(int groupIndex)
			throws ConnectionClosedException, ProtocolViolationException {
		int groupId = getGroupId(groupIndex);
		logWindow.startSend();
		mh.sendCode(Protocol.COM_LIST_ART);
		mh.sendIntParameter(groupId);
		mh.sendCode(Protocol.COM_END);
		logWindow.stopSend();

		logWindow.startReceive();
		int code = mh.recvCode();
		checkCode("List articles", Protocol.ANS_LIST_ART, code);
		code = mh.recvCode();
		if (code != Protocol.ANS_ACK) {
			checkCondition(code == Protocol.ANS_NAK, "Create group",
					"Did not receive ANS_ACK or ANS_NAK");
			code = mh.recvCode(); // error code
			code = mh.recvCode(); // hopefully ANS_NAK, not checked
			logWindow.stopReceive();
			return null;
		}
		int nbrArticles = mh.recvIntParameter();
		checkCondition(nbrArticles >= 0, "List articles",
				"Number of groups < 0");
		articleIds = new int[nbrArticles];
		String[] articleNames = new String[nbrArticles];
		for (int i = 0; i < nbrArticles; i++) {
			articleIds[i] = mh.recvIntParameter();
			articleNames[i] = mh.recvStringParameter();
		}
		code = mh.recvCode();
		checkCode("List articles", Protocol.ANS_END, code);
		logWindow.stopReceive();
		return articleNames;
	}

	/**
	 * Handle the Create article command.
	 * 
	 * @param groupIndex
	 *            Internal index of previously listed group
	 * @param title
	 *            The title of the article
	 * @param author
	 *            The author of the article
	 * @param text
	 *            The text of the article
	 * @return Error code or 0 if no error
	 * @throws ConnectionClosedException
	 *             If the server dies
	 * @throws ProtocolViolationException
	 *             If the answer from the client does not follow the protocol
	 */
	public int createArticle(int groupIndex, String title, String author,
			String text) throws ConnectionClosedException,
			ProtocolViolationException {
		int groupId = getGroupId(groupIndex);
		logWindow.startSend();
		mh.sendCode(Protocol.COM_CREATE_ART);
		mh.sendIntParameter(groupId);
		mh.sendStringParameter(title);
		mh.sendStringParameter(author);
		mh.sendStringParameter(text);
		mh.sendCode(Protocol.COM_END);
		logWindow.stopSend();

		int errorCode = 0;
		logWindow.startReceive();
		int code = mh.recvCode();
		checkCode("Create article", Protocol.ANS_CREATE_ART, code);
		code = mh.recvCode();
		if (code != Protocol.ANS_ACK) {
			checkCondition(code == Protocol.ANS_NAK, "Create group",
					"Did not receive ANS_ACK or ANS_NAK");
			errorCode = mh.recvCode();
		}
		code = mh.recvCode();
		checkCode("Create article", Protocol.ANS_END, code);
		logWindow.stopReceive();
		return errorCode;
	}

	/**
	 * Handle the Delete article command.
	 * 
	 * @param groupIndex
	 *            Internal index of previously listed group
	 * @param articleIndex
	 *            Internal index of previously listed article
	 * @return Error code or 0 if no error
	 * @throws ConnectionClosedException
	 *             If the server dies
	 * @throws ProtocolViolationException
	 *             If the answer from the client does not follow the protocol
	 */
	public int deleteArticle(int groupIndex, int articleIndex)
			throws ConnectionClosedException, ProtocolViolationException {
		int groupId = getGroupId(groupIndex);
		int articleId = getArticleId(articleIndex);
		logWindow.startSend();
		mh.sendCode(Protocol.COM_DELETE_ART);
		mh.sendIntParameter(groupId);
		mh.sendIntParameter(articleId);
		mh.sendCode(Protocol.COM_END);
		logWindow.stopSend();

		int errorCode = 0;
		logWindow.startReceive();
		int code = mh.recvCode();
		checkCode("Delete article", Protocol.ANS_DELETE_ART, code);
		code = mh.recvCode();
		if (code != Protocol.ANS_ACK) {
			checkCondition(code == Protocol.ANS_NAK, "Create group",
					"Did not receive ANS_ACK or ANS_NAK");
			errorCode = mh.recvCode();
		}
		code = mh.recvCode();
		checkCode("Delete article", Protocol.ANS_END, code);
		logWindow.stopReceive();
		return errorCode;
	}

	/**
	 * Handle the Get article command.
	 * 
	 * @param groupIndex
	 *            Internal index of previously listed group
	 * @param articleIndex
	 *            Internal index of previously listed article
	 * @return String array of length 3 and title in [0], author in [1], text in
	 *         [2], or of length 1 and error code in [0]
	 * @throws ConnectionClosedException
	 *             If the server dies
	 * @throws ProtocolViolationException
	 *             If the answer from the client does not follow the protocol
	 */
	public String[] getArticle(int groupIndex, int articleIndex)
			throws ConnectionClosedException, ProtocolViolationException {
		int groupId = getGroupId(groupIndex);
		int articleId = getArticleId(articleIndex);
		logWindow.startSend();
		mh.sendCode(Protocol.COM_GET_ART);
		mh.sendIntParameter(groupId);
		mh.sendIntParameter(articleId);
		mh.sendCode(Protocol.COM_END);
		logWindow.stopSend();

		String[] result = null;
		logWindow.startReceive();
		int code = mh.recvCode();
		checkCode("Get article", Protocol.ANS_GET_ART, code);
		code = mh.recvCode();
		if (code != Protocol.ANS_ACK) {
			checkCondition(code == Protocol.ANS_NAK, "Create group",
					"Did not receive ANS_ACK or ANS_NAK");
			result = new String[1];
			result[0] = String.valueOf(mh.recvCode());
		} else {
			result = new String[3];
			result[0] = mh.recvStringParameter();
			result[1] = mh.recvStringParameter();
			result[2] = mh.recvStringParameter();
		}
		code = mh.recvCode();
		checkCode("Delete article", Protocol.ANS_END, code);
		logWindow.stopReceive();
		return result;
	}

	private int getGroupId(int groupIndex) {
		return (groupIndex >= 0 && groupIndex < groupIds.length) ? groupIds[groupIndex]
				: NE_GROUP_ID;
	}

	private int getArticleId(int articleIndex) {
		return (articleIndex >= 0 && articleIndex < articleIds.length) ? articleIds[articleIndex]
				: NE_ART_ID;
	}

	private void checkCode(String method, int expectedCode, int code)
			throws ProtocolViolationException {
		if (code != expectedCode) {
			throw new ProtocolViolationException(method, expectedCode, code);
		}
	}

	private void checkCondition(boolean condition, String method, String message)
			throws ProtocolViolationException {
		if (!condition) {
			throw new ProtocolViolationException(method, message);
		}
	}
}
