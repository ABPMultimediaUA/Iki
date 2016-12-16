#ifndef FUZZYSET_H
#define FUZZYSET_H


class FuzzySet
{
    protected:
        double m_dDOM;
        double m_dRepresentativeValue;

    public:
        FuzzySet(double RepVal):m_dDOM(0.0), m_dRepresentativeValue(RepVal){};

        virtual double CalculateDOM(double val)const = 0;
        void           ORwithDOM(double val);

        //accessor methods
        double GetRepresentativeValue()const;
        void   ClearDOM(){m_dDOM = 0.0;}
        double GetDOM()const{return m_dDOM;}
        void   SetDOM(double val);
};

#endif // FUZZYSET_H
