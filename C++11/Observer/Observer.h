#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>
#include <functional>
#include <map>

/*
改进的观察者模式，调用更加灵活
*/

class NonCopyAble{
protected:
    NonCopyAble() = default;
    ~NonCopyAble() = default;

    NonCopyAble(const NonCopyAble&) = delete ;
    NonCopyAble& operator = (const NonCopyAble&) = delete ;
};

//模板Func代表一个可调用对象
template <typename Func>
class Events : public NonCopyAble
{
public:
    Events(){}
    ~Events(){}

    int Connect(Func&& f){
        return Assign(f);
    }

    int Connect(const Func& f){
        return Assign(f);
    }

    void Disconnect(int key){
        m_connections.erase(key);
    }

    //Args表示变长入参
    template<typename ...Args>
    void nofify(Args&& ...args){
        for(auto &it : m_connections){
            it.second(std::forward<Args>(args)...);
        }
    }

private:

    template <typename F>
    int Assign(F && f){
        int newid = m_observerId++;
        m_connections.emplace(newid, std::forward<F>(f));
        return newid;
    }

private:
    int m_observerId = 0;
    std::map<int, Func> m_connections;
};

#endif // OBSERVER_H
