#pragma once

#include "main_lib.h"

/**
 * @brief Bazinė klasė, apibrėžianti asmenį.
 *
 * @details Ši klasė pateikia pagrindinę sąsają asmens informacijos gavimui bei įvedimui.
 */
class zmogus
{
protected:
    string var; ///< Asmens vardas
    string pav; ///< Asmens pavardė

public:
    /**
     * @brief Numatytasis konstruktorius.
     */
    zmogus() = default;

    /**
     * @brief Parametrizuotas konstruktorius.
     *
     * @param vardas Asmens vardas.
     * @param pavarde Asmens pavardė.
     */
    zmogus(const string &vardas, const string &pavarde) : var(vardas), pav(pavarde) {}

    /**
     * @brief Grąžina asmens vardą.
     *
     * @return string Asmens vardas.
     */
    virtual string vardas() const = 0;

    /**
     * @brief Grąžina asmens pavardę.
     *
     * @return string Asmens pavardė.
     */
    virtual string pavarde() const = 0;

    /**
     * @brief Prašo įvesti asmens vardą.
     */
    virtual void rank_vardo_ivedimas() = 0;

    /**
     * @brief Prašo įvesti asmens pažymius.
     */
    virtual void rank_paz_ivedimas() = 0;

    /**
     * @brief Virtualus destruktorius.
     */
    virtual ~zmogus() {};
};