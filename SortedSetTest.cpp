#include <cstdlib>
#include "SortedSet.h"
#include "MtmTst.h"

static const int numElements = 10000;

struct Int {
    int i;

    Int(int i) : i(i) {}

    operator int() const { return i; }
};

class IntCompare {
public:
    bool operator()(const Int& i1, const Int& i2) const {
        return static_cast<int>(i1) < static_cast<int>(i2);
    }
};


bool sortedSetTestExample() {
    ASSERT_NO_THROW((SortedSet<Int, IntCompare>()));
    SortedSet<Int, IntCompare> s;
    for (int i = numElements; i > 0; --i) {
        ASSERT_EQUALS(numElements - i, s.size());
        ASSERT_EQUALS(true, s.insert(i));
    }
    for (int i = 2; i <= numElements; i += 2) {
        ASSERT_EQUALS(true, s.remove(i));
        ASSERT_EQUALS(numElements - i/2, s.size());
    }

    int i = 1;
    for (SortedSet<Int, IntCompare>::iterator it = s.begin(); it != s.end(); ++it) {
        ASSERT_EQUALS(i, *it);
        i += 2;
    }

    return true;
}

bool sortedSetTest() {
    RUN_TEST(sortedSetTestExample);
    return true;
}
