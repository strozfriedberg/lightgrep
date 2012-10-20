/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
