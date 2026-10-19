#include <iostream>
#include <iomanip>

// Глобальні змінні (сегмент статичних даних програми)
int        nVariable     = 100; // Для демонстрації оператора ::
static int nStaticGlobal = 50;  // Статична зовнішня змінна

int main() {

    // Частина 1: Блочна структура, стек, мембранний ефект, присвоювання

    int  nVariable = 10;       // Локальна змінна головного блоку main (стек)
    int  nCounter  = 1;        // Змінна main, яку змінюють вкладені блоки
    int *pnSaved   = nullptr;  // Покажчик для доступу до статичної змінної після виходу з блоку

    std::cout << "\n               PART-1 (Scope & Membrane Effect)\n\n";
    std::cout << std::left;

    // Демонстрація оператора ::
    std::cout << std::setw(28) << "Global Variable (::):"
                                 << "Value: "               << std::setw(6) << ::nVariable
                                 << " Address: "                              << &::nVariable
              << std::endl;

    std::cout << std::setw(28) << "Global Static:"
                                 << "Value: "        << std::setw(6) << nStaticGlobal
                                 << " Address: "                       << &nStaticGlobal
              << std::endl;


    std::cout << std::setw(28) << "Outer Variable:"
                                 << "Value: "         << std::setw(6) << nVariable
                                 << " Address: "                        << &nVariable
              << std::endl;
    std::cout << "\n";

    // Блок 1 (рівень вкладеності 1): перекриває nVariable з main (мембранний ефект)
    {
        int        nVariable    = 20; // Перекриття зовнішньої nVariable
        static int nStaticBlock = 3;  // Статична змінна у вкладеному блоці

        // Оператори присвоювання з використанням описаних змінних
        nStaticBlock = nStaticBlock + 4;        // 3 + 4 = 7
        nVariable    = nVariable + ::nVariable; // 20 + 100 = 120
        nCounter     = nCounter + 1;            // Змінна main доступна у вкладеному блоці: 2

        pnSaved = &nStaticBlock; // Запам'ятовування адреси статичної змінної

        std::cout << std::setw(28) << "Block 1 (nVariable):"
                                     << "Value: "              << std::setw(6) << nVariable
                                     << " Address: "                             << &nVariable
                  << std::endl;

        std::cout << std::setw(28) << "Block 1 Static:"
                                     << "Value: "         << std::setw(6) << nStaticBlock
                                     << " Address: "                        << &nStaticBlock
                  << std::endl;
        std::cout << "\n";

        // Блок 2 (рівень вкладеності 2): блок у блоці
        {
            int nVariable = 30; // Перекриття nVariable з блоку 1
            int nInner    = 5;

            nInner   = nInner + nStaticBlock; // Статична змінна блоку 1 доступна: 5 + 7 = 12
            nCounter = nCounter + 1;          // 3

            std::cout << std::setw(28) << "Block 2 (nVariable):"
                                         << "Value: "              << std::setw(6) << nVariable
                                         << " Address: "                             << &nVariable
                      << std::endl;

            std::cout << std::setw(28) << "Block 2 (nInner):"
                                         << "Value: "           << std::setw(6) << nInner
                                         << " Address: "                          << &nInner
                      << std::endl;
            std::cout << "\n";

            // Блок 3 (рівень вкладеності 3)
            {
                int nVariable = 40; // Перекриття nVariable з блоку 2

                nInner   = nInner + nVariable; // nInner з блоку 2: 12 + 40 = 52
                nCounter = nCounter + 1;       // 4

                std::cout << std::setw(28) << "Block 3 (nVariable):"
                                             << "Value: "              << std::setw(6) << nVariable
                                             << " Address: "                             << &nVariable
                          << std::endl;

                std::cout << std::setw(28) << "Block 3 (nInner: Block 2):"
                          << "Value: "     << std::setw(6) << nInner
                          << " Address: "  << &nInner
                          << std::endl;
                std::cout << "\n";
            } // Знищення nVariable (40)
        }     // Знищення nVariable (30) та nInner
    }         // Знищення nVariable (20); nStaticBlock залишається в пам'яті

    // Паралельний блок на рівні main
    {
        int nVariable = 50; // Ізольована область видимості паралельного блоку

        std::cout << std::setw(28) << "Parallel Block (nVariable):"
                                     << "Value: "                     << std::setw(6) << nVariable
                                     << " Address: "                                    << &nVariable
                  << std::endl;
        std::cout << "\n";
    }

    // Статична змінна блоку 1 існує, але за іменем недоступна - доступ через покажчик
    std::cout << std::setw(28) << "Static after block exit:"
                                 << "Value: "                  << std::setw(6) << *pnSaved
                                 << " Address: "                                 << pnSaved
              << std::endl;

    // Перевірка стану зовнішніх змінних після виходу з вкладених блоків
    std::cout << std::setw(28) << "Final Variable:"
                                 << "Value: "         << std::setw(6) << nVariable
                                 << " Address: "                        << &nVariable
              << std::endl;

    std::cout << std::setw(28) << "Final Counter:"
                                 << "Value: "        << std::setw(6) << nCounter
                                 << " Address: "                       << &nCounter
              << std::endl;
    std::cout << "\n";

    // Частина 2: Порівняння статичної та автоматичної пам'яті в циклі

    std::cout << "                   PART-2 (Static vs Auto in Loop)\n\n";

    for (int i = 1; i <= 5; i++)
    {
        static int nStatic = 0; // Ініціалізується один раз (сегмент статичних даних)
        int        nAuto   = 0; // Створюється та ініціалізується на стеку на кожній ітерації

        nStatic++;
        nAuto++;

        std::cout << "                      --- Iteration " << i << " ---\n\n";
        std::cout << std::setw(28) << "Static Variable:"
                                     << "Value: "          << std::setw(6) << nStatic
                                     << " Address: "                         << &nStatic
                  << std::endl;

        std::cout << std::setw(28) << "Auto Variable:"
                                     << "Value: "        << std::setw(6) << nAuto
                                     << " Address: "                       << &nAuto
                  << std::endl;
        std::cout << "\n";
    }
    std::cout << "\n";

    // Частина 3: Динамічний розподіл пам'яті в купі (Heap) та сміття

    std::cout << "                PART-3 (Heap Allocation & Memory Leak)\n\n";

    // 1. Дві типізовані вказівні змінні.
    // Спочатку захоплюються обидві, щоб адреси в купі були різними
    int *pnHeap1 = new int;
    int *pnHeap2 = new int;

    if (pnHeap1 != nullptr) // Перевірка наявності пам'яті
    {
        *pnHeap1 = 500;

        std::cout << std::setw(28) << "Heap Pointer 1 (stack):"
                                     << "Address: "                     << &pnHeap1
                  << std::endl;
        std::cout << std::setw(28) << "Allocated Memory 1:"
                                     << "Value: "     << std::setw(6) << *pnHeap1
                                     << " Address: "                    << pnHeap1
                  << std::endl;
    }

    if (pnHeap2 != nullptr)
    {
        *pnHeap2 = 600;

        std::cout << std::setw(28) << "Heap Pointer 2 (stack):"
                                     << "Address: "                     << &pnHeap2
                  << std::endl;
        std::cout << std::setw(28) << "Allocated Memory 2:"
                                     << "Value: "     << std::setw(6) << *pnHeap2
                                     << " Address: "                    << pnHeap2
                  << std::endl;
    }

    delete pnHeap1;    // Звільнення пам'яті в купі
    pnHeap1 = nullptr; // Занулення покажчика для безпеки
    delete pnHeap2;
    pnHeap2 = nullptr;

    std::cout << std::setw(28) << "After delete (1, 2):"
                                 << "Address 1: " << pnHeap1
                                 << " Address 2: " << pnHeap2
              << std::endl;
    std::cout << "\n";

    // 2. Перший приклад сміття: покажчик знищується при виході з блоку
    {
        int *pnLeak1 = new int;
        if (pnLeak1 != nullptr)
        {
            *pnLeak1 = 777;

            std::cout << std::setw(28) << "Leak 1 (block exit):"
                                         << "Value: "     << std::setw(6) << *pnLeak1
                                         << " Address: "                    << pnLeak1
                      << std::endl;
            // delete pnLeak1 навмисно НЕ викликається
        }
    } // Покажчик pnLeak1 знищено зі стека, пам'ять у купі залишилась заблокованою
    std::cout << "Exited block without delete -> memory leak (garbage created)\n\n";

    // 3. Другий приклад сміття: перезапис покажчика без delete
    int *pnLeak2 = new int;
    if (pnLeak2 != nullptr)
    {
        *pnLeak2 = 888;

        std::cout << std::setw(28) << "Leak 2 (before overwrite):"
                                     << "Value: "     << std::setw(6) << *pnLeak2
                                     << " Address: "                    << pnLeak2
                  << std::endl;

        pnLeak2 = new int; // Адресу першого блоку втрачено: утворилось сміття

        if (pnLeak2 != nullptr)
        {
            *pnLeak2 = 999;

            std::cout << std::setw(28) << "Leak 2 (after overwrite):"
                                         << "Value: "     << std::setw(6) << *pnLeak2
                                         << " Address: "                    << pnLeak2
                      << std::endl;

            delete pnLeak2; // Звільняється лише другий блок
            pnLeak2 = nullptr;
        }
    }
    std::cout << "Pointer overwritten without delete -> second garbage block\n\n";

    return 0;
}