#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Engine.h"

#include "MansionGenerator.h"
#include "RoomData.h"

int APIENTRY WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst, LPSTR lpszCmdLine, int nCmdShow) {
  //Open console in debug mode
#ifdef _DEBUG
  AllocConsole();
  //SetWindowPos(GetConsoleWindow(), 0, 1920, 200, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  AttachConsole(GetCurrentProcessId());
  freopen("CON", "w", stdout);
#endif
  MansionGenerator mg;
  mg.registerNewRoom(RoomData(10, 7, "Foyer", 5, 0, { {0,3}, {4,6}, {9,3} }));
  mg.registerNewRoom(RoomData(6, 6, "Bathroom", 3, 11, { {3,0}, {5,2} }));
  mg.generateNewMansion();
  //Run the main engine
  Engine engine;
  return engine.Run();
}
