#ifndef _CITY_H
#define _CITY_H

#include "GameSpecs.h"
#include "Zombie.h"
#include "Human.h"
#include "Organism.h"

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City {
protected:
    Organism *m_grid[GRID_HEIGHT][GRID_WIDTH] = {nullptr};
private:
    int m_generation;
    int m_zombies;
    int m_humans;
public:
    City();

    virtual ~City();

    int get_generation() const;

    int get_zombies() const;

    int get_humans() const;

    Organism *get_organisms(int x, int y);

    void set_organism(Organism *organism, int x, int y);

    bool has_diversity() const;

    void reset();

    void populate();

    bool is_empty(int xPos, int yPos);

    static void color(int c);

    void move();

    void move_organism(Organism *organism, int x, int y);

    void delete_human(Organism *organism, int x, int y);

    void create_human(int xPos, int yPos);

    void create_zombie(int xPos, int yPos);

    void cure_human(int xPos, int yPos);

    void infect_human(int xPos, int yPos);

    void populateHumans();

    void populateZombies();

    friend std::ostream &operator<<(std::ostream &output, City &city);

};

#endif

