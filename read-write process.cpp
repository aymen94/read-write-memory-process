#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

using namespace std;

DWORD getProcessPid(string nameProcess);


int main()
{
	DWORD pid,buff;
	string nameP;
	void* address;

	cout <<"insert name of process!"<<endl;
	getline(cin, nameP);

	
	pid = getProcessPid(nameP);
	if (!pid)
	{
		cerr << "process not found"<<endl;
		cin.get();
	}
	HANDLE hProcess= OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	
		
	cout <<"insert address to read/change :)"<<endl;
	cin >> address;

	ReadProcessMemory(hProcess,address, &buff, sizeof(DWORD), NULL);

	cout << "\nvalue  : " << buff<< endl;
	
	
	cout <<"insert new value!"<<endl;
	cin >>buff;
	
	if(!WriteProcessMemory(hProcess,address,&buff,sizeof(DWORD),0))
	{
	cerr << "error: the address not be changed"<<endl;
	return 0;
	}

	cout << "success: has been changed"<<endl;

	CloseHandle(hProcess);
	cin.get();
	return 1;
}


DWORD getProcessPid(string nameProcess)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	if (!Process32First(hProcessSnap, &pe32))
	{
		cerr << "Process32First" << endl;
		CloseHandle(hProcessSnap);
		return 0;
	}

	do
	{
		if (pe32.szExeFile == nameProcess)
		{
			cout << pe32.th32ProcessID<<endl;
			//free(&hProcessSnap);
			return pe32.th32ProcessID;
		}

	} while (Process32Next(hProcessSnap, &pe32));

	//free(&hProcessSnap);
	//free(&pe32);
	
	return 0;
}
