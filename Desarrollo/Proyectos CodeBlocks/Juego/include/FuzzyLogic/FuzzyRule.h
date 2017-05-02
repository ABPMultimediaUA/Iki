#ifndef FUZZYRULE_H
#define FUZZYRULE_H

#include "FuzzyTerm.h"


class FuzzyRule
{
    private:
        const FuzzyTerm* antecedent;
        FuzzyTerm* consequence;

        FuzzyRule(const FuzzyRule&);
        FuzzyRule& operator=(const FuzzyRule&);
    public:
        FuzzyRule(FuzzyTerm& ant, FuzzyTerm& con):antecedent(ant.Clone()), consequence(con.Clone()) {}
        ~FuzzyRule(){delete antecedent; delete consequence;}

        void SetConfidenceOfConsequentToZero(){consequence->ClearDOM();}
        void Calculate() { consequence->ORwithDOM(antecedent->GetDOM()); }
};

#endif // FUZZYRULE_H
