
let g:go_highlight_functions = 1
let g:go_highlight_methods = 1
let g:go_highlight_fields = 1
let g:go_highlight_types = 1
let g:go_highlight_operators = 1
let g:go_highlight_build_constraints = 1
let g:go_play_open_browser = 0
let g:go_bin_path = expand("~/.gotools")
"
autocmd BufRead,BufNewFile *.go set filetype=go
au FileType go nmap <Leader>g <Plug>(go-def)
au FileType go nmap <Leader>oi <Plug>(go-implements)
au FileType go nmap <Leader>oe :GoReferrers<CR>
au FileType go nmap <Leader>or <Plug>(go-rename)

let g:syntastic_go_checkers = ['golint', 'govet', 'errcheck']
let g:syntastic_mode_map = { 'mode': 'active', 'passive_filetypes': ['go']  }

