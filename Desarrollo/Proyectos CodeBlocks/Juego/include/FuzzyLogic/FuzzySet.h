#ifndef FUZZYSET_H
#define FUZZYSET_H


class FuzzySet
{
    public:
        float dom;
        float repv;

    public:
        FuzzySet(float RepVal):dom(0.0), repv(RepVal){}

        virtual float CalculateDOM(float val)const = 0;
        void ORwithDOM(float val){if (val > dom) dom = val;}

        float GetRepv()const{return repv;}
        float GetDOM()const {return dom; }
        void SetDOM(float val){if ((val<=1) && (val>=0)) dom = val;}
        void ClearDOM(){dom = 0.0;}
};

#endif // FUZZYSET_H
