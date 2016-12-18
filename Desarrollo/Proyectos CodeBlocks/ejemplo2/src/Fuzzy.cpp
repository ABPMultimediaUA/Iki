#include "Fuzzy.h"
#include "iostream"
Fuzzy::Fuzzy()
{
    //ctor

    /// Fuzzy Logic Variables
    //FLV DISTANCIA
    const FuzzySet distanciaCorta = { 0, 1, 0,  0, 20, 50 };
    const FuzzySet distanciaMedia = { 0, 1, 1, 20, 50, 80 };
    const FuzzySet distanciaLarga = { 0, 1, 2, 50, 80, 120};
    fzvarDistancia = { distanciaCorta, distanciaMedia, distanciaLarga, distanciaCorta.left, distanciaLarga.right };

    //FLV SOSPECHA
    const FuzzySet sospechaBaja  = { 0, 1, 0,  0, 20, 40 };
    const FuzzySet sospechaMedia = { 0, 1, 1, 20, 40, 70 };
    const FuzzySet sospechaAlta  = { 0, 1, 2, 40, 70, 100};
    fzvarSospecha = { sospechaBaja, sospechaMedia, sospechaAlta, sospechaBaja.left, sospechaAlta.right };

    //FLV INTERES
    const FuzzySet interesBajo  = { 0, 0, 0,  0, 25, 50 };
    const FuzzySet interesMedio = { 0, 0, 1, 25, 50, 75 };
    const FuzzySet interesAlto  = { 0, 0, 2, 50, 75, 100};
    fzvarInteres = { interesBajo, interesMedio, interesAlto, interesBajo.left, interesAlto.right };

    /// Fuzzy Rules
/*
    const FuzzyRule r1 = { distanciaCorta , sospechaBaja , interesMedio };
    const FuzzyRule r2 = { distanciaCorta , sospechaMedia, interesAlto  };
    const FuzzyRule r3 = { distanciaCorta , sospechaAlta , interesAlto  };

    const FuzzyRule r4 = { distanciaMedia , sospechaBaja , interesBajo  };
    const FuzzyRule r5 = { distanciaMedia , sospechaMedia, interesMedio };
    const FuzzyRule r6 = { distanciaMedia , sospechaAlta , interesAlto  };

    const FuzzyRule r7 = { distanciaLarga , sospechaBaja , interesBajo  };
    const FuzzyRule r8 = { distanciaLarga , sospechaMedia, interesBajo  };
    const FuzzyRule r9 = { distanciaLarga , sospechaAlta , interesMedio };
*/
    /// Fuzzy Modules
    fm.vars[0]=fzvarDistancia; fm.vars[1]=fzvarSospecha; fm.vars[2]=fzvarInteres;

}

Fuzzy::~Fuzzy()
{
    //dtor
}

