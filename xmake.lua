-- include subprojects
includes("lib/commonlibsse", "extern/styyx-utils")

local MOD_NAME = "breaking-bows"
local MOD_VERSION = "3.1.0"
local MOD_DESC = "breaks bows when attacked"

-- set project constants
set_project(MOD_NAME)
set_version(MOD_VERSION)
set_license("GPL-3.0")
set_languages("c++23")
set_warnings("allextra")
set_encodings("utf-8")

-- add rules
add_rules("mode.debug", "mode.releasedbg")

-- set policies
set_policy("package.requires_lock", true)
set_config("commonlib_toml", true)
set_config("commonlib_random", true)


-- targets
target(MOD_NAME)
    add_deps("styyx-util")
    add_rules("commonlibsse.plugin", {
        name = MOD_NAME,
        author = "styyx",
        description = MOD_DESC
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")
    add_installfiles("res/(**)")
