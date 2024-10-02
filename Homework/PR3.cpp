#include <iostream>
#include <windows.h>

int deleteFile() {
    const char* filename = "testfile.txt";

    // Удаляем файл
    if (DeleteFileA(filename)) {
        std::cout << "Файл удален успешно." << std::endl;
    }
    else {
        std::cerr << "Ошибка удаления файла: " << GetLastError() << std::endl;
    }

    return 0;
}

int renameFile() {
    const char* oldFilename = "oldfile.txt";
    const char* newFilename = "newfile.txt";

    // Переименование/перемещение файла
    if (MoveFileA(oldFilename, newFilename)) {
        std::cout << "Файл переименован успешно." << std::endl;
    }
    else {
        std::cerr << "Ошибка переименования файла: " << GetLastError() << std::endl;
    }

    return 0;
}

int createCatalog() {
    const char* dirName = "MyDirectory";

    // Создаем каталог
    if (CreateDirectoryA(dirName, NULL)) {
        std::cout << "Каталог создан успешно." << std::endl;
    }
    else if (GetLastError() == ERROR_ALREADY_EXISTS) {
        std::cout << "Каталог уже существует." << std::endl;
    }
    else {
        std::cerr << "Ошибка создания каталога: " << GetLastError() << std::endl;
    }

    // Удаляем каталог
    if (RemoveDirectoryA(dirName)) {
        std::cout << "Каталог удален успешно." << std::endl;
    }
    else {
        std::cerr << "Ошибка удаления каталога: " << GetLastError() << std::endl;
    }

    return 0;
}

int printCatalog() {
    char buffer[MAX_PATH];

    // Получаем текущий каталог
    if (GetCurrentDirectoryA(MAX_PATH, buffer)) {
        std::cout << "Текущий каталог: " << buffer << std::endl;
    }
    else {
        std::cerr << "Ошибка получения текущего каталога: " << GetLastError() << std::endl;
    }

    return 0;
}