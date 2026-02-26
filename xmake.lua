add_rules("mode.release")

set_languages("c++20")

set_warnings("all", "error")

set_policy("build.ccache", false)

--add_requires("gtest")
add_requires("gtest", {system = false, configs = {main = true, gmock = false, shared=false}})
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