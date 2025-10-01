set_project("white")

add_requires("stb", "glm")

target("white")

    set_languages("cxx20")
    add_packages("stb", "glm")
    set_warnings("all", "extra", "error", "pedantic")
    add_includedirs("include")
    add_files("src/**.cpp")
    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
    end)

target_end()
