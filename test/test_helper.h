#pragma once

#include "automata.h"

void edge(NFA::VertexDescriptor source, NFA::VertexDescriptor target, NFA& fsm, TransitionPtr tPtr);

void edge(NFA::VertexDescriptor source, NFA::VertexDescriptor target, NFA& fsm, Transition* tPtr);

bool edgeExists(const NFA& g, const NFA::VertexDescriptor source, const NFA::VertexDescriptor target);

void ASSERT_SUPERGRAPH(const NFA& a, const NFA& b);

void ASSERT_EQUAL_GRAPHS(const NFA& a, const NFA& b);

void ASSERT_EQUAL_LABELS(const NFA& a, const NFA& b);

void ASSERT_EQUAL_MATCHES(const NFA& a, const NFA& b);

