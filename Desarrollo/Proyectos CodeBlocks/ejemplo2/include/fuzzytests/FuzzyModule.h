#ifndef FUZZYMODULE_H
#define FUZZYMODULE_H


class FuzzyModule
{
    private:
        typedef std::map<std::string, FuzzyVariable*> VarMap;

    public:
        enum DefuzzifyType{max_av,centroid};
        enum {NumSamplesToUseForCentroid = 15};

    private:
        VarMap                   m_Variables;
        std::vector<FuzzyRule*>  m_Rules;

        inline void SetConfidencesOfConsecuencesToZero();

    public:
        ~FuzzyModule();

        FuzzyVariable& CreateFLV(const std::string& VarName);
        void           AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence);
        inline void    Fuzzify(const std::string& NameOfFLV, double val);
        inline double  DeFuzzify(const std::strin& key, DefuzzifyType method);
};

#endif // FUZZYMODULE_H
