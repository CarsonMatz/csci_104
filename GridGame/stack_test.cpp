#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
	Stack<int> s;

	cout << s.empty() << " " << s.size() << endl;

	s.push(1);
	s.push(2);
	s.push(3);

	cout << s.top() << " " << s.size() << endl;

	s.pop();
	s.pop();

	cout << s.size() << endl;
	
	return 0;
}