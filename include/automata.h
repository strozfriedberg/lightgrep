/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#pragma once

#include "basic.h"
#include "graph.h"
#include "transition.h"
#include "transitionfactory.h"
#include "vectorfamily.h"

struct Properties {
  Properties(): Deterministic(true), TransFac(new TransitionFactory()) {}

  bool Deterministic;
  std::shared_ptr<TransitionFactory> TransFac;
};

struct Glushkov {
  static const uint32_t NOLABEL;

  Glushkov(): Trans(0), IsMatch(false), Label(NOLABEL) {}

  std::string label() const;

  Transition* Trans;
  bool IsMatch;
  uint32_t Label;
};

struct Empty {};

typedef Graph<Properties,Glushkov,Empty,VectorFamily> NFA;

