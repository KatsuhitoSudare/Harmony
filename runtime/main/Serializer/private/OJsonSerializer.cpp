#include"SerializerMembers/OJsonSerializer.h"

namespace HARMONY
{
	namespace SERIALIZER
	{
		OJsonSerializer::OJsonSerializer()
		{

		}

		OJsonSerializer::~OJsonSerializer()
		{

		}

		namespace DETAIL
		{
			bool SaveBool(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				bool temp = static_cast<PropertyBool*>(prop)->GetValue(object);
				value.Bool(temp);
				return true;
			}
			bool SaveInt(Writer& value, Property* prop, void* object)
			{
				return true;
			}
			bool SaveFlat(Writer& value, Property* prop, void* object)
			{
				return true;
			}

			bool SaveString(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				HMString temp = static_cast<PropertyString*>(prop)->GetValue(object);
				TCHAR* m = temp.GetRaw();
				value.String(temp.GetRaw());
				return true;
			}
		}
	}
}