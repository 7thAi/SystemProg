#include <iostream>
#include <windows.h>

struct Record {
    int id;
    char name[20];
};

int main() {
    // ��������� ���� ��� ������ � ������
    HANDLE hFile = CreateFile(
        "data.bin",                 // ��� �����
        GENERIC_READ | GENERIC_WRITE, // ������ � �����
        0,                          // ����� ������
        NULL,                       // ���������� ������� ������������
        OPEN_EXISTING,             // ������� ������������ ����
        FILE_ATTRIBUTE_NORMAL,     // ���������� ����
        NULL                        // ���������� ������� �����
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file: " << GetLastError() << std::endl;
        return 1;
    }

    // ������������� ��������� �� ������
    DWORD recordNumber = 1; // ������ ������
    DWORD bytesToMove = recordNumber * sizeof(Record);
    DWORD newPos = SetFilePointer(hFile, bytesToMove, NULL, FILE_BEGIN);

    if (newPos == INVALID_SET_FILE_POINTER) {
        std::cerr << "Error setting file pointer: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    // ������ ������
    Record record;
    DWORD bytesRead;
    if (!ReadFile(hFile, &record, sizeof(Record), &bytesRead, NULL)) {
        std::cerr << "Error reading file: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    // ����� ������ ����������� ������
    std::cout << "Record ID: " << record.id << ", Name: " << record.name << std::endl;

    // ��������� ����
    CloseHandle(hFile);
    return 0;
}