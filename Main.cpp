//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DirDlg.h"
#include "inifiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include <stdio.h>


TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
   TIniFile *ini;
   ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
   Path->Text             = ini->ReadString("Form", "Path","c:\\");
   Mask->Text             = ini->ReadString("Form", "Mask","*.txt");
   NewExt->Text           = ini->ReadString("Form", "NewExt","txt");
   SearchStr->Text        = ini->ReadString("Form", "SearchStr","");
   ReplaceStr->Text       = ini->ReadString("Form", "ReplaceStr","");
   ResultFile->Text       = ini->ReadString("Form", "ResultFile","Search Results.txt");
   ResultPath->Text       = ini->ReadString("Form", "ResultPath","c:\\");
   SearchSubs->Checked    = ini->ReadBool  ("Form", "SearchSubs",false);
   CaseSensitive->Checked = ini->ReadBool  ("Form", "CaseSensitive", false);
   delete ini;
}

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
   TIniFile *ini;
   ini = new TIniFile(ChangeFileExt( Application->ExeName, ".INI" ) );
   ini->WriteString("Form", "Path",          Path->Text);
   ini->WriteString("Form", "Mask",          Mask->Text);
   ini->WriteString("Form", "NewExt",        NewExt->Text);
   ini->WriteString("Form", "SearchStr",     SearchStr->Text);
   ini->WriteString("Form", "ReplaceStr",    ReplaceStr->Text);
   ini->WriteString("Form", "ResultFile",    ResultFile->Text);
   ini->WriteString("Form", "ResultPath",    ResultPath->Text);
   ini->WriteBool  ("Form", "SearchSubs",    SearchSubs->Checked);
   ini->WriteBool  ("Form", "CaseSensitive", CaseSensitive->Checked);
   delete ini;

}


// Search Files and List all files that will be erased
//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchFile(String Source)
{
  int i;
  bool IsFirst = true;
  FILE *SFile;
  FILE *DFile;
  char s[10240];
  char* ReadStr;
  String Dest     = ResultPath->Text + ResultFile->Text;
  String Line;
  int    LineNumber = 1;

  Status->Caption = "Scanning: "+Source;
  Status->Update();

  int BufferSize = sizeof(s);

  SFile = fopen(Source.c_str(), "r");  // open a file for update

  if (SFile)
  {
    DFile = fopen(Dest.c_str(), "a+");   // Create Temp File

    if (DFile)
    {
      do {
        ReadStr = fgets(s,BufferSize,SFile);

        if (ReadStr)
        {
          Line = s;

          int StrPosn;
          if (CaseSensitive->Checked)
          {
            StrPosn = Line.Pos(SearchStr->Text);
          }
          else {
            StrPosn = UpperCase(Line).Pos(UpperCase(SearchStr->Text));
          }

          if (StrPosn)
          {
            if (IsFirst)
            {
              fprintf(DFile,"\n\nFile Name: %s\n",Source.c_str());
              IsFirst = false;
            }
            fprintf(DFile,"Line:%4d %s",LineNumber,s);
          }
        }
        LineNumber++;

      } while (ReadStr);

      fclose(DFile);
    }

    fclose(SFile);
  }
}


//---------------------------------------------------------------------------

void __fastcall TMainForm::ReplaceString(String Source)
{
  int i;
  bool StringFound = false;
  FILE *SFile;  // Source File
  FILE *DFile;  // Destination File
  char s[10240];
  char* ReadStr;
  String Destination = Source + ".TMP";
  String Line;

  Status->Caption = "Scanning: "+Source;
  Status->Update();

  int BufferSize = sizeof(s);

  SFile = fopen(Source.c_str(), "r");  // open a file for update
  DFile = fopen(Destination.c_str(), "w+"); // create destination File

  if (SFile)
  {
    do {
      ReadStr = fgets(s,BufferSize,SFile);

      if (ReadStr)
      {
        Line = s;

        int StrPosn;

        if (CaseSensitive->Checked)
        {
          StrPosn = Line.Pos(SearchStr->Text);
        }
        else {
          StrPosn = UpperCase(Line).Pos(UpperCase(SearchStr->Text));
        }

        if ((StrPosn) && (SearchStr->Text.IsEmpty() == false))
        {
          // Replace String
          Line.Delete(StrPosn,SearchStr->Text.Length());
          Line.Insert(ReplaceStr->Text,StrPosn);
          StringFound = true;
        }
        // Write Line to destination file
        fputs(Line.c_str(),DFile);
      }
    } while ((ReadStr) && (!StringFound));

    fclose(SFile);

  }

  if (DFile) fclose(DFile);

  // Delete Old File & Rename temp file old file name
  DeleteFile(Source);              // Remove the File
  RenameFile(Destination,Source);  // Rename the Modified File
}


