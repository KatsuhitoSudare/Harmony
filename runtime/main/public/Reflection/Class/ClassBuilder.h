#pragma once
#include"HMString.h"
#include"Array/HMArray.h"
#include"Map/HMUnorderedMap.h"
#include<functional>

namespace HARMONY
{
	class Class;
	class UTILITY_API ClassBuilder
	{
	public:
		static void Registration(const TCHAR* name, Class* (*classCreateFunc)());
		static void RegistrationBaseClass(const TCHAR* name, Class* (*myClassFunc)());
		static Class* GetClassByname(const TCHAR* name);
	private:
		static inline HMUnorderedMap<HMString, Class* (*)()> _classCreatorFunction;
		static inline HMUnorderedMap<HMString, HMArray<Class* (*)()>> _derivedClass;
	};
}