#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <type_traits>
#include <memory>

template<typename T>
class Optional
{
    using data_t = typename std::aligned_storage<sizeof (T), std::alignment_of<T>::value>::type;    //自定义的内存对齐的数据缓冲区类型
public:
    Optional(){}

    Optional(const T& t){
        Create(t);
    }

    Optional(const Optional& opt){
        if(opt.isInit()){
            Assign(opt);
        }
    }

    Optional& operator=(const Optional& opt)
    {
        if(&opt == this) return *this;
        if(opt.isInit()){
            Assign(opt);
        }
    }

    ~Optional()
    {
        Destroy();
    }

    template<class...Args>                              //支持可变参数传参
    void Emplace(Args&&...args){
        Destroy();
        Create(args...);
    }

    bool isInit() const{
        return m_hasInit;
    }

    explicit operator bool () const{
        return isInit();
    }

    T const& operator*() const{
        if(isInit()){
            return *((T*)(&m_data));
        }
    }


    //使用方式：1.good3 = good2 ; 2.good3.operator=(good2);

private:
    template<class...Args>
    void Create(Args...args){
        new (&m_data) T(std::forward<Args>(args)...);
        m_hasInit = true;
    }

    void Destroy(){
        if(m_hasInit){
            m_hasInit = false;
            ((T*)(&m_data))->~T();
        }
    }

    void Assign(const Optional& opt){
        if(opt.isInit()){
            Copy(opt.m_data);
            m_hasInit = true;
        }else{
            Destroy();
        }
    }

    void Copy(const data_t& value){
        Destroy();
        new (&m_data) T(*((T*)(&value)));
    }


private:
    bool m_hasInit = false;         //是否初始化
    data_t m_data;                  //数据缓存区
};

#endif // OPTIONAL_H
