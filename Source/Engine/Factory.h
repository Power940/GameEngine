#pragma once
#include <memory>
#include "Object.h"
#include "Utils.h"
#include "Singleton.h"
#include <map>

namespace STR_FALL
{
	class ICreator
	{
	public:
		virtual ~ICreator() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};

	template <typename T>
	requires std::derived_from<T, Object>
	class Creator : public ICreator
	{
	public:
		std::unique_ptr<Object> Create() override { return std::make_unique<T>(); }
	};

	class Factory : public Singleton<Factory>
	{
	private:
		std::map<std::string, std::unique_ptr<ICreator>> m_registry;

	public:
		template <typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name)
		{
			std::string lowerName = ToLower(name);

			if (m_registry.contains(lowerName))
			{
				std::cerr << "Object already registered: " << name << std::endl;
				return;
			}
			m_registry[lowerName] = std::make_unique<Creator<T>>();
		}

		template <typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name)
		{
			std::string lowerName = ToLower(name);

			if (!m_registry.contains(lowerName))
			{
				std::cerr << "Object isn't in registry: " << name << std::endl;
				return std::unique_ptr<T>();
			}

			auto object = m_registry[lowerName]->Create();

			T* derived = dynamic_cast<T*>(object.get());
			if (derived)
			{
				object.release();
				return std::unique_ptr<T>(derived);
			}
			else
			{
				std::cerr << "Object not derived | Name: " << name << " Type: " << typeid(T).name() << std::endl;
				return std::unique_ptr<T>();
			}
			return std::unique_ptr<T>();
		}
	};
}