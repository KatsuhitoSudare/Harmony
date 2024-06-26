#pragma once
#define HM_CLASS_CREATE(className)\
static Class* _class = new (GC_NEW(Class)) Class(new (GC_NEW(ClassData)) ClassData(TEXT(#className), sizeof(className), G_Class_Declaration_Field_##className::_propertyField)	);

#define HM_ADD_PROPERTY_STRING(classType,Member)\
new (GC_NEW(PropertyString)) PropertyString(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_INT32(classType,Member)\
new (GC_NEW(PropertyInt32)) PropertyInt32(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_INT64(classType,Member)\
new (GC_NEW(PropertyInt64)) PropertyInt64(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_FLOAT(classType,Member)\
new (GC_NEW(PropertyFloat)) PropertyFloat(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_BOOL(classType,Member)\
new (GC_NEW(PropertyBool)) PropertyBool(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_ARRAY(classType,Member)\
new (GC_NEW(PropertyArray)) PropertyArray(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_CLASS(classType,Member)\
new (GC_NEW(PropertyClass)) PropertyClass(TEXT(#Member),&classType::Member)