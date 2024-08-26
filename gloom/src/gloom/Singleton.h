//
// Created by Bram on 25/08/2024.
//

#ifndef GLOOM_SINGLETON_H
#define GLOOM_SINGLETON_H

#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton {
public:
    static T &GetInstance() {
        static T instance{};
        return instance;
    }

    virtual ~Singleton() = default;

    Singleton(Singleton &&other) = delete;

    Singleton(const Singleton &other) = delete;

    Singleton &operator=(Singleton &&other) = delete;

    Singleton &operator=(const Singleton &other) = delete;

protected:
    Singleton() = default;
};

#endif // SINGLETON_H

#endif //GLOOM_SINGLETON_H
