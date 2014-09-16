#include <bandit/bandit.h>
#include "world/overview.h"

using namespace bandit;

go_bandit([](){
        describe("Overview Map", [](){
                World::Overview overview(50, 100);
                
                it("Remembers Width", [&](){
                        AssertThat(overview.width(), Equals(50u));
                    });
                it("Remembers Height", [&](){
                        AssertThat(overview.height(), Equals(100u));
                    });
            });
    });
