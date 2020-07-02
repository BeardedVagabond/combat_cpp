#include <iostream>

#include "Die.hpp"
#include "Combatant.hpp"

int main()
{
    std::cout << "Hello, world!" << std::endl;

    // Functionality test of Die object
    bv::actors::Die d6(6);
    std::cout << d6.ToString() << std::endl;
    std::cout << "Rolling 4 times..." << std::endl;
    auto results = d6.Roll(4);
    for (int x : results)
    {
        std::cout << x << std::endl;
    }

    // Functionality test of Combatant object
    bv::actors::Combatant nate("Nate");
    bv::actors::Combatant test("Enemy");

    std::cout << nate.ToString() << std::endl;
    std::cout << test.ToString() << std::endl;

    while (test.GetHealth() > 0)
    {
        std::cout << nate.GetName() << " attacked " << test.GetName();
        std::cout << " for " << std::to_string(nate.Attack(&test)) << " damage!\n";
        std::cout << test.GetName() << " now has " << test.GetHealth() << " HP!\n";
    }

    return 0;
}
