#pragma once

// -------------------------------------------------------------------------- //
// Configuration. Ok to change.
// -------------------------------------------------------------------------- //

/** Enable assertions for all configurations. */
#undef NDEBUG

/** Perform naive recovery of structural types. */
#define NC_STRUCT_RECOVERY

/** Generate constants for constant expressions whenever possible. */
#define NC_PREFER_CONSTANTS_TO_EXPRESSIONS

/** Generate C strings instead of their addresses. */
#define NC_PREFER_CSTRINGS_TO_CONSTANTS

/** Generate references to global variables instead of constants. */
// #define NC_PREFER_GLOBAL_VARIABLES_TO_CONSTANTS

/** Generate function names instead of constants. */
#define NC_PREFER_FUNCTIONS_TO_CONSTANTS

/** Use threads. */
// #cmakedefine NC_USE_THREADS

// -------------------------------------------------------------------------- //
// Globals. Do not change.
// -------------------------------------------------------------------------- //

/* Disable some bogus warnings. */
#ifdef _MSC_VER
#                               /* We cannot put this pragma in a push-pop block as the actual warning is triggered in
#   * template instantiations. */
#pragma warning(disable : 4355) /* C4355: 'this' : used in base member initializer list. */
#
#if _MSC_VER == 1600
#                               /* The C++11 standard specifies that the std::hash template shall be
#        * declared using the 'struct' keyword but Visual Studio 2010 Standard
#        * C++ Library declares std::hash as a 'class'. */
#pragma warning(disable : 4099) /* C4099: 'identifier' : type name first seen using                                    \
#                                      * 'objecttype1' now seen using 'objecttype2'. */
#endif
#endif

/* Get GCC version in a format suitable for comparisons. */
#if defined(__GNUC__) && !defined(__clang__)
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

/* Use expression-template-based string concatenation in Qt. */
#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

/* Disable override specifier for GCC < 4.7. */
#if defined(GCC_VERSION) && (GCC_VERSION < 40700)
#define override
#endif

/* Define noexcept as throw() for MSVC before 2015. */
#ifdef _MSC_VER
#if _MSC_VER < 1900
#define noexcept throw()
#define _ALLOW_KEYWORD_MACROS /* Disable Error: The C++ Standard Library forbids macroizing keywords. */
#endif
#endif

/* Ready-made std::make_unique implementation. */
#ifdef _MSC_VER
#if _MSC_VER >= 1800
#define NC_HAVE_STD_MAKE_UNIQUE
#endif
#endif

/* Range-based for. */
#ifdef _MSC_VER
#if _MSC_VER >= 1700
#define NC_HAVE_RANGE_BASED_FOR
#endif
#else
#define NC_HAVE_RANGE_BASED_FOR
#endif

/**
 * Helpful diagnostic for foreach macro.
 *
 * This definition also doesn't let Qt's foreach to get in.
 */
#define foreach(a, b) YOU_HAVE_FORGOTTEN_TO_INCLUDE_COMMON_FOREACH_H;

/* Workaround QTBUG-22829. */
#ifdef Q_MOC_RUN
#define BOOST_ARRAY_HPP
#define BOOST_CONFIG_HPP
#define BOOST_CSTDINT_HPP
#define BOOST_FUNCTIONAL_FACTORY_HPP_INCLUDED
#define BOOST_ITERATOR_HPP
#define BOOST_MPL_AND_HPP_INCLUDED
#define BOOST_MPL_AUX_ADL_BARRIER_HPP_INCLUDED
#define BOOST_MPL_INT_HPP_INCLUDED
#define BOOST_NONCOPYABLE_HPP
#define BOOST_OPERATORS_HPP
#define BOOST_OPTIONAL_FLC_19NOV2002_HPP
#define BOOST_PREPROCESSOR_CAT_HPP
#define BOOST_RANGE_ADAPTOR_MAP_HPP
#define BOOST_RANGE_BEGIN_HPP
#define BOOST_RANGE_END_HPP
#define BOOST_RANGE_ITERATOR_HPP
#define BOOST_RANGE_SIZE_HPP
#define BOOST_RANGE_VALUE_TYPE_HPP
#define BOOST_STATIC_ASSERT_HPP
#define BOOST_TT_IS_BASE_OF_HPP_INCLUDED
#define BOOST_TT_IS_INTEGRAL_HPP_INCLUDED
#define BOOST_TT_IS_POINTER_HPP_INCLUDED
#define BOOST_TT_IS_POLYMORPHIC_HPP
#define BOOST_UNORDERED_MAP_HPP_INCLUDED
#define BOOST_UNORDERED_SET_HPP_INCLUDED
#define BOOST_UTILITY_ENABLE_IF_HPP
#define ITERATOR_DWA122600_HPP_
#define ITERATOR_TRAITS_DWA200347_HPP
#define UUID_316FDA946C0D11DEA9CBAE5255D89593
#define BOOST_FOREACH
#define BOOST_RANGE_ADAPTOR_REVERSED_HPP
#endif

/* vim:set et sts=4 sw=4: */
