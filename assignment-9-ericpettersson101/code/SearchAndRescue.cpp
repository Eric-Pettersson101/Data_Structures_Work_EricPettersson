#include "SearchAndRescue.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


SearchAndRescue::SearchAndRescue(string fileName)
{
    terrain = new int*[4];
    string line;
    ifstream infile(fileName);
    if (infile.is_open())
    {
        for(int i = 0; getline(infile, line); i++)
        {   
            terrain[i] = new int[4];
            stringstream ss(line);
            string s;
            for (int j = 0; getline(ss, s, ' '); j++)
            {
                terrain[i][j] = stoi(s);
            }
        }
    }
    path = vector<State*>();
}


SearchAndRescue::~SearchAndRescue()
{
    State* to_del = path.back();
    delete to_del;
    path.pop_back();

    for (int i = 0; i < 4; i++)
    {
        delete terrain[i];
    }
    delete terrain;
}


void SearchAndRescue::possibleActions(State* current)
{
    int x = current->x, y = current->y;
    if (y < 3) current->possible_actions.push_back("up");
    if (y > 0) current->possible_actions.push_back("down");
    if (x > 0) current->possible_actions.push_back("left");
    if (x < 3) current->possible_actions.push_back("right"); 
}



State* SearchAndRescue::result(State* current, string action)
{
    int newX = current->x;    int newY = current->y;
    // Update coordinates based on action
    if(action == "up") newY++;
    if(action == "right") newX++;
    if(action == "down") newY--;
    if(action == "left") newX--;
   return new State{newX, newY, current->saved_people, action, vector<string>()};
}



vector<State*> SearchAndRescue::expand(State* current)
{
    possibleActions(current); 
    vector<State*> expansion;
    for (auto& action : current->possible_actions) {
        expansion.push_back(result(current, action));
    }
    return expansion;
}

// Implementing iterativeDeepeningWrapper
bool SearchAndRescue::iterativeDeepeningWrapper(State* start) {
    int depth_limit = STARTING_DEPTH;
    path.push_back(start); //add start
    while (!iterativeDeepeningSearch(start, depth_limit)) {
        depth_limit++;
    }
    return true;
}

// Implementing iterativeDeepeningSearch
bool SearchAndRescue::iterativeDeepeningSearch(State* current, int depth_limit) {
    if (isGoal(current)) return true;
    if (depth_limit == 0) return false;
    

    bool saved_People = terrain[current->x][current->y] == 2;
    if (saved_People) { 
                current->saved_people++;
                terrain[current->x][current->y] = 1;
    }
    for (State* state : expand(current)) {

        path.push_back(state);
        bool found = iterativeDeepeningSearch(state, depth_limit - 1);

        if (found) return true;

        path.pop_back();
        delete state;
        
        }
    if (saved_People) current->saved_people--, terrain[current->x][current->y] = 2;
    return false;
}
void SearchAndRescue::printPath()
{       
        for (int i = 0; i < path.size() ; i++) {
            cout << "x: " << path[i]->x << "\ty: " << path[i]->y <<
                "\tprev_action: " << path[i]->prev_action << endl;
        }
}




bool SearchAndRescue::isGoal(State* current)
{
    return current->saved_people == PEOPLE_TO_SAVE && terrain[current->x][current->y] == 3;
}

void SearchAndRescue::printTerrain() {
    for (int j = 3; j >= 0; j--) {
        for (int i = 0; i < 4; i++) { 
            cout << terrain[i][j] << " "; 
        }
        cout << endl; 
    }
}