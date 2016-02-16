#include "Trie/Node.h"
#include "Trie/Trie.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <string>

// TEST(test_case_name, test_name) {
//  ... test body ...
// }

TEST(TrieUnitTests, Dummy) {
    Trie trie;
    trie.addWord("cnm");
    
	ASSERT_EQ(true, trie.isWord("cnm"));
}
TEST(TrieUnitTests, Dummy1) {
    Trie trie;
    trie.addWord("cnm");
    
	ASSERT_EQ(false, trie.isWord("c"));
}
TEST(TrieUnitTests, Dummy2) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
    
	ASSERT_EQ(true, trie.isWord("people"));
}
TEST(TrieUnitTests, Dummy3) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	vector<string> v = trie.allWordsWithPrefix("pe");
    
	ASSERT_EQ(16, v.size());
}

TEST(TrieUnitTests, Dummy4) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	vector<string> v = trie.allWordsWithPrefix("asdfghjkl");
    
	ASSERT_EQ(0, v.size());
}

TEST(TrieUnitTests, Dummy5) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	vector<string> v = trie.allWordsWithPrefix("peace");
    
	ASSERT_EQ(1, v.size());
}

TEST(TrieUnitTests, Dummy6) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	
	
	vector<string> v = trie2.allWordsWithPrefix("map");
    
	ASSERT_EQ(0, v.size());
}
TEST(TrieUnitTests, Dummy7) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	
	Trie trie3(trie);
	vector<string> v = trie3.allWordsWithPrefix("map");
    
	ASSERT_EQ(1, v.size());
}
TEST(TrieUnitTests, Dummy8) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	
	Trie trie3(trie);
	
	trie3=trie2;
	
	vector<string> v = trie3.allWordsWithPrefix("map");
    
	ASSERT_EQ(0, v.size());
}













int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
