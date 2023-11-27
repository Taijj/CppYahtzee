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
        _value = std::clamp(value, 1U, 6U); // Count of die sides
    }

    Score::Kind Kind() const final { return static_cast<Score::Kind>(_value); }

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

class Combo3 : public Combo
{
public:
    Combo3(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::OfKind3; }

    std::uint32_t Score(GameDice& dice) const final { return 33; }
};

class Combo4 : public Combo
{
public:
    Combo4(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::OfKind4; }

    std::uint32_t Score(GameDice& dice) const final { return 44; }
};

class ComboFullHouse : public Combo
{
public:
    ComboFullHouse(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::FullHouse; }

    std::uint32_t Score(GameDice& dice) const final { return 55; }
};

class ComboStraighSmall : public Combo
{
public:
    ComboStraighSmall(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::StraightSmall; }

    std::uint32_t Score(GameDice& dice) const final { return 66; }
};

class ComboStraighLarge : public Combo
{
public:
    ComboStraighLarge(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::StraightLarge; }

    std::uint32_t Score(GameDice& dice) const final { return 66; }
};

class ComboYathzee : public Combo
{
public:
    ComboYathzee(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::Yahtzee; }

    std::uint32_t Score(GameDice& dice) const final { return 100; }
};

class ComboChance : public Combo
{
public:
    ComboChance(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::Chance; }

    std::uint32_t Score(GameDice& dice) const final { return 77; }
};





const ComboInt aces = { "Aces", 1};
const ComboInt twos = { "Twos", 2 };
const ComboInt threes = { "Threes", 3 };
const ComboInt fours = { "Fours", 4 };
const ComboInt fives = { "Fives", 5 };
const ComboInt sixes = { "Sixes", 6 };

const Combo3 ofKind3 = { "3 of a Kind" };
const Combo4 ofKind4 = { "4 of a Kind" };
const ComboFullHouse full = { "Full House" };
const ComboStraighSmall straightS = { "Small Straight" };
const ComboStraighLarge straightL = { "Large Straight" };
const ComboYathzee yathzee = { "Yathzee" };
const ComboChance chance = { "Chance" };

const std::vector<const Combo*> COMBOS =
{
    &aces, &twos, &threes, &fours, &fives, &sixes,
    &ofKind3, &ofKind4, &full, &straightS, &straightL, &yathzee, &chance
};



// Full house | 2 of the same kind && 3 of the same kind | 25
// small Straight | 4 consecutive values | 30
// large straight | 5 consecutive values | 40
// Yahtzee | 5 of the same kind | 50
// Chance | no condition, when selected | Sum of all die values
