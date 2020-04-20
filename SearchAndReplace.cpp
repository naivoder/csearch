//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SearchAndReplace.res");
USEFORM("Main.cpp", MainForm);
USEFORM("DirDlg.cpp", DirForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TDirForm), &DirForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
