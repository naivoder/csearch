//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------

#define REPLACE_STRING 1
#define SEARCH_FILES   2
#define RENAME_FILES   3
//---------------------------------------------------------------------------
class MainForm : public Form
{
__published:	// IDE-managed Components
        TButton *ReplaceBtn;
        TLabel *Label1;
        TLabel *Label3;
        TEdit *Path;
        TPanel *StatusPanel;
        TLabel *Status;
        TLabel *Label4;
        TEdit *Mask;
        TLabel *Label5;
        TEdit *ResultFile;
        TButton *SearchBtn;
        TGroupBox *GroupBox1;
        TCheckBox *CaseSensitive;
        TButton *ViewBtn;
        TLabel *Label6;
        TEdit *NewExt;
        TButton *RenameBtn;
        TButton *DirBtn;
        TCheckBox *SearchSubs;
        TEdit *SearchStr;
        TEdit *ReplaceStr;
        TLabel *Label2;
        TLabel *Label7;
        TEdit *ResultPath;
        TButton *ResultPathBtn;
        void __fastcall ReplaceBtnClick(TObject *Sender);
        void __fastcall SearchBtnClick(TObject *Sender);
        void __fastcall ViewBtnClick(TObject *Sender);
        void __fastcall RenameBtnClick(TObject *Sender);
        void __fastcall DirBtnClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ResultPathBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
  void __fastcall ReplaceString(String Source);
  void __fastcall SearchFile(String Source);
  void __fastcall SearchPath(String APath, int Operation);
  void __fastcall RenameThisFile(String Filename);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
