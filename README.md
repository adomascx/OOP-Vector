# OOP-Vector

Šis projektas yra paprasta dinaminio masyvo (vektoriaus) implementacija, kurios tikslas – atkartoti bent 80% funkcionalumo, pateikto C++ standarto [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) konteineryje. Mūsų sukurta `Vector` klasė turi panašią sąsają ir elgiasi beveik identiškai kaip standartinis konteineris.

## Turinys

- [OOP-Vector](#oop-vector)
  - [Turinys](#turinys)
  - [Instaliacija](#instaliacija)
  - [Implementuotos funkcijos](#implementuotos-funkcijos)
  - [Unit Testai](#unit-testai)
  - [Spartos analizė](#spartos-analizė)
    - [push\_back() spartos analizė](#push_back-spartos-analizė)
    - [Atminties perskirstymų analizė](#atminties-perskirstymų-analizė)
    - [OOP2 spartos analizė](#oop2-spartos-analizė)
  - [Trečiasis darbas](#trečiasis-darbas)
  - [Pastabos](#pastabos)

## Instaliacija

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

## Unit Testai

- **Numatytojo konstruktoriaus testas** – Patikrina, ar naujai sukurtas vektorius yra tuščias, turi nulinį dydį ir talpą.
- **Kopijavimo konstruktoriaus testas** – Patikrina, ar kopija sukuria gilų originalo vektoriaus kloną.
- **Perkėlimo konstruktoriaus testas** – Patikrina, ar perkeliant vektorių, duomenų nuosavybė perkelta, o šaltinis paliekamas tuščias.
- **Kopijavimo priskyrimo testas** – Patvirtina, kad vieno vektoriaus priskyrimas kitam atlieka gilą kopijavimą.
- **Perkėlimo priskyrimo testas** – Patikrina, ar perkėlimo priskyrimas perkelia duomenų nuosavybę ir tinkamai atstatoma pirminio vektoriaus būsena.
- **push_back testas** – Patvirtina, kad įdedant elementus vektoriaus dydis padidėja ir įrašomos teisingos reikšmės.
- **pop_back testas** – Patikrina, ar paskutinio elemento pašalinimas tinkamai sumažina vektoriaus dydį.
- **reserve testas** – Patikrina, ar atminties rezervavimas padidina vektoriaus talpą, nekeisdamas esamo dydžio.
- **resize testas** – Testuoja, ar vektorius gali būti sumažintas (elementų pašalinimu) ir padidintas (nauji elementai inicijuojami numatytosiomis reikšmėmis).
- **clear testas** – Užtikrina, kad išvalius vektorių, dydis nustatomas į nulį, o rezervuota talpa išlieka nepakitusi.

## Spartos analizė

Atlikti `push_back()` funkcijos testai su 1 000 000, 10 000 000 ir 100 000 000 elementų. Taip pat atlikta analizė, kiek kartų įvyksta vidinis atminties perskirstymas (kai `capacity() == size()`) užpildant 100 000 000 elementų. OOP2 programoje [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) buvo pakeistas mūsų [`Vector`](c:\Users\Administrator\source\repos\C++\OOP-Vector\include\Vector.hpp) konteineriu, o vėliau atlikta bendroji programos spartos analizė duomenų failais (100 000, 1 000 000 ir 10 000 000 studentų įrašų).

### push_back() spartos analizė

|             | 1000000 | 10000000 | 100000000 |
| ----------- | ------- | -------- | --------- |
| std::vector | < 0.01s | 0.08s    | 0.52s     |
| Vector      | < 0.01s | 0.07s    | 0.66s     |

### Atminties perskirstymų analizė

| Realizacija | Perskirstymai |
| ----------- | ------------- |
| std::vector | 27            |
| Vector      | 27            |

### OOP2 spartos analizė



## Trečiasis darbas

Trečiojo darbo programoje vietoje [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) naudojamas mūsų sukurtas `Vector`, siekiant užtikrinti pilną funkcionalumą ir spartą. Tai patikrina, ar mūsų implementacija veikia teisingai realiomis sąlygomis.

## Pastabos

Šis dokumentas yra gyvas, todėl ateityje bus įtraukiama papildoma informacija:

- Išsamesnė funkcijų aprašymo dokumentacija.
- Detalesnė spartos analizės ataskaita ir lentelės.
- Papildomi pavyzdžiai ir rezultatai.

---

Prašome papildomai atnaujinti šį README.md failą, kai bus parengta nauja informacija.
