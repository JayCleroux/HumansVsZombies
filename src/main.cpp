#include "City.h"
#include "GameSpecs.h"

int main() {
    City *city = new City();
    city->populate();
    std::chrono:: milliseconds interval((int)(_GAMESPECS_H::PAUSE_SECONDS * 2000));

    while (city->has_diversity()) {
        std::this_thread::sleep_for(interval);
        city->move();
        city->reset();
        std::cout << *city;
        std::cout << "GENERATION " << city->get_generation() << std::endl;
        std::cout << "HUMANS: " << city->get_humans() << std::endl;
        std::cout << "ZOMBIES: " << city->get_zombies() << std::endl;
    }

    std::cout << "There has been an extinction event.";

    delete city;
}

