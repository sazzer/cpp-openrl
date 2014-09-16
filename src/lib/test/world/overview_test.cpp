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
                it("Allows access to tiles", [&](){
                        AssertThat(overview.at(0, 0).height(), Equals(0u));
                        overview.at(0, 0).height(1u);
                        AssertThat(overview.at(0, 0).height(), Equals(1u));
                    });
                it("Allows access to different tiles", [&](){
                        overview.at(1, 1).height(1u);
                        overview.at(2, 2).height(2u);
                        AssertThat(overview.at(1, 1).height(), Equals(1u));
                        AssertThat(overview.at(2, 2).height(), Equals(2u));
                    });
            });
    });
