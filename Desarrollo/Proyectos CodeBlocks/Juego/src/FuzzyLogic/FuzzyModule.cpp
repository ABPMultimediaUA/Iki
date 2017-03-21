#include "FuzzyModule.h"

FuzzyModule::FuzzyModule()
{
    //ctor
}

FuzzyModule::~FuzzyModule()
{
    //dtor
    std::map<std::string, FuzzyVariable*>::iterator curVar = varMap.begin();
    for (curVar; curVar != varMap.end(); ++curVar)
    {
        delete curVar->second;
    }

    std::vector<FuzzyRule*>::iterator curRule = rules.begin();
    for (curRule; curRule != r.end(); ++curRule)
    {
        delete *curRule;
    }
}

void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
    m_Rules.push_back(new FuzzyRule(antecedent, consequence));
}

//-------------------------- CreateFLV ---------------------------
//
//  creates a new fuzzy variable and returns a reference to it
//-----------------------------------------------------------------------------
FuzzyVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
  m_Variables[VarName] = new FuzzyVariable();;

  return *m_Variables[VarName];
}

//---------------------------- WriteAllDOMs -----------------------------------
std::ostream& FuzzyModule::WriteAllDOMs(std::ostream& os)
{
  os << "\n\n";

  VarMap::iterator curVar = m_Variables.begin();
  for (curVar; curVar != m_Variables.end(); ++curVar)
  {
    os << "\n--------------------------- " << curVar->first;;
    curVar->second->WriteDOMs(os);

    os << std::endl;
  }

  return os;
}

///////////////////////////////////////////////////////////////////////////////

//----------------------------- Fuzzify ---------------------------------------
//
//  this method calls the Fuzzify method of the variable with the same name
//  as the key
//-----------------------------------------------------------------------------
inline void FuzzyModule::Fuzzify(const std::string& NameOfFLV, double val)
{
  //first make sure the key exists
  assert ( (m_Variables.find(NameOfFLV) != m_Variables.end()) &&
          "<FuzzyModule::Fuzzify>:key not found");

  m_Variables[NameOfFLV]->Fuzzify(val);
}

//---------------------------- DeFuzzify --------------------------------------
//
//  given a fuzzy variable and a deffuzification method this returns a
//  crisp value
//-----------------------------------------------------------------------------
inline double
FuzzyModule::DeFuzzify(const std::string& NameOfFLV, DefuzzifyMethod method)
{
  //first make sure the key exists
  assert ( (m_Variables.find(NameOfFLV) != m_Variables.end()) &&
          "<FuzzyModule::DeFuzzifyMaxAv>:key not found");

  //clear the DOMs of all the consequents of all the rules
  SetConfidencesOfConsequentsToZero();

  //process the rules
  std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
  for (curRule; curRule != m_Rules.end(); ++curRule)
  {
    (*curRule)->Calculate();
  }

  //now defuzzify the resultant conclusion using the specified method
    return m_Variables[NameOfFLV]->DeFuzzifyMaxAv();

}

//-------------------------- ClearConsequents ---------------------------------
//
//  zeros the DOMs of the consequents of each rule
//-----------------------------------------------------------------------------
inline void FuzzyModule::SetConfidencesOfConsequentsToZero()
{
  std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
  for (curRule; curRule != m_Rules.end(); ++curRule)
  {
    (*curRule)->SetConfidenceOfConsequentToZero();
  }
}
