#include "gtest/gtest.h"

#include <iostream>
#include <string>
using namespace std;

TEST(TEST, unique)
{
    string s = "aabccdedffddcb";

    sort(s.begin(), s.end());
    cout << s << endl;

    s.erase(unique(s.begin(), s.end()), s.end());

    cout <<s << endl;
}