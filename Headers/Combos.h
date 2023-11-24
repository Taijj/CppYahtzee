#pragma once

#include "Config.h"
#include <concepts>



class Combo
{
public:   
    virtual Score::Kind Kind() const = 0;
    virtual std::uint32_t Score(GameDice& dice) const = 0;
};

class ComboInt : public Combo
{
public:
    ComboInt(std::uint32_t value) : _value(value)
    {}

    Score::Kind Kind() const final
    {
        return static_cast<Score::Kind>(_value);
    }

    std::uint32_t Score(GameDice& dice) const final
    {
        Utils::Log("Scored Int");

        std::uint32_t sum = 0;        
        for (Die& d : dice)
        {
            if (d.GetValue() == _value)
                sum += _value;
        }
        return sum;
    }

private:
    std::uint32_t _value;
};




ComboInt aces = { 1 };
ComboInt twos = { 2 };
ComboInt threes = { 3 };
ComboInt fours = { 4 };
ComboInt fives = { 5 };
ComboInt sixes = { 6 };

const std::vector<Combo*> COMBOS =
{
    &aces, &twos, &threes
};


// extra definition
// Name
// IsMatch
// GetScore


// Aces, Twos, Threes, Fours, Fives, Sixes | no condition | #Dice with Value * Value
// 3 of a kind | 3 of the same kind | Sum of all die values
// 4 of a kind | 4 of the same kind | Sum of all die values
// Full house | 2 of the same kind && 3 of the same kind | 25
// small Straight | 4 consecutive values | 30
// large straight | 5 consecutive values | 40
// Yahtzee | 5 of the same kind | 50
// Chance | no condition, when selected | Sum of all die values
