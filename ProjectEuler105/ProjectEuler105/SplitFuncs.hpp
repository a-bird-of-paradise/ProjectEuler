//
//  SplitFuncs.hpp
//  ProjectEuler105
//
//  Created by Mark Douglas on 15/12/2015.
//  Copyright © 2015 Mark Douglas. All rights reserved.
//

#pragma once

#include<vector>
#include<iostream>

typedef std::vector<uint64_t> List;
typedef std::vector<List> ListList;
typedef std::vector<std::pair<List,List>> PairList;

const int InitialCapacity = 64;

std::ostream& operator<<(std::ostream& os, const List& x);

std::ostream& operator<<(std::ostream& os, const ListList& x);

std::ostream& operator<<(std::ostream& os, const PairList& x);

ListList MakePowerSet(const List& x, const bool IncludeNullSet = true);

PairList MakeAllPairs(const ListList& x);

PairList DisjointPairs(const PairList& x);

PairList MakeSplitSet(const uint64_t n);

PairList Peel(const PairList& x, const uint64_t Remove);