#ifndef FUZZYMODULE_H
#define FUZZYMODULE_H

#include <map>

class FuzzyModule
{
    private:

        typedef std::map<std::string, FuzzyVariable*> VarMap;

        VarMap m_Variables;
        std::vector<FuzzyRule*> m_Rules;

        //zeros the DOMs of the consequents of each rule. Used by Defuzzify()
        inline void SetConfidencesOfConsequentsToZero();

    public:
        FuzzyModule();
        virtual ~FuzzyModule();

        //creates a new "empty" fuzzy variable and returns a reference to it.
        FuzzyVariable& CreateFLV(const std::string& VarName);
        //adds a rule to the module
        void AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence);
        //this method calls the Fuzzify method of the named FLV
        inline void Fuzzify(const std::string& NameOfFLV, double val);
        //given a fuzzy variable and a defuzzification method this returns a
        //crisp value
        inline float DeFuzzify(const std::string& key, DefuzzifyType method);

};

#endif // FUZZYMODULE_H

/*
FuzzyModule fm;
FuzzyVariable& DistToTarget = fm.CreateFLV("DistToTarget");
FuzzyVariable& Desirability = fm.CreateFLV("Desirability");
FuzzyVariable& AmmoStatus   = fm.CreateFLV("AmmoStatus");
*/
