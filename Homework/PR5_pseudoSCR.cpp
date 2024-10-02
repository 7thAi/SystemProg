#include <iostream>
#include <windows.h>
#include <process.h>

unsigned __stdcall ThreadFunction(void* pArguments) {
    int threadNum = *(int*)pArguments;
    for (int i = 0; i < 5; i++) {
        std::cout << "����� " << threadNum << " ��������� ������ " << i + 1 << std::endl;
        Sleep(1000); // �������� 1 �������
    }
    return 0;
}

int main() {
    const int numThreads = 2;
    uintptr_t threadHandles[numThreads];
    int threadIds[numThreads];

    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i + 1;
        threadHandles[i] = _beginthreadex(NULL, 0, &ThreadFunction, &threadIds[i], 0, NULL);
    }

    // �������� ���������� �������
    WaitForMultipleObjects(numThreads, (HANDLE*)threadHandles, TRUE, INFINITE);

    // ���������� ������ � ��������
    for (int i = 0; i < numThreads; i++) {
        CloseHandle((HANDLE)threadHandles[i]);
    }

    std::cout << "��� ������ ���������." << std::endl;

    return 0;
}