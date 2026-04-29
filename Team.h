#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

struct Team {
    std::string name;
    int points;
    Team* next;
    Team* prev;
};

void addTeam(Team*& head, Team*& tail, std::string name, int points);
void printList(Team* head);
void clearList(Team*& head, Team*& tail);

int countNodes(Team* head);
Team* removeNode(Team*& head, Team*& tail, Team* target);
void runCompetition(Team*& head, Team*& tail);

#endif