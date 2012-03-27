package testServer2;

class TestNewsgroup {
	private String title;
	private int id;
	private int index;
	private java.util.ArrayList<TestArticle> articles;

	public TestNewsgroup(String title) {
		this.title = title;
		id = -1;
		index = -1;
		articles = new java.util.ArrayList<TestArticle>();
	}

	public int size() {
		return articles.size();
	}

	public String getTitle() {
		return title;
	}

	public void addArticle(TestArticle art) {
		articles.add(art);
	}

	public void deleteArticle(String articleTitle) {
		int i = 0;
		while (i < articles.size()
				&& !articles.get(i).getTitle().equals(articleTitle)) {
			i++;
		}
		if (i < articles.size()) {
			articles.remove(i);
		}
	}

	public TestArticle articleAt(int i) {
		return articles.get(i);
	}

	public int getId() {
		return id;
	}

	public void setId(int newId) {
		id = newId;
	}

	public int getIndex() {
		return index;
	}

	public void setIndex(int newIndex) {
		index = newIndex;
	}
}
