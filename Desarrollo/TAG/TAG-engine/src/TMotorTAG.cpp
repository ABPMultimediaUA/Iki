#include "TMotorTAG.h"

TMotorTAG::TMotorTAG()
{
    //ctor
}

TMotorTAG::~TMotorTAG()
{
    //dtor
}

TNodo *TMotorTAG::crearNodo(TNodo *padre, TEntidad *ent)
{
    TNodo *nodo = new TNodo();
    nodo->setEntidad(ent);
    padre->addHijo(nodo);

    return nodo;
}

TTransform *TMotorTAG::crearTransform()
{
    TTransform *tranformacion = new TTransform();

    return tranformacion;

}

TCamara *TMotorTAG::crearCamara()
{
    TCamara *camara= new TCamara();

    return camara;
}

TLuz *TMotorTAG::crearLuz()
{
    TLuz *luz = new TLuz();

    return luz;
}

TMalla *TMotorTAG::crearMalla(char* fichero)
{

}

int TMotorTAG::registrarCamara(TNodo* nod)
{
    int x;
    for(x = 0; x < camaras.size(); x++)
    {
        camaras.push_back(nod);
        c_activa.push_back(true);
    }

    return x;
}
int TMotorTAG::registrarLuz(TNodo* nod)
{
    int y;
    for(y = 0; y < luces.size(); y++)
    {
        luces.push_back(nod);
        l_activa.push_back(true);

    }

    return y;
}

void TMotorTAG::setLuzActiva(int i)
{
    l_activa[i] = true;
    glEnable(GL_LIGHTING);
}

void TMotorTAG::setLuzApagada(int i)
{
    l_activa[i] = false;
}

void TMotorTAG::setCamaraActiva(int i)
{
    c_activa[i] = true;
}

void TMotorTAG::setCamaraApagada(int i)
{
    c_activa[i] = false;
}



void TMotorTAG::draw()
{
    int i;
    //drawLuces
    for(i= 0; i < luces.size(); i++)
    {
        if(l_activa[i])
        {
            //Guardamos en un vector aux desde la luz hasta la raiz
            TNodo* nodo;
            vector<TNodo*> aux;
            aux.push_back(luces[i]);
            nodo= aux.back()->getPadre();
            while(nodo)
            {
                aux.push_back(nodo);
                nodo= aux.back()->getPadre();
            }
            //Recorre desde la raiz hasta la luz
            vector<TNodo*>::iterator it = aux.end();
            mat4 mat_aux = mat4(1.f);
            while(it != aux.begin())
            {
                //mat_aux= *it->getEntidad().getMatriz() ;
                //* mat_aux
                --it;
            }
            //	printf("LUZ:         %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
            glUniform3f(glGetUniformLocation(sh->Program, "light.position"), pos.x, pos.y, pos.z);

            //propiedades de la luz
            glUniform3f(glGetUniformLocation(sh->Program, "light.ambient"),   0.15f, 0.15f, 0.15f);
            glUniform3f(glGetUniformLocation(sh->Program, "light.diffuse"),   2.5f, 2.5f, 2.5f);
            glUniform3f(glGetUniformLocation(sh->Program, "light.specular"),  1.0f, 1.0f, 1.0f);
            glUniform1f(glGetUniformLocation(sh->Program, "light.constant"),  1.0f);
            glUniform1f(glGetUniformLocation(sh->Program, "light.linear"),    0.09);
            glUniform1f(glGetUniformLocation(sh->Program, "light.quadratic"), 0.032);
            //glUniform3f
            //Aqui hemos llegado a la luz
            //Dibujar luces[i] con mat_aux aplicada
        }
    }

    //drawCamaras
    for(i= 0; i < camaras.size(); i++)
    {
        //recorrer el arbol a la inversa

    }

    //drawEscena
}
