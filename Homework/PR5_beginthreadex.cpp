#include <iostream>
#include <windows.h>
#include <process.h> // Для _beginthreadex

// Функция, выполняемая в потоке
unsigned __stdcall ThreadFunction(void* pArguments) {
    int threadNum = *(int*)pArguments;
    for (int i = 0; i < 5; i++) {
        std::cout << "Поток " << threadNum << " выполняет задачу " << i + 1 << std::endl;
        Sleep(1000); // Задержка 1 секунда
    }
    return 0;
}

int main() {
    const int numThreads = 3;
    uintptr_t threadHandles[numThreads]; // Массив дескрипторов потоков
    int threadIds[numThreads];

    // Создание потоков
    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i + 1; // Идентификатор потока
        threadHandles[i] = _beginthreadex(NULL, 0, &ThreadFunction, &threadIds[i], 0, NULL);

        if (threadHandles[i] == 0) {
            std::cerr << "Ошибка создания потока: " << GetLastError() << std::endl;
        }
    }

    // Ожидание завершения потоков
    WaitForMultipleObjects(numThreads, (HANDLE*)threadHandles, TRUE, INFINITE);

    // Закрытие дескрипторов потоков
    for (int i = 0; i < numThreads; i++) {
        CloseHandle((HANDLE)threadHandles[i]);
    }

    std::cout << "Все потоки завершены." << std::endl;

    return 0;
}