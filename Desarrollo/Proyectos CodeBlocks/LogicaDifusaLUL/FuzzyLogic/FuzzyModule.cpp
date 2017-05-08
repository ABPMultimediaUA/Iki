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

FuzzyVariable& FuzzyModule::CreateFLV(const std::string VarName)
{
    std::string str = VarName;
    varMap[VarName] = new FuzzyVariable();;
    return *varMap[VarName];
}
