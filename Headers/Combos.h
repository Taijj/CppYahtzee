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
    


    virtual Score::Kind Kind() const = 0;
    virtual std::uint32_t Score(GameDice& dice) const = 0;



    static std::uint32_t CountOfKind(GameDice& dice, std::uint32_t value)
    {
        auto count = std::count_if(dice.begin(), dice.end(),
            [value](const Die& d) { return d.GetValue() == value; });
        return static_cast<std::uint32_t>(count);
    }

    static std::uint32_t Sum(GameDice& dice)
    {
        // Could do this:
        //return std::accumulate(dice.begin(), dice.end(), 0,
            //[](std::uint32_t sum, const Die& d) { return sum + d.GetValue(); });

        // But I like this much better, better readable imho:
        std::uint32_t sum = 0;
        for (Die& d : dice)
            sum += d.GetValue();
        return sum;
    }

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

class ComboOfKind : public Combo
{
public:
    ComboOfKind(const char* name, Score::Kind kind, std::uint32_t value, std::uint32_t fixedScore = 0)
        : Combo(name), _kind(kind), _value(value), _fixedScore(fixedScore)
    {}

    Score::Kind Kind() const final { return _kind; }

    std::uint32_t Score(GameDice & dice) const final
    {
        for (Die& d : dice)
        {
            if (CountOfKind(dice, d.GetValue()) >= _value)
                return _fixedScore == 0 ? Sum(dice) : _fixedScore;
        }
        return 0;
    }

private:
    const Score::Kind _kind;
    const std::uint32_t _value;
    const std::uint32_t _fixedScore;
};

class ComboStraight : public Combo
{
public:
    ComboStraight(const char* name, Score::Kind kind, std::int32_t length, std::int32_t score)
        : Combo(name), _kind(kind), _length(length), _score(score)
    {}

    Score::Kind Kind() const final { return _kind; }

    std::uint32_t Score(GameDice& dice) const final
    {
        const Die& min = *std::min_element(dice.begin(), dice.end(),
            [](const Die& d1, const Die& d2) { return d1.GetValue() < d2.GetValue(); });

        std::uint32_t count = 0;
        for (std::uint32_t i = 0; i < _length; ++i)
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

        return count == _length ? _score : 0;
    }

private:
    const Score::Kind _kind;
    const std::uint32_t _length;
    const std::uint32_t _score;
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

class ComboChance : public Combo
{
public:
    ComboChance(const char* name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::Chance; }

    std::uint32_t Score(GameDice& dice) const final { return Sum(dice); }
};





const ComboInt aces = { "Aces", 1};
const ComboInt twos = { "Twos", 2 };
const ComboInt threes = { "Threes", 3 };
const ComboInt fours = { "Fours", 4 };
const ComboInt fives = { "Fives", 5 };
const ComboInt sixes = { "Sixes", 6 };

const ComboOfKind ofKind3 = { "3 of a Kind", Score::OfKind3, 3 };
const ComboOfKind ofKind4 = { "4 of a Kind", Score::OfKind4, 4 };
const ComboFullHouse full = { "Full House" };
const ComboStraight straightS = { "Small Straight", Score::StraightSmall, 4, 30 };
const ComboStraight straightL = { "Large Straight", Score::StraightLarge, 5, 40 };
const ComboOfKind yathzee = { "Yathzee", Score::Yahtzee, 5, 50 };
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
