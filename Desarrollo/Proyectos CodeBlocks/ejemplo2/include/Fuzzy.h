#ifndef FUZZY_H
#define FUZZY_H


class Fuzzy
{
    public:
        Fuzzy();
        virtual ~Fuzzy();

    /// STRUCTS
    private:
        // FUZZY SET
        typedef struct{
            float dom;   //Degree of Membership
            float rep;   //Representative Value

            int   type;  //0=Left Shoulder, 1=Triangle, 2=Right Shoulder
            float left;
            float peak;
            float right;
        }FuzzySet;

        // FUZZY VARIABLE
        // Formada por Fuzzy Sets
        typedef struct{
            FuzzySet leftSet;
            FuzzySet triangularSet;
            FuzzySet rightSet;

            float minRange;
            float maxRange;
        }FuzzyVar;

        // FUZZY RULE
        // Contiene antecedentes y consecuentes
        typedef struct{
            FuzzySet antecedent1;
            FuzzySet antecedent2;
            float    consequent;
        }FuzzyRule;

        // FUZZY MODULE
        // Contiene las reglas, y las variables
        typedef struct{
            FuzzyRule rules[9];  //FuzzyRule rules[numRules];
            FuzzyVar  vars[3];   //FuzzyVar  vars[numVars];
        }FuzzyModule;            //(int numRules, int numVars);

    /// DECLARATE ALL THE ITEMS
    public:
        FuzzyModule fm;
        FuzzyVar fzvarDistancia, fzvarSospecha, fzvarInteres;
        FuzzyRule r1, r2, r3, r4, r5, r6, r7, r8, r9;

        float CalculateDOM(float val, FuzzyVar var, int fzSetType)const;
        void  Fuzzify(float val, FuzzyVar &var);
        void  InitializeRules();
        float CalculateRule(FuzzyRule rule);
        void  CalculateFAM();
        float Defuzzify();

};

#endif // FUZZY_H
