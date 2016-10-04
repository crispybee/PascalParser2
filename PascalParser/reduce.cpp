#include <stdexcept>
#include <iostream>
#include "GoldCPP\MIMParser.h"
#include "GoldCPP\Parser.h"
#include "constants.h"

#ifdef __GNUC__
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED
#endif

namespace GoldCPP{
	std::shared_ptr<Reduction> MIMParser::Reduce(MIMParser UNUSED *parser, const std::shared_ptr<Reduction> &reduction)
	{
		switch(reduction->Parent->TableIndex){
			// <Program> ::= program variable ';' <Deklarationsteil> <Anweisungsteil>
			case PROD_PROGRAM_PROGRAM_VARIABLE_SEMI: 
			break;
			// <Deklarationsteil> ::= <Deklarationsteil> <Varblock>
			case PROD_DEKLARATIONSTEIL: 
			break;
			// <Deklarationsteil> ::= <Varblock>
			case PROD_DEKLARATIONSTEIL2: 
			break;
			// <Varblock> ::= var <Deklarationslisten>
			case PROD_VARBLOCK_VAR: 
			break;
			// <Deklarationslisten> ::= <Deklarationslisten> <Deklarationsliste>
			case PROD_DEKLARATIONSLISTEN: 
			break;
			// <Deklarationslisten> ::= <Deklarationsliste>
			case PROD_DEKLARATIONSLISTEN2: 
			break;
			// <Deklarationsliste> ::= variable ',' <Deklarationsliste>
			case PROD_DEKLARATIONSLISTE_VARIABLE_COMMA: 
			break;
			// <Deklarationsliste> ::= variable ':' <Typ> ';'
			case PROD_DEKLARATIONSLISTE_VARIABLE_COLON_SEMI: 
			break;
			// <Typ> ::= integer
			case PROD_TYP_INTEGER: 
			break;
			// <Typ> ::= real
			case PROD_TYP_REAL: 
			break;
			// <Anweisungsteil> ::= begin <Anweisungen> ';' 'end.'
			case PROD_ANWEISUNGSTEIL_BEGIN_SEMI_ENDDOT: 
			break;
			// <Anweisungen> ::= <Anweisungen> ';' <Anweisung>
			case PROD_ANWEISUNGEN_SEMI: 
			break;
			// <Anweisungen> ::= <Anweisung>
			case PROD_ANWEISUNGEN: 
			break;
			// <Anweisung> ::= <Zuweisung>
			case PROD_ANWEISUNG: 
			break;
			// <Anweisung> ::= <if-Anweisung>
			case PROD_ANWEISUNG2: 
			break;
			// <Anweisung> ::= <if-else-Anweisung>
			case PROD_ANWEISUNG3: 
			break;
			// <Anweisung> ::= <while-Anweisung>
			case PROD_ANWEISUNG4: 
			break;
			// <Anweisung> ::= <repeat-Anweisung>
			case PROD_ANWEISUNG5: 
			break;
			// <Anweisung> ::= <for-Anweisung>
			case PROD_ANWEISUNG6: 
			break;
			// <Anweisung> ::= begin <Anweisungen> ';' end
			case PROD_ANWEISUNG_BEGIN_SEMI_END: 
			break;
			// <Zuweisung> ::= variable ':=' <Ausdruck>
			case PROD_ZUWEISUNG_VARIABLE_COLONEQ: 
			break;
			// <Ausdruck> ::= <Ausdruck> '=' <pm-Term>
			case PROD_AUSDRUCK_EQ: 
			break;
			// <Ausdruck> ::= <Ausdruck> '<' <pm-Term>
			case PROD_AUSDRUCK_LT: 
			break;
			// <Ausdruck> ::= <Ausdruck> '>' <pm-Term>
			case PROD_AUSDRUCK_GT: 
			break;
			// <Ausdruck> ::= <pm-Term>
			case PROD_AUSDRUCK: 
			break;
			// <pm-Term> ::= <pm-Term> '+' <md-Term>
			case PROD_PMTERM_PLUS: 
			break;
			// <pm-Term> ::= <pm-Term> '-' <md-Term>
			case PROD_PMTERM_MINUS: 
			break;
			// <pm-Term> ::= <md-Term>
			case PROD_PMTERM: 
			break;
			// <md-Term> ::= <md-Term> '*' <pot-Term>
			case PROD_MDTERM_TIMES: 
			break;
			// <md-Term> ::= <md-Term> '/' <pot-Term>
			case PROD_MDTERM_DIV: 
			break;
			// <md-Term> ::= <pot-Term>
			case PROD_MDTERM: 
			break;
			// <pot-Term> ::= <Faktor> '^' <pot-Term>
			case PROD_POTTERM_CARET: 
			break;
			// <pot-Term> ::= <Faktor>
			case PROD_POTTERM: 
			break;
			// <Faktor> ::= konstante
			case PROD_FAKTOR_KONSTANTE: 
			break;
			// <Faktor> ::= variable
			case PROD_FAKTOR_VARIABLE: 
			break;
			// <Faktor> ::= '(' <Ausdruck> ')'
			case PROD_FAKTOR_LPAREN_RPAREN: 
			break;
			// <if-Anweisung> ::= <if-Anfang> <Anweisung>
			case PROD_IFANWEISUNG: 
			break;
			// <if-Anfang> ::= if <Ausdruck> then
			case PROD_IFANFANG_IF_THEN: 
			break;
			// <if-else-Mitte> ::= <if-Anfang> <Anweisung> else
			case PROD_IFELSEMITTE_ELSE: 
			break;
			// <if-else-Anweisung> ::= <if-else-Mitte> <Anweisung>
			case PROD_IFELSEANWEISUNG: 
			break;
			// <while-Anfang> ::= while
			case PROD_WHILEANFANG_WHILE: 
			break;
			// <while-Mitte> ::= <while-Anfang> <Ausdruck> do
			case PROD_WHILEMITTE_DO: 
			break;
			// <while-Anweisung> ::= <while-Mitte> <Anweisung>
			case PROD_WHILEANWEISUNG: 
			break;
			// <repeat-Anfang> ::= repeat
			case PROD_REPEATANFANG_REPEAT: 
			break;
			// <repeat-Anweisung> ::= <repeat-Anfang> <Anweisungen> ';' until <Ausdruck>
			case PROD_REPEATANWEISUNG_SEMI_UNTIL: 
			break;
			// <for-Anfang> ::= for <Zuweisung> to <Ausdruck> do
			case PROD_FORANFANG_FOR_TO_DO: 
			break;
			// <for-Anweisung> ::= <for-Anfang> <Anweisung>
			case PROD_FORANWEISUNG: 
			break;
		};
		return reduction;
	}
}
	
