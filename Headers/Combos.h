#pragma once

#include "Config.h"
#include <algorithm>



class Combo
{
public:   
    
    Combo(const char* name) : _name(name)
    {}

    ~Combo() = default;

    const char* Name() const
    {
        return _name;
    }

    virtual Score::Kind Kind() const = 0;
    virtual std::uint32_t Score(GameDice& dice) const = 0;

private:
    const char* _name;
};

class ComboInt : public Combo
{
public:
    ComboInt(const char* name, std::uint32_t value) : Combo(name)
    {
        _value = std::clamp(value, 1U, Rules::DICE);
    }

    Score::Kind Kind() const final
    {
        return static_cast<Score::Kind>(_value);
    }

    std::uint32_t Score(GameDice& dice) const final
    {
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




const ComboInt aces = { "Aces", 1};
const ComboInt twos = { "Twos", 2 };
const ComboInt threes = { "Threes", 3 };
const ComboInt fours = { "Fours", 4 };
const ComboInt fives = { "Fives", 5 };
const ComboInt sixes = { "Sixes", 6 };

const std::vector<const Combo*> COMBOS =
{
    &aces, &twos, &threes, &fours, &fives, &sixes
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
