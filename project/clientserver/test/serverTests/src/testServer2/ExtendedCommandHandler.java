package testServer2;

import common.CommandHandler;
import common.MessageHandler;

public class ExtendedCommandHandler extends CommandHandler {
	public ExtendedCommandHandler(MessageHandler mh) {
		super(mh);
	}

	public int[] getGroupIds() {
		return groupIds;
	}

	public int[] getArticleIds() {
		return articleIds;
	}
}
