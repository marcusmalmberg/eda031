#include <iostream>
#include <string>
using namespace std;

bool palindrome(string word)
{
    bool pal = true;
    int len = word.length();
    for (int i = 0; i < len / 2; i++) {
        pal = word[i] == word[len-1-i] && pal;
    }
    return pal;
}

int main()
{
    cout << "Input a word:" << endl;
    string word;
    cin >> word;
    cout << "The word " << word;
    if (palindrome(word)) {
        cout << " is";
    } else {
        cout << " isn't";
    }
    cout << " a palindrome" << endl;
}

