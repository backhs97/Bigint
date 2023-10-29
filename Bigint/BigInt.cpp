#include "BigInt.h"

BigInt::BigInt() : v(1, '0') {}

BigInt::BigInt(int num)
{
    while (num)
    {
        v.push_back(num % 10 + '0');
        num /= 10;
    }
    std::reverse(v.begin(), v.end());
}

BigInt::BigInt(const std::string& num)
{
    for (const char& c : num)
    {
        if (isdigit(c))
            v.push_back(c);
    }
}

BigInt BigInt::operator+(const BigInt& rhs)
{
    std::string result = "";
    int carry = 0, sum;

    auto lhs_it = this->v.rbegin();
    auto rhs_it = rhs.v.rbegin();

    while (lhs_it != this->v.rend() || rhs_it != rhs.v.rend())
    {
        sum = carry;
        if (lhs_it != this->v.rend())
        {
            sum += *lhs_it - '0';
            lhs_it++;
        }
        if (rhs_it != rhs.v.rend())
        {
            sum += *rhs_it - '0';
            rhs_it++;
        }
        carry = sum / 10;
        result += std::to_string(sum % 10);
    }

    if (carry)
        result += std::to_string(carry);

    std::reverse(result.begin(), result.end());
    return BigInt(result);
}

BigInt BigInt::operator++()
{
    *this = *this + 1;
    return *this;
}

BigInt BigInt::operator++(int)
{
    BigInt temp = *this;
    ++* this;
    return temp;
}

bool BigInt::operator<(const BigInt& rhs) const
{
    if (this->v.size() != rhs.v.size())
    {
        return this->v.size() < rhs.v.size();
    }
    else
    {
        for (size_t i = 0; i < this->v.size(); ++i)
        {
            if (this->v[i] != rhs.v[i])
            {
                return this->v[i] < rhs.v[i];
            }
        }
    }
    return false;
}


BigInt BigInt::operator*(const BigInt& rhs)
{
    BigInt result("0");

    if (this->isEven() && rhs.isEven())
    {
        BigInt lhs_half = this->half();
        BigInt rhs_half = rhs.half();
        BigInt temp = lhs_half * rhs_half;
        result = temp + temp;
    }
    else
    {
        for (BigInt i = 0; i < rhs; i++)
        {
            result = result + *this;
        }
    }

    return result;
}

BigInt BigInt::half() const
{
    std::string result = "";
    int carry = 0;
    for (const char& digit : this->v)
    {
        int current = carry * 10 + (digit - '0');
        result += std::to_string(current / 2);
        carry = current % 2;
    }

    if (result[0] == '0' && result.length() > 1)
        result.erase(result.begin());

    return BigInt(result);
}


bool BigInt::isOdd() const
{
    return (this->v.back() - '0') % 2 != 0;
}

bool BigInt::isEven() const
{
    return (this->v.back() - '0') % 2 == 0;
}

bool BigInt::operator==(const BigInt& rhs) const
{
    return this->v == rhs.v;
}

std::ostream& operator<<(std::ostream& os, const BigInt& num)
{
    for (const char& digit : num.v)
    {
        os << digit;
    }
    return os;
}
