#include <gtest/gtest.h>
#include "Team.h"

// Тест на створення списку та додавання елементів
TEST(TeamListTest, AddTeamTest) {
    Team* head = nullptr;
    Team* tail = nullptr;

    addTeam(head, tail, "Dynamo", 10);
    addTeam(head, tail, "Shakhtar", 12);

    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->name, "Dynamo");
    EXPECT_EQ(tail->name, "Shakhtar");
    EXPECT_EQ(countNodes(head), 2);

    clearList(head, tail);
}

// Тест на видалення конкретного вузла (перевірка зв'язків)
TEST(TeamListTest, RemoveNodeTest) {
    Team* head = nullptr;
    Team* tail = nullptr;

    addTeam(head, tail, "A", 1);
    addTeam(head, tail, "B", 2);
    addTeam(head, tail, "C", 3);

    // Видаляємо середній елемент "B"
    Team* second = head->next;
    removeNode(head, tail, second);

    EXPECT_EQ(countNodes(head), 2);
    EXPECT_EQ(head->next->name, "C");
    EXPECT_EQ(head->next->prev->name, "A"); // Перевірка зворотного зв'язку

    clearList(head, tail);
}

// Тест на повне очищення списку
TEST(TeamListTest, ClearListTest) {
    Team* head = nullptr;
    Team* tail = nullptr;

    addTeam(head, tail, "Team1", 5);
    addTeam(head, tail, "Team2", 5);

    clearList(head, tail);

    EXPECT_EQ(head, nullptr);
    EXPECT_EQ(tail, nullptr);
}

// Тест логіки змагань (Етап 1: з 4 команд має залишитись 2)
TEST(TeamLogicTest, CompetitionStepTest) {
    Team* head = nullptr;
    Team* tail = nullptr;

    // 1. Створюємо 4 команди: T1, T2, T3, T4
    addTeam(head, tail, "T1", 10);
    addTeam(head, tail, "T2", 20);
    addTeam(head, tail, "T3", 30);
    addTeam(head, tail, "T4", 40);

    // 2. Логіка проведення етапу
    int total = countNodes(head);
    int toRemove = total / 2; // Має бути 2
    int removedCount = 0;

    Team* current = head;
    while (current != nullptr && removedCount < toRemove) {
        // Ми хочемо видалити наступний елемент після поточного (кожен другий)
        if (current->next != nullptr) {
            Team* target = current->next;
            // Видаляємо target, функція перешиває зв'язки
            removeNode(head, tail, target);
            removedCount++;

            // Після видалення переходимо до наступного "живого" елемента,
            // щоб на наступній ітерації знову видалити його сусіда
            current = current->next;
        } else {
            // Якщо наступного немає, виходимо
            break;
        }
    }

    // 3. Перевірки результату
    int finalCount = countNodes(head);
    EXPECT_EQ(finalCount, 2); // Очікуємо 2 (T1 та T3)

    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->name, "T1");

    ASSERT_NE(head->next, nullptr);
    EXPECT_EQ(head->next->name, "T3");

    clearList(head, tail);
}

// Тест на фінального переможця
TEST(TeamLogicTest, WinnerTest) {
    Team* head = nullptr;
    Team* tail = nullptr;

    addTeam(head, tail, "Winner", 100);
    addTeam(head, tail, "Loser", 0);

    // Видаляємо одну команду (половину від 2)
    removeNode(head, tail, head->next);

    EXPECT_EQ(countNodes(head), 1);
    EXPECT_EQ(head->name, "Winner");

    clearList(head, tail);
}