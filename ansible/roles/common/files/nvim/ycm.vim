
let g:ycm_confirm_extra_conf=0
let g:syntastic_always_populate_loc_list=1
let g:ycm_min_num_of_chars_for_completion=2
let g:ycm_autoclose_preview_window_after_insertion=1
"let g:ycm_collect_identifiers_from_tags_files=1
"let g:ycm_path_to_python_interpreter = '/usr/bin/python3'
let g:ycm_collect_identifiers_from_tags_files=0
let g:ycm_complete_in_comments=1
let g:ycm_complete_in_strings=1
let g:ycm_collect_identifiers_from_comments_and_strings=1
let g:ycm_add_preview_to_completeopt = 1
nnoremap <leader>d :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>g :YcmCompleter GoTo<CR>
nnoremap <leader>e :YcmCompleter GoToReferences<CR>
let g:ycm_key_list_select_completion = ['<TAB>', '<Down>']

let g:ycm_filetype_whitelist = {
    \ 'c': 1 ,
    \ 'cpp': 1,
    \ 'python': 1
    \}

" for debug
" let g:ycm_server_use_vim_stdout = 1
" let g:ycm_server_log_level = 'debug'

