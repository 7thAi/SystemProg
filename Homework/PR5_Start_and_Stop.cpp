#include <iostream>
#include <windows.h>
#include <process.h>

unsigned __stdcall ThreadFunction(void* pArguments) {
    while (true) {
        std::cout << "Поток выполняется..." << std::endl;
        Sleep(1000); // Задержка 1 секунда
    }
    return 0;
}

int main() {
    uintptr_t threadHandle = _beginthreadex(NULL, 0, &ThreadFunction, NULL, 0, NULL);

    // Дайте потоку поработать некоторое время
    Sleep(5000);

    // Приостановка потока
    SuspendThread((HANDLE)threadHandle);
    std::cout << "Поток приостановлен." << std::endl;

    Sleep(3000); // Ждем 3 секунды

    // Возобновление потока
    ResumeThread((HANDLE)threadHandle);
    std::cout << "Поток возобновлен." << std::endl;

    // Ожидание завершения потока
    WaitForSingleObject((HANDLE)threadHandle, INFINITE);
    CloseHandle((HANDLE)threadHandle);

    return 0;
}