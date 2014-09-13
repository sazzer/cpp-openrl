#include <bandit/bandit.h>

using namespace bandit;

go_bandit([](){
    describe("sample", [](){
        it("Can do maths", [](){
            AssertThat(1 + 1, Equals(2));
        });
        it("Can't do maths", [](){
            AssertThat(1 + 1, Equals(3));
        });
    });
});
