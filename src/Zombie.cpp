#include <random>
#include <algorithm>
#include "Zombie.h"
#include "GameSpecs.h"
#include "City.h"

//constructor
Zombie::Zombie(City *city) : Organism(city) {
    this->m_city = city;
    this->m_species = _GAMESPECS_H::ZOMBIE_CH;
}

//destructor
Zombie::~Zombie() {
    this->m_city = nullptr;
}

//function to check if the zombie has m_moved yet, if not,
// call move, check_recruit, and checkStarving
void Zombie::turn() {

    if (!m_moved) {
        move();
        check_recruit();
        check_if_starved();
    }
}

//function to attempt to move the zombie
void Zombie::move() {

    check_directions();

    if (!this->m_nearby_humans.empty()) {
        shuffle_recruit_options();
        eat();
        this->m_steps_until_starved = 0;
    } else if (!this->m_squares_to_move.empty()) {
        shuffle_directions();
        move_directions();
        this->m_steps_until_starved++;
    } else {
        this->m_steps_until_starved++;
    }
    clear_targets();
    this->m_moved = true;

}

//function to check if the zombie can breed,
// and increment the humans time m_steps
void Zombie::check_recruit() {

    if (this->m_steps > _GAMESPECS_H::ZOMBIE_BREED) {
        recruit();
        clear_targets();
    }
    this->m_steps++;
}

//function to check which available m_directions are empty,
// and which ones have humans in them
void Zombie::check_directions() {

    //check north
    if (this->m_y >= 1) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty(this->m_x, (this->m_y - 1))) {
            this->m_squares_to_move.push_back(NORTH);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms(this->m_x, (this->m_y - 1))->
                get_species() == _GAMESPECS_H::HUMAN_CH) {

            this->m_nearby_humans.push_back(NORTH);
        }
    }

    //check south
    if (this->m_y <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty(this->m_x, (this->m_y + 1))) {
            this->m_squares_to_move.push_back(SOUTH);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms(this->m_x, (this->m_y + 1))->
                get_species() == _GAMESPECS_H::HUMAN_CH) {

            this->m_nearby_humans.push_back(SOUTH);
        }
    }

    //check west
    if (this->m_x >= 1) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty((this->m_x - 1), this->m_y)) {
            this->m_squares_to_move.push_back(WEST);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms((this->m_x - 1), this->m_y)->
                get_species() == _GAMESPECS_H::HUMAN_CH) {

            this->m_nearby_humans.push_back(WEST);
        }
    }

    //check east
    if (this->m_x <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty((this->m_x + 1), this->m_y)) {
            this->m_squares_to_move.push_back(EAST);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms((this->m_x + 1), this->m_y)->
                get_species() == _GAMESPECS_H::HUMAN_CH) {

            this->m_nearby_humans.push_back(EAST);
        }
    }

    //check north-east
    if (this->m_x <= (_GAMESPECS_H::GRIDSIZE - 2) && this->m_y >= 1) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty((this->m_x + 1), (this->m_y - 1))) {
            this->m_squares_to_move.push_back(NEAST);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms((this->m_x + 1), (this->m_y - 1))->
                get_species() == _GAMESPECS_H::HUMAN_CH) {
            this->m_nearby_humans.push_back(NEAST);
        }
    }

    //check north-west
    if (this->m_x >= 1 && this->m_y >= 1) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty((this->m_x - 1), (this->m_y - 1))) {
            this->m_squares_to_move.push_back(NWEST);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms((this->m_x - 1), (this->m_y - 1))->
                get_species() == _GAMESPECS_H::HUMAN_CH) {

            this->m_nearby_humans.push_back(NWEST);
        }
    }

    //check south-east
    if (this->m_x <= (_GAMESPECS_H::GRIDSIZE - 2) &&
        this->m_y <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty((this->m_x + 1), (this->m_y + 1))) {
            this->m_squares_to_move.push_back(SEAST);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms((this->m_x + 1), (this->m_y + 1))->
                get_species() == _GAMESPECS_H::HUMAN_CH) {

            this->m_nearby_humans.push_back(SEAST);
        }
    }

    //check south-west
    if (this->m_x >= 1 && this->m_y <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the m_squares_to_move array
        if (this->m_city->is_empty((this->m_x - 1), (this->m_y + 1))) {
            this->m_squares_to_move.push_back(SWEST);
        }
            //else if it's a human add it to the m_nearby_humans array
        else if (this->m_city->get_organisms((this->m_x - 1), (this->m_y + 1))->
                get_species() == _GAMESPECS_H::HUMAN_CH) {

            this->m_nearby_humans.push_back(SWEST);
        }
    }
}

