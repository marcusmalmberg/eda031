package testServer2;

class TestNewsarchive {
	private java.util.ArrayList<TestNewsgroup> groups;

	public TestNewsarchive() {
		groups = new java.util.ArrayList<TestNewsgroup>();
	}

	public int size() {
		return groups.size();
	}

	public void addGroup(TestNewsgroup group) {
		groups.add(group);
	}

	public void deleteGroup(String groupTitle) {
		int i = 0;
		while (i < groups.size()
				&& !groups.get(i).getTitle().equals(groupTitle)) {
			i++;
		}
		if (i < groups.size()) {
			groups.remove(i);
		}
	}

	public TestNewsgroup groupAt(int i) {
		return groups.get(i);
	}
}
