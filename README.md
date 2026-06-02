# OOP-Vector

Šis projektas yra paprasta dinaminio masyvo (vektoriaus) implementacija, kurios tikslas – atkartoti bent 80% funkcionalumo, pateikto C++ standarto [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) konteineryje. Sukurta [`custm::vector`](include/Vector.hpp) klasė turi panašią sąsają ir funkcionuoja beveik identiškai standartiniam vector konteineriui.

## Turinys

- [OOP-Vector](#oop-vector)
  - [Turinys](#turinys)
  - [Instaliacija](#instaliacija)
    - [Surinkimas iš source failų per Makefile](#surinkimas-iš-source-failų-per-makefile)
    - [Instaliacija naudojant Setup.exe](#instaliacija-naudojant-setupexe)
  - [Implementuotos funkcijos](#implementuotos-funkcijos)
  - [Unit Testai](#unit-testai)
  - [Spartos analizė](#spartos-analizė)
    - [push\_back() spartos analizė](#push_back-spartos-analizė)
    - [Atminties perskirstymų analizė](#atminties-perskirstymų-analizė)
    - [`Studentas` klasės spartos analizė](#studentas-klasės-spartos-analizė)
      - [std::vector](#stdvector)
      - [custm::vector](#custmvector)
  - [Rezultatai](#rezultatai)

## Instaliacija

### Surinkimas iš source failų per Makefile

1. Atidarykite terminalą projekto šakninėje direktorijoje ir paleiskite:

   ```shell
   make
   ```

   Tai sukurs:

- build/ direktoriją
- Vector.dll ir Vector.a  
- Vienetinių testų exe (`build/unit_test.exe`)  
- Push-back spartos testų exe (`build/pushback_test.exe`)  

1. Pagrindinių programos versijų kompiliavimas:

   ```shell
   make std      # build/OOP3_std.exe       – standartinė std::vector versija  
   make custm    # build/OOP3_custm.exe     – custm::vector versija  
   make main     # abi aukščiau nurodytos versijos  
   ```

2. Spartos analizės testai:

   ```shell
   make std_test   # build/time_std.exe  
   make custm_test # build/time_custm.exe  
   ```

3. Distributable exe failas:

   ```shell
   make dist      # dist/OOP3.exe (su custm::vector)
   ```

4. Išvalymui:

   ```shell
   make clean
   ```

### Instaliacija naudojant Setup.exe

1. Atsisiųskite naujausią `Setup.exe` iš projekto GitHub Releases puslapio.  
2. Dukart spustelėkite `Setup.exe` ir sekite diegimo nurodymus.  
3. Pasirinkite diegimo katalogą (numatytasis: `C:\Program Files\VU\Adomas-Lukosevicius`).  
4. Palaukite, kol diegimas bus užbaigtas.  
5. Po diegimo bus sukurta:
   - Pradžios meniu nuoroda „OOP-Vector“,  
   - (pasirinktinai) darbalaukio nuoroda (jei pažymėjote „Create a desktop icon“).
  
**Svarbu:** Kadangi programa rašo tiesiai į `C:\Program Files`, ją būtina paleisi su administratoriaus teisėmis

## Implementuotos funkcijos

- **Default konstruktorius**  
  Inicijuoja tuščią vektorių be pradinės atminties rezervacijos.

- **Kopijavimo konstruktorius**  
  Sukuria naują vektorių, nukopijuodamas esamo objekto duomenis.

- **Perkėlimo konstruktorius**  
  Perima kito vektoriaus turinį be nereikalingų kopijų, paliekant originalą tuščią.

- **Kopijavimo priskyrimo operatorius**  
  Nukopijuoja kito vektoriaus turinį, užtikrindamas nepriklausomą naujo objekto egzistavimą.

- **Perkėlimo priskyrimo operatorius**  
  Perima kito vektoriaus turinį, atlaisvindamas senojo išteklius.

- **Destruktorius**  
  Atlaisvina dinamiškai priskirtą atmintį, užkertant kelią atminties nutekėjimui.

- **push_back(const T &value)**  
  Prideda naują elementą vektoriaus pabaigoje. Jei esama talpa pasibaigia, automatiškai didina talpą.

- **pop_back()**  
  Pašalina paskutinį elementą. Jei vektorius yra tuščias, išmeta `std::out_of_range` klaidą.

- **reserve(size_type new_cap)**  
  Rezervuoja bent nurodytą talpos dydį, perkeldamas esamus elementus į naują atminties bloką.

- **resize(size_type count)**  
  Keičia vektoriaus dydį. Jei naujas dydis yra didesnis, nauji elementai inicializuojami pagal numatytąją vertę; jei mažesnis – pertekliniai elementai pašalinami.

- **clear()**  
  Išvalo visus elementus, nenuleis talpos dydžio.

- **size() const noexcept**  
  Grąžina esamą elementų skaičių vektoriuje.

- **capacity() const noexcept**  
  Grąžina rezervuotos talpos dydį.

- **empty() const noexcept**  
  Patikrina, ar vektorius neturi jokių elementų.

- **operator[](size_type idx)**  
  Leidžia pasiekti elementą pagal indeksą be ribų tikrinimo.

- **erase(T* first, T* last)**  
  Pašalina elementų intervalą nuo `first` iki `last` (paskutinis elementas neįtraukiamas) ir grąžina iteratorių į pirmą pašalinto elemento vietą. Tai leidžia efektyviai ištrinti dalį vektoriaus elementų.

- **begin() / end()**  
  Grąžina iteratorius į atitinkamai pirmą elementą ir (paskutinio elemento + 1) poziciją, leidžiančius naudoti vektorių su standartinėmis iteratorių operacijomis, kaip – pereiti per visus elementus.

Detalesnę informaciją apie kiekvieną funkciją galite rasti [dokumentacijoje](https://adomascx.github.io/OOP-Vector/html/index.html).

## Unit Testai

- **Numatytojo konstruktoriaus testas** – Patikrina, ar naujai sukurtas vektorius yra tuščias, turi nulinį dydį ir talpą.
- **Kopijavimo konstruktoriaus testas** – Patikrina, ar kopija sukuria gilų originalo vektoriaus kloną.
- **Perkėlimo konstruktoriaus testas** – Patikrina, ar perkeliant vektorių, duomenų nuosavybė perkelta, o šaltinis paliekamas tuščias.
- **Konstruktoriaus iš intervalo testas** – Patikrina, ar vektorius teisingai sukonstruojamas iš duoto iteratorių intervalo.
- **Kopijavimo priskyrimo testas** – Patvirtina, kad vieno vektoriaus priskyrimas kitam atlieka gilą kopijavimą.
- **Perkėlimo priskyrimo testas** – Patikrina, ar perkėlimo priskyrimas perkelia duomenų nuosavybę ir tinkamai atstatoma pirminio vektoriaus būsena.
- **push_back testas** – Patvirtina, kad įdedant elementus vektoriaus dydis padidėja ir įrašomos teisingos reikšmės.
- **pop_back testas** – Patikrina, ar paskutinio elemento pašalinimas tinkamai sumažina vektoriaus dydį.
- **pop_back testas iš tuščio vektoriaus** – Patikrina, ar metamas `std::out_of_range`, kai bandoma pašalinti elementą iš tuščio vektoriaus.
- **reserve testas** – Patikrina, ar atminties rezervavimas padidina vektoriaus talpą, nekeisdamas esamo dydžio.
- **reserve testas su mažesne talpa** – Patikrina, ar kvietimas `reserve()` su nauja talpa, mažesne už esamą, nekeičia `capacity()`.
- **resize testas** – Testuoja, ar vektorius gali būti mažinamas (elementų pašalinimu) ir didinamas (nauji elementai inicijuojami numatytosiomis reikšmėmis).
- **clear testas** – Užtikrina, kad išvalius vektorių, dydis nustatomas į nulį, o rezervuota talpa išlieka nepakitusi.
- **erase vidurinio segmento testas** – Patikrina, ar šalinant intervalą viduryje, elementai teisingai persikelia.
- **erase paskutinio elemento testas** – Patikrina, ar šalinant paskutinį elementą, iteratorius grąžina `end()`, o dydis sumažėja.
- **erase viso intervalo testas** – Užtikrina, kad ištrynus visą intervalą, vektorius tampa tuščias, o iteratorius grąžina `begin()`.
- **const subscript testas** – Patikrina, ar konstantiniu kontekstu operatorius `operator[]` grąžina teisingą reikšmę.

## Spartos analizė

Atlikti `push_back()` funkcijos testai su 1 000 000, 10 000 000 ir 100 000 000 elementų. Taip pat atlikta analizė, kiek kartų įvyksta vidinis atminties perskirstymas (kai `capacity() == size()`) užpildant 100 000 000 elementų. OOP2 spartos analizės programoje [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) buvo pakeistas mūsų [`custm::vector`](include/Vector.hpp) konteineriu, o vėliau atlikta bendroji programos spartos analizė duomenų failais (100 000, 1 000 000 ir 10 000 000 studentų įrašų).

### push_back() spartos analizė

|               | 1000000 | 10000000 | 100000000 |
| ------------- | ------- | -------- | --------- |
| std::vector   | < 0.01s | 0.01s    | 0.15s     |
| custm::vector | < 0.01s | 0.02s    | 0.22s     |

### Atminties perskirstymų analizė

Testas atliktas naudojant 100 000 000 elementų dydį.

| Realizacija   | Perskirstymai |
| ------------- | ------------- |
| std::vector   | 27            |
| custm::vector | 27            |

### `Studentas` klasės spartos analizė

#### std::vector

| Testai                               | 100000  | 1000000 | 10000000 |
| ------------------------------------ | ------- | ------- | -------- |
| Duomenu nuskaitymas                  | 0.15s   | 1.47s   | 15.20s   |
| Studentų rūšiavimas                  | 0.02s   | 0.20s   | 2.42s    |
| Sudentų išskirstymas                 | < 0.01s | 0.02s   | 0.18s    |
| Išvedimas į failą                    | 0.30s   | 3.02s   | 31.24s   |
| **Bendras programos veikimo laikas** | 0.47s   | 4.71s   | 49.04s   |

#### custm::vector

| Testai                               | 100000  | 1000000 | 10000000 |
| ------------------------------------ | ------- | ------- | -------- |
| Duomenu nuskaitymas                  | 0.14s   | 1.43s   | 15.16s   |
| Studentų rūšiavimas                  | 0.02s   | 0.19s   | 2.34s    |
| Sudentų išskirstymas                 | < 0.01s | 0.09s   | 0.87s    |
| Išvedimas į failą                    | 0.30s   | 3.02s   | 30.25s   |
| **Bendras programos veikimo laikas** | 0.47s   | 4.73s   | 48.62s   |

## Rezultatai

Apibendrinant visus atliktus spartos ir atminties perskirstymų testus:

- **push_back() sparta**  
  – Mažesniuose rinkiniuose (1 000 000 ir 10 000 000 elementų) abi implementacijos veikia praktiškai vienodu greičiu (< 0.01 s / 0.01–0.02 s). Didžiausioje skalėje (100 000 000) std::vector užtruko ~0.15 s, o custm::vector ~0.22 s (~85 % std::vector spartumo).

- **Atminties perskirstymai (100 000 000 elementų)**  
  – Abu vektoriai atliko po 27 perskirstymus.

- **`Studentas` klasės sparta**  
  – Bendras vykdymo laikas (100 000 / 1 000 000 / 10 000 000):  
    • std::vector: 0.47 s / 4.71 s / 49.04 s  
    • custm::vector: 0.47 s / 4.73 s / 48.62 s  
  – custm::vector šiek tiek greitesnis duomenų nuskaityme ir rašyme, tačiau elementų išskirstymas didžiausiuose rinkiniuose (10 000 000) užtrunka ilgiau (0.87 s vs 0.18 s).

Iš viso custm::vector pasiekia >90% std::vector spartumo, su identišku atminties perskirstymo dažniu
