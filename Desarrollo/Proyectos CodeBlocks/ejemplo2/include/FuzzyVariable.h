#ifndef FUZZYVARIABLE_H
#define FUZZYVARIABLE_H


class FuzzyVariable
{
    private:
        typedef std::map<std::string, FuzzySet*> MemberSets;

    private:
        FuzzyVariable(const FuzzyVariable&);
        FuzzyVariable& operator=(const FuzzyVariable&);

    private:
        MemberSets m_MemberSets;

        double     m_dMinRange;
        double     m_dMaxRange;

        void AdjustRangeToFit(double min, double max);

        ~FuzzyVariable();

        friend class FuzzyModule;

    public:
        FuzzyVariable():m_dMinRange(0.0),m_dMaxRange(0.0){}

        FzSet AddLeftShoulderSet(std::string name,
                                 double      minBound,
                                 double      peak,
                                 double      maxBound);

        FzSet AddRightShoulderSet(std::string name,
                                  double      minBound,
                                  double      peak,
                                  double      maxBound);

        FzSet AddTriangularSet(std::string name,
                               double      minBound,
                               double      peak,
                               double      maxBound);

        FzSet AddSingletonSet(std::string name,
                              double      minBound,
                              double      peak,
                              double      maxBound);

        void   Fuzzify(double val);
        double DeFuzzify()const;
        double DeFuzzifyCentroid(int NumSamles)const;
};

#endif // FUZZYVARIABLE_H
