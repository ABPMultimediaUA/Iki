#ifndef HUD_H
#define HUD_H

class Image;

class HUD
{
    public:
        HUD();
        ~HUD();

        void inicializar_HUD();
        void draw();

    protected:

    private:
        Image* Vida;
        Image* Laser;
        Image* Desc_laser;
        Image* Num_balas;

        //Player* player;
};

#endif // HUD_H
