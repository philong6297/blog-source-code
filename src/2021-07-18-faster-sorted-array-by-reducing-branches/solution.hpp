// Copyright 2021 Long Le Phi. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef _2021_07_18_HPP_
#define _2021_07_18_HPP_

#include <algorithm>
#include <cstdint>

namespace longlp {

  // Constructs a sorted union beginning at d_first consisting of the set of
  // elements present in both sorted ranges [first1, last1) and [first2,
  // last2)
  //
  //  Parameters
  //  first1, last1  -  the first input sorted range
  //  first2, last2  -  the second input sorted range
  //  d_first        -  the beginning of the output range
  //  comp           -  comparison function object (i.e. an object that
  //                    satisfies the requirements of Compare) which returns
  //                    ​true if the first argument is "less" than (i.e. is
  //                    ordered before) the second. The signature of the
  //                    comparison function should be equivalent to the
  //                    following:
  //
  //                      bool cmp(const Type1 &a, const Type2 &b);
  //
  //                    While the signature does not need to have const &, the
  //                    function must not modify the objects passed to it and
  //                    must be able to accept all values of type (possibly
  //                    const) Type1 and Type2 regardless of value category
  //                    (thus, Type1 & is not allowed, nor is Type1 unless for
  //                    Type1 a move is equivalent to a copy (since C++11)).
  //                    The types Type1 and Type2 must be such that objects of
  //                    types InputIt1 and InputIt2 can be dereferenced and
  //                    then implicitly converted to both Type1 and Type2.​
  //
  //  Type requirements
  //  - InputIt1, InputIt2 must meet the requirements of LegacyInputIterator.
  //  - ForwardIt1, ForwardIt2, ForwardIt3 must meet the requirements of
  //    LegacyForwardIterator.
  //
  //  Return value
  //  Iterator past the end of the constructed range.
  struct Union2By2 {
    template <typename ForwardIt1,
              typename ForwardIt2,
              typename ForwardIt3,
              typename Compare = std::less<>>
    static auto StandardVersion(ForwardIt1 first1,
                                ForwardIt1 last1,
                                ForwardIt2 first2,
                                ForwardIt2 last2,
                                ForwardIt3 d_first,
                                Compare comp = Compare{}) -> ForwardIt3 {
      return std::set_union(first1, last1, first2, last2, d_first, comp);
    }

    template <typename ForwardIt1,
              typename ForwardIt2,
              typename ForwardIt3,
              typename Compare = std::less<>>
    static auto BranchlessVersion(ForwardIt1 first1,
                                  ForwardIt1 last1,
                                  ForwardIt2 first2,
                                  ForwardIt2 last2,
                                  ForwardIt3 d_first,
                                  Compare comp = Compare{}) -> ForwardIt3 {
      while ((first1 != last1) && (first2 != last2)) {
        const bool comp_is_true = comp(*first1, *first2);

        *(d_first++) = comp_is_true ? *first1 : *first2;

        std::advance(first1, comp_is_true);
        std::advance(first2, !comp_is_true);
      }

      std::copy(first1, last1, d_first);
      std::copy(first2, last2, d_first);

      return d_first;
    }
  };

}   // namespace longlp

#endif   // _2021_07_18_HPP_