//function to shuffle the potential m_directions to move in to avoid movement bias
void Zombie::shuffle_directions() {

    //create random seed using system clock
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch().count();

    std::shuffle(this->m_squares_to_move.begin(), this->m_squares_to_move.end(),
                 std::default_random_engine(seed));
}

//function to shuffle the potential m_directions to eat/breed in to avoid movement bias
void Zombie::shuffle_recruit_options() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock
    std::shuffle(this->m_nearby_humans.begin(), this->m_nearby_humans.end(),
                 std::default_random_engine(seed));
}

//function to move in a given direction
void Zombie::move_directions() {

    //function to move to the first location in m_squares_to_move
    switch (this->m_squares_to_move[0]) {
        case NORTH:
            m_city->move_organism(this, this->m_x, (this->m_y - 1));
            break;
        case EAST:
            m_city->move_organism(this, (this->m_x + 1), this->m_y);
            break;
        case SOUTH:
            m_city->move_organism(this, this->m_x, (this->m_y + 1));
            break;
        case WEST:
            m_city->move_organism(this, (this->m_x - 1), this->m_y);
            break;
        case NEAST:
            m_city->move_organism(this, (this->m_x + 1), (this->m_y - 1));
            break;
        case NWEST:
            m_city->move_organism(this, (this->m_x - 1), (this->m_y - 1));
            break;
        case SEAST:
            m_city->move_organism(this, (this->m_x + 1), (this->m_y + 1));
            break;
        case SWEST:
            m_city->move_organism(this, (this->m_x - 1), (this->m_y + 1));
            break;
        default:
            break;
    }
}

//function to eat in a given direction
void Zombie::eat() {

    //function to eat the human at the first location in m_nearby_humans
    switch (this->m_nearby_humans[0]) {
        case NORTH:
            m_city->delete_human(this, this->m_x, (this->m_y - 1));
            break;
        case EAST:
            m_city->delete_human(this, (this->m_x + 1), this->m_y);
            break;
        case SOUTH:
            m_city->delete_human(this, this->m_x, (this->m_y + 1));
            break;
        case WEST:
            m_city->delete_human(this, (this->m_x - 1), this->m_y);
            break;
        case NEAST:
            m_city->delete_human(this, (this->m_x + 1), (this->m_y - 1));
            break;
        case NWEST:
            m_city->delete_human(this, (this->m_x - 1), (this->m_y - 1));
            break;
        case SEAST:
            m_city->delete_human(this, (this->m_x + 1), (this->m_y + 1));
            break;
        case SWEST:
            m_city->delete_human(this, (this->m_x - 1), (this->m_y + 1));
            break;
        default:
            break;
    }
}

//function to clear the m_squares_to_move and m_nearby_humans vectors
void Zombie::clear_targets() {

    if (!this->m_squares_to_move.empty()) {
        this->m_squares_to_move.erase(m_squares_to_move.begin(), m_squares_to_move.end());
    }

    if (!this->m_nearby_humans.empty()) {
        this->m_nearby_humans.erase(m_nearby_humans.begin(), m_nearby_humans.end());
    }

}

//function to check if there is a human near to create an ally
void Zombie::recruit() {

    check_directions();

    if (!m_nearby_humans.empty()) {
        breed();
        this->m_steps = 0;
    }
}

//function to create an ally in a space where a human is
void ::Zombie::breed() {

    //make a new zombie at the location of the first m_nearby_humans
    switch (this->m_nearby_humans[0]) {
        case NORTH:
            m_city->infect_human(this->m_x, (this->m_y - 1));
            break;
        case EAST:
            m_city->infect_human((this->m_x + 1), this->m_y);
            break;
        case SOUTH:
            m_city->infect_human(this->m_x, (this->m_y + 1));
            break;
        case WEST:
            m_city->infect_human((this->m_x - 1), this->m_y);
            break;
        case NEAST:
            m_city->infect_human((this->m_x + 1), (this->m_y - 1));
            break;
        case NWEST:
            m_city->infect_human((this->m_x - 1), (this->m_y - 1));
            break;
        case SEAST:
            m_city->infect_human((this->m_x + 1), (this->m_y + 1));
            break;
        case SWEST:
            m_city->infect_human((this->m_x - 1), (this->m_y + 1));
            break;
        default:
            break;
    }
}

//function to check if zombie has gone too many turns without eating
void ::Zombie::check_if_starved() {

    if (m_steps_until_starved >= _GAMESPECS_H::ZOMBIE_STARVE) {
        starve();
    }
}

//function to call for the zombie to be turned back into a human
void Zombie::starve() {
    m_city->cure_human(this->m_x, this->m_y);
}