// Calculamos el Degree of Membership de un FuzzySet de una FuzzyVar
float Fuzzy::CalculateDOM(float val, FuzzyVar var, int fzSetType)const
{
    float dLeft, dPeak, dRight;

    switch (fzSetType)
    {
        case 0: // FuzzySet Left Shoulder

            dLeft  = var.leftSet.left;
            dPeak  = var.leftSet.peak;
            dRight = var.leftSet.right;

            if ( val <= dPeak )
            //if ( ((dRight == 0.0) && (dPeak == val)) ||
            //     ((dLeft == 0.0)  && (dPeak == val)) )
            {
                return 1.0;
            }
            else if ( val > dPeak && val < dRight)
            //else if ( (val >= dPeak) && (val < (dPeak + dRight)) )
            {
                /// ARREGLAR ESTO
                double grad = 1.0 / -dRight;
                return grad * (val - dPeak) + 1.0;
            }
            //else if ( (val < dPeak) && (val >= dPeak-dLeft) )
            //{
            //  return 1.0;
            //}
            else
            {
                return 0.0;
            }
        break;

        case 1: // FuzzySet Triangular

            dLeft  = var.triangularSet.left;
            dPeak  = var.triangularSet.peak;
            dRight = var.triangularSet.right;

            if ( val == dPeak )
            //if ( ((dRight == 0.0) && (dPeak == val)) ||
            //     ((dLeft == 0.0)  && (dPeak == val)) )
            {
                return 1.0;
            }

            if ( val < dPeak && val > dLeft )
            //if ( (val <= dPeak) && (val >= (dPeak - dLeft)) )
            {
                double grad = 1.0 / dLeft;
                return grad * (val - (dPeak - dLeft));
            }
            else if ( val > dPeak && val < dRight )
            //else if ( (val > dPeak) && (val < (dPeak + dRight)) )
            {
                /// ARREGLAR ESTO
                double grad = 1.0 / -dRight;
                return grad * (val - dPeak) + 1.0;
            }
            else
            {
                return 0.0;
            }
        break;

        case 2: // FuzzySet Right Shoulder

            dLeft  = var.rightSet.left;
            dPeak  = var.rightSet.peak;
            dRight = var.rightSet.right;

            if ( val >= dPeak )
            //if ( ((dRight == 0.0) && (dPeak == val)) ||
            //     ((dLeft == 0.0)  && (dPeak == val)) )
            {
                return 1.0;
            }
            else if ( val < dPeak && val > dLeft )
            //else if ( (val <= dPeak) && (val > (dPeak - dLeft)) )
            {
                /// ARREGLAR ESTO
                double grad = 1.0 / dLeft;
                return grad * (val - (dPeak - dLeft));
            }
            //else if ( (val > dPeak) && (val <= dPeak+dRight) )
            //{
            //    return 1.0;
            //}
            else
            {
                return 0;
            }
        break;
    }
}

// Se calculan todos los DOM de un valor para una FuzzyVariable
void Fuzzy::Fuzzify(float val, FuzzyVar &var)
{
    var.leftSet.dom       = CalculateDOM(val, var, 0);
    var.triangularSet.dom = CalculateDOM(val, var, 1);
    var.rightSet.dom      = CalculateDOM(val, var, 2);
}

// Inicializamos las reglas
void Fuzzy::InitializeRules()
{
    r1 = { fm.vars[0].leftSet, fm.vars[1].leftSet, 0.0 };
    r2 = { fm.vars[0].leftSet, fm.vars[1].triangularSet, 0.0 };
    r3 = { fm.vars[0].leftSet, fm.vars[1].rightSet, 0.0 };

    r4 = { fm.vars[0].triangularSet, fm.vars[1].leftSet, 0.0 };
    r5 = { fm.vars[0].triangularSet, fm.vars[1].triangularSet, 0.0 };
    r6 = { fm.vars[0].triangularSet, fm.vars[1].rightSet, 0.0 };

    r7 = { fm.vars[0].rightSet, fm.vars[1].leftSet, 0.0 };
    r8 = { fm.vars[0].rightSet, fm.vars[1].triangularSet, 0.0 };
    r9 = { fm.vars[0].rightSet, fm.vars[1].rightSet, 0.0 };

    fm.rules[0]=r1; fm.rules[1]=r2; fm.rules[2]=r3; fm.rules[3]=r4; fm.rules[4]=r5;
    fm.rules[5]=r4; fm.rules[6]=r7; fm.rules[7]=r8; fm.rules[8]=r9;
}

// Calcula el Representative Value de cada FuzzySet del Consequent ( interes )
float Fuzzy::CalculateRule(FuzzyRule rule)
{
    if (rule.antecedent1.dom > rule.antecedent2.dom)
    {
        return rule.antecedent2.dom;
    }
    else if (rule.antecedent1.dom < rule.antecedent2.dom)
    {
        return rule.antecedent1.dom;
    }
    else if (rule.antecedent1.dom = rule.antecedent2.dom)
    {
        return rule.antecedent1.dom;
    }
}

// Calcula Fuzzy Associative Matrix
void Fuzzy::CalculateFAM()
{
    for (int i=0; i<9; i++)
    {
        fm.rules[i].consequent = CalculateRule(fm.rules[i]);
    }
}

// Defuzzificamos la variable interes
float Fuzzy::Defuzzify()
{

}
