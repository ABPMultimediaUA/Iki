#ifndef SINGLETON_H
#define SINGLETON_H


class Singleton
{
    public:
        static Singleton* Instance();
        Singleton();
        virtual ~Singleton();
        Singleton(const Singleton& orig);

    private:
        static Singleton* pinstance;
};

#endif // SINGLETON_H
