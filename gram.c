#include <stdio.h>
#include <gtype.h>
#include <errno.h>
#include <ctype.h>

typedef enum {ER, G0, G1, G2, G3} Tipo_grammatica;

Tipo_grammatica classifica(Rule* rules);
Rule* parse_rule(FILE* f);

// G3:
// from è lungo 1 e contiene solo un metasimbolo
// to è lungo 1 o 2
// se to è lungo 1 allora contiene solo un simbolo terminale
// se to è lungo 2 allora contiene un simbolo termiale seguito da un metasimbolo

// G2:
// from è lungo 1 e contiene solo un metasimbolo
// to non è vuoto

// G1:
// from è più breve di to

Rule* parse_rule(FILE* f) {
	if (f == NULL) {
		errno = 2;
		fprintf(stderr, "(parse_rule) file not found %m");
		return NULL;
	}

	char not_in_quotes = 0, c, preceded_by_newline = 0;
	int lines_c = 0;
	
	// get number of rules (lines)
	// add checks (bug prone)
	while ((c = getc(f)) != EOF) {
		if (not_in_quotes && !preceded_by_newline) {
			if (c == '\n') {
				lines_c++;
				preceded_by_newline++;
			}
		}
		else preceded_by_newline = 0;
	}

	// allocate rules array + NULL byte
	Rule* rules = malloc(lines_c * sizeof(Rune*) + 1);;
	
	token = strtok(f, " ");

	while (token != NULL) {
		// ...
		token = strtok(NULL, s);
	}
	
	rules[lines_c] = NULL;


	
}


Tipo_grammatica classifica(Rule* rules) {
	Tipo_grammatica tipo = G3;

	int rule_c, from_c, to_c;
	
	for (rule_c = 0; rules[rule_c] != NULL; rule_c++) {
		for (from_c = 0; (rules[rule_c] -> from)[from_c] != NULL; from_c++) {
			if ((tipo == G2 || tipo == G2) && !((rules[rule_c] -> from)[from_c] -> is_metasymbol))
				tipo = G1;
		}
		
		for (to_c = 0; (rules[rule_c] -> to)[to_c] != NULL; to_c++);

		switch (tipo) {
			case G3:
				// len from == 1 e to è non vuoto
				// oppure from è formato solo da metasiboli
				if ((from_c != 1 || to_c < 1) ||
				     (!((rules[rule_c] -> from)[0] -> is_metasymbol))) tipo = G1;			
				// to non supera i due simboli oppure
				// il primo simbolo di to è sempre un simbolo terminale
				// e se to è lungo 2 allora contiene un simbolo termiale seguito da un metasimbolo
				else if ((to_c > 2) ||
				     (to_c >= 1 && ((rules[rule_c] -> to)[0] -> is_metasymbol)
				     && (!to_c == 2 ||  !((rules[rule_c] -> to)[1] -> is_metasymbol)))) tipo = G2;
				else break;
			case G2:
				if ((from_c > 1 || to_c < 1) ||
				     !((rules[rule_c] -> from)[0] -> is_metasymbol)) tipo = G0;
				else break;
			case G1:
				if (from_c >= to_c) tipo = G0;
				else break;
			default:
				tipo = G0;
		}
	}

	return tipo;
}


