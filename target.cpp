#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

int i = 5555;
int main() {
	
	cout << "target to read i" << endl;

	while(1)
	{
		cout << "i:" << i++ << " address i:" << &i << endl;
		Sleep(5000);
	}	
	return 0;
}



