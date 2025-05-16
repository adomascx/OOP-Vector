#pragma once

#include "zmogus.h"

/**
 * @brief 'studentas' klasė, paveldinti iš klasės zmogus.
 */
class studentas : public zmogus
{
private:
    vector<int> paz;
    int egz;
    double galutinisVid;
    double galutinisMed;

public:
    // Konstruktoriai

    /**
     * @brief Numatytasis 'studentas' klasės konstruktorius.
     */
    studentas();

    /**
     * @brief Parametrizuotas 'studentas' konstruktorius.
     *
     * @param vardas Studento vardas.
     * @param pavarde Studento pavardė.
     * @param paz Vektorius, turintis studento namų darbų pažymius.
     * @param egzaminas Egzamino pažymys.
     */
    studentas(const string &vardas, const string &pavarde, const vector<int> &paz, const int &egzaminas);

    /**
     * @brief Konstruktorius, naudojant įvesties srautą.
     *
     * @param is Įvesties srautas, iš kurio skaitomi studento duomenys.
     * @param nd_count Laukiamas namų darbų pažymių skaičius.
     */
    studentas(istream &is, int nd_count);

    /**
     * @brief Copy konstruktorius.
     *
     * @param other Reference į 'studentas' objektą, kurį reikia kopijuoti.
     */
    studentas(const studentas &other);

    /**
     * @brief Move konstruktorius.
     *
     * @param other Rvalue reference į 'studentas' objektą, kurį reikia perkelti.
     */
    studentas(studentas &&other) noexcept;

    // Operatoriai

    /**
     * @brief Copy priskyrimo operatorius.
     *
     * @param other Reference į 'studentas' objektą, kurį reikia kopijuoti.
     * @return studentas& Reference į priskirtą objektą.
     */
    studentas &operator=(const studentas &other);

    /**
     * @brief Move priskyrimo operatorius.
     *
     * @param other Rvalue reference į 'studentas' objektą, kurį reikia perkelti.
     * @return studentas& Reference į priskirtą objektą.
     */
    studentas &operator=(studentas &&other) noexcept;

    /**
     * @brief 'studentas' klasės destruktorius.
     */
    ~studentas();

    // Getteriai

    string vardas() const { return var; }
    string pavarde() const { return pav; }
    double galutinis_vidurkis() const { return galutinisVid; }
    double galutinis_mediana() const { return galutinisMed; }

    // Setteriai

    /**
     * @brief Nuskaito studento namų darbų pažymius iš įvesties srauto.
     *
     * @param is Įvesties srautas.
     * @param nd_count Namų darbų pažymių skaičius, kuriuos reikia nuskaityti.
     * @return istream& Įvesties srauto reference.
     */
    istream &paz_ivedimas(istream &is, int nd_count);

    /**
     * @brief Perkrautas '>>' operatorius studento duomenų skaitymui.
     *
     * @param is Įvesties srautas.
     * @param s Reference į 'studentas' objektą.
     * @return istream& Įvesties srauto reference.
     */
    friend istream &operator>>(istream &is, studentas &s);

    /**
     * @brief Perkrautas '<<' operatorius studento duomenų išvedimui.
     *
     * @param os Išvesties srautas.
     * @param s Const reference į 'studentas' objektą.
     * @return ostream& Išvesties srauto reference.
     */
    friend ostream &operator<<(ostream &os, const studentas &s);

    /**
     * @brief Pateikia prašymą įvesti studento vardą ir pavardę.
     */
    void rank_vardo_ivedimas();

    /**
     * @brief Pateikia prašymą įvesti studento pažymius ir egzamino pažymį.
     */
    void rank_paz_ivedimas();

    /**
     * @brief Generuoja atsitiktinius studento namų darbų pažymius bei egzamino pažymį.
     */
    void gen_paz();

    /**
     * @brief Apskaičiuoja galutinį pažymį, remiantis studento namų darbų pažymių vidurkiu ir egzamino pažymiu.
     */
    void calc_gal_vidurkis();

    /**
     * @brief Apskaičiuoja galutinį pažymį, remiantis studento namų darbų pažymių mediana ir egzamino pažymiu.
     */
    void calc_gal_mediana();
};

/**
 * @brief Nuskaito studento duomenis iš įvesties failo srauto.
 *
 * Pirmoje eilutėje surašomi stulpelių pavadinimai, iš kurių nustatomas namų darbų pažymių skaičius (nd_count).
 *
 * @param grupe Vektorius 'studentas' objektų, kurie bus užpildyti.
 * @param is Įvesties srautas, iš kurio skaitomi duomenys.
 */
void failo_ivedimas(vector<studentas> &grupe, istream &is);

/**
 * @brief Išskiria studentus į dvi grupes, remiantis jų galutiniu pažymiu.
 *
 * Studentai, kurių galutinis pažymys (vidurkis) yra mažesnis nei 5, laikomi kartotojais, o likę – išlaikytojais.
 *
 * @param grupe Nuolatinė reference į 'studentas' objektų vektorių.
 */
void stud_isskirstymas(const vector<studentas> &grupe);