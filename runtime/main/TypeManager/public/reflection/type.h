#pragma once
#include<string_view>
#include<vector>
#include<typeindex>
#include<memory>

namespace HARMONY
{
	class variant;
	class enumeration;
	class constructor;
	class property;
	class instance;

	namespace DETAIL
	{
		struct type_data;
	}

	class TYPEMANAGER_API type
	{
	public:
		type(const type& othr);
		template<typename T>
		static type get();

		template<typename T>
		static type get(T&& object);

		static type getByName(std::string_view name); 

		variant Create();

		template<typename... Args>
		variant Create(Args... arg);

		std::string_view GetName();

		std::type_index GetTypeID();

		std::size_t GetSizeof()const noexcept;

		explicit operator bool()const noexcept;

		type GetRawType()noexcept;

		type GetWrappedType()const noexcept;  

		enumeration GetEnumeration()const;

		constructor GetConstructor()const noexcept;

		property GetProperty(std::string_view prop_name)noexcept;

		std::vector<property> GetProperties()noexcept;

		variant GetPropertyValue(std::string_view name,instance obj)noexcept; 

		bool SetPropertyValue(std::string_view name, instance obj)noexcept;

		bool isValid()noexcept;

		bool isArithmetic()noexcept;

		bool isEnumeration()noexcept;

		bool isArray()noexcept;

		bool isClass()noexcept;

		bool isWrapped()noexcept;

		bool isSequential()noexcept;

		bool isAssociation()noexcept;

		bool isPointer()noexcept;

		bool isFunctionPointer()noexcept;

		bool isMemberObjectPointer()noexcept;

		bool isMemberFunctionPointer()noexcept;

	private:
		type();
		type(DETAIL::type_data* _data);
		std::unique_ptr<DETAIL::type_data> _data;
	};

	//無効なタイプ型を生成します
	type GetInvalidType();
}

#include"reflection/impl/type_impl.h"