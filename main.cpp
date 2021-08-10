 IKnownFolderManager* pKnownFolderManager = NULL;
 HRESULT hr = CoCreateInstance(CLSID_KnownFolderManager, NULL, CLSCTX_ALL, IID_IKnownFolderManager, (void**)&pKnownFolderManager);
 if (SUCCEEDED(hr))
 {
  PWSTR pwszDownloadPath = NULL;
  hr = SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &pwszDownloadPath); // "C:\\Users\\Christian\\Downloads"
  WCHAR wszNewPath[MAX_PATH] = L"C:\\Users\\Christian\\Source";
  IKnownFolder* pKnownFolder;
  hr = pKnownFolderManager->FindFolderFromPath(pwszDownloadPath, FFFP_EXACTMATCH, &pKnownFolder);
  if (SUCCEEDED(hr))
  {
  KNOWNFOLDERID kfid = { 0 };
  hr = pKnownFolder->GetId(&kfid);
  DWORD dwFlags = KF_REDIRECT_WITH_UI | KF_REDIRECT_PIN; // random flags, to be tested with other flags...
  PWSTR pwszError;
  hr = pKnownFolderManager->Redirect(kfid, hWnd, dwFlags, wszNewPath, 0, NULL, &pwszError);
  // Notifications
  PIDLIST_ABSOLUTE pidlUsersFiles;
  if (SUCCEEDED(SHGetKnownFolderIDList(FOLDERID_UsersFiles, 0, NULL, &pidlUsersFiles)))
  {
  SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlUsersFiles, NULL);
  ILFree(pidlUsersFiles);
  }
  PIDLIST_ABSOLUTE pidlDownloadFolder;
  if (SUCCEEDED(SHGetKnownFolderIDList(kfid, 0, NULL, &pidlDownloadFolder)))
  {
  SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlDownloadFolder, NULL);
  ILFree(pidlDownloadFolder);
  }
  }
 }
