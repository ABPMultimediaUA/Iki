#ifndef FUZZYMODULE_H
#define FUZZYMODULE_H

#include <vector>
#include <string>
#include <map>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"

class FuzzyModule
{
    private:

        std::map<std::string, FuzzyVariable*> varMap;
        std::vector<FuzzyRule*> rules;

        inline void SetConfidencesOfConsequentsToZero();

    public:
        FuzzyModule();
        virtual ~FuzzyModule();

        FuzzyVariable& CreateFLV(const std::string& VarName);
        void AddRule(FuzzySet& antecedent, FuzzySet& consequence);
        inline void Fuzzify(const std::string& NameOfFLV, double val);
        inline float DeFuzzify(const std::string& key);

};

#endif // FUZZYMODULE_H

/*
FuzzyModule fm;
FuzzyVariable& DistToTarget = fm.CreateFLV("DistToTarget");
FuzzyVariable& Desirability = fm.CreateFLV("Desirability");
FuzzyVariable& AmmoStatus   = fm.CreateFLV("AmmoStatus");
*/
/*
FuzzyModule fm;
FzSet Target_Close = DistToTarget.AddLeftShoulderSet("Target_Close",
                                                            0,
                                                            25,
                                                            150);
FzSet Target_Medium = DistToTarget.AddTriangularSet("Target_Medium",
                                                                25,
                                                                50,
                                                                300);
FzSet Target_Far = DistToTarget.AddRightShoulderSet("Target_Far",
                                                            150,
                                                            300,
                                                            500);
*/
/*
fm.AddRule(FzAND(Target_Far, Ammo_Low), Undesirable);
*/
/*
double CalculateDesirability(FuzzyModule& fm, double dist, double ammo)
{
    //fuzzify the inputs
    fm.Fuzzify("DistToTarget", dist);
    fm.Fuzzify("AmmoStatus", ammo);
    //this method automatically processes the rules and defuzzifies
    //the inferred conclusion
    return fm.DeFuzzify("Desirability", FuzzyModule::max_av);
}
*/
