#include <iostream>
#include <windows.h>
#include <process.h>

unsigned __stdcall ThreadFunction(void* pArguments) {
    while (true) {
        std::cout << "����� �����������..." << std::endl;
        Sleep(2000); // �������� 2 �������
    }
    return 0;
}

int main() {
    uintptr_t threadHandle = _beginthreadex(NULL, 0, &ThreadFunction, NULL, 0, NULL);

    // ����� ������ ���������� ��������� �����
    Sleep(5000);

    // ���������� ������
    TerminateThread((HANDLE)threadHandle, 0);
    CloseHandle((HANDLE)threadHandle);

    std::cout << "����� ��������." << std::endl;

    return 0;
}