#include "bigint.hpp"
#include <algorithm>
    void bigint::remove_zeros()
    {
        while(store.size() > 1 && store[0] == '0')
            store.erase(0,1);
    }
    std::string bigint::add_string(const std::string &a, const std::string &b) const
    {
        std::string r ;
        int i = a.size() -1;
        int j = b.size() -1;
        int c = 0;
        int s;
        while(i>=0||j>=0||c)
        {
            s = c + (i>=0?a[i--] -'0': 0) + (j>=0?b[j--] - '0' : 0);
            r += (s%10) + '0';
            c = s /10; 
        }
        std::reverse(r.begin(), r.end());
        return r;
    }
    unsigned long long bigint::from_string(const std::string &s) const
    {
            unsigned long long   r = 0;
            for(size_t i = 0; i <  s.size(); i++)
            {
                char c = s[i];
                if(!isdigit(c))
                    throw std::invalid_argument("err");
                r = r * 10 + (c - '0');
            }
            return r;
    }
        bigint::bigint() : store("0")
        {
            
        }
        bigint::bigint(const bigint &o) : store(o.store)
        {
            
        }
        bigint::bigint(const std::string &s) : store(s)
        {
            remove_zeros();
        }   
        bigint::bigint(unsigned long long n) : store(std::to_string(n))
        {
            
        }


        bigint &bigint::operator=(const bigint &o)
        {
            if(this != &o)
            {
                store = o.store;
            }
            return *this;
        }


        bigint &bigint::operator++()
        {
            *this = *this + 1;
            return *this;
        }
        bigint bigint::operator++(int)
        {
            bigint t(*this);
            *this = *this + 1;
            return t;
        }

        bigint bigint::operator<<(const bigint &o) const
        {
            return *this << from_string(o.store);
        }
        bigint &bigint::operator<<=(const bigint &o)
        {
            return *this <<= from_string(o.store);

        }
        bigint &bigint::operator>>=(const bigint &o)
        {
            return *this >>= from_string(o.store);
            
        }
        bigint  bigint::operator>>(const bigint &o) const
        {
            return *this >> from_string(o.store);
            
        }

        bigint bigint::operator<<(int shift) const
        {
            if(shift <= 0)
                return *this;
            return store + std::string(shift, '0');
        }
        bigint &bigint::operator<<=(int shift)
        {
            *this = *this << shift;
            return *this;
        }
        bigint &bigint::operator>>=(int shift)
        {
            *this = *this >> shift;
            return *this;
        }
        bigint  bigint::operator>>(int shift) const
        {
            if(shift >= (int)store.size())
                return bigint(0);
            return store.substr(0, (store.size() - shift));
        }

        bigint bigint::operator+(const bigint &o) const
        {
            return bigint(add_string(store,o.store));
            
        }
        bigint &bigint::operator+=(const bigint &o)
        {
            store = add_string(store,o.store);
            return *this;
        }


        bigint bigint::operator+(unsigned long long n) const
        {
            return *this + bigint(n);
        }
        bigint  &bigint::operator+=(unsigned long long n)
        {
            return *this += bigint(n);
            
        }


        bool bigint::operator<(const bigint &o)const
        {
            if(store.size() != o.store.size())
            {
                return store.size() < o.store.size();
            }
            return store   < o.store;
            
        }
        bool bigint::operator>(const bigint &o)const
        {
            return o < *this;
        }
        bool bigint::operator<=(const bigint &o)const 
        {
            return !(o < *this);
            
        }
        bool bigint::operator>=(const bigint &o)const 
        {
            return !(*this < o);
            
        }
        bool bigint::operator==(const bigint &o)const
        {
            return store == o.store;
        }
        bool bigint::operator!=(const bigint &o)const
        {
            return store != o.store;
            
        }
        std::ostream &operator<<(std::ostream &s, const bigint &o)
        {
            s  << o.store;
            return s;
        }