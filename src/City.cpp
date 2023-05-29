#include <random>
#include <windows.h>

#include "City.h"

City::City() {
    this->m_zombies = 0;
    this->m_humans = 0;
    this->m_generation = 0;
}

City::~City() {
    for (auto &i: m_grid) {
        for (auto &j: i) {
            delete j;
        }
    }
}

int City::get_generation() const { return this->m_generation; }


int City::get_zombies() const {
    return this->m_zombies;
}


int City::get_humans() const {
    return this->m_humans;
}

Organism *City::get_organisms(int x, int y) {
    Organism *temp = this->m_grid[x][y];
    return temp;
}

//set position on the m_city
void City::set_organism(Organism *organism, int x, int y) {
    this->m_grid[x][y] = organism;
}

//check if there has been an extinction event
bool City::has_diversity() const {

    if (this->m_zombies > 0 && this->m_humans > 0) {
        return true;
    } else {
        return false;
    }
}

void City::populate() {

    populateHumans();
    populateZombies();
}

//function to randomly populate the m_grid with humans
void City::populateHumans() {

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist20(0, 19);

    for (int i = 0; i < _GAMESPECS_H::HUMAN_STARTCOUNT; i++) {
        int xPos = dist20(rng);
        int yPos = dist20(rng);
        while (true) {
            if (!is_empty(xPos, yPos)) {
                xPos = dist20(rng);
                yPos = dist20(rng);
            } else {
                create_human(xPos, yPos);
                break;
            }
        }
    }
}

//function to randomly populate the m_grid with zombies
void City::populateZombies() {

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist9(0, 9);
    std::uniform_int_distribution<std::mt19937::result_type> dist19(10, 19);

    //distribute them into each quadrant
    for (int i = 0; i < _GAMESPECS_H::ZOMBIE_STARTCOUNT; i++) {
        int j = i;
        int xPos;
        int yPos;
        while (j >= 4) { j -= 4; }
        while (true) {
            switch (j) {
                case 0:
                    xPos = dist9(rng);
                    yPos = dist9(rng);
                    break;
                case 1:
                    xPos = dist9(rng);
                    yPos = dist19(rng);
                    break;
                case 2:
                    xPos = dist19(rng);
                    yPos = dist9(rng);
                    break;
                default:
                    xPos = dist19(rng);
                    yPos = dist19(rng);
                    break;
            }
            if (is_empty(xPos, yPos)) {
                create_zombie(xPos, yPos);
                break;
            }
        }
    }
}

//function to reset the move flags on the humans and zombies
void City::reset() {

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (!this->is_empty(i, j)) {
                get_organisms(i, j)->end_turn();
            }
        }
    }
}

//colorize the console
void City::color(int c) {

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

void City::move_organism(Organism *organism, int x, int y) {

    int tempX = organism->get_x();
    int tempY = organism->get_y();
    this->m_grid[x][y] = organism;
    this->m_grid[tempX][tempY] = nullptr;
    organism->set_x(x);
    organism->set_y(y);
}

//check if a cell is empty
bool City::is_empty(int xPos, int yPos) {

    if (this->m_grid[xPos][yPos] == nullptr) {
        return true;
    } else {
        return false;
    }
}

void City::move() {
    this->m_generation++;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (!this->is_empty(i, j)) {
                get_organisms(i, j)->turn();
            }
        }
    }
}

void City::delete_human(Organism *organism, int x, int y) {
    delete get_organisms(x, y);
    this->m_grid[x][y] = nullptr;
    this->move_organism(organism, x, y);
    this->m_humans--;
}

void City::create_human(int xPos, int yPos) {
    auto *human = new Human(this);
    human->set_position(xPos, yPos);
    this->set_organism(human, xPos, yPos);
    this->m_humans++;
}

void City::create_zombie(int xPos, int yPos) {
    auto *zombie = new Zombie(this);
    zombie->set_position(xPos, yPos);
    this->set_organism(zombie, xPos, yPos);
    this->m_zombies++;
}

void City::cure_human(int x, int y) {
    delete get_organisms(x, y);
    this->m_grid[x][y] = nullptr;
    create_human(x, y);
    this->m_zombies--;
}

void City::infect_human(int x, int y) {
    delete get_organisms(x, y);
    this->m_grid[x][y] = nullptr;
    create_zombie(x, y);
    this->m_humans--;
}

std::ostream &operator<<(std::ostream &output, City &city) {

    //place the horizontal wall on top of grind
    output << "----------------------" << std::endl;

    for (int i = 0; i < GRID_HEIGHT; i++) {
        //place the vertical wall on left edge of m_grid
        output << "|";
        for (int j = 0; j < GRID_WIDTH; j++) {

            //if no organism at the location, print empty space
            if (city.is_empty(i, j)) {
                output << (char) _GAMESPECS_H::SPACE_CH;
            }
            // if it's a human print the human character
            else if (city.get_organisms(i, j)->get_species() == _GAMESPECS_H::HUMAN_CH) {

                city.color(_GAMESPECS_H::HUMAN_COLOR);
                output << (char) _GAMESPECS_H::HUMAN_CH;
                city.color(_GAMESPECS_H::DEFAULT_COLOR);
            }
            //else print a zombie character
            else {
                city.color(_GAMESPECS_H::ZOMBIE_COLOR);
                output << (char) _GAMESPECS_H::ZOMBIE_CH;
                city.color(_GAMESPECS_H::DEFAULT_COLOR);
            }
        }

        //place the vertical wall on right edge of m_grid
        output << "|" << std::endl;
    }

    //place the horizontal wall on bottom of grind
    output << "----------------------" << std::endl;
    return output;
}