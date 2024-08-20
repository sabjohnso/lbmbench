#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Array.hpp>
#include <lbm/core/Boundary_ID.hpp>
#include <lbm/core/import.hpp>
#include <lbm/core/subdomain_tags.hpp>

namespace lbm::core {

  /**
   * @brief A type describing degree 2 arrays
   *
   * @details This class derives from the more generic `MD_Array` class
   * with enhancements for iterating over specified boundaries and the
   * interior of the array.
   */
  template <class T>
  class Array2 : public MD_Array<T, 2> {
  public:
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;

    using Base = MD_Array<T, 2>;
    using Base::Base;

  private:
    template <typename U>
    struct Add_Const_Reference : add_lvalue_reference<add_const_t<U>> {};

    /**
     * @brief A type describing a iterator over a boundary
     *
     * @tparam boundary - A template value parameter specifing the boundary to iterate over.
     * @tparam Modifier - A template template parameter specifying the constness of the reference.
     */
    template <Boundary_Tag2 Boundary, template <class> class Modifier>
    class Generic_Boundary_Iterator {
    public:
      using Array_Reference = typename Modifier<Array2>::type;
      using Value_Reference = typename Modifier<T>::type;

      Generic_Boundary_Iterator(const Generic_Boundary_Iterator &) = default;
      Generic_Boundary_Iterator(Array_Reference array_ref, size_type index)
          : array_ref_{array_ref}
          , index_{index} {}

      Value_Reference
      operator()(size_type ioffset, size_type joffset) {
        if constexpr (same_as<Boundary, Left>) {
          return array_ref_(ioffset, index_ + joffset);
        } else if constexpr (same_as<Boundary, Right>) {
          const auto nxm1 = array_ref_.size(0) - 1;
          return array_ref_(nxm1 + ioffset, index_ + joffset);
        } else if constexpr (same_as<Boundary, Bottom>) {
          return array_ref_(index_ + ioffset, joffset);
        } else if constexpr (same_as<Boundary, Top>) {
          const auto nym1 = array_ref_.size(1) - 1;
          return array_ref_(index_ + ioffset, nym1 + joffset);
        }
      }

      Generic_Boundary_Iterator &
      operator+=(size_type offset) {
        index_ += offset;
        return *this;
      }
      Generic_Boundary_Iterator &
      operator-=(size_type offset) {
        return *this += -offset;
      }

      Generic_Boundary_Iterator &
      operator++() {
        return *this += 1;
      }

      Generic_Boundary_Iterator
      operator++(int) {
        Generic_Boundary_Iterator result{*this};
        *this += 1;
        return result;
      }

      Generic_Boundary_Iterator &
      operator--() {
        return *this -= 1;
      }

      Generic_Boundary_Iterator
      operator--(int) {
        Boundary_Iterator result{*this};
        *this -= 1;
        return result;
      }

      Value_Reference
      operator*() {
        if constexpr (same_as<Boundary, Left>) {
          return array_ref_(0, index_);
        } else if constexpr (same_as<Boundary, Right>) {
          const auto nxm1 = array_ref_.size(0) - 1;
          return array_ref_(nxm1, index_);
        } else if constexpr (same_as<Boundary, Bottom>) {
          return array_ref_(index_, 0);
        } else if constexpr (same_as<Boundary, Top>) {
          const auto nym1 = array_ref_.size(1) - 1;
          return array_ref_(index_, nym1);
        }
      }

      friend bool
      operator==(const Generic_Boundary_Iterator &iter1, const Generic_Boundary_Iterator &iter2) {
        return &iter1.array_ref_ == &iter2.array_ref_ && iter1.index_ == iter2.index_;
      }

      friend bool
      operator!=(const Generic_Boundary_Iterator &iter1, const Generic_Boundary_Iterator &iter2) {
        return !(iter1 == iter2);
      }

      size_type
      distance(const Generic_Boundary_Iterator &iter) const {
        return iter.index_ - index_;
      }

    private:
      Array_Reference &array_ref_;
      size_type index_;
    };

  public:
    template <Boundary_Tag2 Boundary>
    using Boundary_Iterator = Generic_Boundary_Iterator<Boundary, add_lvalue_reference>;

    template <Boundary_Tag2 Boundary>
    using Const_Boundary_Iterator = Generic_Boundary_Iterator<Boundary, Add_Const_Reference>;

  private:
    template <template <class> class Modifier>
    class Generic_Interior_Iterator {
    public:
      using Array_Reference = typename Modifier<Array2>::type;
      using Value_Reference = typename Modifier<T>::type;

