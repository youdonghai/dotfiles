if [ $UID -eq 0 ]; then NCOLOR="red"; else NCOLOR="green"; fi
local ret_status="%(?:%{$fg_bold[green]%}>:%{$fg_bold[red]%}>)"

PROMPT='%{$fg[$NCOLOR]%}%n%{$reset_color%}@%{$fg[cyan]%}%m%{$reset_color%}:%{$fg[blue]%}%~ $(git_prompt_info)
${ret_status}%{$reset_color%} '

ZSH_THEME_GIT_PROMPT_PREFIX="%{$fg[yellow]%}[%{$fg[cyan]%}"
ZSH_THEME_GIT_PROMPT_CLEAN="%{$reset_color%}"
ZSH_THEME_GIT_PROMPT_DIRTY="%{$fg[red]%}*%{$reset_color%}"
ZSH_THEME_GIT_PROMPT_SUFFIX="%{$fg[yellow]%}]%{$reset_color%}"

