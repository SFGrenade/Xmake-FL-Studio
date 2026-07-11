
target( "SFG-FL-ParamMultiplex" )
    add_rules( "win.sdk.mfc.shared" )

    if is_plat( "windows" ) then
        add_syslinks( "User32", { public = true } )
    else
    end

    set_default( true )
    set_group( "PLUGINS" )

    set_basename( "SFG-FL-ParamMultiplex_$(arch)" )

    set_configvar( "PROJECT_NAME", "SFG-FL-ParamMultiplex_$(arch)" )
    set_configvar( "SHORT_NAME", "SFG-PM" )
    set_configvar( "IS_EFFECT", "true" )
    set_configvar( "IS_GENERATOR", "false" )
    set_configvar( "PLUGIN_DESCRIPTION", "Makes you able to have X parameter inputs + a selector parameter and outputs the selected parameter value" )

    add_deps( "FL-Studio-SDK", { public = true } )

    add_includedirs( "include", "$(builddir)", { public = true } )

    add_headerfiles( "include/(*.h)" )

    add_files( "src/*.cpp" )

    add_configfiles( "include/definitions.h.in" )
    add_configfiles( "plugin.def.in", { filename = "SFG-FL-ParamMultiplex_$(arch).def" } )

    add_files( "$(builddir)/SFG-FL-ParamMultiplex_$(arch).def" )
