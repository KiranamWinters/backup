-- Keymaps are automatically loaded on the VeryLazy event
-- Default keymaps that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/keymaps.lua
-- Add any additional keymaps here

--terminal setting
vim.keymap.set("t", "<Esc>", [[<C-\><C-n>]], { desc = "Exit terminal mode" })

vim.keymap.set("t", "<C->Left", [[<C-\><C-n><C-w>h]], { desc = "Move to left window" })
vim.keymap.set("t", "<C-Down>", [[<C-\><C-n><C-w>j]], { desc = "Move to bottom window" })
vim.keymap.set("t", "<C-Up>", [[<C-\><C-n><C-w>k]], { desc = "Move to top window" })
vim.keymap.set("t", "<C-Right>", [[<C-\><C-n><C-w>l]], { desc = "Move to right window" })

vim.api.nvim_create_autocmd("TermOpen", {
    pattern = "*",
    command = "startinsert",
})

local term_buf = nil
local term_win = nil

local function toggle_terminal()
    -- If the window is open and valid, hide (close) it
    if term_win and vim.api.nvim_win_is_valid(term_win) then
        vim.api.nvim_win_close(term_win, true)
        term_win = nil
        return
    end

    -- 1. Create a native vertical split on the far right using the API
    term_win = vim.api.nvim_open_win(0, false, {
        split = "right",
        win = -1, -- Pushes it to the far right edge globally
    })

    -- Set target column width (e.g., 55 columns wide)
    vim.api.nvim_win_set_width(term_win, 55)

    -- 2. Handle the buffer setup safely
    if term_buf == nil or not vim.api.nvim_buf_is_valid(term_buf) then
        -- Create an unlisted scratch buffer
        term_buf = vim.api.nvim_create_buf(false, true)
        vim.api.nvim_win_set_buf(term_win, term_buf)

        -- Focus the window momentarily to run the safe built-in :terminal command
        -- This works flawlessly in ext_cmdline GUIs when run isolated inside the win context
        vim.api.nvim_set_current_win(term_win)
        vim.cmd("terminal")

        -- Apply clean, borderless layout styles using type-safe methods
        vim.api.nvim_set_option_value("number", false, { win = term_win })
        vim.api.nvim_set_option_value("relativenumber", false, { win = term_win })
        vim.api.nvim_set_option_value("signcolumn", "no", { win = term_win })
    else
        -- If the shell buffer already exists, simply attach it to our new window
        vim.api.nvim_win_set_buf(term_win, term_buf)
        vim.api.nvim_set_current_win(term_win)
    end

    -- 3. Ensure we are in terminal mode typing immediately
    vim.cmd("startinsert")
end

-- Map to <C-`> for Normal, Insert, and Terminal modes
vim.keymap.set({ "n", "i", "t" }, "<C-`>", toggle_terminal, { desc = "Toggle GUI-Safe Vertical Terminal" })

--Moving around
vim.keymap.set("n", "<C-Left>", "<C-w>h", { desc = "Go to Left Window", remap = true })
vim.keymap.set("n", "<C-Down>", "<C-w>j", { desc = "Go to Lower Window", remap = true })
vim.keymap.set("n", "<C-Up>", "<C-w>k", { desc = "Go to Upper Window", remap = true })
vim.keymap.set("n", "<C-Right>", "<C-w>l", { desc = "Go to Right Window", remap = true })

-- Resize window using <ctrl> arrow keys
vim.keymap.set("n", "<C-k>", "<cmd>resize +2<cr>", { desc = "Increase Window Height" })
vim.keymap.set("n", "<C-j>", "<cmd>resize -2<cr>", { desc = "Decrease Window Height" })
vim.keymap.set("n", "<C-h>", "<cmd>vertical resize -2<cr>", { desc = "Decrease Window Width" })
vim.keymap.set("n", "<C-l>", "<cmd>vertical resize +2<cr>", { desc = "Increase Window Width" })
