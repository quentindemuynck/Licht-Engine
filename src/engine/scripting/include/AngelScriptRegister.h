#pragma once
#include <string>

// Add-ons
#include <scriptstdstring.h>
#include <scriptarray.h>
#include <scriptdictionary.h>
#include <scriptbuilder.h>

#include <cassert>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "AngelScriptStubWriter.h"

namespace licht::scripting
{
    [[angelscript("test")]]
    inline void registration_succes_checker(int r, const std::string& what)
    {
        if (r < 0)
        {
            spdlog::error("Angel script registration failed: {}", what);
            throw std::runtime_error("Angelscript registration failed");
        }
    }

    class AngelScriptRegister final
    {
    public:
        explicit AngelScriptRegister(asIScriptEngine& engine, AngelScriptStubWriter& writer)
            : m_engine(engine)
            , m_writer(writer)
        {
        }

        AngelScriptRegister(const AngelScriptRegister&) = delete;
        AngelScriptRegister& operator=(const AngelScriptRegister&) = delete;
        AngelScriptRegister(AngelScriptRegister&&) = delete;
        AngelScriptRegister& operator=(AngelScriptRegister&&) = delete;
        ~AngelScriptRegister() = default;

        // Global registration

        template<class Function>
        AngelScriptRegister& add_a_global_function(const std::string& declaration, Function function)
        {
            int r = m_engine.RegisterGlobalFunction(declaration.c_str(), asFUNCTION(function), asCALL_CDECL);
            registration_succes_checker(r, declaration);

            emit_decl(declaration);
            return *this;
        }

        template<class T>
        AngelScriptRegister& add_a_global_property(const std::string& declaration, T* address)
        {
            int r = m_engine.RegisterGlobalProperty(declaration.c_str(), address);
            registration_succes_checker(r, declaration);

            emit_decl(declaration);
            return *this;
        }

        // Object types

        template<class ValueType>
        AngelScriptRegister& add_a_value_type(const std::string& typeName,
                                              int                flags = asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<ValueType>())
        {
            int r = m_engine.RegisterObjectType(typeName.c_str(), sizeof(ValueType), flags);
            registration_succes_checker(r, typeName);

            m_writer.add_line("class " + typeName + " {");
            m_writer.add_line("}");
            m_writer.add_line("");

            return *this;
        }

        template<class RefType>
        AngelScriptRegister& add_a_ref_type(const std::string& typeName,
                                            int                flags = asOBJ_REF)
        {
            int r = m_engine.RegisterObjectType(typeName.c_str(), 0, flags);
            registration_succes_checker(r, typeName);

            m_writer.add_line("class " + typeName + " {");
            m_writer.add_line("}");
            m_writer.add_line("");

            return *this;
        }

        // Behaviours for value types

        template<class T>
        AngelScriptRegister& add_a_value_default_constructor(const std::string& typeName)
        {
            int r = m_engine.RegisterObjectBehaviour(
                typeName.c_str(),
                asBEHAVE_CONSTRUCT,
                "void f()",
                asFUNCTION(construct_default<T>),
                asCALL_CDECL_OBJLAST);

            registration_succes_checker(r, typeName + " default ctor");
            return *this;
        }

        template<class T>
        AngelScriptRegister& add_a_value_copy_constructor(const std::string& typeName)
        {
            int r = m_engine.RegisterObjectBehaviour(
                typeName.c_str(),
                asBEHAVE_CONSTRUCT,
                ("void f(const " + typeName + " &in)").c_str(),
                asFUNCTION(construct_copy<T>),
                asCALL_CDECL_OBJLAST);

            registration_succes_checker(r, typeName + " copy ctor");
            return *this;
        }

        template<class T>
        AngelScriptRegister& add_a_value_destructor(const std::string& typeName)
        {
            int r = m_engine.RegisterObjectBehaviour(
                typeName.c_str(),
                asBEHAVE_DESTRUCT,
                "void f()",
                asFUNCTION(destruct<T>),
                asCALL_CDECL_OBJLAST);

            registration_succes_checker(r, typeName + " dtor");
            return *this;
        }

