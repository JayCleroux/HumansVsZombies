#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include <vector>

class City;

class Organism {
protected:
    int m_x;
    int m_y;
    int m_species;
    bool m_moved = false;
    int m_steps = 0;

    enum m_directions {
        WEST, NORTH, EAST, SOUTH
    };
    City *m_city;
    std::vector<m_directions> m_squares_to_move;

public:
    //constructor/destructor
    explicit Organism(City *city);

    virtual ~Organism();

    //virtual logic functions
    virtual void move() = 0;

    virtual void recruit() = 0;

    virtual void turn() = 0;

    virtual void check_recruit() = 0;

    virtual void check_directions() = 0;

    virtual void shuffle_directions() = 0;

    virtual void move_directions() = 0;

    virtual void clear_targets() = 0;

    int get_x() const;

    int get_y() const;

    int get_species() const;

    void set_x(int x);

    void set_y(int y);

    void set_position(int x, int y);

    void end_turn();
};

#endif
