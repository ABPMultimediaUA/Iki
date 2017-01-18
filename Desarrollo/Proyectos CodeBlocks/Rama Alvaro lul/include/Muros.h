#ifndef MUROS_H
#define MUROS_H
#include <irrlicht.h>
#include <World.h>
#include <iostream>

using namespace irr;
using namespace scene;


class Muros
{
    public:
        Muros();
        virtual ~Muros();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setCuboMuros(core::vector3df);
        void setPosition(core::vector3df vec);
        core::vector3df getCuboMuros();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();

        b2Body *body, *body2, *body3, *body4, *body5, *body6, *body7, *body8, *body9, *body10, *body11, *body12, *body13, *body14, *body15,
        *body16, *body17, *body18, *body19, *body20, *body21, *body22, *body23, *body24, *body25, *body26;
    protected:

    private:
        core::vector3df cuboMuros;
        int dim;
        float tam, tam10, tam15, tam25, tam30, tam40, tam70, tam80;
        class World* iworld;

        IMesh *mura1, *mura2, *mura3, *mura4, *mura5, *mura6, *mura7, *mura8, *mura9, *mura10, *mura11, *mura12, *mura13, *mura14, *mura15, *mura16, *mura17, *mura18,
        *mura19, *mura20, *mura21, *mura22, *mura23, *mura24, *mura25, *mura26;

        IMeshSceneNode *modelo, *muro1, *muro2, *muro3, *muro4, *muro5, *muro6, *muro7, *muro8, *muro9, *muro10, *muro11, *muro12, *muro13, *muro14, *muro15, *muro16, *muro17, *muro18,
        *muro19, *muro20, *muro21, *muro22, *muro23, *muro24, *muro25, *muro26;


};

#endif // MUROS_H

