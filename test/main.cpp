#include <catch2/catch_test_macros.hpp>
#include <sup.hpp>
using namespace std;

class HelloWorld : public Sup {
public:
    HelloWorld(Sup *p) : Sup(p) {}
    string hello() {return "hello world";}
};

class FooBar : public Sup {
public:
    FooBar(Sup *p) : Sup(p) {}
    string hello() {return "baz";}
};

class Named : public Sup {
public:
    Named(Sup *p) : Sup(p) {}
    virtual optional<string> name() {return "Named";}
};

TEST_CASE ("Sanity") {
    REQUIRE (2 + 2 == 4);
}

TEST_CASE ("Basic", "[sup]") {
    Sup app;

    new HelloWorld(&app);

    REQUIRE(app.findChild<HelloWorld>()->hello() == "hello world");
}

TEST_CASE("Recursive", "[recursive]") {
    Sup app;

    new FooBar(new HelloWorld(&app));

    REQUIRE(app.findChild<FooBar>()->hello() == "baz");
    REQUIRE(app.findChild<FooBar>(nullopt, false) == nullptr);
}

TEST_CASE("Named", "[named]") {
    Sup app;

    new Named(&app);

    REQUIRE(app.findChild<Named>("Named")->name() == "Named");
    REQUIRE(app.findChild<Named>("Invalid") == nullptr);
}
