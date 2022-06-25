typedef unsigned int Metasymbol;
typedef unsigned int Symbol;
typedef unsigned int State;

typedef struct {
	unsigned int t : 1;	// type (M (metasymbol) | S (symbol))
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
  * \struct 
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
	Rule* regole;
	size_t len_regole;
}* Definition;

/**
  * Rep. invariant:
  *
  *
  *
  */
int check_definition(Definition d) {

	int i, a; b = 1;

	b &= (d -> len_sigma) & (d -> len_meta) & (d -> len_regole);

	for (i = 0, a = 0; i < d -> len_meta; i++)
		if ((d -> meta)[i] == (d -> assioma)) a++;

	b &= (a == 1);

	b &= ((d -> sigma)[len_sigma - 1] == (len_sigma - 1)) & ((d -> meta)[len_meta - 1] == (len_meta - 1))
	
	return b;
}
