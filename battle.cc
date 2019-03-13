#include <utility>
#include <type_traits>
#include <iostream>

#include "battle.h"

SpaceBattle::SpaceBattle(std::vector<std::shared_ptr<RebelStarship>> RS,
                         std::vector<std::shared_ptr<OrdinaryImperialObject>> IS,
                         Time start, Time maximumTime) : RebelStarships(std::move(RS)),
                                                         ImperialStarships(std::move(IS)),
                                                         start(start),
                                                         currentTime(start),
                                                         maximumTime(maximumTime),
                                                         defaultClock(start, maximumTime),
                                                         defaultStrategy() {
    clock = &defaultClock;
    strategy = &defaultStrategy;
}

size_t SpaceBattle::countImperialFleet() {
    size_t sum = 0;
    for (const std::shared_ptr<OrdinaryImperialObject> &ship : ImperialStarships)
        if (ship->getShield() > 0) {
            sum += ship->getComponentsQuantity();
        }

    return sum;
}

size_t SpaceBattle::countRebelFleet() {
    size_t sum = 0;
    for (const std::shared_ptr<RebelStarship> &ship : RebelStarships) {
        if (ship->getShield() > 0) {
            sum++;
        }
    }

    return sum;
}

SpaceBattle::Builder& SpaceBattle::Builder::ship(const std::shared_ptr<OrdinaryImperialObject> &s) {
    ImperialStarships.push_back(s);
    return *this;
}

SpaceBattle::Builder& SpaceBattle::Builder::ship(const std::shared_ptr<RebelStarship> &s) {
    RebelStarships.push_back(s);
    return *this;
}

SpaceBattle::Builder& SpaceBattle::Builder::startTime(Time t) {
    start = t;
    return *this;
}

SpaceBattle::Builder& SpaceBattle::Builder::maxTime(Time t) {
    maximumTime = t;
    return *this;
}

SpaceBattle SpaceBattle::Builder::build() const {
    return SpaceBattle(RebelStarships, ImperialStarships, start, maximumTime);
}

DefaultBattleClock::DefaultBattleClock(Time startTime, Time maximumTime) : startTime(startTime), maximumTime(maximumTime) {}

Time DefaultBattleClock::nextTime(Time currentTime, Time timeStep) {
    return (currentTime+timeStep)%(maximumTime+1);
}

bool DefaultBattleStrategy::isAttackTime(Time currentTime) {
    return currentTime % 5 != 0 && (currentTime % 2 == 0 || currentTime % 3 == 0);
}

void SpaceBattle::tick(Time timeStep) {
    std::string msg;

    if (countImperialFleet() == 0 && countRebelFleet() == 0)
        msg = "DRAW\n";
    else if (countImperialFleet() == 0)
        msg = "REBELLION WON\n";
    else if (countRebelFleet() == 0)
        msg = "IMPERIUM WON\n";

    if (!msg.empty()) {
        std::cout << msg;
        return;
    }

    if (strategy->isAttackTime(currentTime)) {
        for (auto iShip = ImperialStarships.begin();
             iShip != ImperialStarships.end(); ++iShip) {
            for (auto rShip = RebelStarships.begin();
                 rShip != RebelStarships.end(); ++rShip) {
                if ((*rShip)->getShield() != 0 && (*iShip)->getShield() != 0) {
                    (*rShip)->takeDamage((*iShip)->getAttackPower());

                    (*rShip)->fightBack(**iShip);
                }
            }
        }
    }

    currentTime = clock->nextTime(currentTime, timeStep);
}