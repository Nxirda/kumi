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

        friend std::ostream& operator<<(std::ostream& os, member_capture const& w)
        {
          return os << ID << " : " << w.value;
        }
    };

    template<himo::str ID>
    struct member_name
    {
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

    template<typename T>
    struct is_member_capture : std::false_type{};

    template<himo::str ID, typename T>
    struct is_member_capture<member_capture<ID, T>> : std::true_type{};

    template<typename T>
    inline constexpr bool is_member_capture_v = is_member_capture<T>::value;
    
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
}

namespace kumi::literals
{
    template<himo::str ID>
    inline constexpr auto member = kumi::_::member_name<ID>{};
    
    template<himo::str ID> constexpr auto operator""_m() noexcept { return member<ID>; }
}
