#include "lib/studentas.h"
#include "lib/isvedimas.h"

int main(int argc, char *argv[])
{
    srand(69420);
    vector<studentas> grupe;

    ar_skaiciuoti_laika = true;
    int dydis;
    string gen_file;

    /*
    Argumentai:
    1. Failo dydis
    3. Failo generavimo pasirinkimas (1/0)
    */

    switch (argc)
    {
    case 2:
        dydis = atoi(argv[1]);
        break;

    case 3:

        dydis = atoi(argv[1]);

        if (string(argv[2]) == "1")
        {
            gen_file = "txt/studentai" + to_string(dydis) + ".txt";
            failo_generavimas(gen_file, 10, dydis);
        }
        break;

    default:
        cout << "Iveskite failo dydi: ";
        cin >> dydis;
        cout << endl;
        break;
    }

    gen_file = "txt/studentai" + to_string(dydis) + ".txt";
    cout << endl
         << "filesize: " << dydis;

    ifstream fd(gen_file);
    failo_ivedimas(grupe, fd);
    fd.close();

    char choice_mediana = 'y';

    for (auto &stud : grupe)
    {
        stud.calc_gal_vidurkis();
        if (choice_mediana == 'y')
            stud.calc_gal_mediana();
    }

    stud_isskirstymas(grupe);
}
