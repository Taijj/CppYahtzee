#pragma once

/// <summary>
/// Defines an enum for the 13 kinds of combos a player can make
/// to be used all over the programm for combo identification
/// </summary>
namespace Score
{
    enum Kind
    {
        Undefined = 0,

        Aces,
        Twos,
        Threes,
        Fours,
        Fives,
        Sixes,

        OfKind3,
        OfKind4,
        FullHouse,
        StraightSmall,
        StraightLarge,
        Yahtzee,

        Chance
    };
}