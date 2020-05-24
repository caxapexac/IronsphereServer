#ifndef LOGIC_SINGLETON_HPP
#define LOGIC_SINGLETON_HPP

namespace utils {
    template<class Derived>
    class singleton {
    private:
        singleton (const singleton<Derived>&);
        singleton<Derived>& operator= (const singleton<Derived>&);
    protected:
        singleton () { }

    public:
        static Derived& get () {
            static Derived theInstance;
            return theInstance;
        }
    };
}


#endif //LOGIC_SINGLETON_HPP
