#include <catch2/catch_test_macros.hpp>
#include <sup.hpp>
#include <cstdlib>
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
    virtual optional<string> name() const {return "Named";}
};

TEST_CASE ("Sanity") {
    REQUIRE (2 + 2 == 4);
}

TEST_CASE ("Basic", "[sup]") {
    Sup app;

    new HelloWorld(&app);

    REQUIRE(app.findChild<HelloWorld>()->hello() == "hello world");
    REQUIRE(app.children().size() == 1);
    REQUIRE(app.children<FooBar>().size() == 0);
    new Named(new FooBar(&app));
    REQUIRE(app.children(true).size() == 3);

    REQUIRE(app.parent() == nullptr);
    REQUIRE(app.findChild<HelloWorld>()->parent() == &app);
}

TEST_CASE("Managed", "[manage]") {
    Sup app;
    char *c = (char*)malloc(sizeof(char));
    *c = 'a';
    REQUIRE(*c == 'a');
    app.manage([&c](){free(c);});
    // if it didn't work, the test will leak memory. check it with valgrind.
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

TEST_CASE("Find Parent", "[findParent]") {
    Sup app;

    new Named(new FooBar(new HelloWorld(&app)));

    REQUIRE(app.findChild<Named>()->findParent<FooBar>() == app.findChild<FooBar>());
    REQUIRE(app.findChild<Named>()->findParent<HelloWorld>() == app.findChild<HelloWorld>());
}
