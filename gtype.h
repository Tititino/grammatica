#ifndef TYPES_H
#define TYPES_H



typedef unsigned int Metasymbol;
typedef unsigned int Symbol;
typedef unsigned int State;

typedef struct {
	unsigned int is_metasymbol : 1;	// type (M (metasymbol) | S (symbol))
	union {
		Metasymbol m;
		Symbol s;
	} value;
}* Token;

typedef struct {
	Symbol* sigma;
	size_t len_sigma;
	State* stati;
	size_t len_stati;
	State init;
	(State) (*delta) (State, Symbol);
	(State) (*lambda) (int);
}* Automa;

/**
  * Invariante di rappresentazione:
  * \begin{align*}
      from \neq NULL \\
      to \neq NULL \\
      from \neq [] \\
      to \neq [] \\
      \forall x \in from (x \in \Sigma \vee x \in M) \\
      \forall x \in to (x \in \Sigma \vee x \in M)
    \end{align*}
  * Funzione d'astrazione:
  * <from> ::= <to> (id)
  * a token is ended by NULL
  */
typedef struct {
	int id;
	Token* from;
	Token* to;
}* Rule;


typedef struct {
	Symbol* sigma;
	size_t len_sigma;
	Metasymbol assioma;
	Metasymbol* meta;
	size_t len_meta;
	Rune* regole;
}* Definition;

int check_definition(Definition);

#endif

