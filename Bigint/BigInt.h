#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigInt
{
private:
    std::vector<char> v;

public:
    BigInt();
    BigInt(int);
    BigInt(const std::string&);
    BigInt operator+(const BigInt&);
    BigInt operator++();
    BigInt operator++(int);
    BigInt operator*(const BigInt&);
    BigInt half() const;
    bool isOdd() const;
    bool isEven() const;
    bool operator==(const BigInt&) const;
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    bool operator<(const BigInt&) const;
};
