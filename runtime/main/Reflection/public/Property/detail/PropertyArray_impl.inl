#include"Property/PropertyArray.h"
#pragma once
#include"Property/PropertyAccessor.h"
#include"gc/gc.h"
#include<new>

namespace HARMONY
{
	template<typename C, typename T>
	inline PropertyArray::PropertyArray(const TCHAR* name, HARMONY::HMArray<T> C::* memberptr)
	:PropertyArray::Property
	(
		name,
		nullptr,
		sizeof(T)
	)
	{
		GetScriptArrayFunc = [memberptr](void* classinstance)->ScriptArray {
			C* pclass = reinterpret_cast<C*>(classinstance);
			return ScriptArray(&(pclass->*memberptr));
		};
	}
}