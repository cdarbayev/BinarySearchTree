#include <iostream>
#include "tree.h"
#include <vector>

using namespace std;

int main() {
	/*Tree<int> t;
	t.insert(15);
	t.insert(10);
	t.insert(20);
	t.print();*/

	Tree<int> t;
	vector<int> data = {7, 2, 1, 2, 5, 7, 9, 10, 4, 3, 6};
	t.balance(data);
	t.print();
	return 0;
}