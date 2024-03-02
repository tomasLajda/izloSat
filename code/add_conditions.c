#include <stddef.h>
#include "cnf.h"

//
// LOGIN: xlajdat00
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street* streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    // pre kazdy krok
    for (unsigned i = 0; i < num_of_streets; ++i) {
        Clause* cl = create_new_clause(formula);
        // existujuca ulica
        for (unsigned j = 0; j < num_of_streets; ++j) {
            add_literal_to_clause(cl, true, i, streets[j].crossroad_from, streets[j].crossroad_to);
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void at_most_one_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // pre kazdy krok
    for (unsigned i = 0; i < num_of_streets; ++i) {
        // zaciatok prvej ulice
        for (unsigned j = 0; j < num_of_crossroads; ++j) {
            // koniec prvej ulice
            for (unsigned k = 0; k < num_of_crossroads; ++k) {
                // zaciatok druhej ulice
                for (unsigned l = 0; l < num_of_crossroads; ++l) {
                    // koniec druhej ulice
                    for (unsigned m = 0; m < num_of_crossroads; ++m) {
                        // ulice sa nesmu rovnat
                        if (j == l && k == m){
                            continue;
                        }
                    
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, j, k);
                        add_literal_to_clause(cl, false, i, l, m);
                    }
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // pre kazdy krok
    for (unsigned i = 0; i < num_of_streets; ++i) {
        // zaciatok prvej ulice
        for (unsigned j = 0; j < num_of_crossroads; ++j) {
            // spojenie dvoch ulic
            for (unsigned k = 0; k < num_of_crossroads; ++k) {
                Clause* cl = create_new_clause(formula);
                add_literal_to_clause(cl, false, i, j, k);

                // koniec ulice
                for (unsigned l = 0; l < num_of_crossroads; ++l) {
                    add_literal_to_clause(cl, true, i+1, k, l);
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    
    for (unsigned i = 0; i < num_of_streets; ++i) {
        // pro kazdy krok i
        for (unsigned j = 0; j < num_of_streets; ++j) {
            if (i != j) {
                // pro kazdy jiny krok j
                for (unsigned z = 0; z < num_of_crossroads; ++z) {
                    for (unsigned k = 0; k < num_of_crossroads; ++k) {
                        // pro kazdu dvojici krizovatek (z, k)
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, j, z, k);
                    }
                }
            }
        }
    }
}
