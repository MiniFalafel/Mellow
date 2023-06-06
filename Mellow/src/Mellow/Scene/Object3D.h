#pragma once

#include "Transform3D.h"

#include <any>

namespace Mellow
{

	class Object3D
	{
	public:

		struct CustomAttributeList
		{
			std::map<const char*, std::any> RawAttributeList; // keeping this public in case it's useful somehow.

			template<typename T>
			void AddAttribute(const char* name, T attrib)
			{
				RawAttributeList.emplace(std::make_pair(name, std::make_any<T>(attrib)));
			}

			template<typename T>
			T GetAttribute(const char* name)
			{
				try
				{
					return std::any_cast<T>(RawAttributeList[name]);
				}
				catch (std::bad_any_cast& e)
				{
					MW_CORE_ERROR("CANT CAST {0} to that type!:\n   {1}", name, e.what());
				}
			}
		};

		struct ObjectData
		{
			std::string Name;
			Transform3D Transform;
			CustomAttributeList CustomAttributes;
		};

	private:
		ObjectData m_Data;
		std::vector<Ref<Object3D>> m_ChildObjects;

	};

}
