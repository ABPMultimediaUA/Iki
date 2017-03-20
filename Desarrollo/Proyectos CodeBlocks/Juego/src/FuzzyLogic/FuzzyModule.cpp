#include "FuzzyModule.h"

FuzzyModule::FuzzyModule()
{
    //ctor
}

FuzzyModule::~FuzzyModule()
{
    //dtor
}

inline float FuzzyModule::DeFuzzify(const std::string& NameOfFLV)
{
    //first make sure the named FLV exists in this module
    //assert ( (m_Variables.find(NameOfFLV) != m_Variables.end()) && "<FuzzyModule::DeFuzzifyMaxAv>:key not found");

    //clear the DOMs of all the consequents
    SetConfidencesOfConsequentsToZero();

    //process the rules
    std::vector<FuzzyRule*>::iterator curRule = rules.begin();
    for (curRule; curRule != rules.end(); ++curRule)
    {
        (*curRule)->Calculate();
    }

    return varMap[NameOfFLV]->DeFuzzifyMaxAv();
}

//return 0;
