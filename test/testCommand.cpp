#include "catch2.h"
#include "../inc/command.h"

TEST_CASE("Constructor")
{

    std::string exitCommandU = "EXIT";
    std::string exitCommandL = "exit";
    std::string exitCommandR = "eXiT";

    SECTION("Name - uppercase")
    {
        Command testCommand(exitCommandU);
        REQUIRE(exitCommandU.compare(testCommand.getName()) == 0);
    }

    SECTION("Name - lowercase")
    {
        Command testCommand(exitCommandL);
        REQUIRE(exitCommandU.compare(testCommand.getName()) == 0);
    }

    SECTION("Name - random case")
    {
        Command testCommand(exitCommandR);
        REQUIRE(exitCommandU.compare(testCommand.getName()) == 0);
    }

    SECTION("Name - wrong")
    {
        std::string exitCommandW = "quit";
        REQUIRE_THROWS_AS(Command(exitCommandW) , std::invalid_argument);
    }
}

TEST_CASE("Add Arguments")
{
    SECTION("Add 1 argument")
    {
        std::string exitCommand = "EXIT";
    }

    SECTION("Count Error")
    {
        //std::vector  <std::string> = {"Arg1"}
    }
}

TEST_CASE("Copy Constructor")
{
    SECTION("Name only")
    {
        std::string exitCommand = "EXIT";
        Command testCommand1(exitCommand);
        Command testCommand2 = testCommand1;
        
    }

    SECTION("Name and arguments")
    {
        std::string exitCommand = "EXIT";
        Command testCommand1(exitCommand);
        Command testCommand2 = testCommand1;
    }
}