      Generic_Interior_Iterator() = delete;
      Generic_Interior_Iterator(const Generic_Interior_Iterator &) = default;
      Generic_Interior_Iterator(Array_Reference array_ref, size_type i, size_type j)
          : array_ref_{array_ref}
          , i_(i)
          , j_(j)
          , nym1_{array_ref_.size(1) - 1} {}

      Generic_Interior_Iterator &
      operator++() {
        ++j_;
        if (j_ == nym1_) {
          ++i_;
          j_ = 1;
        }
        return *this;
      }

      Generic_Interior_Iterator
      operator++(int) {
        Generic_Interior_Iterator result = *this;
        ++(*this);
        return result;
      }

      friend bool
      operator==(const Generic_Interior_Iterator &iter1, const Generic_Interior_Iterator &iter2) {
        return &iter1.array_ref_ == &iter2.array_ref_ && iter1.i_ == iter2.i_ &&
               iter1.j_ == iter2.j_;
      }

      friend bool
      operator!=(const Generic_Interior_Iterator &iter1, const Generic_Interior_Iterator &iter2) {
        return !(iter1 == iter2);
      }

      Value_Reference
      operator()(size_type ioffset, size_type joffset) {
        return array_ref_(i_ + ioffset, j_ + joffset);
      }

      Value_Reference
      operator*() {
        return array_ref_(i_, j_);
      }

    private:
      Array_Reference array_ref_;
      size_type i_;
      size_type j_;
      size_type nym1_;
    };

  public:
    using Interior_Iterator = Generic_Interior_Iterator<add_lvalue_reference>;
    using Const_Interior_Iterator = Generic_Interior_Iterator<Add_Const_Reference>;

    using Base::begin;
    using Base::end;

    using Base::cbegin;
    using Base::cend;

    template <Boundary_Tag2 Boundary>
    Boundary_Iterator<Boundary>
    begin(Boundary) {
      return {*this, 1};
    }

    template <Boundary_Tag2 Boundary>
    Boundary_Iterator<Boundary>
    end(Boundary) {
      if constexpr (same_as<Boundary, Left> || same_as<Boundary, Right>) {
        return {*this, this->size(1) - 1};
      } else if constexpr (same_as<Boundary, Bottom> || same_as<Boundary, Top>) {
        return {*this, this->size(0) - 1};
      }
    }

    template <Boundary_Tag2 Boundary>
    Const_Boundary_Iterator<Boundary>
    begin(Boundary) const {
      return {*this, 1};
    }

    template <Boundary_Tag2 Boundary>
    Const_Boundary_Iterator<Boundary>
    end(Boundary) const {
      if constexpr (same_as<Boundary, Left> || same_as<Boundary, Right>) {
        return {*this, this->size(1) - 1};
      } else if constexpr (same_as<Boundary, Bottom> || same_as<Boundary, Top>) {
        return {*this, this->size(0) - 1};
      }
    }

    template <Boundary_Tag2 Boundary>
    Const_Boundary_Iterator<Boundary>
    cbegin(Boundary) const {
      return begin(Boundary{});
    }

    template <Boundary_Tag2 Boundary>
    Const_Boundary_Iterator<Boundary>
    cend(Boundary) const {
      return end(Boundary{});
    }

    Interior_Iterator
    begin(Interior) {
      return {*this, 1, 1};
    }

    Interior_Iterator
    end(Interior) {
      return {*this, Base::size(0) - 1, 1};
    }

    Const_Interior_Iterator
    begin(Interior) const {
      return {*this, 1, 1};
    }

    Const_Interior_Iterator
    end(Interior) const {
      return {*this, Base::size(0) - 1, 1};
    }

    Const_Interior_Iterator
    cbegin(Interior) const {
      return begin(interior);
    }

    Const_Interior_Iterator
    cend(Interior) const {
      return end(interior);
    }
  };

} // namespace lbm::core

namespace std {

  template <class T, lbm::core::Boundary_ID boundary>
  ptrdiff_t
  distance(const typename lbm::core::Array2<T>::template Boundary_Iterator<boundary> &iter1,
           const typename lbm::core::Array2<T>::template Boundary_Iterator<boundary> &iter2) {
    return iter1.distance(iter2);
  }

  template <class T, lbm::core::Boundary_ID boundary>
  ptrdiff_t
  distance(const typename lbm::core::Array2<T>::template Const_Boundary_Iterator<boundary> &iter1,
           const typename lbm::core::Array2<T>::template Const_Boundary_Iterator<boundary> &iter2) {
    return iter1.distance(iter2);
  }

} // end of namespace std
