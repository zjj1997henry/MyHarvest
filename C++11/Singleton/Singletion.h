#ifndef SINGLETION_H
#define SINGLETION_H

#include <forward_list>

/*
改进的单例模式，使用模板，支持任意参数创建，支持完美转发。
*/

//类存储的数据是T
template<typename T>
class Singleton final   //不允许继承
{
private:

    Singleton();
    virtual ~Singleton();
    Singleton(const Singleton&);                //不允许复制
    Singleton& operator = (const Singleton&);   //不允许赋值

    static T* instance;
public:

    template<typename ...Args>
    static T *get_Instance(Args&& ...args){
        if(!instance) instance = new T(std::forward<Args>(args)...);    //完美转发
        return instance;
    }
};

template <class T>
T* Singleton<T>::instance = nullptr;
#endif // SINGLETION_H
