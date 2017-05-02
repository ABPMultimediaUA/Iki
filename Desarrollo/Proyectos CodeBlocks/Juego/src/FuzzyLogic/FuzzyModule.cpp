#include "FuzzyModule.h"


FuzzyModule::~FuzzyModule()
{
    std::map<std::string, FuzzyVariable*>::iterator curVar = varMap.begin();
    for (curVar; curVar != varMap.end(); ++curVar)
    {
        delete curVar->second;
    }

    std::vector<FuzzyRule*>::iterator curRule = rules.begin();
    for (curRule; curRule != rules.end(); ++curRule)
    {
        delete *curRule;
    }
}

void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
    rules.push_back(new FuzzyRule(antecedent, consequence));
}

FuzzyVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
    varMap[VarName] = new FuzzyVariable();;
    return *varMap[VarName];
}

inline void FuzzyModule::Fuzzify(const std::string& NameOfFLV, double val)
{
    varMap[NameOfFLV]->Fuzzify(val);
}

inline float FuzzyModule::DeFuzzify(const std::string& NameOfFLV)
{
    SetConfidencesOfConsequentsToZero();

    std::vector<FuzzyRule*>::iterator curRule = rules.begin();
    for (curRule; curRule != rules.end(); ++curRule)
    {
        (*curRule)->Calculate();
    }
    return varMap[NameOfFLV]->DeFuzzifyMaxAv();
}

inline void FuzzyModule::SetConfidencesOfConsequentsToZero()
{
    std::vector<FuzzyRule*>::iterator curRule = rules.begin();
    for (curRule; curRule != rules.end(); ++curRule)
    {
        (*curRule)->SetConfidenceOfConsequentToZero();
    }
}
