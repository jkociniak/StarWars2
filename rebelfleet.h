#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

#include <memory>
#include "helper.h"
#include "imperialfleet.h"

class RebelStarship : public details::HasShield,
                      public details::HasSpeed {

  public:
    RebelStarship(ShieldPoints shield, Speed speed);
    virtual void fightBack(OrdinaryImperialObject& iShip);

    virtual ~RebelStarship();
};

class AttackingRebelStarship : public RebelStarship, public details::HasAttackPower {
  public:
    AttackingRebelStarship(AttackPower attack, ShieldPoints shield, Speed speed);
    void fightBack(OrdinaryImperialObject& iShip) override;
};

class Explorer : public RebelStarship {
  public:
    Explorer(ShieldPoints shield, Speed speed);
};

class StarCruiser : public AttackingRebelStarship {
  public:
    StarCruiser(AttackPower attack, ShieldPoints shield, Speed speed);
};

class XWing : public AttackingRebelStarship {
  public:
    XWing(AttackPower attack, ShieldPoints shield, Speed speed);
};

std::shared_ptr<RebelStarship> createExplorer(ShieldPoints shield, Speed speed);

std::shared_ptr<RebelStarship> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower attack);

std::shared_ptr<RebelStarship> createXWing(ShieldPoints shield, Speed speed, AttackPower attack);


/*Dobra plan jest taki:
 * klasa Ship dla wszystkich statków w helper zawiera getShield():ShieldPoints i takeDamage(AttackPower damage):void
 * i ShieldPoints, bo są statki bez AttackPower i bez Speed więc no
 * klasa RebelStarship trzymająca tam speeda dla statków rebelii i odpowiednie metody też dziedzicząca po Ship
 * klasa pomocniccza AttackRebelStarship(???) trzymająca ogólnie statki rebelii zdolne do ataku po której dziedziczą
 * StarCruiser i XWing
 * Explorer dziedziczy po prostu po RebelStarship
 * klasa ImperialStarship po której dziedziczą wszystkie statki imperium bo z tego co rozumiem treść to wyjebane
 * Squadron niczym się chyba nie różni od statku kurwa zwykłego to ty no nie wiem o co cho
 * Co do battle to nie wiem, zająłbym się w pierwszej kolejności implementacją statków
 * A no i zero kurwa jakiegoś metaprogramowania tak o po prostu bym siupnął .h i .cc do wszystkiego jak człowiek
 * Ona nie wie że ma do czynienia z bestią
 * A jeśli będzie miała dalej diabeł to jej dziecko
 * To zapłaci jak za studia jak za ciuchy
 * Wiesz o co chodzi 2 tysiące za buty
 * Chodzę tak jakbym miał skrzydła na sobie
 * Rozumiem wasz ból bo też byłem na dole
 * I to co zrozumiałem trzeba pracowac ciągle
 * Bo sukces w żaden sposób nigdy nie istniał w szkole
 * Oj nie nie nie nie nie nie nie
 * nie nie nie nie nie nie nie nie
 *
 *
 * Jesteśmy na stacji tak jak hot dogi
 * Chcę duże zabawki tak jak Toy Story
 *
 * Pozdro
 * Elo z fartem
 */


#endif //STARWARS2_REBELFLEET_H