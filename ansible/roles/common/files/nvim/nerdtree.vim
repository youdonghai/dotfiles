
map <leader>n :NERDTreeToggle<CR>
map <leader>e :NERDTreeFind<CR>
let NERDTreeShowBookmarks=1
let NERDTreeIgnore=['\.py[cd]$', '\~$', '\.swo$', '\.swp$', '^\.git$', '^\.hg$', '^\.svn$', '\.bzr$']
let NERDTreeQuitOnOpen=1
let NERDTreeShowHidden=1
let g:nerdtree_tabs_open_on_gui_startup=0
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTreeType") && b:NERDTreeType == "primary") | q | endif


