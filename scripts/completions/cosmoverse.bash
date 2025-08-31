
# bash completion for cosmoverse
_cosmoverse() {
  local cur prev
  COMPREPLY=()
  cur="${COMP_WORDS[COMP_CWORD]}"
  prev="${COMP_WORDS[COMP_CWORD-1]}"
  local cmds="version bench bench-omp plugin help"
  if [[ ${COMP_CWORD} -eq 1 ]]; then
    COMPREPLY=( $(compgen -W "${cmds}" -- ${cur}) )
  fi
  return 0
}
complete -F _cosmoverse cosmoverse
