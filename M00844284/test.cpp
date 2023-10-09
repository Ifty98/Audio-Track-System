#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hash_table.h"

TEST_CASE("Test keyCheck with collision") {
    HashTable table;
    AudioTrack track1("Ven Tad", "Ryan", 200);
    AudioTrack track2("Rios de sal", "Tina Scan", 620);
    AudioTrack track3("Dela getto", "Nayr", 436);
    table.addTrack(track1);
    table.addTrack(track2);
    table.addTrack(track3);
    
    REQUIRE(table.keyCheck("Ryan") == true);
    REQUIRE(table.keyCheck("Andrey Geg") == false);
    REQUIRE(table.keyCheck("ryan") == false);
    REQUIRE(table.keyCheck("Tina Scan") == true);
    REQUIRE(table.keyCheck("Nayr") == true);
}

TEST_CASE("Test removeTrack with collision") {
    HashTable table;
    AudioTrack track1("Ven Tad", "Ryan", 200);
    AudioTrack track2("Rios de sal", "Tina Scan", 620);
    table.addTrack(track1);
    table.addTrack(track2);

    REQUIRE(table.removeTrack("Ryan") == true);
    REQUIRE(table.removeTrack("Nayr") == false);
    REQUIRE(table.keyCheck("Ryan") == false);
}

TEST_CASE("Adding a track already stored in the table") {
    HashTable table;
    AudioTrack track1 = new AudioTrack("Ven Tad", "Ryan", 300);
    table.addTrack(track1);
    AudioTrack track2 = new AudioTrack("Nayr", "Ryan", 220);
    REQUIRE(table.addTrack(track2) == false);
}
