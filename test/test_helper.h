#pragma once

#include "graph.h"

void edge(Graph::vertex source, Graph::vertex target, Graph& fsm, TransitionPtr tPtr);

void edge(Graph::vertex source, Graph::vertex target, Graph& fsm, Transition* tPtr);

void ASSERT_SUPERGRAPH(const Graph& a, const Graph& b);

void ASSERT_EQUAL_GRAPHS(const Graph& a, const Graph& b);
