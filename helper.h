#ifndef STARWARS2_HELPER_H
#define STARWARS2_HELPER_H

using ShieldPoints = unsigned int;
using AttackPower = unsigned int;
using Speed = unsigned int;
using Time = int;

namespace details {
    class HasAttackPower {
      public:
        virtual const AttackPower& getAttackPower() const;

      protected:
        explicit HasAttackPower(AttackPower ap);
        void setAttackPower(AttackPower newAp);

      private:
        AttackPower ap;
    };

    class HasSpeed {
      public:
        const Speed& getSpeed() const;

      protected:
        explicit HasSpeed(Speed s);

      private:
        const Speed s;
    };

    class HasShield {
      public:
        virtual const ShieldPoints& getShield() const;
        virtual void takeDamage(AttackPower damage);

      protected:
        explicit HasShield(ShieldPoints sp);
        void setShieldPoints(ShieldPoints newSp);

      private:
        ShieldPoints sp;
    };
}




#endif //STARWARS2_HELPER_H
