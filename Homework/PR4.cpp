#include <iostream>
#include <windows.h>

// Функция, выполняемая в потоке
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    int threadId = *(int*)lpParam;
    for (int i = 0; i < 5; i++) {
        std::cout << "Поток " << threadId << " выполняет задачу " << i + 1 << std::endl;
        Sleep(1000); // Задержка 1 секунда
    }
    return 0;
}

int main() {
    const int numThreads = 3; // Количество потоков
    HANDLE threads[numThreads]; // Массив дескрипторов потоков
    int threadIds[numThreads];   // Массив идентификаторов потоков

    // Создание потоков
    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i + 1; // Идентификатор потока
        threads[i] = CreateThread(
            NULL,           // Атрибуты безопасности по умолчанию
            0,              // Начальный размер стека
            ThreadFunction, // Функция потока
            &threadIds[i],  // Передаем идентификатор потока
            0,              // Параметры создания
            NULL            // Возвращаемый идентификатор потока
        );

        if (threads[i] == NULL) {
            std::cerr << "Ошибка создания потока: " << GetLastError() << std::endl;
        }
    }

    // Ожидание завершения потоков
    WaitForMultipleObjects(numThreads, threads, TRUE, INFINITE);

    // Закрытие дескрипторов потоков
    for (int i = 0; i < numThreads; i++) {
        CloseHandle(threads[i]);
    }

    std::cout << "Все потоки завершены." << std::endl;

    return 0;
}