#pragma once
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

namespace licht::system {
    class ServiceLocator final {
    public:
        ServiceLocator(const ServiceLocator&) = delete;
        ServiceLocator(ServiceLocator&&) = delete;
        ServiceLocator& operator=(const ServiceLocator&) = delete;
        ServiceLocator& operator=(ServiceLocator&&) = delete;

        template <typename T>
        static inline void RegisterService(std::unique_ptr<T>&& instance) {
            GetInstance().RegisterServiceInternal<T>(std::forward<std::unique_ptr<T>>(instance));
        }

        template <typename T>
        [[nodiscard]] static inline T* GetService() {
            return GetInstance().GetServiceInternal<T>();
        }

        template <typename T>
        [[nodiscard]] static inline bool HasService() {
            return GetInstance().HasServiceInternal<T>();
        }

        template <typename T>
        static inline void RemoveService() {
            GetInstance().RemoveServiceInternal<T>();
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<void, void(*)(void*)>> m_services;

        ServiceLocator() = default;

        static ServiceLocator& GetInstance() {
            static ServiceLocator instance;
            return instance;
        }

        template <typename T>
        void RegisterServiceInternal(std::unique_ptr<T>&& instance) {
            const auto type = std::type_index(typeid(T));
            if (m_services.contains(type)) throw std::runtime_error("Already registered");

            m_services.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(type),
                std::forward_as_tuple(instance.release(), &Delete<T>)
            );
        }

        template <typename T>
        T* GetServiceInternal() {
            const auto type = std::type_index(typeid(T));
            const auto it = m_services.find(type);
            if (it == m_services.end()) throw std::runtime_error("Service does not exist");
            return static_cast<T*>(it->second.get());
        }

        template <typename T>
        bool HasServiceInternal() const {
            return m_services.contains(std::type_index(typeid(T)));
        }

        template <typename T>
        void RemoveServiceInternal() {
            m_services.erase(std::type_index(typeid(T)));
        }

        template <typename T>
        static void Delete(void* ptr) {
            delete static_cast<T*>(ptr);
        }
    };
}
