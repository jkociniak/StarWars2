#include <memory>

#include "imperialfleet.h"
#include <numeric>

OrdinaryImperialObject::OrdinaryImperialObject(ShieldPoints shield,
                                               AttackPower power, size_t q) : ImperialObject(), HasShield(shield), HasAttackPower(power), componentsQuantity(q) {}

OrdinaryImperialStarship::OrdinaryImperialStarship(ShieldPoints shield, AttackPower power) : ImperialStarship(), OrdinaryImperialObject(shield, power, 1) {}

ImperialObject::~ImperialObject() = default;

void OrdinaryImperialObject::takeDamage(AttackPower damage) {
    HasShield::takeDamage(damage);
    if (this->getShield() == 0)
        componentsQuantity--;
}

size_t OrdinaryImperialObject::getComponentsQuantity() const {return componentsQuantity;}

DeathStar::DeathStar(ShieldPoints shield, AttackPower power) : OrdinaryImperialStarship(shield, power) {}

ImperialDestroyer::ImperialDestroyer(ShieldPoints shield, AttackPower power) : OrdinaryImperialStarship(shield, power) {}

TIEFighter::TIEFighter(ShieldPoints shield, AttackPower power) : OrdinaryImperialStarship(shield, power) {}

void Squadron::updateAttackPower() {
    AttackPower sum = 0;

    for (std::shared_ptr<OrdinaryImperialObject>& ship : squadronShips) {
        if (ship->getShield() != 0)
            sum += ship->getAttackPower();
    }

    setAttackPower(sum);
}

void Squadron::updateShieldPoints() {
    ShieldPoints sum = 0;

    for (std::shared_ptr<OrdinaryImperialObject>& ship : squadronShips)
        sum += ship->getShield();

    setShieldPoints(sum);
}

void Squadron::updateComponentsQuantity() {
    size_t sum = 0;

    for (std::shared_ptr<OrdinaryImperialObject>& ship : squadronShips)
        sum += ship->getComponentsQuantity();

    componentsQuantity = sum;
}

void Squadron::takeDamage(AttackPower damage) {
    for (std::shared_ptr<OrdinaryImperialObject>& ship : squadronShips) {
        if (ship->getShield() != 0)
            ship->takeDamage(damage);
    }

    updateAttackPower();
    updateShieldPoints();
    updateComponentsQuantity();
}

Squadron::Squadron(std::initializer_list<std::shared_ptr<OrdinaryImperialObject>> ships) : OrdinaryImperialObject(
        [ships]()->ShieldPoints{
            ShieldPoints sum = 0;
            for (const std::shared_ptr<OrdinaryImperialObject>& ship : ships)
                sum += ship->getShield();

            return sum;
        }(), [ships]()->AttackPower{
            AttackPower sum = 0;
            for (const std::shared_ptr<OrdinaryImperialObject>& ship : ships)
                sum += ship->getAttackPower();

            return sum;
        }(), [ships]()->size_t{
            size_t sum = 0;
            for (const std::shared_ptr<OrdinaryImperialObject>& ship : ships)
                sum += ship->getComponentsQuantity();

            return sum;
        }()), squadronShips(ships) {}

Squadron::Squadron(std::vector<std::shared_ptr<OrdinaryImperialObject>> ships) : OrdinaryImperialObject(
        [ships]()->ShieldPoints{
            ShieldPoints sum = 0;
            for (const std::shared_ptr<OrdinaryImperialObject>& ship : ships)
                sum += ship->getShield();

            return sum;
        }(), [ships]()->AttackPower{
            AttackPower sum = 0;
            for (const std::shared_ptr<OrdinaryImperialObject>& ship : ships)
                sum += ship->getAttackPower();

            return sum;
        }(), [ships]()->size_t{
            size_t sum = 0;
            for (const std::shared_ptr<OrdinaryImperialObject>& ship : ships)
                sum += ship->getComponentsQuantity();

            return sum;
        }()), squadronShips(ships) {}

std::shared_ptr<OrdinaryImperialObject> createDeathStar(ShieldPoints shield, AttackPower attack) {
    return std::make_shared<DeathStar>(shield, attack);
}

std::shared_ptr<OrdinaryImperialObject> createTIEFighter(ShieldPoints shield, AttackPower attack) {
    return std::make_shared<TIEFighter>(shield, attack);
}

std::shared_ptr<OrdinaryImperialObject> createImperialDestroyer(ShieldPoints shield, AttackPower attack) {
    return std::make_shared<ImperialDestroyer>(shield, attack);
}

std::shared_ptr<OrdinaryImperialObject> createSquadron(std::vector<std::shared_ptr<OrdinaryImperialObject>> shipPtrs) {
    return std::make_shared<Squadron>(shipPtrs);
}