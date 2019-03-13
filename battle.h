#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

#include "rebelfleet.h"
#include "imperialfleet.h"

class BattleClock {
  public:
    virtual Time nextTime(Time currentTime, Time timeStep) = 0;
};

class DefaultBattleClock : public BattleClock {
  public:
    DefaultBattleClock(Time startTime, Time maximumTime);
    Time nextTime(Time currentTime, Time timeStep) override;

  private:
    Time startTime;
    Time maximumTime;
};

class BattleStrategy {
  public:
    virtual bool isAttackTime(Time currentTime) = 0;
};

class DefaultBattleStrategy : public BattleStrategy {
  public:
    bool isAttackTime(Time currentTime) override;
};

class SpaceBattle {
  private:
    SpaceBattle(std::vector<std::shared_ptr<RebelStarship>> RS,
                std::vector<std::shared_ptr<OrdinaryImperialObject>> IS,
                Time start, Time maximumTime);

    std::vector<std::shared_ptr<RebelStarship>> RebelStarships;
    std::vector<std::shared_ptr<OrdinaryImperialObject>> ImperialStarships;

    Time start;
    Time currentTime;
    Time maximumTime;

    DefaultBattleClock defaultClock;
    DefaultBattleStrategy defaultStrategy;
    BattleClock* clock;
    BattleStrategy* strategy;

  public:
    class Builder {
      public:

        Builder& ship(const std::shared_ptr<OrdinaryImperialObject> &s);

        Builder& ship(const std::shared_ptr<RebelStarship> &s);

        Builder& startTime(Time t);

        Builder& maxTime(Time t);

        SpaceBattle build() const;

      private:
        std::vector<std::shared_ptr<RebelStarship>> RebelStarships;
        std::vector<std::shared_ptr<OrdinaryImperialObject>> ImperialStarships;

        Time start{};
        Time maximumTime{};
    };

    size_t countImperialFleet();
    size_t countRebelFleet();
    void tick(Time timeStep);
};


#endif //STARWARS2_BATTLE_H
