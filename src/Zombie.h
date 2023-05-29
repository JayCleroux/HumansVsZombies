#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"

class Zombie : public Organism {
private:
    enum m_directions {
        WEST, NORTH, EAST, SOUTH, NEAST, SEAST, NWEST, SWEST
    };
    std::vector<m_directions> m_squares_to_move;
    std::vector<m_directions> m_nearby_humans;
    int m_steps_until_starved = 0;
public:
    Zombie(City *city);

    ~Zombie() override;

    void recruit() override;

    void turn() override;

    void check_recruit() override;

    void move() override;

    void check_directions() override;

    void shuffle_directions() override;

    void clear_targets() override;

    void move_directions() override;

    void shuffle_recruit_options();

    void eat();

    void breed();

    void starve();

    void check_if_starved();
};

#endif