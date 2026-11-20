
#pragma once

#include <cstdint>

#include "stats.hpp"
#include "stat_alignment.hpp"
#include "stat_alignment_data.hpp"
#include "individual_pokemon.hpp"

namespace pokemon
{
    enum class BattleStat : std::uint8_t
    {
        HP,
        Attack,
        Defense,
        SpecialAttack,
        SpecialDefense,
        Speed
    };

    constexpr std::uint16_t getBaseStat(
        const Stats &stats,
        BattleStat stat)
    {
        switch (stat)
        {
        case BattleStat::HP:
            return stats.hp;

        case BattleStat::Attack:
            return stats.attack;

        case BattleStat::Defense:
            return stats.defense;

        case BattleStat::SpecialAttack:
            return stats.specialAttack;

        case BattleStat::SpecialDefense:
            return stats.specialDefense;

        case BattleStat::Speed:
            return stats.speed;
        }

        return 0;
    }

    constexpr std::uint16_t calculateHP(
        std::uint16_t baseHP,
        std::uint8_t hpSP)
    {
        return baseHP + hpSP + 75;
    }

    constexpr std::uint16_t calculateOtherStat(
        std::uint16_t baseStat,
        std::uint8_t statSP,
        float alignmentMultiplier)
    {
        const float rawStat = static_cast<float>(baseStat + statSP + 20);

        return static_cast<std::uint16_t>(
            rawStat * alignmentMultiplier);
    }

    constexpr float getAlignmentMultiplier(
        const StatAlignment &alignment,
        Stat stat)
    {
        if (alignment.increasedStat == stat)
        {
            return alignment.increasedMultiplier;
        }

        if (alignment.decreasedStat == stat)
        {
            return alignment.decreasedMultiplier;
        }

        return 1.0f;
    }

    constexpr std::uint16_t calculateAlignedStat(
        std::uint16_t baseStat,
        std::uint8_t statSP,
        const StatAlignment &alignment,
        Stat stat)
    {
        const float multiplier =
            getAlignmentMultiplier(alignment, stat);

        return calculateOtherStat(
            baseStat,
            statSP,
            multiplier);
    }

    constexpr Stats calculateBattleStats(
        const IndividualPokemon &pokemon)
    {
        const Stats &base = pokemon.species->baseStats;

        const StatAlignment alignment =
            getStatAlignment(pokemon.alignment);

        return {
            calculateHP(base.hp, pokemon.statPoints.hp),

            calculateAlignedStat(
                base.attack,
                pokemon.statPoints.attack,
                alignment,
                Stat::Attack),

            calculateAlignedStat(
                base.defense,
                pokemon.statPoints.defense,
                alignment,
                Stat::Defense),

            calculateAlignedStat(
                base.specialAttack,
                pokemon.statPoints.specialAttack,
                alignment,
                Stat::SpecialAttack),

            calculateAlignedStat(
                base.specialDefense,
                pokemon.statPoints.specialDefense,
                alignment,
                Stat::SpecialDefense),

            calculateAlignedStat(
                base.speed,
                pokemon.statPoints.speed,
                alignment,
                Stat::Speed)};
    }
}
