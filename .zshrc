autoload -U colors && colors

alias 42FileChecker='bash ~/42checker/42FileChecker.sh'
mkdir -p /tmp/.$(whoami)-brew-locks
export PATH="$HOME/.brew/bin:$PATH"
export CLICOLOR=1
export LSCOLORS='gxfxcxdxbxegedabagacad' 
if [[ -n "$SSH_CLIENT" || -n "$SSH2_CLIENT" ]]; then
  host="%F{black}%f[%F{blue}%f%m%F{black}%f] " #SSH
else
  unset host # no SSH
fi

bindkey "^[[H"  beginning-of-line 
bindkey "^[[F"  end-of-line
bindkey '\e[3~' delete-char

PROMPT="%F{magenta}> %f"
RPROMPT='%F{green}%3~%f'
# git
alias gd='git diff'
alias gs='git status'
alias ga='git add'

setopt autocd
