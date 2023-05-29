#ifndef _Human_H
#define _Human_H

#include "Organism.h"
#include "City.h"
#include "GameSpecs.h"

class Human : public Organism {
public:
    Human(City *city);

    ~Human() override;

    void move() override;

    void recruit() override;

    void turn() override;

    void check_recruit() override;

    void check_directions() override;

    void shuffle_directions() override;

    void move_directions() override;

    void clear_targets() override;
};

#endif
