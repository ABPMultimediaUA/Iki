#ifndef TMATRIZ_H
#define TMATRIZ_H

#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

class TMatriz
{
    public:
        TMatriz(mat4 m);
        virtual ~TMatriz();
        //static mat4 G_matriz;

    protected:

    private:
        mat4 G_matriz;
};

#endif // TMATRIZ_H
