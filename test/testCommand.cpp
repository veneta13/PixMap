#include "catch2.h"
#include "../inc/command.h"

TEST_CASE("Constructor")
{

    SECTION("Name - uppercase")
    {
        std::string exitCommandU = "EXIT";
        Command testCommand(exitCommandU);
        REQUIRE(exitCommandU.compare(testCommand.getName()) == 0);
    }

    SECTION("Name - lowercase")
    {
        std::string exitCommandL = "exit";
        std::string exitCommandU = "EXIT";
        Command testCommand(exitCommandL);
        REQUIRE(exitCommandU.compare(testCommand.getName()) == 0);
    }

    SECTION("Name - random case")
    {
        std::string exitCommandL = "eXiT";
        std::string exitCommandU = "EXIT";
        Command testCommand(exitCommandL);
        REQUIRE(exitCommandU.compare(testCommand.getName()) == 0);
    }

    SECTION("Name - wrong")
    {
        std::string exitCommandW = "quit";
        REQUIRE_THROWS_AS(Command(exitCommandW) , std::invalid_argument);
    }
}