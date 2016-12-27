#InstallKeybdHook
#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

+Capslock::Capslock
Capslock::RCtrl

$*H::
if GetKeyState("Capslock", "P")
    send {Blind}{RCtrl Up}{Left}{RCtrl Down}
else
    send {Blind}{h}
return

$*J::
if GetKeyState("Capslock", "P")
    send {Blind}{RCtrl Up}{Down}{RCtrl Down}
else
    send {Blind}{j}
return

$*K::
if GetKeyState("Capslock", "P")
    send {Blind}{RCtrl Up}{Up}{RCtrl Down}
else
    send {Blind}{l}
return

$*L::
if GetKeyState("Capslock", "P")
    send {Blind}{RCtrl Up}{Right}{RCtrl Down}
else
    send {Blind}{l}
return

$*[::
if GetKeyState("Capslock", "P")
    send {Blind}{RCtrl Up}{Escape}{RCtrl Down}
else
    send {Blind}{[}
return

$*i::
if GetKeyState("Capslock", "P")
    send {Blind}{RCtrl Up}{LShift down}{Insert}{LShift Up}{RCtrl Down}
else
    send {Blind}{i}
return

