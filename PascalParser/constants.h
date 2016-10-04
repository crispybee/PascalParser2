
#include "GoldCPP\MIMParser.h"
#include "GoldCPP\Parser.h"
#include <stdexcept>
#include <iostream>
#ifdef __GNUC__
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED
#endif

namespace GoldCPP{
	enum ProductionConstants
	{
		PROD_PROGRAM_PROGRAM_VARIABLE_SEMI         =  0, // <Program> ::= program variable ';' <Deklarationsteil> <Anweisungsteil>
		PROD_DEKLARATIONSTEIL                      =  1, // <Deklarationsteil> ::= <Deklarationsteil> <Varblock>
		PROD_DEKLARATIONSTEIL2                     =  2, // <Deklarationsteil> ::= <Varblock>
		PROD_VARBLOCK_VAR                          =  3, // <Varblock> ::= var <Deklarationslisten>
		PROD_DEKLARATIONSLISTEN                    =  4, // <Deklarationslisten> ::= <Deklarationslisten> <Deklarationsliste>
		PROD_DEKLARATIONSLISTEN2                   =  5, // <Deklarationslisten> ::= <Deklarationsliste>
		PROD_DEKLARATIONSLISTE_VARIABLE_COMMA      =  6, // <Deklarationsliste> ::= variable ',' <Deklarationsliste>
		PROD_DEKLARATIONSLISTE_VARIABLE_COLON_SEMI =  7, // <Deklarationsliste> ::= variable ':' <Typ> ';'
		PROD_TYP_INTEGER                           =  8, // <Typ> ::= integer
		PROD_TYP_REAL                              =  9, // <Typ> ::= real
		PROD_ANWEISUNGSTEIL_BEGIN_SEMI_ENDDOT      = 10, // <Anweisungsteil> ::= begin <Anweisungen> ';' 'end.'
		PROD_ANWEISUNGEN_SEMI                      = 11, // <Anweisungen> ::= <Anweisungen> ';' <Anweisung>
		PROD_ANWEISUNGEN                           = 12, // <Anweisungen> ::= <Anweisung>
		PROD_ANWEISUNG                             = 13, // <Anweisung> ::= <Zuweisung>
		PROD_ANWEISUNG2                            = 14, // <Anweisung> ::= <if-Anweisung>
		PROD_ANWEISUNG3                            = 15, // <Anweisung> ::= <if-else-Anweisung>
		PROD_ANWEISUNG4                            = 16, // <Anweisung> ::= <while-Anweisung>
		PROD_ANWEISUNG5                            = 17, // <Anweisung> ::= <repeat-Anweisung>
		PROD_ANWEISUNG6                            = 18, // <Anweisung> ::= <for-Anweisung>
		PROD_ANWEISUNG_BEGIN_SEMI_END              = 19, // <Anweisung> ::= begin <Anweisungen> ';' end
		PROD_ZUWEISUNG_VARIABLE_COLONEQ            = 20, // <Zuweisung> ::= variable ':=' <Ausdruck>
		PROD_AUSDRUCK_EQ                           = 21, // <Ausdruck> ::= <Ausdruck> '=' <pm-Term>
		PROD_AUSDRUCK_LT                           = 22, // <Ausdruck> ::= <Ausdruck> '<' <pm-Term>
		PROD_AUSDRUCK_GT                           = 23, // <Ausdruck> ::= <Ausdruck> '>' <pm-Term>
		PROD_AUSDRUCK                              = 24, // <Ausdruck> ::= <pm-Term>
		PROD_PMTERM_PLUS                           = 25, // <pm-Term> ::= <pm-Term> '+' <md-Term>
		PROD_PMTERM_MINUS                          = 26, // <pm-Term> ::= <pm-Term> '-' <md-Term>
		PROD_PMTERM                                = 27, // <pm-Term> ::= <md-Term>
		PROD_MDTERM_TIMES                          = 28, // <md-Term> ::= <md-Term> '*' <pot-Term>
		PROD_MDTERM_DIV                            = 29, // <md-Term> ::= <md-Term> '/' <pot-Term>
		PROD_MDTERM                                = 30, // <md-Term> ::= <pot-Term>
		PROD_POTTERM_CARET                         = 31, // <pot-Term> ::= <Faktor> '^' <pot-Term>
		PROD_POTTERM                               = 32, // <pot-Term> ::= <Faktor>
		PROD_FAKTOR_KONSTANTE                      = 33, // <Faktor> ::= konstante
		PROD_FAKTOR_VARIABLE                       = 34, // <Faktor> ::= variable
		PROD_FAKTOR_LPAREN_RPAREN                  = 35, // <Faktor> ::= '(' <Ausdruck> ')'
		PROD_IFANWEISUNG                           = 36, // <if-Anweisung> ::= <if-Anfang> <Anweisung>
		PROD_IFANFANG_IF_THEN                      = 37, // <if-Anfang> ::= if <Ausdruck> then
		PROD_IFELSEMITTE_ELSE                      = 38, // <if-else-Mitte> ::= <if-Anfang> <Anweisung> else
		PROD_IFELSEANWEISUNG                       = 39, // <if-else-Anweisung> ::= <if-else-Mitte> <Anweisung>
		PROD_WHILEANFANG_WHILE                     = 40, // <while-Anfang> ::= while
		PROD_WHILEMITTE_DO                         = 41, // <while-Mitte> ::= <while-Anfang> <Ausdruck> do
		PROD_WHILEANWEISUNG                        = 42, // <while-Anweisung> ::= <while-Mitte> <Anweisung>
		PROD_REPEATANFANG_REPEAT                   = 43, // <repeat-Anfang> ::= repeat
		PROD_REPEATANWEISUNG_SEMI_UNTIL            = 44, // <repeat-Anweisung> ::= <repeat-Anfang> <Anweisungen> ';' until <Ausdruck>
		PROD_FORANFANG_FOR_TO_DO                   = 45, // <for-Anfang> ::= for <Zuweisung> to <Ausdruck> do
		PROD_FORANWEISUNG                          = 46  // <for-Anweisung> ::= <for-Anfang> <Anweisung>
	};
}
	
