#include <cassert>

#include "rebelfleet.h"

RebelStarship::RebelStarship(ShieldPoints shield, Speed speed) : HasShield(shield), HasSpeed(speed) {}

void RebelStarship::fightBack(OrdinaryImperialObject &iShip) {}

RebelStarship::~RebelStarship() = default;

AttackingRebelStarship::AttackingRebelStarship(AttackPower attack, ShieldPoints shield, Speed speed) : RebelStarship(shield, speed), details::HasAttackPower(attack) {}

void AttackingRebelStarship::fightBack(OrdinaryImperialObject &iShip) {
    iShip.takeDamage(this->getAttackPower());
}

Explorer::Explorer(ShieldPoints shield, Speed speed) : RebelStarship(shield, speed) {
    assert(speed >= 299796);
    assert(speed <= 2997960);
}

StarCruiser::StarCruiser(AttackPower attack, ShieldPoints shield, Speed speed) : AttackingRebelStarship(attack, shield, speed) {
    assert(speed >= 99999);
    assert(speed <= 299795);
}

XWing::XWing(AttackPower attack, ShieldPoints shield, Speed speed) : AttackingRebelStarship(attack, shield, speed) {
    assert(speed >= 299796);
    assert(speed <= 2997960);
}

std::shared_ptr<RebelStarship> createExplorer(ShieldPoints shield, Speed speed) {
    return std::make_shared<Explorer>(shield, speed);
}

std::shared_ptr<RebelStarship> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower attack) {
    return std::make_shared<StarCruiser>(attack, shield, speed);
}

std::shared_ptr<RebelStarship> createXWing(ShieldPoints shield, Speed speed, AttackPower attack) {
    return std::make_shared<XWing>(attack, shield, speed);
}