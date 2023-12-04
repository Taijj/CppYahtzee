#pragma once

#include <cstdint>
#include <array>
#include <algorithm>
#include <numeric>

#include "../Global/Rules.h"
#include "../Global/ScoreKinds.h"



/// <summary>
/// Base class for all achieveable Combos in the game.
/// 
/// Concepts:
///     Roll - The result of one throw of all game dice in an array of face values
///     Face - The value of the showing up side of a die
/// </summary>
class Combo
{
public:

    using uInt = std::uint32_t;
    using Roll = std::array<uInt, Rules::DIE_COUNT>;
    

    
    Combo(const std::string name) : _name(name)
    {}

    ~Combo() = default;

    const std::string Name() const
    {
        return _name;
    }            
    


    virtual Score::Kind Kind() const = 0;

    /// <summary>
    /// Returns the score the given roll would achieve.
    /// </summary>
    virtual uInt Score(Roll& roll) const = 0;

    /// <summary>
    /// Returns the highest score that could be achieved,
    /// with a perfect Roll for this Combo.
    /// </summary>
    virtual uInt MaxPossibleScore() const = 0;



    /// <summary>
    /// Counts how often the given face occurs in the given roll.
    /// </summary>
    static uInt CountIn(uInt face, Roll& roll)
    {
        auto count = std::count_if(roll.begin(), roll.end(),
            [face](const uInt& f) { return f == face; });
        return static_cast<uInt>(count);
    }

    /// <summary>
    /// Returns the sum of all faces in the given roll.
    /// </summary>
    static uInt SumUp(Roll& roll)
    {
        return std::accumulate(roll.begin(), roll.end(), 0);
    }

private:
    const std::string _name;
};



/// <summary>
/// Used for Combos that count the number of same faces, e.g. Aces
/// "Face": One side of a die showing a certain number of dots.
/// </summary>
class ComboFace : public Combo
{
public:
    ComboFace(const std::string name, uInt face) : Combo(name)
    {
        _face = std::clamp(face, 1U, Rules::DIE_SIDES);
    }

    Score::Kind Kind() const final { return static_cast<Score::Kind>(_face); }

    uInt Score(Roll& roll) const final
    {
        return CountIn(_face, roll) * _face;
    }

    uInt MaxPossibleScore() const final { return _face * Rules::DIE_COUNT; }

private:
    uInt _face;
};

/// <summary>
/// Used for Combos that require a certain number of same faces in a roll, e.g. 4 of a Kind, Yahtzee
/// </summary>
class ComboOfKind : public Combo
{
public:

    /// <summary>
    /// If the fixedScore parameter is not 0, it will be used as the score achievable
    /// by this Combo, otherwise the score will be the sum of all throw faces.
    /// </summary>
    ComboOfKind(const std::string name, Score::Kind kind, uInt count, uInt fixedScore = 0)
        : Combo(name), _kind(kind), _count(count), _fixedScore(fixedScore)
    {}

    Score::Kind Kind() const final { return _kind; }

    uInt Score(Roll& roll) const final
    {
        for (uInt f : roll)
        {
            if (CountIn(f, roll) >= _count)
                return _fixedScore == 0 ? SumUp(roll) : _fixedScore;
        }
        return 0;
    }

    uInt MaxPossibleScore() const final
    {
        return _fixedScore == 0
            ? Rules::DIE_SIDES * Rules::DIE_COUNT
            : _fixedScore;
    }

private:
    const Score::Kind _kind;
    const uInt _count;
    const uInt _fixedScore;
};

/// <summary>
/// Used for straight Combos, e.g. Large Straight
/// </summary>
class ComboStraight : public Combo
{
public:
    ComboStraight(const std::string name, Score::Kind kind, uInt length, uInt score)
        : Combo(name), _kind(kind), _length(length), _score(score)
    {}

    Score::Kind Kind() const final { return _kind; }

    uInt Score(Roll& roll) const final
    {
        const uInt min = *std::min(roll.begin(), roll.end());

        uInt count = 0;
        for (uInt i = 0; i < _length; ++i)
        {
            for (uInt f : roll)
            {
                if (f == min + i)
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
    const Score::Kind _kind;
    const uInt _length;
    const uInt _score;
};



/// <summary>
/// A Combo implementing the logic for a Full House
/// </summary>
class ComboFullHouse : public Combo
{
public:
    ComboFullHouse(const std::string name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::FullHouse; }

    uInt Score(Roll& roll) const final
    {
        bool found3 = false;
        bool found2 = false;
        for (uInt f : roll)
        {
            const uInt count = CountIn(f, roll);
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

/// <summary>
/// A Combo implementing the logic for a Chance.
/// </summary>
class ComboChance : public Combo
{
public:
    ComboChance(const std::string name) : Combo(name)
    {}

    Score::Kind Kind() const final { return Score::Chance; }

    uInt Score(Roll& roll) const final { return SumUp(roll); }

    uInt MaxPossibleScore() const final { return Rules::DIE_COUNT * Rules::DIE_SIDES; }
};