#include "Human.h"

#include "GameSpecs.h"

Human::Human(City *city) : Organism(city) {
    this->m_city = city;
    this->m_species = _GAMESPECS_H::HUMAN_CH;
}

Human::~Human() {

    this->m_city = nullptr;
}

void Human::turn() {

    if (!m_moved) {
        move();
        check_recruit();
    }
}

void Human::move() {

    check_directions();

    //verify there is possible m_directions to move
    if (!this->m_squares_to_move.empty()) {
        shuffle_directions();
        move_directions();
        clear_targets();
    }

    //set m_moved flag
    this->m_moved = true;
}

void Human::check_recruit() {

    if (this->m_steps > _GAMESPECS_H::HUMAN_BREED) {
        recruit();
        this->m_steps = 0;
        clear_targets();
    }

    this->m_steps++;
}

void Human::check_directions() {

    //check north
    if (this->m_y >= 1) {
        if (this->m_city->is_empty(this->m_x, (this->m_y - 1))) {
            this->m_squares_to_move.push_back(NORTH);
        }
    }

    //check south
    if (this->m_y <= (_GAMESPECS_H::GRIDSIZE - 2)) {
        if (this->m_city->is_empty(this->m_x, (this->m_y + 1))) {
            this->m_squares_to_move.push_back(SOUTH);
        }
    }

    //check west
    if (this->m_x >= 1) {
        if (this->m_city->is_empty((this->m_x - 1), this->m_y)) {
            this->m_squares_to_move.push_back(WEST);
        }
    }

    //check east
    if (this->m_x <= (_GAMESPECS_H::GRIDSIZE - 2)) {
        if (this->m_city->is_empty((this->m_x + 1), this->m_y)) {
            this->m_squares_to_move.push_back(EAST);
        }
    }
}

void Human::shuffle_directions() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->m_squares_to_move.begin(), this->m_squares_to_move.end(),
                 std::default_random_engine(seed));
}

//function to move in a given direction
void Human::move_directions() {

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
        default:
            break;
    }
}

void Human::recruit() {
    check_directions();
    if (!this->m_squares_to_move.empty()) {
        shuffle_directions();
        switch (this->m_squares_to_move[0]) {
            case NORTH:
                m_city->create_human(this->m_x, (this->m_y - 1));
                break;
            case EAST:
                m_city->create_human((this->m_x + 1), this->m_y);
                break;
            case SOUTH:
                m_city->create_human(this->m_x, (this->m_y + 1));
                break;
            case WEST:
                m_city->create_human((this->m_x - 1), this->m_y);
                break;
            default:
                break;
        }
    }
}

//function to clear the m_squares_to_move vector
void Human::clear_targets() {

    if (!this->m_squares_to_move.empty()) {
        this->m_squares_to_move.clear();
    }
}
