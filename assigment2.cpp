/*
Hesham ashraf mousa(139593)
Section 7
Assignment 2 (Stack).
*/
#include<iostream>
#include<string>
using namespace std;
//Node class
class Node {
public:
	Node* next;
	char info;
};
/*****************************************************/
//stack class
class stack {
	Node* stackTop;
	int length;//the length of stack
public:
	stack();
	stack(char info);
	void push(char);
	void pop();
	void clearStack();
	void copyStack(stack old);
	char top();
	bool isEmpty();
	int getLength();
};
stack::stack() {
	stackTop = 0;
	length = 0;
}
stack::stack(char info) {
	stackTop = 0;
	length = 0;
	push(info);
}
void stack::push(char info) {
	Node* node;
	node = new Node;

	node->info = info;

	node->next = stackTop;
	stackTop = node;

	length++;
}
void stack::pop(){
	if (!isEmpty()) {
		Node* current;

		current = stackTop;
		stackTop = stackTop->next;

		delete current;
		length--;
	}
	else
		cout << "You can`t pop from an empty stack.\n";
}
void stack::clearStack() {
	if (!isEmpty()) {
		Node* current;

		current = stackTop;
		while (stackTop != 0){
			stackTop = stackTop->next;

			delete current;
			current = stackTop;
		}
		length = 0;
	}
	else
		cout << "You can`t clear an empty stack.\n";
}
void stack::copyStack(stack old) {
	if (this != &old) {
		stack temp;

		while (old.top() != 0) {
			temp.push(old.top());
			old.pop();
		}

		while(temp.top() != 0){
			push(temp.top());

			temp.pop();
		}
		length = old.length;
	}
	else
		cout << "You cant copy the same stack.\n";
}
char stack::top() {
	if (!isEmpty()) {
		return stackTop->info;
	}
	else
		cout << "You can`t top element from empty stack.\n";
}
bool stack::isEmpty() { return stackTop == 0; }
int stack::getLength() { return length; }
/*****************************************************************/
class pharse {
	string word;
	stack content;
public:
	pharse();
	pharse(string info);
	pharse(const pharse& old);
	void readPharse(string &);//this function will ask the user to enter the word
	bool isLetter(char);
	bool isPalindrome();
};
pharse::pharse(){
	word = "";
}
pharse::pharse(string info){
	word = info;
}
pharse::pharse(const pharse& old){
	word = old.word;

	content.copyStack(old.content);
}
void pharse::readPharse(string& test){
	cout << "Please enter the Pharse : ";
	getline(cin, test);
	word = test;

	//This loop will convert any upper case letter to lower case letter
	for (int i = 0; i < word.length(); i++) {
		if (isLetter(word[i]))
			if (word[i] >= 65 && word[i] <= 90)
				word[i] = word[i] + 32;
	}

	for (int i = 0; i < word.length(); i++)
		if (isLetter(word[i]))
			content.push(word[i]);
}
//this function will check if the contain of index aletter of not
bool pharse::isLetter(char letter){
	if (letter >= 97 && letter <= 122 || letter >= 65 && letter <= 90)
		return true;
	return false;
}
bool pharse::isPalindrome(){
	int test = 0, length = word.length() - (word.length() - content.getLength());
	//test:check if the length of stack like a word length
	stack temp;//temporary stack to saved the original stack content

	//This loop will make the word contain just a letters
	for (int i = 0; i < word.length(); i++)
		if (!isLetter(word[i])) {
			word.erase(i, 1);
			i--;
		}

	//This loop will compare the content of stack with the content in the word variable
	for (int i = 0; i < length ; i++) {
		if (content.top() == word[i])
			test++;
		
		temp.push(content.top());
		content.pop();
	}

	while (!temp.isEmpty()) {
		content.push(temp.top());
		temp.pop();
	}
	
	if(test == length)
		return true; 
	return false;
}
int main() {
	pharse* object1;
	string word;

	object1 = new pharse();

	object1->readPharse(word);
	if (object1->isPalindrome())
		cout << "The word : " << "\"" << word << "\" it`s Palindrome.\n";
	else
		cout << "The word : " << "\"" << word << "\" it`s not Palindrome.\n";
	return 0;
}