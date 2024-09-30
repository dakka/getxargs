let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <Nul> <C-Space>
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <S-Tab> pumvisible() ? "\" : "\<S-Tab>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
cnoremap <F23> <Nop>
cnoremap <F22> <Nop>
inoremap <expr> <F22> terminus#private#paste('')
inoremap <silent> <F21> :silent doautocmd <nomodeline> FocusGained %
inoremap <silent> <F20> :silent doautocmd <nomodeline> FocusLost %
cnoremap <silent> <F21> eterminus#private#focus_gained()
cnoremap <silent> <F20> eterminus#private#focus_lost()
inoremap <F2> 
map  :execute "tabmove" tabpagenr() - 2 
map <NL> :execute "tabmove" tabpagenr() + 1 
nnoremap  :noh
map  <Plug>(ctrlp)
map  :Explore
nmap [18;6~ :autocmd! VimLeave:qa
nmap [18;5~ :autocmd! VimLeave:q
nmap [15;5~ :NERDTreeToggle
nmap [6;5~ :bN
nmap [5;5~ :bp
map [1;5C <C-Right>
map [1;5D <C-Left>
nmap  T
nmap [18;2~ <S-F7>
map @ \be
nnoremap \d :YcmShowDetailedDiagnostic
nnoremap \uu :execute 'CtrlPFunky ' . expand('<cword>')
nnoremap \fu :CtrlPFunky
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
nnoremap <SNR>94_: :=v:count ? v:count : ''
nnoremap <silent> <Plug>(YCMFindSymbolInDocument) :call youcompleteme#finder#FindSymbol( 'document' )
nnoremap <silent> <Plug>(YCMFindSymbolInWorkspace) :call youcompleteme#finder#FindSymbol( 'workspace' )
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
nmap <silent> <Plug>CommentaryUndo :echoerr "Change your <Plug>CommentaryUndo map to <Plug>Commentary<Plug>Commentary"
vnoremap <expr> <F22> terminus#private#paste('c')
nnoremap <expr> <F22> terminus#private#paste('i')
vnoremap <silent> <F21> :silent doautocmd <nomodeline> FocusGained %gv
vnoremap <silent> <F20> :silent doautocmd <nomodeline> FocusLost %gv
onoremap <silent> <F21> :silent doautocmd <nomodeline> FocusGained %
onoremap <silent> <F20> :silent doautocmd <nomodeline> FocusLost %
nnoremap <silent> <F21> :silent doautocmd <nomodeline> FocusGained %
nnoremap <silent> <F20> :silent doautocmd <nomodeline> FocusLost %
tmap <expr> <F21> terminus#private#term_focus_gained()
tmap <expr> <F20> terminus#private#term_focus_lost()
nnoremap <Plug>CtrlSFQuickfixPrompt :CtrlSFQuickfix 
nnoremap <Plug>CtrlSFPrompt :CtrlSF 
map <C-P> <Plug>(ctrlp)
nnoremap <silent> <Plug>(ctrlp) :CtrlP
map <F6> :w:make %<
nmap <F3> <Plug>CtrlSFCwordExec
nnoremap <C-Right> :tabnext
nnoremap <C-Left> :tabprevious
noremap <ScrollWheelUp> 6
nmap <C-[><C-]> T
map <F11> :rew!:$
map <F8> :call FlipPaste()
map <C-J> :execute "tabmove" tabpagenr() + 1 
map <C-H> :execute "tabmove" tabpagenr() - 2 
map <F10> :call FlipMouse()
map <F9> :call FlipCaseWrap()
map <S-F7> :q
map <F7> :qa
map <F5> :wall
map <F4> :w
inoremap <expr> 	 pumvisible() ? "\" : "\	"
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autoread
set background=dark
set backspace=2
set cindent
set cinoptions=:0g0
set completeopt=preview,menuone
set cpoptions=aAceFsB
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set hidden
set hlsearch
set keywordprg=:SuperMan
set laststatus=2
set matchpairs=(:),{:},[:],<:>
set mouse=nv
set pastetoggle=<F23>
set printoptions=paper:letter
set ruler
set rulerformat=%60(%2*%<%f%=\ %1*%M%*%r\ %l/%L\ %c\ %p%%%)\ %o\ 0x%02B/%-3b
set runtimepath=~/.vim/bundle/ctrlp.vim,~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/YouCompleteMe,~/.vim/bundle/bufexplorer,~/.vim/bundle/ctrlp-funky,~/.vim/bundle/ctrlsf.vim,~/.vim/bundle/nerdtree,~/.vim/bundle/terminus,~/.vim/bundle/vim-airline,~/.vim/bundle/vim-airline-themes,~/.vim/bundle/vim-commentary,~/.vim/bundle/vim-fugitive,~/.vim/bundle/vim-nerdtree-syntax-highlight,~/.vim/bundle/vim-obsession,~/.vim/bundle/vim-van,/var/lib/vim/addons,/etc/vim,/usr/share/vim/vimfiles,/usr/share/vim/vim82,/usr/share/vim/vimfiles/after,/etc/vim/after,/var/lib/vim/addons/after,~/.vim/bundle/vim-nerdtree-syntax-highlight/after,~/.vim/bundle/ctrlsf.vim/after,~/.vim/after
set selectmode=key
set shiftwidth=3
set shortmess=filnxtToOSc
set showtabline=2
set splitbelow
set splitright
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabline=%!MyTabLine()
set tabstop=3
set title
set titlelen=70
set titlestring=tamil:/home/davidd/prog/args/src/[BufExplorer]
set ttimeoutlen=10
set viminfo='50,/100
set wildmenu
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/prog/args/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
$argadd ./tags.cpp
$argadd ./argproc.cpp
$argadd ./argument.h
$argadd ./integer.cpp
$argadd ./double.cpp
$argadd ./argument.cpp
$argadd ./function.cpp
$argadd ./arglist.cpp
$argadd ./boolean.cpp
$argadd ./config.h
$argadd ./character.cpp
$argadd ./string.cpp
$argadd ./arglist.h
set splitbelow splitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
enew
file \[BufExplorer]
balt ./tags.cpp
nnoremap <buffer> <silent> G :keepjumps normal! G
nnoremap <buffer> <silent> H :keepjumps normal! H
nnoremap <buffer> <silent> L :keepjumps normal! L
nnoremap <buffer> <silent> M :keepjumps normal! M
nnoremap <buffer> <silent> N :keepjumps normal! N
nnoremap <buffer> <silent> n :keepjumps normal! n
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal nobuflisted
setlocal buftype=nofile
setlocal cindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=:0g0
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal cursorline
setlocal cursorlineopt=both
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'bufexplorer'
setlocal filetype=bufexplorer
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal nofoldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=tcq
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:],<:>
setlocal modeline
setlocal nomodifiable
setlocal nrformats=bin,octal,hex
setlocal nonumber
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal scrolloff=-1
setlocal shiftwidth=3
setlocal noshortname
setlocal showbreak=
setlocal sidescrolloff=-1
setlocal signcolumn=auto
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statusline=%!airline#statusline(1)
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'bufexplorer'
setlocal syntax=bufexplorer
endif
setlocal tabstop=3
setlocal tagcase=
setlocal tagfunc=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal noundofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal wincolor=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
tabnext 1
badd +1 ./tags.cpp
badd +0 ./argproc.cpp
badd +0 ./argument.h
badd +0 ./integer.cpp
badd +0 ./double.cpp
badd +0 ./argument.cpp
badd +0 ./function.cpp
badd +0 ./arglist.cpp
badd +0 ./boolean.cpp
badd +0 ./config.h
badd +0 ./character.cpp
badd +0 ./string.cpp
badd +0 ./arglist.h
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOSc
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
