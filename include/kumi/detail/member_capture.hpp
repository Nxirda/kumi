#pragma once

#include <iostream>
#include <cstdint>

namespace himo
{
    struct str
    {
        static constexpr std::size_t max_size = 64;

        char            data_[max_size+1];
        std::uint8_t    size_;

        template<std::size_t N, std::size_t... Is>
        constexpr str(const char (&s)[N], std::index_sequence<Is...>)
            : data_{s[Is]...}, size_(N)
        {}

        template <std::size_t N>
        constexpr str(const char (&s)[N])
            : str{s, std::make_index_sequence<N>{}}
        {}

        constexpr std::size_t       size()  const { return size_; }
        constexpr std::string_view  value() const { return std::string_view(&data_[0], size_); }

        friend constexpr bool operator <=>(str const&, str const&) noexcept = default;

        friend std::ostream& operator<<(std::ostream& os, str const& s)
        {
            return os << '\'' << s.value() << '\'';
        }
    };
}

namespace kumi::_
{
    template<himo::str ID, typename T>
    struct member_capture
    {
        using type = T;
        T value;
        
        static constexpr auto name = ID;
        
        constexpr operator T() const noexcept { return value; };
        constexpr operator T&() noexcept { return value; };
        
        friend std::ostream& operator<<(std::ostream& os, member_capture const& w)
        {
          return os << ID << " : " << w.value;
        }
    };

    template<himo::str ID>
    struct member_name
    {
        static constexpr auto name = ID;

        friend std::ostream& operator<<(std::ostream& os, member_name const&)
        {
          return os << ID;
        }
        
        template<typename T>
        constexpr member_capture<ID,T> operator=(T v)
        {
            return {std::move(v)};
        }
    };

//================================================================================================

    template<typename T>
    struct is_member_capture : std::false_type{};

    template<himo::str ID, typename T>
    struct is_member_capture<member_capture<ID, T>> : std::true_type{};

    template<typename T>
    inline constexpr bool is_member_capture_v = is_member_capture<T>::value;

//================================================================================================

    template<typename T>
    struct unwrap_member_capture
    {
        using type = T;
    };
    
    template<himo::str ID, typename T> 
    struct unwrap_member_capture<member_capture<ID, T>>
    {
        using type = T;
    };
    
    template<typename T>
    using unwrap_member_capture_t = typename unwrap_member_capture<T>::type;

//================================================================================================

    template<typename T>
    struct is_named;

    template<typename T>
    requires( requires { T::is_named; } )
    struct is_named<T> : std::bool_constant<T::is_named>
    {};

    template<typename T>
    inline constexpr auto is_named_v = is_named<T>::value;

    template<typename T>
    concept named_tuple = product_type<T> && is_named_v<std::remove_cvref_t<T>>;
//================================================================================================

    template<auto... Ts>
    struct name_list {};

    template<named_tuple T>
    constexpr auto names_of(T const&)
    {
        return []<std::size_t...I>(std::index_sequence<I...>)
        {
            return name_list<element_t<I,T>::name...>{};
        }
        (std::make_index_sequence<size_v<T>>{});
    }
    
    namespace result
    {
        template<named_tuple T>
        struct names_of
        {
            using type = decltype( kumi::_::names_of( std::declval<T>() ));
        };

        template<named_tuple T>
        using names_of_t = typename names_of<T>::type;
    }

//================================================================================================

    template<typename T, typename U>
    constexpr auto check_matching_names()
    {
        return []<auto...Names>( name_list<Names...> )
        {
            return (( _::comparable<  element_t<T::template get_name_index<Names>(), T>
                                    , element_t<U::template get_name_index<Names>(), U>
                                    >
                    ) && ...);
        }( result::names_of_t<T>{} ); 
    }

    template<typename T, typename U>
    concept named_equality_comparable = (named_tuple<T>) && (named_tuple<U>) 
                                     && (size_v<T> == size_v<U>) 
                                     && _::check_matching_names<T,U>();

}

namespace kumi::literals
{
    template<himo::str ID>
    inline constexpr auto member = kumi::_::member_name<ID>{};
    
    template<himo::str ID> constexpr auto operator""_m() noexcept { return member<ID>; }
}
