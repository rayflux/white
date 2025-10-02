set_project("white")

add_requires("stb", "glm")

target("white")

    set_languages("cxx20")
    add_packages("stb", "glm")
    set_warnings("all", "extra", "error", "pedantic")
    add_includedirs("include")
    add_files("src/**.cpp")

    if is_plat("windows") then
        add_cxflags("/utf-8", {force = true})
        add_cxxflags("/utf-8", {force = true})
        add_cxxflags("/wd4068", {force = true}) -- for #pragma clang
    elseif is_plat("linux") then
        add_cxxflags("-Wno-unknown-pragmas", {force = true}) -- for #pragma clang
    end

    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
        os.cp("assets", "bin/")
    end)

target_end()