        // Behaviours for ref types

        template<class T>
        AngelScriptRegister& add_ref_counting(const std::string& typeName)
        {
            int r1 = m_engine.RegisterObjectBehaviour(
                typeName.c_str(), asBEHAVE_ADDREF, "void f()", asMETHOD(T, add_ref), asCALL_THISCALL);
            registration_succes_checker(r1, typeName + " addref");

            int r2 = m_engine.RegisterObjectBehaviour(
                typeName.c_str(), asBEHAVE_RELEASE, "void f()", asMETHOD(T, release), asCALL_THISCALL);
            registration_succes_checker(r2, typeName + " release");

            return *this;
        }

        template<class FactoryFn>
        AngelScriptRegister& add_a_factory(const std::string& typeName, const std::string& factoryDecl, FactoryFn factoryFn)
        {
            int r = m_engine.RegisterObjectBehaviour(
                typeName.c_str(), asBEHAVE_FACTORY, factoryDecl.c_str(), asFUNCTION(factoryFn), asCALL_CDECL);

            registration_succes_checker(r, typeName + " factory");
            return *this;
        }

        // Methods

        template<class T, class Method>
        AngelScriptRegister& add_a_method(const std::string& typeName, const std::string& declaration, Method method)
        {
            int r = m_engine.RegisterObjectMethod(
                typeName.c_str(), declaration.c_str(), asMETHOD(T, method), asCALL_THISCALL);

            registration_succes_checker(r, declaration);
            emit_member(typeName, declaration);
            return *this;
        }

        template<class T, class Method>
        AngelScriptRegister& add_a_const_method(const std::string& typeName, const std::string& declaration, Method method)
        {

            int r = m_engine.RegisterObjectMethod(
                typeName.c_str(), declaration.c_str(), asMETHOD(T, method), asCALL_THISCALL);

            registration_succes_checker(r, declaration);
            emit_member(typeName, declaration);
            return *this;
        }

        // Properties

        AngelScriptRegister& add_a_property_offset(const std::string& typeName, const std::string& declaration, int byteOffset)
        {
            int r = m_engine.RegisterObjectProperty(typeName.c_str(), declaration.c_str(), byteOffset);
            registration_succes_checker(r, declaration);

            // Emit as comment, like your methods
            emit_member(typeName, declaration);
            return *this;
        }

        template<class T, class FieldT>
        AngelScriptRegister& add_a_property(std::string typeName, std::string declaration, FieldT T::*field)
        {
            static_assert(std::is_standard_layout_v<T>,
                          "add_a_property requires standard-layout type. "
                          "Otherwise use add_a_property_offset or expose with get/set methods.");

            const int offset = member_offset(field);
            // register + emit handled inside add_a_property_offset now
            return add_a_property_offset(typeName, declaration, offset);
        }

    private:
        template<class T>
        static void construct_default(void* mem)
        {
            new (mem) T();
        }

        template<class T>
        static void construct_copy(const T& other, void* mem)
        {
            new (mem) T(other);
        }

        template<class T>
        static void destruct(void* mem)
        {
            static_cast<T*>(mem)->~T();
        }

        template<class T, class FieldT>
        static int member_offset(FieldT T::*member)
        {
            return int(reinterpret_cast<std::ptrdiff_t>(
                &(reinterpret_cast<T const volatile*>(0)->*member)));
        }

        void emit_decl(const std::string& decl)
        {
            std::string out = decl;
            if (!out.empty() && out.back() != ';')
                out.push_back(';');
            m_writer.add_line(out);
        }

        void emit_member(const std::string& typeName, const std::string& memberDecl)
        {
            std::string out = memberDecl;
            if (!out.empty() && out.back() != ';')
                out.push_back(';');

            m_writer.add_line("// " + typeName + ":: " + out);
        }

    private:
        asIScriptEngine&       m_engine;
        AngelScriptStubWriter& m_writer;
    };
} // namespace licht::scripting
