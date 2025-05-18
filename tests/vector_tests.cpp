#define CATCH_CONFIG_MAIN
#include "../tests/catch_amalgamated.hpp"
#include "Vector.hpp"
using custm::vector;

TEST_CASE("Default constructor creates empty vector", "[constructor]")
{
    vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("copy constructor makes deep copy", "[copy_constructor]")
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    vector<int> copy(v);
    REQUIRE(copy.size() == v.size());
    REQUIRE(copy[0] == 1);
    REQUIRE(copy[1] == 2);
    // original object modification does not affect the copy
    v[0] = 100;
    REQUIRE(copy[0] == 1);
}

TEST_CASE("move constructor transfers ownership", "[move_constructor]")
{
    vector<int> v;
    v.push_back(7);
    v.push_back(8);
    vector<int> m(std::move(v));
    REQUIRE(m.size() == 2);
    REQUIRE(v.size() == 0);
    REQUIRE(m[0] == 7);
    REQUIRE(m[1] == 8);
}

TEST_CASE("copy assignment makes deep copy", "[copy_assignment]")
{
    vector<int> v;
    v.push_back(5);
    v.push_back(6);
    vector<int> a;
    a = v;
    REQUIRE(a.size() == v.size());
    REQUIRE(a[0] == 5);
    REQUIRE(a[1] == 6);
    v[0] = 100;
    REQUIRE(a[0] == 5);
}

TEST_CASE("move assignment transfers ownership", "[move_assignment]")
{
    vector<int> v;
    v.push_back(9);
    v.push_back(10);
    vector<int> a;
    a = std::move(v);
    REQUIRE(a.size() == 2);
    REQUIRE(v.size() == 0);
    REQUIRE(a[0] == 9);
    REQUIRE(a[1] == 10);
}

TEST_CASE("push_back increases size and stores elements", "[push_back]")
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 20);
}

TEST_CASE("pop_back decreases size and removes last element", "[pop_back]")
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 1);
}

TEST_CASE("reserve increases capacity without changing size", "[reserve]")
{
    vector<int> v;
    v.reserve(5);
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() >= 5);
    // add an element after reserve
    v.push_back(1);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 1);
}

TEST_CASE("resize shrinks and expands with default values", "[resize]")
{
    vector<int> v;
    v.push_back(5);
    v.push_back(6);
    v.resize(1);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 5);
    v.resize(3);
    REQUIRE(v.size() == 3);
    REQUIRE(v[1] == 0);
    REQUIRE(v[2] == 0);
}

TEST_CASE("clear resets size to zero but retains capacity", "[clear]")
{
    vector<int> v;
    v.reserve(4);
    v.push_back(1);
    v.push_back(2);
    size_t cap = v.capacity();
    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == cap);
}
