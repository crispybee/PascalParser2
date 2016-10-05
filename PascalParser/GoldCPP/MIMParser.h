#ifndef GoldCPP_SIMPLEPARSER_H
#define GoldCPP_SIMPLEPARSER_H

#include "String.h"
#include <memory>
#include <sstream>


// Not used, but included for consumers
#include "Reduction.h"
#include "Production.h"
#include "..\SymbolTable.h"
#include "..\QuadrupleSpace.h"
namespace GoldCPP
{
  /* Only for native numeric types! */
  template <typename T>
  GPSTR_T toString(T number)
  {
    // Convert to standard string
    std::ostringstream ss;
    ss << number;
    std::string tmp(ss.str());

    // Because character codes 0-127 are identical in ASCII and UTF,
    // this conversion actually works (for latin digits).
    GPSTR_T ret(tmp.size(), ' ');
    for (size_t i = 0; i < tmp.size(); ++i)
      ret[i] = (GPCHR_T)tmp[i];

    return ret;
  }

  class Parser;

  class MIMParser
  {
  private:
    Parser *parser_;	
	//Anzupassen: Deklaration von Symboltabelle und Quadruppelbereich
	SymbolTable symbolTable;
	QuadrupleSpace quadrupleSpace;
#ifndef __GNUC__
    MIMParser(const MIMParser& that){}
#else
    MIMParser(const SimpleParser& that) = delete;
#endif
	
  public:
    void* User0;
    void* User1;
    std::shared_ptr<Reduction> Root;
    MIMParser(const uint8_t* egt_data, size_t len);
	MIMParser(std::string egtFile);
    virtual ~MIMParser();

    // Override these functions to get custom behavior
    virtual GPSTR_T LexicalError(MIMParser *parser, Parser* parserCore);
    virtual GPSTR_T SyntaxError(MIMParser *parser, Parser* parserCore);
    virtual std::shared_ptr<Reduction> Reduce(MIMParser *parser, const std::shared_ptr<Reduction> &reduction);
    virtual GPSTR_T InternalError(MIMParser *parser);
    virtual GPSTR_T TablesNotLoaded(MIMParser *parser);
    virtual GPSTR_T Runaway(MIMParser *parser);

    bool Parse(const GPSTR_T &source, GPSTR_T &msgOut, bool trimReductions = false);
    Parser* GetParserCore() const { return parser_; }
	std::shared_ptr<GoldCPP::Token> elementFromProduction(int);
	
	std::string MIMParser::findNewType(std::string,std::string);	
	//Anzupassen: Methoden, um Symboltabelle und Quadruppelbereich auszugeben
  };
}

#endif // GoldCPP_SIMPLEPARSER_H

