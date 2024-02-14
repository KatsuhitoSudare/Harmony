#include"Types/type.h"
#include"gc.h"
#include"type_data.h"
#include"ItemCreator.h"

namespace HARMONY
{
	using namespace DETAIL;
	Type::Type()
	{
		
	}
	const std::string& Type::GetName() const
	{
		return _data->_name;
	}

	size_t Type::GetSize() const
	{
		return _data->_size;
	}

	bool Type::operator==(const Type& other) const
	{
		return (_data->_typeCategory == other._data->_typeCategory) &&
			(_data->_name == other._data->_name) &&
			(_data->_size == other._data->_size);
	}

	bool Type::operator!=(const Type& other) const
	{
		return !(*this == other);
	}

	Type Type::FindByName(const std::string& name)
	{
		for (auto type_base : Type_Data::_typeMap)
		{
			if (name == type_base.second._data->_name)
			{
				return type_base.second;
			}
		}
		return Type();
	}

	Type Type::FindByTypeInfo(const std::type_index& info)
	{
		for (auto type_base : Type_Data::_typeMap)
		{
			if (info == type_base.second._data->_index)
			{
				return type_base.second;
			}
		}
		return Type();
	}

	bool Type::IsArithmetic()noexcept
	{
		if (_data->_typeCategory == TYPE_CATEGORY::TYPE_ARITHMETIC)
		{
			return true;
		}
		return false;
	}

	bool Type::IsEnum()noexcept
	{
		if (_data->_typeCategory == TYPE_CATEGORY::TYPE_ENUM)
		{
			return true;
		}
		return false;
	}

	bool Type::IsArray()noexcept
	{
		if (_data->_typeCategory == TYPE_CATEGORY::TYPE_ARRAY)
		{
			return true;
		}
		return false;
	}

	bool Type::IsClass()noexcept
	{
		if (_data->_typeCategory == TYPE_CATEGORY::TYPE_OBJECT)
		{
			return true;
		}
		return false;
	}

	bool Type::IsAssociativeContainer() noexcept
	{
		if (_data->_typeCategory == TYPE_CATEGORY::TYPE_ASSOCIATIVE_CONTAINER)
		{
			return true;
		}
		return false;
	}

	bool Type::IsSequentialContainer() noexcept
	{
		if (_data->_typeCategory == TYPE_CATEGORY::TYPE_SEQUENTIAL_CONTAINER)
		{
			return true;
		}
		return false;
	}

	void* Type::CreateInstanceByType()
	{
		return (void*)GC_MALLOC(_data->_size); 
	}
}