#pragma once

#include <unordered_map>
#include <vector>

#include "String.hpp"
#include "Log.hpp"

#include "core/Internal.hpp"

namespace ht { namespace utils {

	class VFS {
	private:
		static std::unordered_map<String, std::vector<String>> mounts;

	public:
		static void Mount(const String &virtualPath, const String &physicalPath);
		static void Unmount(const String &path);

		static String Resolve(const String& path);

		inline static bool Exists(const String& path) {
			struct stat buffer;
			return (stat(path.GetData(), &buffer) == 0);
		}
	};

} }
