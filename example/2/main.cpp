#include <spdlog/spdlog.h>

#include "foo.pb.h"
#include "../../cache.h"

int main(int argc, char **argv){
    (void)argc, (void)argv;

    spdlog::info("Hello, App2!");

    foo::User foo1;
    foo1.set_id(1);
    foo1.set_name("foo1");

    foo::User foo2;
    foo2.set_id(2);
    foo2.set_name("foo2");

    foo::User foo3;
    foo3.set_id(3);
    foo3.set_name("foo3");


    cache::Cache<foo::User, 3> UserCache;
    bool ok = false;
    {
        auto new_ = UserCache.Peek(&ok);
        if (!ok) {
            spdlog::error("Peek error");
        }
    }

    UserCache.Update(foo1);
    UserCache.Update(foo2);
    UserCache.Update(foo3);
    UserCache.Update(foo1);
    UserCache.Update(foo1);
    UserCache.Update(foo1);
    UserCache.Update(foo2);
    UserCache.Update(foo3);
    UserCache.Update(foo1);
    UserCache.Update(foo2);

    auto new_ = UserCache.Peek(&ok);
    if (!ok) {
        spdlog::error("Peek error");
    }
    if (ok) {
        new_.PrintDebugString();
    } else {
        spdlog::error("Peek error");
    }


    return 0;
}
