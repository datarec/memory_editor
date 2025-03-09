#include <windows.h>
#include <iostream>
using namespace std;


int writeMemory(HANDLE pHandle, int hAddress, int uValue) {
    DWORD cBox = MessageBox(
        NULL, 
        "Are you sure you want to proceed?",
        "Manipulate Data", 
        MB_YESNO
    );
    if (cBox  == 7) {
        cout << "\nMemory operation failed.";
        exit(1);
    }
    else if (cBox == 6) {
        BOOL wMem =  WriteProcessMemory(
            (HANDLE)pHandle,
            (LPVOID)hAddress,
            (LPCVOID)&uValue,
            (SIZE_T)sizeof(DWORD),
            NULL
        );   
        if (wMem == 0) {
            cout << "\nMemory write failed with ERROR code: " << GetLastError();
        }
        else if (wMem == 1) {
            cout << "\nMemory operation successfully completed! ";
        }
    }
}

int main() {
    int pId;
    int hAddress; 
    int uValue;

    cout << "\nEnter PID: ";
    cin >> pId;
    cout << "Enter memory address: ";
    cin >> hAddress;
    cout << "Enter new value for this address: ";
    cin >> uValue;

    HANDLE pHandle = OpenProcess(
        PROCESS_VM_OPERATION | PROCESS_VM_WRITE, 
        FALSE, 
        pId
    );
    writeMemory(pHandle, hAddress, uValue);
}
