#include "Organism.h"

//constructor
Organism::Organism(City *city) {
    this->m_city = city;
}

//destructor
Organism::~Organism() = default;

//getters
int Organism::get_species() const {return this->m_species;}

int Organism::get_x() const { return this->m_x;}

int Organism::get_y() const { return this->m_y;}

//setters
void Organism::set_x(int x) { this->m_x = x;}

void Organism::set_y(int y){ this->m_y = y;};

void Organism::set_position(int xPos, int yPos) {
    this->m_x = xPos;
    this->m_y = yPos;
}

//set the move flag back to false
void Organism::end_turn() { this->m_moved = false;}

