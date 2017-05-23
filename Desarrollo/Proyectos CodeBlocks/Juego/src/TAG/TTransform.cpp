#include "TTransform.h"

TTransform::TTransform()
{
    matriz = glm::mat4(1.f);
/*
    TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
    !!! BEWARE !!! This lines actually performs the scaling FIRST, and THEN the rotation,
    and THEN the translation. This is how matrix multiplication works.
*/
}

TTransform::~TTransform()
{
    //dtor
}

void TTransform::identidad()
{
     matriz = glm::mat4(1.f);
}

void TTransform::cargar(glm::mat4 mat)
{
    matriz = mat;

}

void TTransform::trasponer()
{
    transpose(matriz);
}

void TTransform::trasladar(float x, float y, float z)
{
    matriz = translate(matriz, vec3(x, y, z));

//comprobamos que realiza bien la translacion
   // cout<<"Trasladamos: "<<endl;
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            if(j != 3){}
             //   cout<<matriz[i][j]<<" ";
            else{}
               // cout<<matriz[i][j]<<endl;
        }
    }
    cout<<endl;
}

void TTransform::rotar(float angulo, float x, float y, float z)
{
    matriz = rotate(matriz, (float) radians(angulo), vec3(x, y, z));

//comprobamos que realiza bien la rotacion
    //cout<<"Rotamos: "<<endl;
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            if(j != 3){}
               // cout<<matriz[i][j]<<" ";
            else{}
               // cout<<matriz[i][j]<<endl;
        }
    }
    //cout<<endl;

}

void TTransform::escalarRel(float x, float y, float z)
{
    matriz = scale(matriz, vec3(x, y, z));

//comprobamos que realiza bien el escalado relativo
    //cout<<"Escalamos Rel: "<<endl;
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            if(j != 3){}
                //cout<<matriz[i][j]<<" ";
            else{}
                //cout<<matriz[i][j]<<endl;
        }
    }
    //cout<<endl;
}

void TTransform::escalarAbs(float num)
{
    matriz = scale(matriz, vec3(num, num, num));

//comprobamos que realiza bien el escalado absoluto
    //cout<<"Escalamos Abs: "<<endl;
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            if(j != 3){}
               // cout<<matriz[i][j]<<" ";
            else{}
              //  cout<<matriz[i][j]<<endl;
        }
    }
    //cout<<endl;
}

void TTransform::beginDraw()
{
    pila.push(ms_gmatriz);
    //std::cout<<"apilando matriz"<<std::endl;

    ms_gmatriz= ms_gmatriz * matriz;


   // std::cout<<"multiplicando la transformacion a la actual"<<std::endl;
}

void TTransform::endDraw()
{
    ms_gmatriz= pila.top();
    pila.pop();
  //  std::cout<<"desapilando matriz"<<std::endl;
}
