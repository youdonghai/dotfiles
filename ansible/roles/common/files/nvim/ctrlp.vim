
let g:ctrlp_map = '<leader>m'
let g:ctrlp_cmd = 'CtrlP'
"set wildignore+=*/tmp/*,*.so,*.swp,*.zip " MacOSX/Linux"
let g:ctrlp_custom_ignore = {
    \ 'dir': '\v[\/]\.(git|hg|svn|rvm)$',
    \ 'file': '\v\.(exe|so|a|o|pyc|d|dll|zip|tar|tar.gz)$',
    \ }
let g:ctrlp_working_path_mode=0
let g:ctrlp_match_window_bottom=1
let g:ctrlp_max_height=10
let g:ctrlp_mruf_max=500
let g:ctrlp_follow_symlinks=1
let g:ctrlp_max_files=100000
let g:ctrlp_max_depth = 100



