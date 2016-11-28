let g:python_host_prog='/usr/bin/python3'

set nocompatible
filetype off

function! BuildYCM(info)
  " info is a dictionary with 3 fields
  " - name:   name of the plugin
  " - status: 'installed', 'updated', or 'unchanged'
  " - force:  set on PlugInstall! or PlugUpdate!
  if a:info.status == 'installed' || a:info.force
    !./install.py
  endif
endfunction

call plug#begin("~/.nvim/bundle")
" Plugin List
Plug 'scrooloose/nerdtree'
Plug 'kien/ctrlp.vim'
Plug 'majutsushi/tagbar'
Plug 'mbbill/undotree'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'altercation/vim-colors-solarized'
Plug 'tpope/vim-surround'
Plug 'jiangmiao/auto-pairs'
Plug 'easymotion/vim-easymotion'
Plug 'scrooloose/syntastic'
Plug 'tpope/vim-fugitive'
Plug 'Valloric/YouCompleteMe', { 'do': function('BuildYCM') }
Plug 'fatih/vim-go'
Plug 'chase/vim-ansible-yaml'
call plug#end()

nmap <leader>t :TagbarToggle<CR>

source ~/.config/nvim/general.vim
source ~/.config/nvim/nerdtree.vim
source ~/.config/nvim/ctrlp.vim
source ~/.config/nvim/solarized.vim
source ~/.config/nvim/airline.vim
source ~/.config/nvim/easymotion.vim
source ~/.config/nvim/undotree.vim
source ~/.config/nvim/syntastic.vim
source ~/.config/nvim/ycm.vim
source ~/.config/nvim/go.vim
