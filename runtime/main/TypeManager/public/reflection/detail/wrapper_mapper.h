#pragma once
#include<memory>
#include<utility>

namespace HARMONY
{
	namespace DETAIL
	{
		//ラッパータイプじゃない場合に代わりに宣言するためのダミー型
		struct invalid_wrapper_type { };
		template<typename T>
		struct wrapper_mapper
		{
			using type = T;
			using wrapper_type = invalid_wrapper_type;
		};

		template<typename T>
		struct wrapper_mapper<std::unique_ptr<T>>
		{
			using type = std::unique_ptr<T>;
			using wrapper_type = decltype(std::declval<std::unique_ptr<T>>().get());
			static inline wrapper_type get(const type& obj)
			{
				return obj.get();
			}

			static inline type create(const wrapper_type& t)
			{
				return type(t);
			}
		};

		template<typename T>
		struct wrapper_mapper<std::shared_ptr<T>>
		{
			using type = std::shared_ptr<T>;
			using wrapper_type = decltype(std::declval<std::shared_ptr<T>>().get());
			static inline wrapper_type get(const type& obj)
			{
				return obj.get();
			}

			static inline type create(const wrapper_type& t)
			{
				return type(t);
			}
		};

		template<typename T>
		struct wrapper_mapper<std::weak_ptr<T>>
		{
			using type = std::weak_ptr<T>;
			using wrapper_type = decltype(std::declval<std::weak_ptr<T>>().get());
			static inline wrapper_type get(const type& obj)
			{
				return obj.lock.get();
			}
		};

		template<typename T>
		struct wrapper_mapper<std::reference_wrapper<T>>
		{
			using type = std::reference_wrapper<T>;
			using wrapper_type = decltype(std::declval<std::reference_wrapper<T>>().get());
			static inline wrapper_type get(const type& obj)
			{
				return obj.get();
			}

			static inline type create(const wrapper_type& t)
			{
				return type(t);
			}
		};

		/// @brief ラッパークラスのラッピング前の型を
		/// @tparam T 
		template<typename T>
		using wrapper_mapper_t = 
			typename wrapper_mapper
			<typename std::remove_cv
			<typename std::remove_reference<T>::type>
			::type>
			::wrapper_type;


		template<typename T>
		using is_wrapper = 
			std::integral_constant
			<bool, 
			!std::is_same<invalid_wrapper_type, wrapper_mapper_t<T>
			>::value >;

		template<typename T>
		typename std::enable_if<is_wrapper<T>::value, wrapper_mapper_t<T>>::type wrapped_raw_addressof(T& obj)
		{
			using raw_wrapper_type = std::remove_cv_t<std::remove_reference_t<T>>;
			wrapper_mapper_t<T> value = wrapper_mapper<raw_wrapper_type>::get(obj);
			return std::addressof(value);
		}

		//////////////////////////////////////////////////////////////////////////////////////

		template<typename T>
		typename std::enable_if<!is_wrapper<T>::value,T>::type wrapped_raw_addressof(T& obj)
		{
			return std::addressof(obj);
		}
	}
}