#include <iostream>
#include <windows.h>

struct Record {
    int id;
    char name[20];
};

int main() {
    // Открываем файл для чтения и записи
    HANDLE hFile = CreateFile(
        "data.bin",                 // имя файла
        GENERIC_READ | GENERIC_WRITE, // доступ к файлу
        0,                          // режим защиты
        NULL,                       // отсутствие шаблона безопасности
        OPEN_EXISTING,             // открыть существующий файл
        FILE_ATTRIBUTE_NORMAL,     // нормальный файл
        NULL                        // отсутствие шаблона файла
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file: " << GetLastError() << std::endl;
        return 1;
    }

    // Устанавливаем указатель на запись
    DWORD recordNumber = 1; // Индекс записи
    DWORD bytesToMove = recordNumber * sizeof(Record);
    DWORD newPos = SetFilePointer(hFile, bytesToMove, NULL, FILE_BEGIN);

    if (newPos == INVALID_SET_FILE_POINTER) {
        std::cerr << "Error setting file pointer: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    // Чтение записи
    Record record;
    DWORD bytesRead;
    if (!ReadFile(hFile, &record, sizeof(Record), &bytesRead, NULL)) {
        std::cerr << "Error reading file: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    // Вывод данных прочитанной записи
    std::cout << "Record ID: " << record.id << ", Name: " << record.name << std::endl;

    // Закрываем файл
    CloseHandle(hFile);
    return 0;
}