#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

#include "helper.h"
#include <vector>
#include <memory>

class ImperialObject {
  public:
    virtual ~ImperialObject();
};


/* Assuming that ordinary imperial object is composed of ships, has a shield
 * and is able to attack. */
class OrdinaryImperialObject : public virtual ImperialObject,
                               public details::HasShield,
                               public details::HasAttackPower {
  public:
    OrdinaryImperialObject(ShieldPoints shield, AttackPower power, size_t q);
    void takeDamage(AttackPower damage) override;
    size_t getComponentsQuantity() const;

  protected:
    size_t componentsQuantity;
};

class ImperialStarship : public virtual ImperialObject {};

class OrdinaryImperialStarship : public ImperialStarship,
                                 public OrdinaryImperialObject {
  public:
    OrdinaryImperialStarship(ShieldPoints shield, AttackPower power);
};

class DeathStar : public OrdinaryImperialStarship {
  public:
    DeathStar(ShieldPoints shield, AttackPower power);
};

class ImperialDestroyer : public OrdinaryImperialStarship {
  public:
    ImperialDestroyer(ShieldPoints shield, AttackPower power);
};

class TIEFighter : public OrdinaryImperialStarship {
  public:
    TIEFighter(ShieldPoints shield, AttackPower power);
};

class Squadron : public OrdinaryImperialObject {
  public:
    Squadron(std::vector<std::shared_ptr<OrdinaryImperialObject>> ships);
    Squadron(std::initializer_list<std::shared_ptr<OrdinaryImperialObject>> ships);
    void takeDamage(AttackPower damage) override;

  private:
    std::vector<std::shared_ptr<OrdinaryImperialObject>> squadronShips;
    void updateAttackPower();
    void updateShieldPoints();
    void updateComponentsQuantity();
};

std::shared_ptr<OrdinaryImperialObject> createDeathStar(ShieldPoints shield, AttackPower attack);

std::shared_ptr<OrdinaryImperialObject> createTIEFighter(ShieldPoints shield, AttackPower attack);

std::shared_ptr<OrdinaryImperialObject> createImperialDestroyer(ShieldPoints shield, AttackPower attack);

std::shared_ptr<OrdinaryImperialObject> createSquadron(std::vector<std::shared_ptr<OrdinaryImperialObject>> shipPtrs);


#endif //STARWARS2_IMPERIALFLEET_H
