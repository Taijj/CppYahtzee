#pragma once

#include "Config.h"
#include <algorithm>
#include <numeric>



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
            
    static std::uint32_t CountOfKind(GameDice& dice, std::uint32_t value)
    {
        auto count = std::count_if(dice.begin(), dice.end(),
            [value](const Die& d) { return d.GetValue() == value; });
        return static_cast<std::uint32_t>(count);
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
        _value = std::clamp(value, 1U, Rules::DIE_SIDES); // Count of die sides
    }

    Score::Kind Kind() const final { return static_cast<Score::Kind>(_value); }

    std::uint32_t Score(GameDice& dice) const final
    {
        return CountOfKind(dice, _value) * _value;
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

    std::uint32_t Score(GameDice& dice) const final
    {         
        for (Die& d : dice)
        {
            const std::uint32_t count = CountOfKind(dice, d.GetValue());
            if (count < 3) // 3 of a kind
                continue;
            
            // Wanted to try accumulate
            return std::accumulate(dice.begin(), dice.end(), 0,
                [](std::uint32_t sum, const Die& d) { return sum + d.GetValue(); });
        }

        return 0;
    }
};

class Combo4 : public Combo
{
public:
    Combo4(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::OfKind4; }

    std::uint32_t Score(GameDice& dice) const final
    { 
        for (Die& d : dice)
        {
            const std::uint32_t count = CountOfKind(dice, d.GetValue());
            if (count < 4) // 4 of a kind
                continue;
            
            // Actually prefer this way, is more readably i think
            std::uint32_t sum = 0;
            for (Die& d : dice)
                sum += d.GetValue();
            return sum;
        }

        return 0;
    }
};

class ComboFullHouse : public Combo
{
public:
    ComboFullHouse(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::FullHouse; }

    std::uint32_t Score(GameDice& dice) const final
    {
        bool found3 = false;
        bool found2 = false;
        for (Die& d : dice)
        {
            const std::uint32_t count = CountOfKind(dice, d.GetValue());
            if (count == 2 && !found2)
                found2 = true;

            if (count == 3 && !found3)
                found3 = true;            
        }

        return found2 && found3 ? 25 : 0;
    }    
};

class ComboStraighSmall : public Combo
{
public:
    ComboStraighSmall(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::StraightSmall; }

    std::uint32_t Score(GameDice& dice) const final
    {
        const Die& min = *std::min_element(dice.begin(), dice.end(),
            [](const Die& d1, const Die& d2) { return d1.GetValue() < d2.GetValue(); });

        std::uint32_t count = 0;
        for (std::uint32_t i = 0; i < Rules::DICE-1; ++i)
        {
            for (Die &d : dice)
            {
                if (d.GetValue() == min.GetValue() + i)
                {
                    count++;
                    break;
                }
            }
        }

        return count == Rules::DICE-1 ? 30 : 0;
    }
};

class ComboStraighLarge : public Combo
{
public:
    ComboStraighLarge(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::StraightLarge; }

    std::uint32_t Score(GameDice& dice) const final
    {
        const Die& min = *std::min_element(dice.begin(), dice.end(),
            [](const Die& d1, const Die& d2) { return d1.GetValue() < d2.GetValue(); });

        std::uint32_t count = 0;
        for (std::uint32_t i = 0; i < Rules::DICE; ++i)
        {
            for (Die& d : dice)
            {
                if (d.GetValue() == min.GetValue() + i)
                {
                    count++;
                    break;
                }
            }
        }

        return count == Rules::DICE ? 40 : 0;
    }
};

class ComboYathzee : public Combo
{
public:
    ComboYathzee(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::Yahtzee; }

    std::uint32_t Score(GameDice& dice) const final
    {
        for (std::uint32_t i = 0; i < Rules::DIE_SIDES; ++i)
        {
            if (CountOfKind(dice, i) == Rules::DICE)
                return 50;
        }
        return 0;
    }
};

class ComboChance : public Combo
{
public:
    ComboChance(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::Chance; }

    std::uint32_t Score(GameDice& dice) const final 
    { 
        std::uint32_t sum = 0;
        for (Die& d : dice)
            sum += d.GetValue();
        return sum;
    }
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
