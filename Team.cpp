#include "Team.h"

// Додавання нової команди в кінець двозв'язного списку
void addTeam(Team*& head, Team*& tail, std::string name, int points) {
    Team* newNode = new Team{name, points, nullptr, nullptr};
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Виведення списку на екран
void printList(Team* head) {
    if (!head) {
        std::cout << "Список порожній." << std::endl;
        return;
    }
    Team* current = head;
    while (current) {
        std::cout << " -> [" << current->name << ": " << current->points << "]";
        current = current->next;
    }
    std::cout << std::endl;
}

// Підрахунок кількості елементів у списку
int countNodes(Team* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Видалення конкретного вузла (перебудова зв'язків)
Team* removeNode(Team*& head, Team*& tail, Team* target) {
    if (!target) return nullptr;

    Team* nextNode = target->next;

    if (target->prev) 
        target->prev->next = target->next;
    else 
        head = target->next;

    if (target->next) 
        target->next->prev = target->prev;
    else 
        tail = target->prev;

    delete target;
    return nextNode;
}

// Проведення змагань до визначення переможця
void runCompetition(Team*& head, Team*& tail) {
    int stage = 0;
    
    // Змагання тривають, поки не залишиться одна команда
    while (countNodes(head) > 1) {
        stage++;
        int total = countNodes(head);
        int toRemove = total / 2; // Вилучаємо половину
        
        std::cout << "\n=== Етап №" << stage << " ===" << std::endl;
        std::cout << "Кількість команд: " << total << std::endl;

        Team* current = head;
        int removedInThisStage = 0;

        // Проходимо по списку і вилучаємо кожну другу команду
        while (current && removedInThisStage < toRemove) {
            if (current->next) {
                Team* target = current->next;
                std::cout << "Вилучається команда: " << target->name << std::endl;
                
                // Видаляємо вузол і перескакуємо на наступний за ним
                current = removeNode(head, tail, target);
                removedInThisStage++;
            }
            if (current) current = current->next;
        }

        std::cout << "Команди, що проходять далі: ";
        printList(head);
    }

    std::cout << "\n-----------------------------------" << std::endl;
    if (head) {
        std::cout << "ПЕРЕМОЖЕЦЬ: " << head->name << " (" << head->points << " балів)" << std::endl;
    }
    std::cout << "Всього етапів проведено: " << stage << std::endl;
}

// Очищення пам'яті
void clearList(Team*& head, Team*& tail) {
    while (head) {
        head = removeNode(head, tail, head);
    }
}