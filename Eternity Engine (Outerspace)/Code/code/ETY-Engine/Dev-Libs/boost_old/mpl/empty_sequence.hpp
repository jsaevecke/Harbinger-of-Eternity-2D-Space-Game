
#ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
// Copyright Alexander Nasonov 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: empty_sequence.hpp 3 2013-07-17 10:04:05Z Trout-31 $
// $Date: 2013-07-17 12:04:05 +0200 (Mi, 17 Jul 2013) $
// $Revision: 3 $

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace mpl {

struct empty_sequence
{
    struct tag; 
    struct begin { typedef random_access_iterator_tag category; };    
    typedef begin end;
};

template<>
struct size_impl<empty_sequence::tag>
{
    template< typename Sequence > struct apply
        : int_<0>
    {
    };
};

}}

#endif // #ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED
