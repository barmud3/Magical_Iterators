#include "doctest.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "sources/MagicalContainer.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("AscendingIterator go through MagicalCOntainer in ascending")
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);
    MagicalContainer::AscendingIterator ascIter(container);
    MagicalContainer::AscendingIterator curr = ascIter.begin();
    CHECK(*(curr) == 2);
    curr++;
    CHECK(*(curr) == 3);
    curr++;
    CHECK(*(curr) == 9);
    curr++;
    CHECK(*(curr) == 17);
    curr++;
    CHECK(*(curr) == 25);

    curr++; //index outside
    CHECK_THROWS(*(curr));
}

TEST_CASE("SideCrossIterator go through MagicalCOntainer in side cross way")
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);
    //container has : 17 2 25 9 3
    MagicalContainer::SideCrossIterator sideCrossIter(container);
    MagicalContainer::SideCrossIterator curr = sideCrossIter.begin();
    CHECK(*(curr) == 17);
    curr++;
    CHECK(*(curr) == 3);
    curr++;
    CHECK(*(curr) == 2);
    curr++;
    CHECK(*(curr) == 9);
    curr++;
    CHECK(*(curr) == 25);

    curr++; //index outside
    CHECK_THROWS(*(curr));
}

TEST_CASE("PrimeIterator go through MagicalContainer prime numbers")
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);
    MagicalContainer::PrimeIterator primeIter(container);
    MagicalContainer::PrimeIterator curr = primeIter.begin();
    CHECK(*(curr) == 2);
    curr++;
    CHECK(*(curr) == 3);

    curr++; //index outside
    CHECK_THROWS(*(curr));
}

TEST_CASE("handle nullptr")
{
    MagicalContainer* container2 = nullptr;
    CHECK_THROWS(MagicalContainer::AscendingIterator(*container2));
    CHECK_THROWS(MagicalContainer::SideCrossIterator(*container2));
    CHECK_THROWS(MagicalContainer::PrimeIterator(*container2));
}

TEST_CASE("delete() , size () work well")
{
    MagicalContainer container;
    CHECK_THROWS(container.removeElement(3));

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    CHECK(container.size() == 5);
    container.removeElement(9);
    CHECK(container.size() == 4);

}