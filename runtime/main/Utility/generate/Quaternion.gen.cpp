#include"Quaternion.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Quaternion()
{
    HARMONY::ClassBuilder::Registration(TEXT("Quaternion"), &HARMONY::MATH::Quaternion::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_Quaternion
{
   AUTO_REGISTER_STRUCTURE_Quaternion()
    {
       G_AUTO_REGISTER_FUNCTION_Quaternion();
    }
};
struct AUTO_REGISTER_STRUCTURE_Quaternion ARS={};
namespace HARMONY{
namespace MATH{
   struct G_Class_Declaration_Field_Quaternion
    {
       const static inline HMArray<Property*> _propertyField = 
        {
           HM_ADD_PROPERTY_FLOAT(Quaternion,x),
           HM_ADD_PROPERTY_FLOAT(Quaternion,y),
           HM_ADD_PROPERTY_FLOAT(Quaternion,z),
           HM_ADD_PROPERTY_FLOAT(Quaternion,w),
        };
    };
   inline Class* Quaternion::G_GetClassDataQuaternion()
    {
       HM_CLASS_CREATE(Quaternion,nullptr)
return _class;

    }
}
}
