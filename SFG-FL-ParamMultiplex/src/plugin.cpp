#include "plugin.h"

#include <array>

extern "C" PLUGIN_EXPORT TFruityPlug* _stdcall CreatePlugInstance( TFruityPlugHost* Host, int Tag ) {
  auto plug = new Plugin( Tag, Host );
  return (TFruityPlug*)plug;
};

// constructor
Plugin::Plugin( int Tag, TFruityPlugHost* Host ) : TCPPFruityPlug( Tag, Host, nullptr ) {
  // Information structure describing this plugin to the host
  static TFruityPlugInfo g_PlugInfo;
  static char g_PLUGIN_NAME[] = PLUGIN_NAME;
  static char g_PLUGIN_SHORT_NAME[] = PLUGIN_SHORT_NAME;
  {
    g_PlugInfo.SDKVersion = CurrentSDKVersion;
    g_PlugInfo.LongName = g_PLUGIN_NAME;
    g_PlugInfo.ShortName = g_PLUGIN_SHORT_NAME;
    // Set plugin type.
    g_PlugInfo.Flags = FPF_Type_Effect | FPF_Type_Visual | FPF_CantSmartDisable | FPF_Interfaceless;
    g_PlugInfo.NumParams = InitialNumParamsConst;
    // infinite polyphony (it's an effect plugin)
    g_PlugInfo.DefPoly = 0;
    // one internal output controller
    g_PlugInfo.NumOutCtrls = 1;
    // no internal output voices
    g_PlugInfo.NumOutVoices = 0;
  }

  Info = &g_PlugInfo;
  HostTag = Tag;

  ResetParams();
}

void _stdcall Plugin::DestroyObject() {
  // todo

  TCPPFruityPlug::DestroyObject();  // don't forget this
};

int _stdcall Plugin::Dispatcher( int ID, int Index, int Value ) {
  // todo
  return 0;
};

void _stdcall Plugin::Idle() {
  TCPPFruityPlug::Idle();
  // todo
};

void _stdcall Plugin::SaveRestoreState( IStream* Stream, BOOL Save ) {
  unsigned long written, read;

  if( Save ) {
    Stream->Write( &SelectedParam, sizeof( int ), &written );
    for( int value : ParamValues ) {
      Stream->Write( &value, sizeof( int ), &written );
    }
  } else {
    Stream->Read( &SelectedParam, sizeof( int ), &read );
    for( int i = 0; i < ParamValues.size(); i++ ) {
      Stream->Read( &ParamValues[i], sizeof( int ), &read );
    }

    ProcessAllParams();
  }
};

void _stdcall Plugin::GetName( int Section, int Index, int Value, char* Name ) {
  switch( Section ) {
    // for the parameter names, we look at the (long) hint of the parameter control
    case FPN_Param:
      if( Index == 0 ) {
        strcpy( Name, "Selected Parameter" );
      } else if( ( Index - 1 ) < ParamValues.size() ) {
        std::array< char, 256 > buff;
        buff.fill( 0 );
        std::snprintf( buff.data(), buff.size(), "%s %d", "Parameter", Index );
        strcpy( Name, buff.data() );
      }
      break;

    // the name of our only internal controller
    case FPN_OutCtrl:
      if( Index == 0 ) {
        strcpy( Name, "Out Value" );
      }
      break;
  }
}

int _stdcall Plugin::ProcessParam( int Index, int Value, int RECFlags ) {
  if( Index == 0 ) {
    // Selected Param
    if( ( RECFlags & REC_FromMIDI ) != 0 ) {
      Value = TranslateMidi( Value, 0, ParamValues.size() - 1 );
    }
    if( ( RECFlags & REC_UpdateValue ) != 0 ) {
      SelectedParam = Value;
      PlugHost->OnControllerChanged( HostTag, 0, ParamValues[SelectedParam] );
    } else if( ( RECFlags & REC_GetValue ) != 0 ) {
      Value = SelectedParam;
    }
    if( ( RECFlags & REC_UpdateControl ) != 0 ) {
      // editor->ParamsToControls();
    }
    if( RECFlags & REC_ShowHint ) {
      // we show the parameter value as a hint
      ShowHintMsg_Percent( Value, ParamValues.size() );
    }
  } else if( Index < Info->NumParams ) {
    // Individual Param
    int adjustedIndex = Index - 1;
    if( ( RECFlags & REC_UpdateValue ) != 0 ) {
      ParamValues[adjustedIndex] = Value;
      if( adjustedIndex == SelectedParam ) {
        PlugHost->OnControllerChanged( HostTag, 0, Value );
      }
    } else if( ( RECFlags & REC_GetValue ) != 0 ) {
      Value = ParamValues[adjustedIndex];
    }
    if( ( RECFlags & REC_UpdateControl ) != 0 ) {
      // editor->ParamsToControls();
    }
    if( RECFlags & REC_ShowHint ) {
      // we show the parameter value as a hint
      ShowHintMsg_Percent( Value, FromMIDI_Max );
    }
  }
  return Value;
}

void _stdcall Plugin::Eff_Render( PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length ) {
  // todo
}

void Plugin::ResetParams() {
  SelectedParam = 0;
}
