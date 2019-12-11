#include <iostream>
#include <string>

#include <utility>
#include <tuple>

template <std::size_t> struct overload {};


////

template <class tstruct>
auto as_tuple(tstruct&&, overload <0>) noexcept { return std::tuple{}; }

template <class tstruct>
auto as_tuple(tstruct&& obj, overload <1>) noexcept {
	auto&& [_1] = std::forward <tstruct>(obj);

	return std::forward_as_tuple(_1);
}

template <class tstruct>
auto as_tuple(tstruct&& obj, overload <2>) noexcept {
	auto&& [_1, _2] = std::forward <tstruct>(obj);

	return std::forward_as_tuple(_1, _2);
}

template <class tstruct>
auto as_tuple(tstruct&& obj, overload <3>) noexcept {
	auto&& [_1, _2, _3] = std::forward <tstruct>(obj);

	return std::forward_as_tuple(_1, _2, _3);
}

template <class tstruct>
auto as_tuple(tstruct&& obj, overload <4>) noexcept {
	auto&& [_1, _2, _3, _4] = std::forward <tstruct>(obj);

	return std::forward_as_tuple(_1, _2, _3, _4);
}

template <class tstruct>
auto as_tuple(tstruct&& obj, overload <5>) noexcept {
	auto&& [_1, _2, _3, _4, _5] = std::forward <tstruct>(obj);

	return std::forward_as_tuple(_1, _2, _3, _4, _5);
}

////


// generic type
template <std::size_t>
struct auto_t {
	template <class t> operator t() { return t{}; }
};

// sfinae aggregate initialization
template <class tstruct, std::size_t... indexes>
auto aggregate(std::index_sequence <indexes...>) -> decltype(std::decay_t <tstruct>{ auto_t <indexes>{}... }, void()) {
}


//

template <class tstruct, std::size_t n = 0, class = std::void_t <>>
struct rank : std::integral_constant <std::size_t, n> {
};

template <class tstruct, std::size_t n>
struct rank <tstruct, n, std::void_t <decltype(/**/ aggregate <tstruct>(std::make_index_sequence <n + 1>()) /**/) >> : rank <tstruct, n + 1> {
};

template <class tstruct>
inline constexpr std::size_t rank_v = rank <tstruct>::value;

//


template <std::size_t index, class tstruct>
decltype(auto) get(tstruct&& obj) {
	return std::get <index>(as_tuple(std::forward <tstruct>(obj), overload <rank_v <tstruct>>{}));
}


//

template <class tstruct, class ptr_f, std::size_t... indexes>
void for_each_impl(tstruct&& obj, ptr_f f, std::index_sequence <indexes...>) {
	(f(get <indexes>(std::forward <tstruct>(obj))), ...);
}

template <class tstruct, class ptr_f>
void for_each(tstruct&& obj, ptr_f f) {
	for_each_impl(std::forward<tstruct>(obj), f, std::make_index_sequence <rank_v <tstruct>>());
}

//


//

template <class ptr_f, class tstruct, std::size_t... indexes>
void apply_impl(ptr_f f, tstruct&& obj, std::index_sequence <indexes...>) {
	f(get <indexes>(std::forward <tstruct>(obj))...);
}

template <class ptr_f, class tstruct>
void apply(ptr_f f, tstruct&& obj) {
	apply_impl(f, std::forward <tstruct>(obj), std::make_index_sequence <rank_v <tstruct>>());
}

//
