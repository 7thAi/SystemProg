#include <iostream>
#include <windows.h>

int deleteFile() {
    const char* filename = "testfile.txt";

    // ������� ����
    if (DeleteFileA(filename)) {
        std::cout << "���� ������ �������." << std::endl;
    }
    else {
        std::cerr << "������ �������� �����: " << GetLastError() << std::endl;
    }

    return 0;
}

int renameFile() {
    const char* oldFilename = "oldfile.txt";
    const char* newFilename = "newfile.txt";

    // ��������������/����������� �����
    if (MoveFileA(oldFilename, newFilename)) {
        std::cout << "���� ������������ �������." << std::endl;
    }
    else {
        std::cerr << "������ �������������� �����: " << GetLastError() << std::endl;
    }

    return 0;
}

int createCatalog() {
    const char* dirName = "MyDirectory";

    // ������� �������
    if (CreateDirectoryA(dirName, NULL)) {
        std::cout << "������� ������ �������." << std::endl;
    }
    else if (GetLastError() == ERROR_ALREADY_EXISTS) {
        std::cout << "������� ��� ����������." << std::endl;
    }
    else {
        std::cerr << "������ �������� ��������: " << GetLastError() << std::endl;
    }

    // ������� �������
    if (RemoveDirectoryA(dirName)) {
        std::cout << "������� ������ �������." << std::endl;
    }
    else {
        std::cerr << "������ �������� ��������: " << GetLastError() << std::endl;
    }

    return 0;
}

int printCatalog() {
    char buffer[MAX_PATH];

    // �������� ������� �������
    if (GetCurrentDirectoryA(MAX_PATH, buffer)) {
        std::cout << "������� �������: " << buffer << std::endl;
    }
    else {
        std::cerr << "������ ��������� �������� ��������: " << GetLastError() << std::endl;
    }

    return 0;
}