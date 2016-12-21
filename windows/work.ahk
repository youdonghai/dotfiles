#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
#InstallKeybdHook
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

SetCapsLockState, AlwaysOff

+Capslock::Capslock
Capslock::LCtrl

$Capslock::
    Gui, 93:+Owner ; prevent display of taskbar button
    Gui, 93:Show, y-99999 NA, Enable nav-hotkeys: hjkl
    Send {LCtrl Down}
    KeyWait, Capslock ; wait until the Capslock button is released
    Gui, 93:Cancel
    Send, {LCtrl Up}
Return

#IfWinExist, Enable nav-hotkeys: hjkl
    *h::Send {Blind}{LCtrl Up}{Left}{LCtrl Down}
    *j::Send {Blind}{LCtrl Up}{Down}{LCtrl Down}
    *k::Send {Blind}{LCtrl Up}{Up}{LCtrl Down}
    *l::Send {Blind}{LCtrl Up}{Right}{LCtrl Down}
    *[::Send {Blind}{LCtrl Up}{Escape}{LCtrl Down}
    *i::Send {Blind}{LCtrl Up}{LShift down}{Insert}{LShift Up}{LCtrl Down}
#IfWinExist, ; end context-sensitive block

#IfWinActive, ahk_class Chrome_WidgetWin_1
*!1::SendInput, ^{1}
*!2::SendInput, ^{2}
*!3::SendInput, ^{3}
*!4::SendInput, ^{4}
*!5::SendInput, ^{5}
*!6::SendInput, ^{6}
*!7::SendInput, ^{7}
*!8::SendInput, ^{8}
*!9::SendInput, ^{9}
#IfWinActive

