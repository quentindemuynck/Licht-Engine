#pragma once
#include <expected>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

namespace licht::system {
    enum class ServiceLocatorError
    {
        not_found
    };

    class ServiceLocator final {
    public:
        ServiceLocator() = default;

        ServiceLocator(const ServiceLocator&) = delete;
        ServiceLocator(ServiceLocator&&) = delete;
        ServiceLocator& operator=(const ServiceLocator&) = delete;
        ServiceLocator& operator=(ServiceLocator&&) = delete;

        template <typename T>
        auto RegisterService(std::unique_ptr<T>&& instance)  {
            const auto type = std::type_index(typeid(T));
            if (m_services.contains(type)) throw std::runtime_error("Service already registered");

            m_services.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(type),
                std::forward_as_tuple(instance.release(), &Delete<T>)
            );
        }

        template <typename T>
        [[nodiscard]] auto GetService() -> std::expected<T*, ServiceLocatorError>  {
            const auto type = std::type_index(typeid(T));
            const auto it = m_services.find(type);
            if (it == m_services.end()) return std::unexpected(ServiceLocatorError::not_found);
            return static_cast<T*>(it->second.get());
        }

        template <typename T>
        bool HasService() const {
            return m_services.contains(std::type_index(typeid(T)));
        }

        template <typename T>
        void RemoveService() {
            m_services.erase(std::type_index(typeid(T)));
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<void, void(*)(void*)>> m_services;

        template <typename T>
        static void Delete(void* ptr) {
            delete static_cast<T*>(ptr);
        }
    };
}
