
TMainForm *MainForm;

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
