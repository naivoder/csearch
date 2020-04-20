//---------------------------------------------------------------------------
#ifndef DirDlgH
#define DirDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TDirForm : public TForm
{
__published:	// IDE-managed Components
        TDirectoryListBox *DirList;
        TDriveComboBox *DriveComboBox;
        TButton *Button1;
        TButton *Button2;
        TLabel *DirLabel;
private:	// User declarations
public:		// User declarations
        __fastcall TDirForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDirForm *DirForm;
//---------------------------------------------------------------------------
#endif
