#include "Team.h"

int main() {
    Team* head = nullptr;
    Team* tail = nullptr;

    int choice;
    std::cout << "Виберіть спосіб введення (1 - Клавіатура, 2 - Файл): ";
    std::cin >> choice;

    if (choice == 1) {
        int n;
        std::cout << "Введіть кількість команд: ";
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::string name;
            int pts;
            std::cout << i + 1 << ". Назва та бали: ";
            std::cin >> name >> pts;
            addTeam(head, tail, name, pts);
        }
    } else {
        std::ifstream file("teams.txt");
        if (!file) {
            std::cout << "Помилка відкриття файлу!" << std::endl;
            return 1;
        }
        std::string name;
        int pts;
        while (file >> name >> pts) {
            addTeam(head, tail, name, pts);
        }
        file.close();
    }

    std::cout << "\nСформований список команд:" << std::endl;
    printList(head);

    // Запуск основної логіки завдання
    runCompetition(head, tail);

    // Обов'язкове очищення пам'яті перед завершенням
    clearList(head, tail);

    return 0;
}