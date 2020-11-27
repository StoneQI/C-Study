#include <type_traits>
#include <string>
#include <functional>
#include <map>
#include <memory>
#include <any>
class IocContainer
{
private:
    std::map<std::string,std::any> m_map;
    void registerType(std::string key, std::any func){
        if(m_map.find(key) != m_map.end()){
            throw std::invalid_argument("this key has exist");
        }
        m_map.emplace(key,func);
    }
    /* data */
public:
    template<class T, class Depend, typename ...args>
    typename std::enable_if<!std::is_base_of<T, Depend>::value>::type
     registerType(std::string key){
        std::function<T*(Args...)> func = [](Args...args){return new T(new Depend(args...))};
        registerType(key,func);
    }
    template<class T, class Depend, typename ...Args>
	typename std::enable_if<std::is_base_of<T, Depend>::value>::type //此时type为void
	 registerType(string key)
	{
		std::function<T*(Args...)> func = [](Args...args) {return new Depend(args...); };
		registerType(key, func);
	}

    template<class T>
    void registerType(std::string key){
        std::function<T*()> func = []{return new T()};
        registerType(key,func);
    }
    template<class T,  typename...Args>
    T* resolve(std::string key, Args ...args){
        if(m_map.find(key) != m_map.end()){
            return nullptr;
        }
        std::any func = m_map[key];
        std::function<T*(Args...)>f = func.cast<std::function<T*(Args...)>>();
        return f(args...);
    }
    template<class T, typename...Args>
    std::shared_ptr<T> resolveShared(std::string, Args ...args){
        T * t = resolve<T>(key,args...);
        return std::shared_ptr<T>(t);
    }
};

