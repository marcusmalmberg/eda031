package testServer2;

class TestArticle {
	private String title;
	private String author;
	private String text;
	private int id;
	private int index;

	public TestArticle(String title, String author, String text) {
		this.title = title;
		this.author = author;
		this.text = text;
		id = -1;
		index = -1;
	}

	public String getTitle() {
		return title;
	}

	public String getAuthor() {
		return author;
	}

	public String getText() {
		return text;
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