void __fastcall TMainForm::SearchPath(String APath, int Operation)
{
  bool       Result;
  int        FileAttributes = faAnyFile;
  TSearchRec FileSearch;

  if (APath[APath.Length()] != '\\')
  {
     APath = APath + "\\";
  }

  Result = FindFirst(APath + Mask->Text, FileAttributes, FileSearch);

  while (Result == 0)
  {
    switch (Operation) {
      case SEARCH_FILES   : SearchFile(APath+FileSearch.Name); break;
      case REPLACE_STRING : ReplaceString(APath+FileSearch.Name); break;
      case RENAME_FILES   : RenameThisFile(APath+FileSearch.Name); break;
    }
    Result = FindNext(FileSearch);
  }

  // Look In any sub Directories if Checked

  if (SearchSubs->Checked)
  {
    Result = FindFirst(APath + "*.*", faDirectory, FileSearch);

    while (Result == 0)
    {
      if ((FileSearch.Name != ".") && (FileSearch.Name != ".."))
      {
        SearchPath(APath+FileSearch.Name, Operation);
      }
      Result = FindNext(FileSearch);
    }
  }

  Status->Caption = "Idle";

  FindClose(FileSearch);
}

void __fastcall TMainForm::ReplaceBtnClick(TObject *Sender)
{
  bool  Result;

  if (SearchStr->Text.IsEmpty())
  {
    MessageBox(Handle,"Your Find String is empty!","Error",MB_OK|MB_ICONERROR);
  }
  else {
    if (Path->Text[Path->Text.Length()] != '\\')
    {
       Path->Text = Path->Text + "\\";
    }

    String Msg = "Are you Absolutely sure you want to replace all of the strings in all files?";

    if (MessageBox(Handle,Msg.c_str(),"Verify",MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
      SearchPath(Path->Text, REPLACE_STRING);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SearchBtnClick(TObject *Sender)
{
  if (SearchStr->Text.IsEmpty())
  {
    MessageBox(Handle,"Your Find Strings is empty!","Error",MB_OK|MB_ICONERROR);
  }
  else {
    if (Path->Text[Path->Text.Length()] != '\\')
    {
       Path->Text = Path->Text + "\\";
    }

    if (ResultPath->Text[ResultPath->Text.Length()] != '\\')
    {
      ResultPath->Text = ResultPath->Text + "\\";
    }

    String Dest = ResultPath->Text + ResultFile->Text;

    FILE* DFile = fopen(Dest.c_str(), "w+");   // Create Result File

    if (DFile)
    {
      fprintf(DFile,"Search results for: \"%s\" in path: \"%s\" for file mask: \"%s\"",SearchStr->Text.c_str(),Path->Text.c_str(),Mask->Text.c_str());

      fclose(DFile);

      SearchPath(Path->Text, SEARCH_FILES);
    }
    else {
      MessageBox(Handle,"Could not create Search Result File!","Error",MB_OK|MB_ICONERROR);
    }
  }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewBtnClick(TObject *Sender)
{
  if (ResultPath->Text[ResultPath->Text.Length()] != '\\')
  {
    ResultPath->Text = ResultPath->Text + "\\";
  }



  if (FileExists(ResultPath->Text + ResultFile->Text))
  {
    String DataPath = "Notepad.exe "+ResultPath->Text + ResultFile->Text;
    WinExec(DataPath.c_str(),SW_SHOW);
  }
  else {
    MessageBox(Handle,"Search Result File does not exist!","Error",MB_OK|MB_ICONERROR);
  }
}

void __fastcall TMainForm::RenameThisFile(String FileName)
{
  String Dest   = FileName.SubString(1,FileName.LastDelimiter("."))+NewExt->Text;
  Status->Caption = "Re-Naming: "+FileName;
  Status->Update();
  RenameFile(FileName,Dest);
}


//---------------------------------------------------------------------------


void __fastcall TMainForm::RenameBtnClick(TObject *Sender)
{
  bool       Result;

  if (NewExt->Text.IsEmpty())
  {
    MessageBox(Handle,"Your New File Extension String is empty!","Error",MB_OK|MB_ICONERROR);
  }
  else {
    if (Path->Text[Path->Text.Length()] != '\\')
    {
       Path->Text = Path->Text + "\\";
    }

    String Msg = "Are you Absolutely sure you rename all matching Files with the extension\n\""+Mask->Text+
      "\" With \""+NewExt->Text+"\"?";

    if (MessageBox(Handle,Msg.c_str(),"Verify",MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
      SearchPath(Path->Text, RENAME_FILES);
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::DirBtnClick(TObject *Sender)
{
  DirForm->DirList->Directory = Path->Text;
  if (DirForm->ShowModal() == mrOk)
  {
    Path->Text = DirForm->DirLabel->Caption;
  }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ResultPathBtnClick(TObject *Sender)
{
  DirForm->DirList->Directory = ResultPath->Text;
  if (DirForm->ShowModal() == mrOk)
  {
    ResultPath->Text = DirForm->DirLabel->Caption;
  }
}
//---------------------------------------------------------------------------



