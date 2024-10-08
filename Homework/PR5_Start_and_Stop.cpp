#include <iostream>
#include <windows.h>
#include <process.h>

unsigned __stdcall ThreadFunction(void* pArguments) {
    while (true) {
        std::cout << "����� �����������..." << std::endl;
        Sleep(1000); // �������� 1 �������
    }
    return 0;
}

int main() {
    uintptr_t threadHandle = _beginthreadex(NULL, 0, &ThreadFunction, NULL, 0, NULL);

    // ����� ������ ���������� ��������� �����
    Sleep(5000);

    // ������������ ������
    SuspendThread((HANDLE)threadHandle);
    std::cout << "����� �������������." << std::endl;

    Sleep(3000); // ���� 3 �������

    // ������������� ������
    ResumeThread((HANDLE)threadHandle);
    std::cout << "����� �����������." << std::endl;

    // �������� ���������� ������
    WaitForSingleObject((HANDLE)threadHandle, INFINITE);
    CloseHandle((HANDLE)threadHandle);

    return 0;
}