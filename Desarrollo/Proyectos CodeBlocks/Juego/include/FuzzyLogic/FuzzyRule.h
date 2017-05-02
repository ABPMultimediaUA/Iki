#ifndef FUZZYRULE_H
#define FUZZYRULE_H

#include "FuzzyTerm.h"


class FuzzyRule
{
    private:
        //antecedent (usually a composite of several fuzzy sets and operators)
        const FuzzyTerm* antecedent;
        //consequence (usually a single fuzzy set, but can be several ANDed together)
        FuzzyTerm* consequence;
        //it doesn't make sense to allow clients to copy rules
        FuzzyRule(const FuzzyRule&);
        FuzzyRule& operator=(const FuzzyRule&);
    public:
        FuzzyRule(FuzzyTerm& ant,
                  FuzzyTerm& con):antecedent(ant.Clone()),
                                  consequence(con.Clone())
                                                        {}
        ~FuzzyRule(){delete antecedent; delete consequence;}
        void SetConfidenceOfConsequentToZero(){consequence->ClearDOM();}
        //this method updates the DOM (the confidence) of the consequent term with
        //the DOM of the antecedent term.
        void Calculate()
        {
            consequence->ORwithDOM(antecedent->GetDOM());
        }
};

#endif // FUZZYRULE_H
