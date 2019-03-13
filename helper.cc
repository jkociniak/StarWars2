#include "helper.h"


details::HasAttackPower::HasAttackPower(AttackPower ap) : ap(ap) {}

const AttackPower& details::HasAttackPower::getAttackPower() const { return ap; }

void details::HasAttackPower::setAttackPower(AttackPower newAp) { ap = newAp; }

details::HasSpeed::HasSpeed(Speed s) : s(s) {}

const Speed& details::HasSpeed::getSpeed() const { return s; }

const ShieldPoints& details::HasShield::getShield() const {
    return sp;
}

void details::HasShield::takeDamage(AttackPower damage) {
    sp = (damage >= sp) ? 0 : sp - damage;
}

details::HasShield::HasShield(ShieldPoints sp) : sp(sp) {}

void details::HasShield::setShieldPoints(ShieldPoints newSp) { sp = newSp; }
