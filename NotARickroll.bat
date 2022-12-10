set /a a=%random% %%4
if %a%==1 {
start "" https://www.youtube.com/watch?v=oHg5SJYRHA0
}
start cmd.exe /C %~0 parameters
tasklist | find /I "Music.UI.exe" 
if errorlevel 1 (
        start "explorer.exe shell:C:\Program Files\WindowsApps\Microsoft.ZuneMusic_3.6.25021.0_x64__8wekyb3d8bbwe!Microsoft.ZuneMusic" "Rickroll.mp3"
) else (
cd c:/
tree
)
