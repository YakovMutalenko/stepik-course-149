#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cctype>

bool try_read_next(std::istream& ss, uint64_t& degree, int64_t& k){
    char p = ss.peek();
    if(!ss || ss.peek() == EOF)
        return false;

    int64_t mult = 1;
    if(ss.peek() == '-'){
        ss.get();
        mult = -1;
    }

    if(ss.peek() == '+'){
        ss.get();
        mult = 1;
    }

    if(isdigit(ss.peek())){
        ss >> k;
        if(ss.peek() == '*'){
            ss.get();
        }
    }
    else{
        k = 1;
    }

    k *= mult;

    degree = 0;

    if(ss.peek() == 'x'){
        ss.get();
        degree = 1;
    }

    if(ss.peek() == '^'){
        ss.get();
        ss >> degree;
    }
    return true;
}

std::string find_derivative(const std::map<uint64_t, int64_t>& degrees){
    std::stringstream result;
    bool first = true;
    for(auto it = degrees.crbegin(); it != degrees.crend(); ++it){
        if(it->first == 0 || it->second == 0){
            continue;
        }

        if(false == first && it->second > 0){
            result << '+';
        }
        first = false;

        result << it->second * (int64_t)it->first;

        if(it->first == 1)
            continue;

        if(it->first == 2){
            result << "*x";
        }
        else{
            result << "*x^" << it->first - 1;
        }


    }

    return result.str();
}

std::string derivative(std::string polynomial) {
    std::stringstream ss(polynomial);
    std::map<uint64_t, int64_t> degrees;
    uint64_t degree;
    int64_t k;
    while (try_read_next(ss, degree, k))
    {
        if(degree > 0){
            degrees[degree] += k;
        }
    }

    return find_derivative(degrees);
}
