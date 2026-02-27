set_project("op")
set_version("1.0")
set_description("Objects container implementation based on Wookash & Anton Mikhailov discussion https://www.youtube.com/watch?v=-m7lhJ_Mzdg")
set_license("MIT")

add_rules("mode.release")

set_languages("c++20")

set_warnings("all", "error")

set_policy("build.ccache", false)

add_requires("gtest", {system = false, configs = {main = true, gmock = false, shared=false}})

target("op")
    set_kind("headeronly")
    add_headerfiles("include/ObjectsPool.hpp", "include/ObjectsPool.inl", {public=true})


-- Iterate over test files and create test targets
for _, file in ipairs(os.files("tests/*.cpp")) do
    local name = path.basename(file)
    target(name)
        set_kind("binary")
        add_packages("gtest", {main = true, gmok = false})
        set_default(false)
        add_files(file)
        add_tests("default")
        add_includedirs("include/", {public = true})
        --add_deps("op")
        add_includedirs("tests/")
        set_group("test")
end
for _, file in ipairs(os.files("tests/build-should-fail/*.cpp")) do
    local name = path.basename(file)
    target(name)
        set_kind("binary")
        add_packages("gtest", {main = true, gmok = false})
        set_default(false)
        add_files(file)
        add_tests("build-should-fail", {build_should_fail = true})
        add_includedirs("include/", {public = true})
        add_includedirs("tests/")
        set_group("test")
end