
target( "FL-Studio-SDK" )
    set_kind( "static" )

    set_version( "2021.03.11", { build = "20210311b", soname = true } )

    set_default( false )
    set_group( "SDK" )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/(*.h)" )

    add_files( "src/*.cpp" )
