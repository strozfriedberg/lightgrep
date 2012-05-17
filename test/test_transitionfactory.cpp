#include <scope/test.h>

#include "states.h"
#include "transition.h"
#include "transitionfactory.h"

template <class StateType>
void smallestTester(const ByteSet& ebs) {
  TransitionFactory tfac;
  StateType* state = dynamic_cast<StateType*>(tfac.getSmallest(ebs));
  SCOPE_ASSERT(state);
  ByteSet abs;
  state->getBytes(abs);
  SCOPE_ASSERT_EQUAL(ebs, abs);
}

SCOPE_TEST(getSmallestNoneTest) {
  const ByteSet ebs;
  smallestTester<ByteSetState>(ebs);
}

SCOPE_TEST(getSmallestOneTest) {
  const ByteSet ebs('z');
  smallestTester<ByteState>(ebs);
}

SCOPE_TEST(getSmallestTwoTest) {
  ByteSet ebs;
  ebs.set('a');
  ebs.set('z');
  smallestTester<EitherState>(ebs);
}

SCOPE_TEST(getSmallestRangeTest) {
  ByteSet ebs;
  ebs.set('a', 'z' + 1, true);
  smallestTester<RangeState>(ebs);
}

SCOPE_TEST(getSmallestManyTest) {
  ByteSet ebs;
  ebs.set('A');
  ebs.set('a');
  ebs.set('b');
  smallestTester<ByteSetState>(ebs);
}
