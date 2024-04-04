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
				if (!prop || !object) return false;
				int32_t temp = static_cast<PropertyInt32*>(prop)->GetValue(object);
				value.Int(temp);
				return true;
			}

			bool SaveInt64(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				int64_t temp = static_cast<PropertyInt64*>(prop)->GetValue(object);
				value.Int64(temp);
				return true;
			}

			bool SaveFloat(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				float temp = static_cast<PropertyFloat*>(prop)->GetValue(object);
				value.Double(temp);
				return true;
			}

			bool SaveDouble(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				double temp = static_cast<PropertyDouble*>(prop)->GetValue(object);
				value.Double(temp);
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

			bool SaveClass(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				auto* _class = static_cast<PropertyClass*>(prop)->GetClass();
				SerializeObject(value, _class, object);
			}

			bool SaveArray(Writer& writer, Property* prop, void* object) 
			{
				if (!prop || !object) return false;

				auto propArray = static_cast<PropertyArray*>(prop);
				auto sArray = propArray->GetScriptArray(object);
				size_t size = sArray.GetSize();
				void* data = sArray.GetData();
				size_t elementSize = propArray->GetInnerElementSize();

				writer.StartArray();

				for (size_t i = 0; i < size; i++) {
					char* elementPtr = static_cast<char*>(data) + i * elementSize; // オフセット計算

					switch (propArray->GetInnerKind()) {
					case PropertyKind::Bool: {
						// bool値を取得して書き込む
						bool value = *reinterpret_cast<bool*>(elementPtr);
						writer.Bool(value);
						break;
					}
					case PropertyKind::Int32: {
						// int値を取得して書き込む
						int value = *reinterpret_cast<int*>(elementPtr);
						writer.Int(value);
						break;
					}
					case PropertyKind::Int64: {
						// int64_t値を取得して書き込む
						int64_t value = *reinterpret_cast<int64_t*>(elementPtr);
						writer.Int64(value);
						break;
					}
					case PropertyKind::Float: {
						// float値を取得して書き込む
						float value = *reinterpret_cast<float*>(elementPtr);
						writer.Double(value); // JSONにfloatはないため、doubleとして書き込む
						break;
					}
					case PropertyKind::Double: {
						// double値を取得して書き込む
						double value = *reinterpret_cast<double*>(elementPtr);
						writer.Double(value);
						break;
					}
					case PropertyKind::String: {
						// HMStringからCスタイルの文字列を取得して書き込む
						const HMString* strValue = reinterpret_cast<HMString*>(elementPtr);
						writer.String(strValue->GetRaw());
						break;
					}
					case PropertyKind::Class:
					{
						const HMString* strValue = reinterpret_cast<HMString*>(elementPtr);
						writer.String(strValue->GetRaw());
						break;
					}
					default:
						writer.Null();
						break;
					}
				}

				writer.EndArray();
				return true;
			}

			bool SerializeObject(Writer& writer, Class* classPtr, void* obj)
			{
				if (classPtr == nullptr) {
					return; // クラス情報がなければ何もしない
				}

				// クラス名をキーとして使用し、オブジェクトを開始
				writer.Key(classPtr->GetName());
				writer.StartObject();

				// 基底クラスのプロパティを再帰的にシリアライズ
				if (classPtr->GetBaseClass() != nullptr) {
					SerializeObject(writer, classPtr->GetBaseClass(), obj);
				}

				// 現在のクラスのプロパティをシリアライズ
				for (auto prop : classPtr->GetProperties()) {
					writer.Key(prop->GetName());
					auto kind = prop->GetKind();
					switch (kind) {
						// プロパティタイプに基づいて適切なシリアライズ関数を呼び出す
					case PropertyKind::Bool:
						DETAIL::SaveBool(writer, prop, obj);
						break;
					case PropertyKind::Int32:
						DETAIL::SaveInt(writer, prop, obj);
						break;
					case PropertyKind::Int64:
						DETAIL::SaveInt64(writer, prop, obj);
						break;
					case PropertyKind::Float:
						DETAIL::SaveFloat(writer, prop, obj);
						break;
					case PropertyKind::Double:
						DETAIL::SaveDouble(writer, prop, obj);
						break;
					case PropertyKind::String:
						DETAIL::SaveString(writer, prop, obj);
						break;
					case PropertyKind::Array:
						SaveArray(writer, prop, obj);
						break;
					default:
						writer.Null();
						break;
					}
				}
				// クラスのオブジェクトの終了
				writer.EndObject();
			}

		}
	}
}