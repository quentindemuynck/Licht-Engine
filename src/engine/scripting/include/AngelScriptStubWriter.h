#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

// writes all the data of registered 
namespace licht::scripting
{
	class AngelScriptStubWriter final
	{
    public:
        AngelScriptStubWriter(std::filesystem::path outPath);

        
        AngelScriptStubWriter(const AngelScriptStubWriter&) = delete;
        AngelScriptStubWriter& operator=(const AngelScriptStubWriter&) = delete;
        AngelScriptStubWriter(AngelScriptStubWriter&&) = delete;
        AngelScriptStubWriter& operator=(AngelScriptStubWriter&&) = delete;
        ~AngelScriptStubWriter() = default;
        
        void clear_and_begin();
        void add_line(std::string_view stringView);
        void flush();

        const std::filesystem::path& path() const;

    private:

        std::filesystem::path m_path;
        std::stringstream m_ss;
	};


}