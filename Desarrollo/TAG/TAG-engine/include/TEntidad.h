#ifndef TENTIDAD_H
#define TENTIDAD_H


class TEntidad
{
    public:
        TEntidad();
        virtual ~TEntidad();

        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;

    protected:

    private:
};

#endif // TENTIDAD_H
