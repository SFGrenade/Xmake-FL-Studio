set_project( "FL-Studio-Plugins" )

set_version( "0.0.1", { build = "%Y%m%d", soname = true } )

add_rules( "mode.debug", "mode.release", "mode.releasedbg", "mode.minsizerel" )
add_rules( "plugin.compile_commands.autoupdate", { outputdir = ".vscode" } )

set_languages( "c++20" )

if is_plat( "windows" ) then
    add_cxflags( "/Zc:__cplusplus" )
    add_cxflags( "/Zc:preprocessor" )

    add_cxflags( "/permissive-" )

    add_ldflags( "-force", { force = true } )

    --set_runtimes( is_mode( "debug" ) and "MDd" or "MD" )
else
end

set_warnings( "allextra" )

includes( "FL-Studio-SDK" )
includes( "SFG-FL-ParamMultiplex" )
