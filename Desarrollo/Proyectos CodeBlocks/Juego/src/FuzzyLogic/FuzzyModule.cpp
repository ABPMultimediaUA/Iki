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
/*
std::ostream& FuzzyModule::WriteAllDOMs(std::ostream& os)
{
    os << "\n\n";
    std::map<std::string, FuzzyVariable*>::iterator curVar = varMap.begin();
    for (curVar; curVar != varMap.end(); ++curVar)
    {
        os << "\n--------------------------- " << curVar->first;;
        curVar->second->WriteDOMs(os);
        os << std::endl;
    }
    return os;
}
*/
inline void FuzzyModule::Fuzzify(const std::string& NameOfFLV, double val)
{
    //assert ( (varMap.find(NameOfFLV) != varMap.end()) &&
    //      "<FuzzyModule::Fuzzify>:key not found");

    varMap[NameOfFLV]->Fuzzify(val);
}

inline float FuzzyModule::DeFuzzify(const std::string& NameOfFLV)
{
    //first make sure the key exists
    //assert ( (varMap.find(NameOfFLV) != varMap.end()) &&
    //        "<FuzzyModule::DeFuzzifyMaxAv>:key not found");

    //clear the DOMs of all the consequents of all the rules
    SetConfidencesOfConsequentsToZero();

    //process the rules
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
