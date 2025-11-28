-- set minimum xmake version
set_xmakever("2.8.2")

-- includes
includes("lib/commonlibsse")
includes("extern/styyx-utils")


-- set project
set_project("breaking-bows")
set_version("3.0.0")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_warnings("allextra")

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- set policies
set_policy("package.requires_lock", true)
set_config("commonlib_toml", true)


-- targets
target("breaking-bows")
    -- add dependencies to target
    add_deps("commonlibsse")
    add_deps("styyx-util")

    -- add commonlibsse plugin
    add_rules("commonlibsse.plugin", {
        name = "breaking-bows",
        author = "styyx"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")
    add_extrafiles("contrib/**.toml", {public=true}, "contrib/**.json", {public=true})
    add_includedirs("extern/clib-util/include", {public = true})
