#include <iostream>
#include <windows.h>

// �������, ����������� � ������
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    int threadId = *(int*)lpParam;
    for (int i = 0; i < 5; i++) {
        std::cout << "����� " << threadId << " ��������� ������ " << i + 1 << std::endl;
        Sleep(1000); // �������� 1 �������
    }
    return 0;
}

int main() {
    const int numThreads = 3; // ���������� �������
    HANDLE threads[numThreads]; // ������ ������������ �������
    int threadIds[numThreads];   // ������ ��������������� �������

    // �������� �������
    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i + 1; // ������������� ������
        threads[i] = CreateThread(
            NULL,           // �������� ������������ �� ���������
            0,              // ��������� ������ �����
            ThreadFunction, // ������� ������
            &threadIds[i],  // �������� ������������� ������
            0,              // ��������� ��������
            NULL            // ������������ ������������� ������
        );

        if (threads[i] == NULL) {
            std::cerr << "������ �������� ������: " << GetLastError() << std::endl;
        }
    }

    // �������� ���������� �������
    WaitForMultipleObjects(numThreads, threads, TRUE, INFINITE);

    // �������� ������������ �������
    for (int i = 0; i < numThreads; i++) {
        CloseHandle(threads[i]);
    }

    std::cout << "��� ������ ���������." << std::endl;

    return 0;
}