#include "MIMParser.h"
#include "Parser.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#ifdef __GNUC__
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED
#endif


namespace GoldCPP
{
	 MIMParser::MIMParser(std::string egtFile) :
      parser_(NULL), User0(NULL), User1(NULL), Root(NULL)
    {
      parser_ = new Parser();
	  // Load binary EGT definition
	  std::ifstream egtInput(egtFile, std::ios::binary);
	  std::vector<char> egtBuffer((std::istreambuf_iterator<char>(egtInput)), (std::istreambuf_iterator<char>()));
	  egtInput.close();  

      if (!parser_->LoadTables((uint8_t*)egtBuffer.data(), egtBuffer.size()))
      {
        throw std::runtime_error("Could not load EGT parser tables.");
        delete parser_;
      }
	  //Anzupassen: Initialisierung von Quadruppeltabelle und Symboltabelle
    }

    MIMParser::MIMParser(const uint8_t* egt_data, size_t len) :
      parser_(NULL), User0(NULL), User1(NULL), Root(NULL)
    {
      parser_ = new Parser();

      if (!parser_->LoadTables(egt_data, len))
      {
        throw std::runtime_error("Could not load EGT parser tables.");
        delete parser_;
      }	
    }
	
	//Anzupassen: Implementierung der Methoden zur Initialisierung und Ausgabe der Tabellen (Symbol, Quadruppel)
	
	std::shared_ptr<GoldCPP::Token> MIMParser::elementFromProduction(int pos)
	{		
		return parser_->GetCurrentReduction()->Branches.GetItemAt(pos);
	}
	
	MIMParser::~MIMParser()
    {
      delete parser_;
    }

    GPSTR_T MIMParser::LexicalError(MIMParser UNUSED *parser, Parser* parserCore)
    {
      //Cannot recognize token
      return GPSTR_T(GPSTR_C("Lexical Error:\n")) +
             GPSTR_C("Position: ") + toString(parserCore->GetCurrentPosition().Line) + GPSTR_C(", ") + toString(parserCore->GetCurrentPosition().Column) + GPSTR_T(GPSTR_C("\n")) +
             GPSTR_C("Read: ") + parserCore->GetCurrentToken()->StringData;
    }
	GPSTR_T MIMParser::SyntaxError(MIMParser UNUSED *parser, Parser* parserCore)
    {
      //Expecting a different token
      return GPSTR_T(GPSTR_C("Syntax Error:\n")) +
             GPSTR_C("Position: ") + toString(parserCore->GetCurrentPosition().Line) + GPSTR_C(", ") +  toString(parserCore->GetCurrentPosition().Column) + GPSTR_C("\n") +
             GPSTR_T(GPSTR_C("Read: ")) + parserCore->GetCurrentToken()->StringData + GPSTR_C("\n") +
             GPSTR_T(GPSTR_C("Expecting: ")) + parserCore->GetExpectedSymbols().GetText();
    }
	GPSTR_T MIMParser::InternalError(MIMParser UNUSED *parser)
    {
      //INTERNAL ERROR! Something is horribly wrong.
      return GPSTR_C("Ka-BOOOOM!");
    }
    GPSTR_T MIMParser::TablesNotLoaded(MIMParser UNUSED *parser)
    {
      //This error occurs if the EGT was not loaded.
      return GPSTR_C("No parser tables loaded! (Since we load the EGT table with RAII, this case is pretty impossible...)");
    }
    GPSTR_T MIMParser::Runaway(MIMParser UNUSED *parser)
    {
      //GROUP ERROR! Unexpected end of file
      return GPSTR_C("Unexpecetd end of input. Probably unclosed structure in input.");
    }

    bool MIMParser::Parse(const GPSTR_T &source, GPSTR_T &msgOut, bool trimReductions)
    {
      /* This procedure starts the GOLD Parser Engine and handles each of the
      messages it returns. Each time a reduction is made, you can create new
      custom object and reassign the .CurrentReduction property. Otherwise,
      the system will use the Reduction object that was returned.

      The resulting tree will be a pure representation of the language
      and will be ready to implement. */

      ParseMessage response;
      bool done;                      //Controls when we leave the loop
      bool accepted = false;          //Was the parse successful?

      parser_->Open(source);
      parser_->TrimReductions = trimReductions;  //Please read about this feature before enabling

      done = false;
      while (!done)
      {
          response = parser_->Parse();

          switch (response)
          {
              case ParseMessage::LexicalError:
                  //Cannot recognize token
                  msgOut = LexicalError(this, parser_);
                  done = true;
                  break;

              case ParseMessage::SyntaxError:
                  //Expecting a different token
                  msgOut = SyntaxError(this, parser_);
                  done = true;
                  break;

              case ParseMessage::Reduction:
                  parser_->SetCurrentReduction(Reduce(this, parser_->GetCurrentReduction()));
                  break;

              case ParseMessage::Accept:
                  //Accepted!
                  Root = parser_->GetCurrentReduction();    //The root node!
                  done = true;
                  accepted = true;
                  break;

              case ParseMessage::TokenRead:
                  //You don't have to do anything here.
                  break;

              case ParseMessage::InternalError:
                  //INTERNAL ERROR! Something is horribly wrong.
                  msgOut = InternalError(this);
                  done = true;
                  break;

              case ParseMessage::NotLoadedError:
                  //This error occurs if the EGT was not loaded.
                  msgOut = TablesNotLoaded(this);
                  done = true;
                  break;

              case ParseMessage::GroupError:
                  //GROUP ERROR! Unexpected end of file
                  msgOut = Runaway(this);
                  done = true;
                  break;
          }
      } //while

      return accepted;
    }
}
