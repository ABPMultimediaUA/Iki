#ifndef FZSET_H
#define FZSET_H

#include <FuzzyTerm.h>
#include "FuzzySet.h"

class FzSet : public FuzzyTerm
{
    private:
        //let the hedge classes be friends
        //friend class FzVery;
        //friend class FzFairly;

    private:
        //a reference to the fuzzy set this proxy represents
        FuzzySet& fSet;

    public:
        FzSet(FuzzySet& fs):fSet(fs){}

        FuzzyTerm* Clone()const{return new FzSet(*this);}
        float     GetDOM()const {return fSet.GetDOM();}
        void       ClearDOM(){fSet.ClearDOM();}
        void       ORwithDOM(float val){fSet.ORwithDOM(val);}
};


#endif // FZSET_H
