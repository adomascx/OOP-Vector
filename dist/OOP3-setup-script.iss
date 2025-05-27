[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2CE632A3-5B8E-4D30-B876-6BB48F71F1DA}
AppName=OOP-Vector
AppVersion=v3.0
;AppVerName=OOP-Vector v3.0
AppPublisher=Adomas Lukoševičius
AppPublisherURL=https://github.com/adomascx
AppSupportURL=https://github.com/adomascx
AppUpdatesURL=https://github.com/adomascx
DefaultDirName={autopf}\VU\Adomas-Lukosevicius
UninstallDisplayIcon={app}\OOP3.exe
; "ArchitecturesAllowed=x64compatible" specifies that Setup cannot run
; on anything but x64 and Windows 11 on Arm.
ArchitecturesAllowed=x64compatible
; "ArchitecturesInstallIn64BitMode=x64compatible" requests that the
; install be done in "64-bit mode" on x64 or Windows 11 on Arm,
; meaning it should use the native 64-bit Program Files directory and
; the 64-bit view of the registry.
ArchitecturesInstallIn64BitMode=x64compatible
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only).
;PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
OutputBaseFilename=Setup
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\Administrator\source\repos\C++\OOP-Vector\dist\OOP3.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Administrator\source\repos\C++\OOP-Vector\build\Vector.dll"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{autoprograms}\VU\OOP-Vector"; Filename: "{app}\OOP3.exe"
Name: "{autodesktop}\OOP-Vector"; Filename: "{app}\OOP3.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\OOP3.exe"; Description: "{cm:LaunchProgram,OOP-Vector}"; Flags: nowait postinstall skipifsilent

