#include <bandit/bandit.h>

using namespace bandit;

go_bandit([](){
    describe("sample", [](){
        it("Can do maths", [](){
            AssertThat(1 + 1, Equals(2));
        });
    });
});

int main(int argc, char** argv) {
    return bandit::run(argc, argv);
}
