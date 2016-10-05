#include <stdexcept>
#include <iostream>
#include "GoldCPP\MIMParser.h"
#include "GoldCPP\Parser.h"
#include "constants.h"
#include "helperUtility.h"
#
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
			{
				cout << "Symboltabelle" << endl;
				cout << "--------------------------" << endl;

				for (int i = 0; i < 27; i++)
				{
					cout << to_string(i) << "\t";

					for (int j = 0; j < 4; j++)
					{
						cout << symbolTable.table[i][j] << "\t";
					}

					cout << endl;
				}

				cout << "Quadrupeltabelle" << endl;
				cout << "--------------------------" << endl;

				for (int i = 0; i < 17; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						cout << quadrupleSpace.quadrupleTable[i][j] << "\t";
					}

					cout << endl;
				}
			}
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
			{
				symbolTable.addNextEntry(elementFromProduction(0)->GetStringData(), "variable", elementFromProduction(2)->ReductionData->typ, "");
				reduction->typ = elementFromProduction(2)->ReductionData->typ;
			}
			break;
			// <Deklarationsliste> ::= variable ':' <Typ> ';'
			case PROD_DEKLARATIONSLISTE_VARIABLE_COLON_SEMI: 
			{
				symbolTable.addNextEntry(elementFromProduction(0)->GetStringData(), "variable", elementFromProduction(2)->ReductionData->typ, "");
				reduction->typ = elementFromProduction(2)->ReductionData->typ;
			}
			break;
			// <Typ> ::= integer
			case PROD_TYP_INTEGER: 
				reduction->typ = "integer";
			break;
			// <Typ> ::= real
			case PROD_TYP_REAL: 
				reduction->typ = "real";
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
			{
				string variable_name = elementFromProduction(0)->GetStringData();
				int adresse2 = elementFromProduction(2)->ReductionData->adresse;
				int index = symbolTable.getIndexFromVariable(variable_name);

				reduction->adresse = index;
				quadrupleSpace.addNextEntry("IS", adresse2, -1, index);
			}
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
				reduction->adresse = elementFromProduction(0)->ReductionData->adresse;
			break;
			// <pm-Term> ::= <pm-Term> '+' <md-Term>
			case PROD_PMTERM_PLUS: 
			{
				int adresse1 = elementFromProduction(0)->ReductionData->adresse;
				int adresse2 = elementFromProduction(2)->ReductionData->adresse;

				string typeOfAdresse1 = symbolTable.table[adresse1][2];
				string typeOfAdresse2 = symbolTable.table[adresse2][2];
				
				int addresseHilfsvariable = symbolTable.addNextEntry(
					"",
					"HVar",
					helperUtility::getTypeForSymboltabelle(typeOfAdresse1, typeOfAdresse2),
					"");

				reduction->adresse = addresseHilfsvariable;
				quadrupleSpace.addNextEntry("ADD", adresse1, adresse2, addresseHilfsvariable);
			}
			break;
			// <pm-Term> ::= <pm-Term> '-' <md-Term>
			case PROD_PMTERM_MINUS: 
			{
				int adresse1 = elementFromProduction(0)->ReductionData->adresse;
				int adresse2 = elementFromProduction(2)->ReductionData->adresse;

				string typeOfAdresse1 = symbolTable.table[adresse1][2];
				string typeOfAdresse2 = symbolTable.table[adresse2][2];

				int addresseHilfsvariable = symbolTable.addNextEntry(
					"",
					"HVar",
					helperUtility::getTypeForSymboltabelle(typeOfAdresse1, typeOfAdresse2),
					"");

				quadrupleSpace.addNextEntry("SUB", adresse1, adresse2, addresseHilfsvariable);
				reduction->adresse = addresseHilfsvariable;
			}
			break;
			// <pm-Term> ::= <md-Term>
			case PROD_PMTERM: 
				reduction->adresse = elementFromProduction(0)->ReductionData->adresse;
			break;
			// <md-Term> ::= <md-Term> '*' <pot-Term>
			case PROD_MDTERM_TIMES: 
			{
				int adresse1 = elementFromProduction(0)->ReductionData->adresse;
				int adresse2 = elementFromProduction(2)->ReductionData->adresse;

				string typeOfAdresse1 = symbolTable.table[adresse1][2];
				string typeOfAdresse2 = symbolTable.table[adresse2][2];

				int addresseHilfsvariable = symbolTable.addNextEntry(
					"",
					"HVar",
					helperUtility::getTypeForSymboltabelle(typeOfAdresse1, typeOfAdresse2),
					"");

				quadrupleSpace.addNextEntry("MULT", adresse1, adresse2, addresseHilfsvariable);
				reduction->adresse = addresseHilfsvariable;
			}
			break;
			// <md-Term> ::= <md-Term> '/' <pot-Term>
			case PROD_MDTERM_DIV: 
			{
				int adresse1 = elementFromProduction(0)->ReductionData->adresse;
				int adresse2 = elementFromProduction(2)->ReductionData->adresse;

				int addresseHilfsvariable = symbolTable.addNextEntry(
					"",
					"HVar",
					"real",
					"");

				quadrupleSpace.addNextEntry("DIV", adresse1, adresse2, addresseHilfsvariable);
				reduction->adresse = addresseHilfsvariable;
			}
			break;
			// <md-Term> ::= <pot-Term>
			case PROD_MDTERM: 
				reduction->adresse = elementFromProduction(0)->ReductionData->adresse;
			break;
			// <pot-Term> ::= <Faktor> '^' <pot-Term>
			case PROD_POTTERM_CARET: 
			{
				int adresse1 = elementFromProduction(0)->ReductionData->adresse;
				int adresse2 = elementFromProduction(2)->ReductionData->adresse;

				string typeOfAdresse1 = symbolTable.table[adresse1][2];
				string typeOfAdresse2 = symbolTable.table[adresse2][2];

				int addresseHilfsvariable = symbolTable.addNextEntry(
					"",
					"HVar",
					helperUtility::getTypeForSymboltabelle(typeOfAdresse1, typeOfAdresse2),
					"");

				quadrupleSpace.addNextEntry("POT", adresse1, adresse2, addresseHilfsvariable);
				reduction->adresse = addresseHilfsvariable;
			}
			break;
			// <pot-Term> ::= <Faktor>
			case PROD_POTTERM: 
				reduction->adresse = elementFromProduction(0)->ReductionData->adresse;
			break;
			// <Faktor> ::= konstante
			case PROD_FAKTOR_KONSTANTE: 
			{
				reduction->adresse = symbolTable.addNextEntry(
					"",
					"constant",
					helperUtility::returnVariableType(elementFromProduction(0)->GetStringData()),
					elementFromProduction(0)->GetStringData());
			}
			break;
			// <Faktor> ::= variable
			case PROD_FAKTOR_VARIABLE: 
			{
				int adresse = symbolTable.getIndexFromVariable(elementFromProduction(0)->GetStringData());
				reduction->adresse = adresse;
			}
			break;
			// <Faktor> ::= '(' <Ausdruck> ')'
			case PROD_FAKTOR_LPAREN_RPAREN: 
				reduction->adresse = elementFromProduction(1)->ReductionData->adresse;
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
	
