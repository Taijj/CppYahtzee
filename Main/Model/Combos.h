#pragma once

#include <cstdint>
#include <array>
#include <algorithm>
#include <numeric>

#include "Rules.h"



class Combo
{
public:

    using uInt = std::uint32_t;
    using RolledValues = std::array<uInt, Rules::DIE_COUNT>;

    enum ComboKind
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


    
    Combo(const char* name) : _name(name)
    {}

    ~Combo() = default;

    const char* Name() const
    {
        return _name;
    }            
    


    virtual ComboKind Kind() const = 0;
    virtual uInt Score(RolledValues& values) const = 0;
    virtual uInt MaxPossibleScore() const = 0;



    static uInt CountIn(uInt value, RolledValues& values)
    {
        auto count = std::count_if(values.begin(), values.end(),
            [value](const uInt& v) { return v == value; });
        return static_cast<uInt>(count);
    }

    static uInt SumUp(RolledValues& values)
    {
        return std::accumulate(values.begin(), values.end(), 0);
    }

private:
    const char* _name;
};



class ComboFace : public Combo
{
public:
    ComboFace(const char* name, uInt value) : Combo(name)
    {
        _value = std::clamp(value, 1U, Rules::DIE_SIDES);
    }

    ComboKind Kind() const final { return static_cast<ComboKind>(_value); }

    uInt Score(RolledValues& values) const final
    {
        return CountIn(_value, values) * _value;
    }

    uInt MaxPossibleScore() const final { return _value * Rules::DIE_COUNT; }

private:
    uInt _value;
};

class ComboOfKind : public Combo
{
public:
    ComboOfKind(const char* name, ComboKind kind, uInt value, uInt fixedScore = 0)
        : Combo(name), _kind(kind), _value(value), _fixedScore(fixedScore)
    {}

    ComboKind Kind() const final { return _kind; }

    uInt Score(RolledValues& values) const final
    {
        for (uInt v : values)
        {
            if (CountIn(v, values) >= _value)
                return _fixedScore == 0 ? SumUp(values) : _fixedScore;
        }
        return 0;
    }

    uInt MaxPossibleScore() const final
    {
        return _fixedScore == 0
            ? _value * Rules::DIE_COUNT
            : _fixedScore;
    }

private:
    const ComboKind _kind;
    const uInt _value;
    const uInt _fixedScore;
};

class ComboStraight : public Combo
{
public:
    ComboStraight(const char* name, ComboKind kind, uInt length, uInt score)
        : Combo(name), _kind(kind), _length(length), _score(score)
    {}

    ComboKind Kind() const final { return _kind; }

    uInt Score(RolledValues& values) const final
    {
        const uInt min = *std::min(values.begin(), values.end());

        uInt count = 0;
        for (uInt i = 0; i < _length; ++i)
        {
            for (uInt v : values)
            {
                if (v == min + i)
                {
                    count++;
                    break;
                }
            }
        }

        return count == _length ? _score : 0;
    }

    uInt MaxPossibleScore() const final { return _score; }

private:
    const ComboKind _kind;
    const uInt _length;
    const uInt _score;
};



class ComboFullHouse : public Combo
{
public:
    ComboFullHouse(const char* name) : Combo(name)
    {}

    ComboKind Kind() const final { return FullHouse; }

    uInt Score(RolledValues& values) const final
    {
        bool found3 = false;
        bool found2 = false;
        for (uInt v : values)
        {
            const uInt count = CountIn(v, values);
            if (count == 2 && !found2)
                found2 = true;

            if (count == 3 && !found3)
                found3 = true;            
        }

        return found2 && found3 ? SCORE : 0;
    }    

    uInt MaxPossibleScore() const final { return SCORE; }

private:
    inline static constexpr uInt SCORE = 25;
};

class ComboChance : public Combo
{
public:
    ComboChance(const char* name) : Combo(name)
    {}

    ComboKind Kind() const final { return Chance; }

    uInt Score(RolledValues& values) const final { return SumUp(values); }

    uInt MaxPossibleScore() const final { return Rules::DIE_COUNT * Rules::DIE_SIDES; }
};