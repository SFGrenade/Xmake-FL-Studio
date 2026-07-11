#ifndef FL_STUDIO_SDK_CMAKE_TEMPLATE_PLUGIN_H
#define FL_STUDIO_SDK_CMAKE_TEMPLATE_PLUGIN_H

// Header files included for the SDK
#include "fp_cplug.h"
#include "fp_plugclass.h"
#include "generictransport.h"

// header file, automatically configurated by CMake.
#include "definitions.h"

// C++ std includes
#include <array>
#include <vector>

const int InitialNumParamsConst = 1 + 16;  // the amount of parameters
// const int StateSizeConst = InitialNumParamsConst * sizeof(int);  // the size of all parameters together

// Minimal Example Plugin class.
class Plugin : public TCPPFruityPlug {
  public:
  int SelectedParam;
  std::array< int, 16 > ParamValues;
  // constructor
  Plugin( int Tag, TFruityPlugHost* Host );
  // inherited functions
  virtual void _stdcall DestroyObject() override;
  virtual intptr_t _stdcall Dispatcher( intptr_t ID, intptr_t Index, intptr_t Value ) override;
  virtual void Idle() override;
  virtual void _stdcall SaveRestoreState( IStream* Stream, BOOL Save ) override;
  virtual void _stdcall GetName( int Section, int Index, int Value, char* Name ) override;
  virtual int _stdcall ProcessParam( int Index, int Value, int RECFlags ) override;
  virtual void _stdcall Eff_Render( PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length ) override;

  void ResetParams();
};

#endif  // FL_STUDIO_SDK_CMAKE_TEMPLATE_PLUGIN_H
