
" General
syntax on                   " Syntax highlighting
set mouse-=a                 " Automatically enable mouse usage
set mousehide               " Hide the mouse cursor while typing
scriptencoding utf-8

if has('clipboard')
    if has('unnamedplus')  " When possible use + register for copy-paste
        set clipboard=unnamed,unnamedplus
    else         " On mac and Windows, use * register for copy-paste
        set clipboard=unnamed
    endif
endif

set encoding=utf-8
set fileencoding=utf-8
set termencoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set ambiwidth=double

set shortmess+=filmnrxoOtT          " Abbrev. of messages (avoids 'hit enter')
set viewoptions=folds,options,cursor,unix,slash " Better Unix / Windows compatibility
set virtualedit=onemore             " Allow for cursor beyond last character
set history=1000                    " Store a ton of history (default is 20)
set hidden                          " Allow buffer switching without saving
set iskeyword-=.                    " '.' is an end of word designator
set iskeyword-=#                    " '#' is an end of word designator
set iskeyword-=-                    " '-' is an end of word designator


" Restore cursor to file position in previous editing session
function! ResCur()
    if line("'\"") <= line("$")
        silent! normal! g`"
        return 1
    endif
endfunction
augroup resCur
    autocmd!
    autocmd BufWinEnter * call ResCur()
augroup END

set nobackup
set nowritebackup
set noswapfile
if has('persistent_undo')
    set undofile                " So is persistent undo ...
    set undolevels=1000         " Maximum number of changes that can be undone
    set undoreload=10000        " Maximum number lines to save for undo on a buffer reload
endif

"Turn backup off
set nowb
set nobackup
set noswapfile
"unsave buffers switch
set hidden
set matchtime=2 " show matching bracket for 0.2 seconds
set colorcolumn=80

"Set 6 lines to the curors - when moving vertical..
set so=7
set sidescroll=6

" auto remove right whitespace
au BufWritePre * :%s/\s\+$//e
set fileformats+=dos

set background=dark
set t_Co=256
if &term == 'xterm' || &term == 'screen'
    set t_Co=256            " Enable 256 colors to stop the CSApprox warning and make xterm vim shine
endif
set tabpagemax=15               " Only show 15 tabs
set showmode                    " Display the current mode

set cursorline                  " Highlight current line
set cursorcolumn
hi CursorLine cterm=NONE ctermbg=darkred ctermfg=white guibg=darkred guifg=white

highlight clear SignColumn      " SignColumn should match background
highlight clear LineNr          " Current line number row will have same background color in relative mode
"highlight clear CursorLineNr    " Remove highlight color from current line number

if has('cmdline_info')
    set ruler                   " Show the ruler
    set rulerformat=%30(%=\:b%n%y%m%r%w\ %l,%c%V\ %P%) " A ruler on steroids
    set showcmd                 " Show partial commands in status line and
endif

if has('statusline')
    set laststatus=2

    " Broken down into easily includeable segments
    set statusline=%<%f\                     " Filename
    set statusline+=%w%h%m%r                 " Options
    if exists("*fugitive#statusline")
        set statusline+=%{fugitive#statusline()} " Git Hotness
    endif
    set statusline+=\ [%{&ff}/%Y]            " Filetype
    set statusline+=\ [%{getcwd()}]          " Current dir
    set statusline+=%=%-14.(%l,%c%V%)\ %p%%  " Right aligned file nav info
endif

set backspace=indent,eol,start  " Backspace for dummies
set linespace=0                 " No extra spaces between rows
set number                      " Line numbers on
set relativenumber
set showmatch                   " Show matching brackets/parenthesis
set incsearch                   " Find as you type search
set hlsearch                    " Highlight search terms
set winminheight=0              " Windows can be 0 line high
set ignorecase                  " Case insensitive search
set smartcase                   " Case sensitive when uc present
set wildmenu                    " Show list instead of just completing
set completeopt=menu,preview,longest "自动补全效果
set wildmode=list:longest,full  " Command <Tab> completion, list matches, then longest common part, then all.
set whichwrap=b,s,h,l,<,>,[,]   " Backspace and cursor keys wrap too
set scrolljump=5                " Lines to scroll when cursor leaves screen
set scrolloff=3                 " Minimum lines to keep above and below cursor
set foldenable                  " Auto fold code

"设置标记一列的背景颜色和数字一行颜色一致
hi! link SignColumn LineNr
hi! link ShowMarksHLl DiffAdd
hi! link ShowMarksHLu DiffChange


set wrap                        " Wrap long lines
set smartindent
set autoindent                  " Indent at the same level of the previous line
set shiftwidth=4                " Use indents of 4 spaces
set expandtab                   " Tabs are spaces, not tabs
set smarttab
set tabstop=4                   " An indentation every four columns
set softtabstop=4               " Let backspace delete indent
set nojoinspaces                " Prevents inserting two spaces after punctuation on a join (J)
set splitright                  " Puts new vsplit windows to the right of the current
set splitbelow                  " Puts new split windows to the bottom of the current
"set matchpairs+=<:>             " Match, to be used with %
set pastetoggle=<F2>           " pastetoggle (sane indentation on pastes)

set cino=:0g0t0(sus "C/C++

let mapleader = ';'
let maplocalleader = ','

" Yank from the cursor to the end of the line, to be consistent with C and D.
nnoremap Y y$

nnoremap <C-j> <C-W>j
nnoremap <C-k> <C-W>k
nnoremap <C-h> <C-W>h
nnoremap <C-l> <C-W>l
nnoremap <C-w>n <C-W>v
nnoremap <C-w>m <C-W>s

function NumberToggle()
    if &number == 1
        let &number = 0
        let &relativenumber = 0
        :silent execute "SyntasticReset"
        :silent execute "SignifyDisable"
    else
        let &number = 1
        let &relativenumber = 1
        :silent execute "SignifyEnable"
    endif
endfunc
noremap <F12> :call NumberToggle()<CR>

"autocmd BufEnter * :inoremap <buffer> <silent> <C-h> <Left>
inoremap <C-h> <Left>
inoremap <C-j> <Down>
inoremap <C-k> <Up>
inoremap <C-l> <Right>

map <leader>k :bn<CR>
map <leader>j :bp<CR>
map <leader>x :bd<CR>
"map <C-w> :bd<CR>

set tags=./tags;/,~/.vimtags

