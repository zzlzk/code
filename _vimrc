source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
behave mswin

set nu
set tabstop=4
set shiftwidth=4
colorscheme molokai
syntax on
set guifont=Courier_new:h14:b:cDEFAULT
set autoindent
set smartindent
set go-=T
set go-=m

imap <c-]> {<cr>}<c-o>O<left><right>
inoremap ( ()<LEFT>
inoremap [ []<LEFT>
inoremap { {}<LEFT>
inoremap " ""<LEFT>
inoremap ' ''<LEFT>


map <F11> :call CR()<CR>
func! CR()
exec "w"
exec "!g++ -O2 -g  % -o %<"
exec "! %<"
endfun

map <F2> :call SetTitle()<CR>
func SetTitle()
let l = 0
let l = l + 1 | call setline(l,'#include<cstdio>')
let l = l + 1 | call setline(l,'#include<cstring>')
let l = l + 1 | call setline(l,'#include<algorithm>')
let l = l + 1 | call setline(l,'using namespace std;')
let l = l + 1 | call setline(l,'typedef long long ll;')
let l = l + 1 | call setline(l,'')
let l = l + 1 | call setline(l,'template<typename T>')
let l = l + 1 | call setline(l,'void input(T &x) {')
let l = l + 1 | call setline(l,'	x=0; T a=1;')
let l = l + 1 | call setline(l,'	register char c=getchar();')
let l = l + 1 | call setline(l,'	for(;c<48||c>57;c=getchar())')
let l = l + 1 | call setline(l,'		if(c==45) a=-1;')
let l = l + 1 | call setline(l,'	for(;c>=48&&c<=57;c=getchar())')
let l = l + 1 | call setline(l,'		x=x*10+c-48;')
let l = l + 1 | call setline(l,'	x*=a;')
let l = l + 1 | call setline(l,'	return;')
let l = l + 1 | call setline(l,'}')
let l = l + 1 | call setline(l,'')
let l = l + 1 | call setline(l,'int main() {')
let l = l + 1 | call setline(l,'	')
let l = l + 1 | call setline(l,'	return 0;')
let l = l + 1 | call setline(l,'}')
endfunc

set diffexpr=MyDiff()
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  if $VIMRUNTIME =~ ' '
    if &sh =~ '\<cmd'
      if empty(&shellxquote)
        let l:shxq_sav = ''
        set shellxquote&
      endif
      let cmd = '"' . $VIMRUNTIME . '\diff"'
    else
      let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
    endif
  else
    let cmd = $VIMRUNTIME . '\diff'
  endif
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3
  if exists('l:shxq_sav')
    let &shellxquote=l:shxq_sav
  endif
endfunction

