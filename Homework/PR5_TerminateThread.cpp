#include <iostream>
#include <windows.h>
#include <process.h>

unsigned __stdcall ThreadFunction(void* pArguments) {
    while (true) {
        std::cout << "Поток выполняется..." << std::endl;
        Sleep(2000); // Задержка 2 секунды
    }
    return 0;
}

int main() {
    uintptr_t threadHandle = _beginthreadex(NULL, 0, &ThreadFunction, NULL, 0, NULL);

    // Дайте потоку поработать некоторое время
    Sleep(5000);

    // Завершение потока
    TerminateThread((HANDLE)threadHandle, 0);
    CloseHandle((HANDLE)threadHandle);

    std::cout << "Поток завершен." << std::endl;

    return 0;
}